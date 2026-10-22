# Runtime / Landscape

- module root: `Source/Runtime/Landscape`
- headers: 77; symbols: 4793
- symbol kinds: class=120, delegate=19, enum=64, enumerator=315, externvar=7, function=613, macro=12, member=1436, namespace=104, prototype=1948, struct=130, typedef=19, union=1, variable=5
- DynamicallyLoadedModuleNames: NaniteBuilder
- PrivateDependencyModuleNames: ActionableMessage, ApplicationCore, Core, CoreUObject, DeveloperSettings, EditorFramework, Engine, Foliage, GeometryCore, ImageCore, MaterialUtilities, MathCore, MeshBuilder, MeshBuilderCommon, MeshDescription, MeshUtilities, MeshUtilitiesCommon, RHI, RenderCore, Renderer, Slate, SlateCore, StaticMeshDescription, TraceLog, UnrealEd
- PrivateIncludePathModuleNames: DerivedDataCache, LandscapeEditor, NaniteBuilder, Shaders, TargetPlatform

### `Source/Runtime/Landscape/Classes/ControlPointMeshActor.h` (Public)


#### class `AControlPointMeshActor`  
`class AControlPointMeshActor : public AActor`  
_L16-44_
- reflection: `UCLASS(NotPlaceable, hideCategories = (Input), showCategories = ("Input|MouseInput", "Input|TouchInput"), ConversionRoot, ComponentWrapperClass, meta = (ChildCanTick), MinimalAPI)`
- inherits: `AActor`
- desc: ControlPointMeshActor is an actor with a ControlPointMeshComponent. @see UControlPointMeshComponent
- L22 _private member_ `TObjectPtr<class UControlPointMeshComponent> ControlPointMeshComponent;` — `UPROPERTY(Category = ControlPointMeshActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh,Components|ControlPointMesh", AllowPrivateAccess = "true"))`
- L27 _public prototype_ `void SetMobility(EComponentMobility::Type InMobility);` — Function to change mobility type
- L31 _public prototype_ `virtual void CheckForErrors() override;`
- L32 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L38 _protected prototype_ `virtual FString GetDetailedInfoInternal() const override;`
- L43 _public prototype_ `class UControlPointMeshComponent* GetControlPointMeshComponent() const;` — Returns ControlPointMeshComponent subobject

### `Source/Runtime/Landscape/Classes/ControlPointMeshComponent.h` (Public)


#### class `UControlPointMeshComponent`  
`class UControlPointMeshComponent : public UStaticMeshComponent`  
_L11-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UStaticMeshComponent`
- L17 _private member_ `uint32 bSelected:1;` — `UPROPERTY(transient)`
- L20 _private member_ `TObjectPtr<UHLODLayer> HLODLayerOverrideForSplinePartitioning;` — `UPROPERTY(EditAnywhere, Category = HLOD, AdvancedDisplay)`
- L28 _private member_ `float VirtualTextureMainPassMaxDrawDistance = 0.f;` — `UPROPERTY()` — The max draw distance to use in the main pass when also rendering to a runtime virtual texture. This is only exposed to the user through the same setting on ULandscapeSplineControlPoint.
- L32 _private function_ `virtual bool ShouldRenderSelected() const override`
- L36 _private prototype_ `virtual bool IsEditorOnly() const override;`
- L38 _private function_ `virtual float GetVirtualTextureMainPassMaxDrawDistance() const override`
- L42 _private prototype_ `bool IsRelevantForSplinePartitioning() const;`
- L43 _private prototype_ `UHLODLayer* GetHLODLayerForSplinePartitioning() const;`

### `Source/Runtime/Landscape/Classes/ILandscapeSplineInterface.h` (Public)


#### class `ULandscapeSplineInterface`  
`class ULandscapeSplineInterface : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ILandscapeSplineInterface`  
`class ILandscapeSplineInterface`  
_L19-35_
- L23 _public prototype_ `virtual FGuid GetLandscapeGuid() const PURE_VIRTUAL(ILandscapeSplineInterface::GetLandscapeGuid, return FGuid(););`
- L24 _public prototype_ `virtual ULandscapeInfo* GetLandscapeInfo() const PURE_VIRTUAL(ILandscapeSplineInterface::GetLandscapeInfo, return nullptr;);`
- L25 _public prototype_ `virtual FTransform LandscapeActorToWorld() const PURE_VIRTUAL(ILandscapeSplineInterface::LandscapeActorToWorld, return FTransform::Identity;);`
- L26 _public prototype_ `virtual ULandscapeSplinesComponent* GetSplinesComponent() const PURE_VIRTUAL(ILandscapeSplineInterface::GetSplineComponent, return nullptr;);`
- L27 _public prototype_ `virtual void UpdateSharedProperties(ULandscapeInfo* InLandscapeInfo) PURE_VIRTUAL(ILandscapeSplineInterface::UpdateSharedProperties);`
- L28 _public prototype_ `virtual bool IsSplineOwnerValid() const PURE_VIRTUAL(ILandscapeSplineInterface::IsSplineOwnerValid, return true;);`
- L31 _public prototype_ `virtual bool SupportsForeignSplineMesh() const PURE_VIRTUAL(ILandscapeSplineInterface::SupportsForeignSplineMesh, return false;);`
- L32 _public prototype_ `virtual void CreateSplineComponent() PURE_VIRTUAL(ILandscapeSplineInterface::CreateSplineComponent);`
- L33 _public prototype_ `virtual void CreateSplineComponent(const FVector& Scale3D) PURE_VIRTUAL(ILandscapeSplineInterface::CreateSplineComponent);`

### `Source/Runtime/Landscape/Classes/Landscape.h` (Public)


#### enum `ERTDrawingType`  
`enum class ERTDrawingType : uint8`  
_L64-71_
- reflection: `UENUM()`
- L66 _public enumerator_ `RTAtlas`
- L67 _public enumerator_ `RTAtlasToNonAtlas`
- L68 _public enumerator_ `RTNonAtlasToAtlas`
- L69 _public enumerator_ `RTNonAtlas`
- L70 _public enumerator_ `RTMips`

#### enum `EHeightmapRTType`  
`enum class EHeightmapRTType : uint8`  
_L74-90_
- reflection: `UENUM()`
- L76 _public enumerator_ `HeightmapRT_CombinedAtlas`
- L77 _public enumerator_ `HeightmapRT_CombinedNonAtlas`
- L78 _public enumerator_ `HeightmapRT_Scratch1`
- L79 _public enumerator_ `HeightmapRT_Scratch2`
- L80 _public enumerator_ `HeightmapRT_Scratch3`
- L82 _public enumerator_ `HeightmapRT_Mip1` — Mips RT
- L83 _public enumerator_ `HeightmapRT_Mip2`
- L84 _public enumerator_ `HeightmapRT_Mip3`
- L85 _public enumerator_ `HeightmapRT_Mip4`
- L86 _public enumerator_ `HeightmapRT_Mip5`
- L87 _public enumerator_ `HeightmapRT_Mip6`
- L88 _public enumerator_ `HeightmapRT_Mip7`
- L89 _public enumerator_ `HeightmapRT_Count`

#### enum `EWeightmapRTType`  
`enum class EWeightmapRTType : uint8`  
_L93-111_
- reflection: `UENUM()`
- L95 _public enumerator_ `WeightmapRT_Scratch_RGBA`
- L96 _public enumerator_ `WeightmapRT_Scratch1`
- L97 _public enumerator_ `WeightmapRT_Scratch2`
- L98 _public enumerator_ `WeightmapRT_Scratch3`
- L101 _public enumerator_ `WeightmapRT_Mip0` — Mips RT
- L102 _public enumerator_ `WeightmapRT_Mip1`
- L103 _public enumerator_ `WeightmapRT_Mip2`
- L104 _public enumerator_ `WeightmapRT_Mip3`
- L105 _public enumerator_ `WeightmapRT_Mip4`
- L106 _public enumerator_ `WeightmapRT_Mip5`
- L107 _public enumerator_ `WeightmapRT_Mip6`
- L108 _public enumerator_ `WeightmapRT_Mip7`
- L110 _public enumerator_ `WeightmapRT_Count`

#### struct `FLandscapeLayerBrush`  
`struct FLandscapeLayerBrush #if CPP && WITH_EDITOR`  
_L118-153_
- reflection: `USTRUCT()`
- inherits: `UE::Landscape::EditLayers::IEditLayerRendererProvider`
- L125 _public prototype_ `FLandscapeLayerBrush() = default;`
- L127 _public function_ `FLandscapeLayerBrush(ALandscapeBlueprintBrushBase* InBlueprintBrush) #if WITH_EDITORONLY_DATA : BlueprintBrush(InBlueprintBrush) #endif`
- L133 _public prototype_ `virtual ~FLandscapeLayerBrush() = default;`
- L136 _public prototype_ `ALandscapeBlueprintBrushBase* GetBrush() const;`
- L137 _public prototype_ `bool AffectsHeightmap() const;`
- L138 _public prototype_ `bool AffectsWeightmapLayer(const FName& InWeightmapLayerName) const;`
- L139 _public prototype_ `bool AffectsVisibilityLayer() const;`
- L140 _public prototype_ `void SetOwner(ALandscape* InOwner);`
- L143 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRendererState> GetEditLayerRendererStates(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) override;`
- L151 _private member_ `TObjectPtr<ALandscapeBlueprintBrushBase> BlueprintBrush;` — `UPROPERTY()`

#### enum `ELandscapeBlendMode`  
`enum ELandscapeBlendMode : int`  
_L157-162_
- reflection: `UENUM()`
- desc: TODO [jonathan.bard] : deprecate this
- L159 _public enumerator_ `LSBM_AdditiveBlend`
- L160 _public enumerator_ `LSBM_AlphaBlend`
- L161 _public enumerator_ `LSBM_MAX`

#### struct `FLandscapeLayer`  
`struct FLandscapeLayer #if CPP && WITH_EDITOR`  
_L165-212_
- reflection: `USTRUCT()`
- inherits: `UE::Landscape::EditLayers::IEditLayerRendererProvider`
- L172 _public function_ `FLandscapeLayer()`
- L175 _public prototype_ `virtual ~FLandscapeLayer() = default;`
- L179 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRendererState> GetEditLayerRendererStates(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) override;`
- L184 _public member_ `FGuid Guid_DEPRECATED = FGuid::NewGuid();` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))`
- L187 _public member_ `FName Name_DEPRECATED = NAME_None;` — `UPROPERTY()`
- L190 _public member_ `bool bVisible_DEPRECATED = true;` — `UPROPERTY(Transient)`
- L193 _public member_ `bool bLocked_DEPRECATED = false;` — `UPROPERTY()`
- L196 _public member_ `float HeightmapAlpha_DEPRECATED = 1.0f;` — `UPROPERTY()`
- L199 _public member_ `float WeightmapAlpha_DEPRECATED = 1.0f;` — `UPROPERTY()`
- L205 _public member_ `TArray<FLandscapeLayerBrush> Brushes;` — `UPROPERTY()`
- L208 _public member_ `TMap<TObjectPtr<ULandscapeLayerInfoObject>, bool> WeightmapLayerAllocationBlend_DEPRECATED;` — `UPROPERTY()` — True -> Substractive, False -> Additive
- L211 _public member_ `TObjectPtr<ULandscapeEditLayerBase> EditLayer;` — `UPROPERTY(Instanced)`

#### enum `ELandscapeEditLayersMergeMode`  
`enum class UE_DEPRECATED(5.7, "Edit layers are now fully processed via BatchedMerge") ELandscapeEditLayersMergeMode : uint8`  
_L215-221_
- L217 _public enumerator_ `GlobalMerge = 0`
- L218 _public enumerator_ `LocalMerge`
- L219 _public enumerator_ `BatchedMerge`
- L220 _public enumerator_ `Invalid`

#### struct `FOnLandscapeEditLayersMergedParams`  
`struct FOnLandscapeEditLayersMergedParams`  
_L225-244_
- desc: TODO [jonathan.bard] : When global merge is a thing of the past, we should pass FOnRenderBatchTargetGroupDoneParams here, or extract some of its higher-level information, because there is a lot more useful information accessible in there (components being rendered, target layers, validity render targets, etc.)
- L227 _public function_ `FOnLandscapeEditLayersMergedParams(UTextureRenderTarget* InRenderTarget, const FIntPoint& InRenderAreaResolution, bool bInIsHeightmapMerge) : RenderTarget(InRenderTarget) , RenderAreaResolution(InRenderAreaResolution) , bIsHeightmapMerge(bInIsHeightmapMerge)`
- L237 _public member_ `UTextureRenderTarget* RenderTarget = nullptr;` — Render target of the section of landscape that was rendered (important note: the render target's resolution can be larger than the actual landscape resolution, so RenderAreaResolution must be used. In the case of weightmaps, the render target will actually be a UTextureRenderTarget2DArray
- L241 _public member_ `FIntPoint RenderAreaResolution = FIntPoint(ForceInit);` — Actual resolution of this render : render targets are usually sized larger than the effective resolution at this point, so this needs to be used instead. Note : it's the true resolution of the landscape : at this point, there are no duplicate vertices in the render target.
- L243 _public member_ `bool bIsHeightmapMerge = false;`

#### struct `FLandscapeEditLayerRenderCommonParams`  
`struct FLandscapeEditLayerRenderCommonParams`  
_L246-255_
- L249 _public member_ `FIntRect Bounds;` — Region to render, in Landscape coordinates
- L252 _public member_ `TBitArray<> ActiveEditLayers;` — Which edit layers to include.  Order matches ALandscape::GetEditLayers().
- L254 _public member_ `bool bRenderBrushes = true;`

#### struct `FLandscapeEditLayerRenderHeightParams`  
`struct FLandscapeEditLayerRenderHeightParams : public FLandscapeEditLayerRenderCommonParams`  
_L258-263_
- inherits: `FLandscapeEditLayerRenderCommonParams`
- desc: Parameters to describe a subset of a landscape heightmap to render.  Can select a subset of edit layers and a subregion of the landscape coordinates.
- L261 _public member_ `TArrayView<uint16> CpuResult;` — Provide either a cpu buffer or render target to receive the data.  Buffer should be allocated large enough to receive the samples in Bounds.
- L262 _public member_ `UTextureRenderTarget2D* RTResult = nullptr;`

#### struct `FLandscapeEditLayerRenderWeightParams`  
`struct FLandscapeEditLayerRenderWeightParams : public FLandscapeEditLayerRenderCommonParams`  
_L266-273_
- inherits: `FLandscapeEditLayerRenderCommonParams`
- desc: Parameters to describe a subset of a landscape weightmaps to render.  Can select a subset of edit layers and a subregion of the landscape coordinates, for a list of weightmaps.
- L268 _public member_ `TArrayView<FName> WeightmapNames;`
- L271 _public member_ `TArrayView<uint8> CpuResult;` — Provide either a cpu buffer or render target to receive the data.  Buffer should be allocated large enough to receive the samples in Bounds.
- L272 _public member_ `UTextureRenderTarget2D* RTResult = nullptr;`

#### class `ALandscape`  
`class ALandscape : public ALandscapeProxy #if CPP && WITH_EDITOR`  
_L276-790_
- reflection: `UCLASS(MinimalAPI, showcategories=(Display, Movement, Collision, Lighting, LOD, Input), hidecategories=(Mobility))`
- inherits: `ALandscapeProxy,UE::Landscape::EditLayers::IEditLayerRendererProvider`
- L286 _public prototype_ `ALandscape(const FObjectInitializer& ObjectInitializer);`
- L289 _public prototype_ `virtual ALandscape* GetLandscapeActor() override;`
- L290 _public prototype_ `virtual const ALandscape* GetLandscapeActor() const override;`
- L294 _public member_ `static FName AffectsLandscapeActorDescProperty;`
- L296 _public prototype_ `bool HasAllComponent();` — determine all component is in this actor
- L300 _public prototype_ `static void CalcComponentIndicesOverlap(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, const int32 ComponentSizeQuads, int32& ComponentIndexX1, int32& ComponentIndexY1, int32& ComponentIndexX2, int32& ComponentIndexY2);` — Include Components with overlapped vertices X2/Y2 Coordinates are "inclusive" max values
- L305 _public prototype_ `static void CalcComponentIndicesNoOverlap(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, const int32 ComponentSizeQuads, int32& ComponentIndexX1, int32& ComponentIndexY1, int32& ComponentIndexX2, int32& ComponentIndexY2);` — Exclude Components with overlapped vertices X2/Y2 Coordinates are "inclusive" max values
- L308 _public prototype_ `static void SplitHeightmap(ULandscapeComponent* Comp, ALandscapeProxy* TargetProxy = nullptr, class FMaterialUpdateContext* InOutUpdateContext = nullptr, TArray<class FComponentRecreateRenderStateContext>* InOutRecreateRenderStateContext = nullptr, bool InReregisterComponent = true);`
- L311 _public function_ `virtual bool IsPartitionActorNameAffectedByDataLayers() const`
- L315 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L316 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L317 _public prototype_ `virtual void PostEditUndo() override;`
- L318 _public prototype_ `virtual void UnregisterAllComponents(bool bForReregister = false) override;`
- L319 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L320 _public prototype_ `virtual void PostActorCreated() override;`
- L321 _public prototype_ `virtual bool ShouldImport(FStringView ActorPropString, bool IsMovingLevel) override;`
- L322 _public prototype_ `virtual void PostEditImport() override;`
- L323 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L324 _public prototype_ `virtual bool CanDeleteSelectedActor(FText& OutReason) const override;`
- L325 _public function_ `virtual bool CanChangeIsSpatiallyLoadedFlag() const override`
- L328 _public prototype_ `virtual void PostLoad() override;`
- L332 _public prototype_ `FBox GetLoadedBounds() const;` — Computes & returns bounds containing all currently loaded landscape proxies (if any) or this landscape's bounds otherwise
- L334 _public prototype_ `bool IsUpToDate() const;`
- L335 _public prototype_ `void TickLayers(float DeltaTime);`
- L337 _public prototype_ `void SetLODGroupKey(uint32 InLODGroupKey);`
- L338 _public prototype_ `uint32 GetLODGroupKey();`
- L341 _public function_ `bool GetGrassEnabled() const` — `UFUNCTION(BlueprintCallable, Category = "Landscape")`
- L344 _public prototype_ `void SetGrassEnabled(bool bEnabled, bool bFlushGrassMaps = true);` — `UFUNCTION(BlueprintCallable, Category = "Landscape")`
- L355 _public prototype_ `bool RenderHeightmap(FTransform InWorldTransform, FBox2D InExtents, UTextureRenderTarget2D* OutRenderTarget);` — `UFUNCTION(BlueprintCallable, Category = "Landscape|Runtime")` — Render the final heightmap in the requested top-down window as one -atlased- texture in the provided render target 2D Can be called at runtime. @param InWorldTransform World transform of the area where the texture should be rendered @param InExtents Extents of the area where the texture should be rendered (local to InWorldTransform). If size is zero, then the entire loaded landscape will be exported. @param OutRenderTarget Render target in which the texture will be rendered. The size/format of the render target will be respected. @return false in case of failure (e.g. invalid inputs, incompatible render target format...)
- L367 _public prototype_ `bool RenderWeightmap(FTransform InWorldTransform, FBox2D InExtents, FName InWeightmapLayerName, UTextureRenderTarget2D* OutRenderTarget);` — `UFUNCTION(BlueprintCallable, Category = "Landscape|Runtime")` — Render the final weightmap for the requested layer, in the requested top-down window, as one -atlased- texture in the provided render target 2D Can be called at runtime. @param InWorldTransform World transform of the area where the texture should be rendered @param InExtents Extents of the area where the texture should be rendered (local to InWorldTransform). If size is zero, then the entire loaded landscape will be exported. @param InWeightmapLayerName Weightmap layer that is being requested to render @param OutRenderTarget Render target in which the texture will be rendered. The size/format of the render target will be respected. @return false in case of failure (e.g. invalid inputs, incompatible render target format...)
- L381 _public prototype_ `bool RenderWeightmaps(FTransform InWorldTransform, FBox2D InExtents, const TArray<FName>& InWeightmapLayerNames, UTextureRenderTarget* OutRenderTarget);` — `UFUNCTION(BlueprintCallable, Category = "Landscape|Runtime")` — Render the final weightmaps for the requested layers, in the requested top-down window, as one -atlased- texture in the provided render target (2D or 2DArray) Can be called at runtime. @param InWorldTransform World transform of the area where the texture should be rendered @param InExtents Extents of the area where the texture should be rendered (local to InWorldTransform). If size is zero, then the entire loaded landscape will be exported. @param InWeightmapLayerNames List of weightmap layers that are being requested to render @param OutRenderTarget Render target in which the texture will be rendered. The size/format of the render target will be respected. - If a UTextureRenderTarget2D is passed, the requested layers will be packed in the RGBA channels in order (up to the number of channels available with the render target's format). - If a UTextureRenderTarget2DArray is passed, the requested layers will be packed in the RGBA channels of each slice (up to the number of channels * slices available with the render target's format and number of slices). @return false in case of failure (e.g. invalid inputs, incompatible render target format...)
- L389 _public prototype_ `TArray<FName> GetTargetLayerNames(bool bInIncludeVisibilityLayer = false) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "Landscape|Editor", meta=(DevelopmentOnly))` — Retrieves the names of valid paint layers on this landscape (editor-only : returns nothing at runtime) @Param bInIncludeVisibilityLayer whether the visibility layer's name should be included in the list or not @return the list of paint layer names
- L395 _public prototype_ `const TArray<ULandscapeEditLayerBase*> GetEditLayersBP() const;` — `UFUNCTION(BlueprintCallable, DisplayName = GetEditLayers, Category = "Landscape|Editor", meta = (DevelopmentOnly))` — @return the list of edit layers on this landscape (editor-only : returns nothing at runtime)
- L401 _public prototype_ `const ULandscapeEditLayerBase* GetEditLayerByNameBP(const FName& InLayerName) const;` — `UFUNCTION(BlueprintCallable, DisplayName = GetEditLayer, Category = "Landscape|Editor", meta = (DevelopmentOnly))` — @return the edit layer whose name matches the parameter on this landscape (editor-only : returns nothing at runtime)
- L403 _public prototype_ `bool IsValidRenderTargetFormatHeightmap(EPixelFormat InRenderTargetFormat, bool& bOutCompressHeight);`
- L404 _public prototype_ `bool IsValidRenderTargetFormatWeightmap(EPixelFormat InRenderTargetFormat, int32& OutNumChannels);`
- L409 _public prototype_ `FBox GetCompleteBounds() const;` — Computes & returns bounds containing all landscape proxies (if any) or this landscape's bounds otherwise. Note that in non-WP worlds this will call GetLoadedBounds().
- L410 _public function_ `void RegisterLandscapeEdMode(ILandscapeEdModeInterface* InLandscapeEdMode)`
- L411 _public function_ `void UnregisterLandscapeEdMode()`
- L412 _public function_ `bool HasLandscapeEdMode() const`
- L414 _public prototype_ `virtual bool HasLayersContent() const override;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")`
- L416 _public prototype_ `virtual void UpdateCachedHasLayersContent(bool bInCheckComponentDataIntegrity) override;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")`
- L417 _public prototype_ `void RequestSplineLayerUpdate();`
- L418 _public prototype_ `void RequestLayersInitialization(bool bInRequestContentUpdate = true, bool bInForceLayerResourceReset = true);`
- L419 _public prototype_ `void RequestLayersContentUpdateForceAll(ELandscapeLayerUpdateMode InModeMask = ELandscapeLayerUpdateMode::Update_All, bool bInUserTriggered = false);`
- L420 _public prototype_ `void RequestLayersContentUpdate(ELandscapeLayerUpdateMode InModeMask);`
- L421 _public prototype_ `bool ReorderLayer(int32 InStartingLayerIndex, int32 InDestinationLayerIndex);`
- L422 _public prototype_ `FLandscapeLayer* DuplicateLayerAndMoveBrushes(const FLandscapeLayer& InOtherLayer);`
- L431 _public prototype_ `int32 CreateLayer(FName InName = NAME_None, const TSubclassOf<ULandscapeEditLayerBase>& InEditLayerClass = TSubclassOf<ULandscapeEditLayerBase>(), bool bInIgnoreLayerCountLimit = false);` — Creates a new edit layer @Param InName is the name of the new edit layer @Param InEditLayerClass is the class of the edit layer to create. Passing null will create a standard layer of type ULandscapeEditLayer @Param bInIgnoreLayerCountLimit create the layer even if this would exceed MaxNumberOfLayers @return the index of the newly-created layer
- L432 _public prototype_ `void CreateDefaultLayer();`
- L434 _public prototype_ `void CopyOldDataToDefaultLayer();`
- L435 _public prototype_ `void CopyOldDataToDefaultLayer(ALandscapeProxy* InProxy);`
- L444 _public prototype_ `void CopyDataToEditLayer(ALandscapeProxy* InProxy, const FGuid& InSourceEditLayerGuid = FGuid(), const FGuid& InDestEditLayerGuid = FGuid(), bool bInUseObsoleteLayerData = false);` — Copies edit layer data from each of the InProxy's landscape components to the given edit layer. Overwrites existing data in the destination edit layer @param InProxy is the Proxy to copy Landscape Component data from @param InSourceEditLayerGuid is the source edit layer Guid. When valid, copies data from the given edit layer. If invalid, copies each components final merged data @param InDestEditLayerGuid is the destination edit layer Guid. When valid, must represent a ULandscapeEditLayerPersistent on the ALandscape. If invalid, the default edit layer is used @param bInUseObsoleteLayerData When true, uses obsolete or duplicated final layer data stored during initial registration. Landscape components only duplicate final data when they have >= 1 obsolete layer on load
- L446 _public prototype_ `void AddLayersToProxy(ALandscapeProxy* InProxy);`
- L447 _public prototype_ `FIntPoint ComputeComponentCounts() const;`
- L448 _public prototype_ `bool IsLayerNameUnique(const FName& InName) const;`
- L451 _public prototype_ `TArrayView<const FLandscapeLayer> GetLayersConst() const;` — FLandscapeLayer accessors : only the const version is provided because we don't want to let them be mutated freely without the landscape being aware
- L452 _public prototype_ `const FLandscapeLayer* GetLayerConst(int32 InLayerIndex) const;`
- L453 _public prototype_ `const FLandscapeLayer* GetLayerConst(const FGuid& InLayerGuid) const;`
- L454 _public prototype_ `const FLandscapeLayer* GetLayerConst(const FName& InLayerName) const;`
- L455 _public prototype_ `const FLandscapeLayer* FindLayerOfTypeConst(const TSubclassOf<ULandscapeEditLayerBase>& InLayerClass) const;`
- L456 _public prototype_ `TArray<const FLandscapeLayer*> GetLayersOfTypeConst(const TSubclassOf<ULandscapeEditLayerBase>& InLayerClass) const;`
- L457 _public prototype_ `int32 GetLayerIndex(const FGuid& InLayerGuid) const;`
- L458 _public prototype_ `int32 GetLayerIndex(FName InLayerName) const;`
- L462 _public prototype_ `const TArray<const ULandscapeEditLayerBase*> GetEditLayersConst() const;` — ULandscapeEditLayerBase accessors : both const and non-const versions are provided because the landscape listens to data changes on the edit layer object and can therefore react to any change
- L463 _public prototype_ `const TArray<ULandscapeEditLayerBase*> GetEditLayers() const;`
- L464 _public prototype_ `const ULandscapeEditLayerBase* GetEditLayerConst(int32 InLayerIndex) const;`
- L465 _public prototype_ `ULandscapeEditLayerBase* GetEditLayer(int32 InLayerIndex) const;`
- L466 _public prototype_ `const ULandscapeEditLayerBase* GetEditLayerConst(const FGuid& InLayerGuid) const;`
- L467 _public prototype_ `ULandscapeEditLayerBase* GetEditLayer(const FGuid& InLayerGuid) const;`
- L468 _public prototype_ `const ULandscapeEditLayerBase* GetEditLayerConst(const FName& InLayerName) const;`
- L469 _public prototype_ `ULandscapeEditLayerBase* GetEditLayer(const FName& InLayerName) const;`
- L471 _public prototype_ `const ULandscapeEditLayerBase* FindEditLayerOfTypeConst(const TSubclassOf<ULandscapeEditLayerBase>& InLayerClass) const;`
- L472 _public prototype_ `ULandscapeEditLayerBase* FindEditLayerOfType(const TSubclassOf<ULandscapeEditLayerBase>& InLayerClass) const;`
- L473 _public prototype_ `TArray<const ULandscapeEditLayerBase*> GetEditLayersOfTypeConst(const TSubclassOf<ULandscapeEditLayerBase>& InLayerClass) const;`
- L474 _public prototype_ `TArray<ULandscapeEditLayerBase*> GetEditLayersOfType(const TSubclassOf<ULandscapeEditLayerBase>& InLayerClass) const;`
- L484 _public prototype_ `void ForEachLayerConst(TFunctionRef<bool(const FLandscapeLayer&)> Fn);` — Runs the given function on each edit layer, with the possibility of early exit Most easily used with a lambda as follows: ForEachLayerConst([](const FLandscapeLayer& InLayer) -> bool { return continueLoop ? true : false; });
- L485 _public prototype_ `void ForEachEditLayerConst(TFunctionRef<bool(const ULandscapeEditLayerBase*)> Fn);`
- L487 _public prototype_ `void GetUsedPaintLayers(int32 InLayerIndex, TArray<ULandscapeLayerInfoObject*>& OutUsedLayerInfos) const;`
- L488 _public prototype_ `void GetUsedPaintLayers(const FGuid& InLayerGuid, TArray<ULandscapeLayerInfoObject*>& OutUsedLayerInfos) const;`
- L489 _public prototype_ `void ClearPaintLayer(int32 InLayerIndex, ULandscapeLayerInfoObject* InLayerInfo);`
- L490 _public prototype_ `void ClearPaintLayer(const FGuid& InLayerGuid, ULandscapeLayerInfoObject* InLayerInfo);`
- L494 _public prototype_ `void ClearLayer(int32 InLayerIndex, TSet<TObjectPtr<ULandscapeComponent>>* InComponents = nullptr, ELandscapeClearMode InClearMode = ELandscapeClearMode::Clear_All);` — `UE_DEPRECATED(5.7, "ELandscapeClearMode is deprecated, use ClearEditLayer with ELandscapeToolTargetType instead.")`
- L496 _public prototype_ `void ClearLayer(const FGuid& InLayerGuid, TSet<TObjectPtr<ULandscapeComponent>>* InComponents = nullptr, ELandscapeClearMode InClearMode = ELandscapeClearMode::Clear_All, bool bMarkPackageDirty = true);` — `UE_DEPRECATED(5.7, "ELandscapeClearMode is deprecated, use ClearEditLayer with ELandscapeToolTargetType instead.")`
- L499 _public prototype_ `void ClearEditLayer(int32 InLayerIndex, TSet<TObjectPtr<ULandscapeComponent>>* InComponents = nullptr, ELandscapeToolTargetTypeFlags InClearMode = ELandscapeToolTargetTypeFlags::All);`
- L500 _public prototype_ `void ClearEditLayer(const FGuid& InLayerGuid, TSet<TObjectPtr<ULandscapeComponent>>* InComponents = nullptr, ELandscapeToolTargetTypeFlags InClearMode = ELandscapeToolTargetTypeFlags::All, bool bMarkPackageDirty = true);`
- L502 _public prototype_ `bool DeleteLayer(int32 InLayerIndex);`
- L503 _public prototype_ `void CollapseLayer(int32 InLayerIndex);`
- L505 _public prototype_ `void DeleteLayers();` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated. Use CollapseAllEditLayers to flatten data to the base edit layer.")`
- L506 _public prototype_ `void CollapseAllEditLayers();`
- L507 _public prototype_ `void SetEditingLayer(const FGuid& InLayerGuid = FGuid());`
- L508 _public prototype_ `void SetGrassUpdateEnabled(bool bInGrassUpdateEnabled);`
- L509 _public prototype_ `const FGuid& GetEditingLayer() const;`
- L510 _public prototype_ `bool IsMaxLayersReached() const;`
- L511 _public prototype_ `void ShowOnlySelectedLayer(int32 InLayerIndex);`
- L512 _public prototype_ `void ShowAllLayers();`
- L514 _public prototype_ `void UpdateLandscapeSplines(const FGuid& InLayerGuid = FGuid(), bool bInUpdateOnlySelected = false, bool bInForceUpdateAllCompoments = false);` — `UE_DEPRECATED(5.7, "Use UpdateLandscapeSplines without bInUpdateOnlySelected. Edit layer landscapes update all splines regardless of selection state")`
- L515 _public prototype_ `void UpdateAllLandscapeSplines(const FGuid& InLayerGuid = FGuid(), bool bInForceUpdateAllCompoments = false);`
- L516 _public prototype_ `void SetSelectedEditLayerIndex(const int32 InEditLayerIndex);`
- L517 _public prototype_ `const int32 GetSelectedEditLayerIndex() const;`
- L519 _public prototype_ `void ReplaceLayerSubstractiveBlendStatus(ULandscapeLayerInfoObject* InFromLayerInfo, ULandscapeLayerInfoObject* InToLayerInfo, bool bInShouldDirtyPackage);`
- L521 _public prototype_ `int32 GetBrushLayer(const ALandscapeBlueprintBrushBase* InBrush) const;`
- L522 _public prototype_ `void AddBrushToLayer(int32 InLayerIndex, class ALandscapeBlueprintBrushBase* InBrush);`
- L523 _public prototype_ `void RemoveBrush(class ALandscapeBlueprintBrushBase* InBrush);`
- L524 _public prototype_ `void RemoveBrushFromLayer(int32 InLayerIndex, class ALandscapeBlueprintBrushBase* InBrush);`
- L525 _public prototype_ `void RemoveBrushFromLayer(int32 InLayerIndex, int32 InBrushIndex);`
- L526 _public prototype_ `int32 GetBrushIndexForLayer(int32 InLayerIndex, class ALandscapeBlueprintBrushBase* InBrush);`
- L527 _public prototype_ `bool ReorderLayerBrush(int32 InLayerIndex, int32 InStartingLayerBrushIndex, int32 InDestinationLayerBrushIndex);`
- L528 _public prototype_ `class ALandscapeBlueprintBrushBase* GetBrushForLayer(int32 InLayerIndex, int32 BrushIndex) const;`
- L529 _public prototype_ `TArray<class ALandscapeBlueprintBrushBase*> GetBrushesForLayer(int32 InLayerIndex) const;`
- L530 _public prototype_ `void OnBlueprintBrushChanged();`
- L531 _public prototype_ `void OnLayerInfoSplineFalloffModulationChanged(const ULandscapeLayerInfoObject* InLayerInfo);`
- L532 _public prototype_ `void OnPreSave();`
- L534 _public prototype_ `void ClearDirtyData(ULandscapeComponent* InLandscapeComponent);`
- L536 _public prototype_ `void ConvertNonEditLayerLandscape();`
- L538 _public prototype_ `void ToggleCanHaveLayersContent();` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated. Use ConvertNonEditLayerLandscape to convert to non-edit layer landscapes to edit layer based landscapes.")`
- L539 _public prototype_ `void ForceUpdateLayersContent();`
- L541 _public prototype_ `void ForceUpdateLayersContent(bool bIntermediateRender);` — `UE_DEPRECATED(5.7, "Intermediate renders are a thing of the past. You should now use SelectiveRenderEditLayersHeightmaps/SelectiveRenderEditLayersWeightmaps to render the landscape edit layers in an \"intermediate\" state")`
- L543 _public prototype_ `bool SelectiveRenderEditLayersHeightmaps(const FLandscapeEditLayerRenderHeightParams& InSelectiveRenderParams);`
- L544 _public prototype_ `bool SelectiveRenderEditLayersWeightmaps(const FLandscapeEditLayerRenderWeightParams& InSelectiveRenderParams);`
- L546 _public prototype_ `void FlushLayerContentThisFrame();`
- L549 _public prototype_ `void ForceLayersFullUpdate();` — `UFUNCTION(BlueprintCallable, Category = "Landscape")`
- L551 _public prototype_ `void InitializeLandscapeLayersWeightmapUsage();`
- L553 _public prototype_ `bool ComputeLandscapeLayerBrushInfo(FTransform& OutLandscapeTransform, FIntPoint& OutLandscapeSize, FIntPoint& OutLandscapeRenderTargetSize);`
- L554 _public prototype_ `void UpdateProxyLayersWeightmapUsage();`
- L555 _public prototype_ `void ValidateProxyLayersWeightmapUsage() const;`
- L557 _public prototype_ `void SetUseGeneratedLandscapeSplineMeshesActors(bool bInEnabled);`
- L558 _public prototype_ `bool GetUseGeneratedLandscapeSplineMeshesActors() const;`
- L559 _public prototype_ `bool PrepareTextureResources(bool bInWaitForStreaming);`
- L567 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(EPrepareTextureResourcesLimitedMode);`
- L568 _public prototype_ `bool PrepareTextureResourcesLimited(EPrepareTextureResourcesLimitedMode Mode = EPrepareTextureResourcesLimitedMode::Default);`
- L570 _public function_ `bool GetVisibilityLayerAllocationIndex() const`
- L572 _public prototype_ `virtual void DeleteUnusedLayers() override;`
- L574 _public prototype_ `void EnableNaniteSkirts(bool bInEnable, float InSkirtDepth, bool bInShouldDirtyPackage);`
- L577 _public prototype_ `void SetNanitePositionPrecision(int32 InPrecision, bool bInShouldDirtyPackage);` — Set the target precision on nanite vertex position.  Precision is set to approximately (2^-InPrecision) in world units.
- L579 _public prototype_ `void SetDisableRuntimeGrassMapGeneration(bool bInDisableRuntimeGrassMapGeneration);`
- L581 _public prototype_ `FName GenerateUniqueLayerName(FName InName = NAME_None) const;`
- L584 _private prototype_ `FLandscapeLayer* GetLayerInternal(int32 InLayerIndex);`
- L585 _private prototype_ `void OnLayerCreatedInternal(ULandscapeEditLayerBase* EditLayer);`
- L586 _private prototype_ `ULandscapeEditLayerBase* GetEditLayerInternal(int32 InLayerIndex);`
- L588 _private prototype_ `void UpdateLayersContent(bool bInWaitForStreaming, bool bInSkipMonitorLandscapeEdModeChanges, bool bFlushRender);`
- L589 _private prototype_ `bool CanUpdateLayersContent() const;`
- L590 _private prototype_ `void MonitorLandscapeEdModeChanges();`
- L593 _private prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRendererState> GetEditLayerRendererStates(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) override;`
- L595 _private prototype_ `TArray<UE::Landscape::EditLayers::FEditLayerRendererState> GetEditLayerRendererStatesEnableOverride(const UE::Landscape::EditLayers::FMergeContext* InMergeContext, const TBitArray<>& InLayerEnableOverride);`
- L597 _private prototype_ `UE::Landscape::EditLayers::FMergeRenderContext PrepareEditLayersMergeRenderContext(const UE::Landscape::EditLayers::FMergeContext& InMergeContext, const UE::Landscape::EditLayers::FMergeRenderParams& InParams);`
- L599 _private prototype_ `int32 RegenerateLayersHeightmaps(const FUpdateLayersContentContext& InUpdateLayersContentContext);`
- L600 _private prototype_ `int32 PerformLayersHeightmapsBatchedMerge(const FUpdateLayersContentContext& InUpdateLayersContentContext, const FEditLayersHeightmapMergeParams& InMergeParams);`
- L601 _private prototype_ `void ResolveLayersHeightmapTexture(const FTextureToComponentHelper& MapHelper, const TSet<UTexture2D*>& HeightmapsToResolve, TArray<FLandscapeEditLayerComponentReadbackResult>& InOutComponentReadbackResults);`
- L603 _private prototype_ `bool PerformSelectiveRenderEditLayersHeightmapsCPU(const FUpdateLayersContentContext& InUpdateLayersContentContext, const FLandscapeEditLayerRenderHeightParams& InSelectiveRenderParams);`
- L604 _private prototype_ `bool PerformSelectiveRenderEditLayersHeightmapsRT(const FUpdateLayersContentContext& InUpdateLayersContentContext, const FLandscapeEditLayerRenderHeightParams& InSelectiveRenderParams);`
- L606 _private prototype_ `int32 RegenerateLayersWeightmaps(FUpdateLayersContentContext& InUpdateLayersContentContext);`
- L607 _private prototype_ `int32 PerformLayersWeightmapsBatchedMerge(FUpdateLayersContentContext& InUpdateLayersContentContext, const FEditLayersWeightmapMergeParams& InMergeParams);`
- L608 _private prototype_ `bool PerformSelectiveRenderEditLayersWeightmapsCPU(FUpdateLayersContentContext& InUpdateLayersContentContext, const FLandscapeEditLayerRenderWeightParams& InSelectiveRenderParams);`
- L609 _private prototype_ `void ResolveLayersWeightmapTexture(const FTextureToComponentHelper& MapHelper, const TSet<UTexture2D*>& WeightmapsToResolve, TArray<FLandscapeEditLayerComponentReadbackResult>& InOutComponentReadbackResults);`
- L611 _private prototype_ `bool ResolveLayersTexture(FTextureToComponentHelper const& MapHelper, FLandscapeEditLayerReadback* InCPUReadBack, UTexture2D* InOutputTexture, TArray<FLandscapeEditLayerComponentReadbackResult>& InOutComponentReadbackResults, bool bIsWeightmap);`
- L614 _private prototype_ `static bool IsUpdateFlagEnabledForModes(ELandscapeComponentUpdateFlag InFlag, uint32 InUpdateModes);`
- L615 _private prototype_ `void UpdateForChangedHeightmaps(const TArrayView<FLandscapeEditLayerComponentReadbackResult>& InComponentReadbackResults);`
- L616 _private prototype_ `void UpdateForChangedWeightmaps(const TArrayView<FLandscapeEditLayerComponentReadbackResult>& InComponentReadbackResults);`
- L617 _private prototype_ `uint32 UpdateCollisionAndClients(const TArrayView<FLandscapeEditLayerComponentReadbackResult>& Components);`
- L618 _private prototype_ `uint32 UpdateAfterReadbackResolves(const TArrayView<FLandscapeEditLayerComponentReadbackResult>& Components);`
- L620 _private prototype_ `bool PrepareLayersTextureResources(bool bInWaitForStreaming);`
- L621 _private prototype_ `bool PrepareLayersTextureResources(const TArray<FLandscapeLayer>& InLayers, bool bInWaitForStreaming);`
- L622 _private prototype_ `bool PrepareLayersResources(EShaderPlatform InShaderPlatform, bool bInWaitForStreaming);`
- L623 _private prototype_ `void InvalidateRVTForTextures(const TSet<UTexture2D*>& InTextures);`
- L625 _private prototype_ `void UpdateLayersMaterialInstances(const TArray<ULandscapeComponent*>& InLandscapeComponents);`
- L627 _private prototype_ `void ReallocateLayersWeightmaps(FUpdateLayersContentContext& InUpdateLayersContentContext, const TMap<ULandscapeComponent*, TArray<ULandscapeLayerInfoObject*>>& InPerComponentAllocations, const TSet<ULandscapeComponent*>& InRestrictTextureSharingToComponents);`
- L630 _private prototype_ `void InitializeLayers();`
- L632 _private prototype_ `void UpdateWeightDirtyData(ULandscapeComponent* InLandscapeComponent, UTexture2D const* InWeightmap, FColor const* InOldData, FColor const* InNewData, uint8 InChannel);`
- L633 _private prototype_ `void OnDirtyWeightmap(FTextureToComponentHelper const& MapHelper, UTexture2D const* InWeightmap, FColor const* InOldData, FColor const* InNewData, int32 InMipLevel, uint8 ChangedChannelsMask);`
- L634 _private prototype_ `void UpdateHeightDirtyData(ULandscapeComponent* InLandscapeComponent, UTexture2D const* InHeightmap, FColor const* InOldData, FColor const* InNewData);`
- L635 _private prototype_ `void OnDirtyHeightmap(FTextureToComponentHelper const& MapHelper, UTexture2D const* InWeightmap, FColor const* InOldData, FColor const* InNewData, int32 InMipLevel);`
- L637 _private prototype_ `static bool IsMaterialResourceCompiled(FMaterialResource* InMaterialResource, bool bInWaitForCompilation);`
- L639 _private prototype_ `void OnEditLayerDataChanged(const FOnLandscapeEditLayerDataChangedParams& InParams);`
- L643 _private prototype_ `void MarkAllLandscapeRenderStateDirty();`
- L644 _private prototype_ `bool RenderMergedTextureInternal(const FTransform& InRenderAreaWorldTransform, const FBox2D& InRenderAreaExtents, const TArray<FName>& InWeightmapLayerNames, UTextureRenderTarget* OutRenderTarget);`
- L647 _private member_ `bool bGrassEnabled = true;` — `UPROPERTY(EditAnywhere, Category="Grass")`
- L654 _public member_ `bool bAreNewLandscapeActorsSpatiallyLoaded = true;` — `UPROPERTY(EditAnywhere, Category = WorldPartition)` — Landscape actor has authority on default streaming behavior for new actors : LandscapeStreamingProxies & LandscapeSplineActors
- L658 _public member_ `bool bIncludeGridSizeInNameForLandscapeActors = false;` — `UPROPERTY()` — If true, LandscapeStreamingProxy actors have the grid size included in their name, for backward compatibility we also check the AWorldSettings::bIncludeGridSizeInNameForPartitionedActors
- L662 _public member_ `bool bCanHaveLayersContent_DEPRECATED = false;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")` — `UPROPERTY()`
- L669 _public member_ `bool bUseGeneratedLandscapeSplineMeshesActors = false;` — `UPROPERTY()` — If true, WorldPartitionLandscapeSplineMeshesBuilder is responsible of generating partitioned actors of type ALandscapeSplineMeshesActor that will contain all landscape spline/controlpoints static meshes. Source components will be editor only and hidden in game for PIE.
- L671 _public prototype_ `DECLARE_EVENT(ALandscape, FLandscapeBlueprintBrushChangedDelegate);`
- L672 _public function_ `FLandscapeBlueprintBrushChangedDelegate& OnBlueprintBrushChangedDelegate()`
- L675 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEditLayersMergedDelegate, const FOnLandscapeEditLayersMergedParams& );` — Delegate that will be called whenever an edit layers merge is done
- L676 _public function_ `FOnEditLayersMergedDelegate::RegistrationType& OnEditLayersMerged() const`
- L681 _public member_ `FGuid LandscapeSplinesTargetLayerGuid_DEPRECATED;` — `UE_DEPRECATED(all, "This has been refactored into the generic ULandscapeEditLayerBase system. Please check for the presence of a ULandscapeEditLayerSplines layer instead")` — `UPROPERTY()` — Target Landscape Layer for Landscape Splines
- L685 _public member_ `FGuid EditingLayer;` — TODO this is used as shared global state for the landscape editor mode. FLandscapeToolStrokeBase::SetEditLayer should manage the shared editor state instead
- L689 _public member_ `int32 SelectedEditLayerIndex = 0;` — `UPROPERTY(Transient, DuplicateTransient)` — Current Selected Edit Layer of this landscape. Used by landscape editor mode to track the current selection
- L692 _public member_ `bool bGrassUpdateEnabled;` — Used to temporarily disable Grass Update in Editor
- L695 _public member_ `bool bEnableEditorLayersTick = true;` — `UPROPERTY(Transient)`
- L699 _public member_ `TArray<FLandscapeLayer> LandscapeLayers_DEPRECATED;` — `UE_DEPRECATED(all, "This property has moved to private. Use the public accessors instead")` — `UPROPERTY()`
- L703 _public member_ `TArray<TObjectPtr<UTextureRenderTarget2D>> HeightmapRTList_DEPRECATED;` — `UE_DEPRECATED(5.7, "Edit layers are now fully processed via BatchedMerge")` — `UPROPERTY(Transient)`
- L707 _public member_ `TArray<TObjectPtr<UTextureRenderTarget2D>> WeightmapRTList_DEPRECATED;` — `UE_DEPRECATED(5.7, "Edit layers are now fully processed via BatchedMerge")` — `UPROPERTY(Transient)`
- L711 _public member_ `TArray<TWeakObjectPtr<UTexture2D>> TrackedStreamingInTextures;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — List of textures that are not fully streamed in yet (updated every frame to track textures that have finished streaming in)
- L715 _public member_ `TArray<FName> TargetDisplayOrderList;` — `UPROPERTY(NonTransactional)` — Display Order of the targets
- L719 _public member_ `ELandscapeLayerDisplayMode TargetDisplayOrder = ELandscapeLayerDisplayMode::Default;` — `UPROPERTY(NonTransactional)` — Display Order mode for the targets
- L723 _private member_ `TArray<FLandscapeLayer> LandscapeEditLayers;` — `UPROPERTY()`
- L725 _private member_ `FLandscapeBlueprintBrushChangedDelegate LandscapeBlueprintBrushChangedDelegate;`
- L726 _private member_ `mutable FOnEditLayersMergedDelegate OnEditLayersMergedDelegate;`
- L730 _private member_ `TSet<TObjectPtr<ULandscapeComponent>> LandscapeSplinesAffectedComponents;` — `UPROPERTY(Transient)` — Components affected by landscape splines (used to partially clear Layer Reserved for Splines)
- L733 _private member_ `ILandscapeEdModeInterface* LandscapeEdMode;` — Provides information from LandscapeEdMode
- L746 _private member_ `FLandscapeEdModeInfo LandscapeEdModeInfo;`
- L750 _private member_ `bool bLandscapeLayersAreInitialized;` — `UPROPERTY(Transient)` — TODO [jonathan.bard] : remove : this isn't really used anymore
- L754 _private member_ `bool WasCompilingShaders_DEPRECATED = false;` — `UE_DEPRECATED(5.8, "WasCompilingShaders property is no longer used.")` — `UPROPERTY(Transient)`
- L757 _private member_ `uint32 LayerContentUpdateModes;` — `UPROPERTY(Transient, NonTransactional)`
- L760 _private member_ `bool bSplineLayerUpdateRequested;` — `UPROPERTY(Transient)`
- L762 _private member_ `bool bWarnedGlobalMergeDimensionsExceeded = false;`
- L763 _private member_ `bool bWarnedNumComponentsPerBatchExceeded = false;`
- L764 _private member_ `bool bWarnedLayerMergeResolution = false;`
- L779 _private member_ `FWaitingForResourcesNotificationHelper WaitingForTexturesNotificationHelper;` — Non-stackable user notifications for landscape editor
- L780 _private member_ `FWaitingForResourcesNotificationHelper WaitingForEditLayerResourcesNotificationHelper;`
- L782 _private member_ `uint32 LastFlushedLayerUpdateFrame = 0;`
- L783 _private member_ `uint32 LastPrepareTextureResourcesCalled = 0;`
- L784 _private member_ `bool bLastPrepareTextureResourcesResult = false;`
- L785 _private member_ `bool bHasWarnedAboutInvalidShadingModel = false;`
- L788 _private member_ `uint32 LayerUpdateCount = 0;` — Counter to detect re-entrance

#### enum `ALandscape::EPrepareTextureResourcesLimitedMode`  
`enum class EPrepareTextureResourcesLimitedMode : uint8`  
_L561-566_
- L563 _public enumerator_ `Default = 0` — Default operation
- L564 _public enumerator_ `WaitForStreaming = 1 << 0` — Block until streaming completes
- L565 _public enumerator_ `BypassRateLimit = 1 << 1` — Bypass rate limit and always call PrepareTextureResources

#### struct `ALandscape::FLandscapeEdModeInfo`  
`struct FLandscapeEdModeInfo`  
_L736-744_
- desc: Information provided by LandscapeEdMode
- L738 _public prototype_ `FLandscapeEdModeInfo();`
- L740 _public member_ `int32 ViewMode;`
- L741 _public member_ `FGuid SelectedLayer;`
- L742 _public member_ `TWeakObjectPtr<ULandscapeLayerInfoObject> SelectedLayerInfoObject;`
- L743 _public member_ `ELandscapeToolTargetType ToolTarget;`

#### struct `ALandscape::FWaitingForResourcesNotificationHelper`  
`struct FWaitingForResourcesNotificationHelper`  
_L766-776_
- L768 _public prototype_ `void Notify(ALandscape* InLandscape, class FLandscapeNotificationManager* InNotificationManager, ELandscapeNotificationType InNotificationType, const FText& InNotificationText);`
- L769 _public prototype_ `void Reset();`
- L772 _public member_ `double WaitingForResourcesStartTime = -1.0;` — Time since waiting for resources to be ready
- L775 _public member_ `TSharedPtr<FLandscapeNotification> Notification;` — Non-stackable user notification for landscape editor

#### class `FScopedSetLandscapeEditingLayer`  
`class FScopedSetLandscapeEditingLayer`  
_L793-803_
- L796 _public prototype_ `FScopedSetLandscapeEditingLayer(ALandscape* InLandscape, const FGuid& InLayerGUID, TFunction<void()> InCompletionCallback = TFunction<void()>());`
- L797 _public prototype_ `~FScopedSetLandscapeEditingLayer();`
- L800 _private member_ `TWeakObjectPtr<ALandscape> Landscape;`
- L801 _private member_ `FGuid PreviousLayerGUID;`
- L802 _private member_ `TFunction<void()> CompletionCallback;`

#### Free symbols / members of external scopes

- L44 _namespace_ `namespace EditLayersHeightmapLocalMerge_RenderThread`
- L49 _namespace_ `namespace EditLayersWeightmapLocalMerge_RenderThread`
- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace Landscape` (scope `UE`)
- L54 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)
- L60 _externvar_ `extern TAutoConsoleVariable<int32> CVarLandscapeSplineFalloffModulation;`
- L671 _delegate_ `DECLARE_EVENT(ALandscape, FLandscapeBlueprintBrushChangedDelegate);`
- L675 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEditLayersMergedDelegate, const FOnLandscapeEditLayersMergedParams& );` — Delegate that will be called whenever an edit layers merge is done

### `Source/Runtime/Landscape/Classes/LandscapeComponent.h` (Public)


#### struct `FLandscapeEditToolRenderData`  
`struct FLandscapeEditToolRenderData`  
_L56-115_
- reflection: `USTRUCT()`
- desc: FLandscapeEditToolRenderData
- L69 _public function_ `FLandscapeEditToolRenderData() : ToolMaterial(NULL), GizmoMaterial(NULL), SelectedType(ST_NONE), DebugChannelR(INDEX_NONE), DebugChannelG(INDEX_NONE), DebugChannelB(INDEX_NONE), DataTexture(NULL), LayerContributionTexture(NULL), DirtyTexture(NULL)`
- L83 _public member_ `TObjectPtr<UMaterialInterface> ToolMaterial;` — `UPROPERTY(NonTransactional)` — Material used to render the tool.
- L87 _public member_ `TObjectPtr<UMaterialInterface> GizmoMaterial;` — `UPROPERTY(NonTransactional)` — Material used to render the gizmo selection region...
- L91 _public member_ `int32 SelectedType;` — `UPROPERTY(NonTransactional)` — Component is selected
- L94 _public member_ `int32 DebugChannelR;` — `UPROPERTY(NonTransactional)`
- L97 _public member_ `int32 DebugChannelG;` — `UPROPERTY(NonTransactional)`
- L100 _public member_ `int32 DebugChannelB;` — `UPROPERTY(NonTransactional)`
- L103 _public member_ `TObjectPtr<UTexture2D> DataTexture;` — `UPROPERTY(NonTransactional)` — Data texture other than height/weight
- L106 _public member_ `TObjectPtr<UTexture2D> LayerContributionTexture;` — `UPROPERTY(NonTransactional)` — Data texture used to represent layer contribution
- L109 _public member_ `TObjectPtr<UTexture2D> DirtyTexture;` — `UPROPERTY(NonTransactional)` — Data texture used to represent layer blend dirtied area
- L112 _public prototype_ `void UpdateDebugColorMaterial(const ULandscapeComponent* const Component);`
- L113 _public prototype_ `void UpdateSelectionMaterial(int32 InSelectedType, const ULandscapeComponent* const Component);`

#### enum `FLandscapeEditToolRenderData::SelectionType`  
`enum SelectionType`  
_L61-67_
- L63 _public enumerator_ `ST_NONE = 0`
- L64 _public enumerator_ `ST_COMPONENT = 1`
- L65 _public enumerator_ `ST_REGION = 2`

#### struct `FLandscapeVertexRef`  
`struct FLandscapeVertexRef`  
_L118-137_
- desc: Used to uniquely reference a landscape vertex in a component.
- L120 _public function_ `FLandscapeVertexRef(int16 InX, int16 InY, int8 InSubX, int8 InSubY) : X(InX) , Y(InY) , SubX(InSubX) , SubY(InSubY)`
- L127 _public member_ `uint32 X : 8;`
- L128 _public member_ `uint32 Y : 8;`
- L129 _public member_ `uint32 SubX : 8;`
- L130 _public member_ `uint32 SubY : 8;`
- L133 _public function_ `static int32 GetVertexIndex(FLandscapeVertexRef Vert, int32 SubsectionCount, int32 SubsectionVerts)` — Helper to provide a standard ordering for vertex arrays.

#### struct `FWeightmapLayerAllocationInfo`  
`struct FWeightmapLayerAllocationInfo`  
_L141-187_
- reflection: `USTRUCT()`
- desc: Stores information about which weightmap texture and channel each layer is stored
- L146 _public member_ `TObjectPtr<ULandscapeLayerInfoObject> LayerInfo;` — `UPROPERTY()`
- L149 _public member_ `uint8 WeightmapTextureIndex;` — `UPROPERTY()`
- L152 _public member_ `uint8 WeightmapTextureChannel;` — `UPROPERTY()`
- L154 _public function_ `FWeightmapLayerAllocationInfo() : LayerInfo(nullptr) , WeightmapTextureIndex(0) , WeightmapTextureChannel(0)`
- L162 _public function_ `FWeightmapLayerAllocationInfo(ULandscapeLayerInfoObject* InLayerInfo) : LayerInfo(InLayerInfo) , WeightmapTextureIndex(255)`
- L169 _public function_ `bool operator == (const FWeightmapLayerAllocationInfo& RHS) const`
- L176 _public prototype_ `FName GetLayerName() const;`
- L178 _public prototype_ `uint32 GetHash() const;`
- L180 _public function_ `void Free()`
- L186 _public function_ `bool IsAllocated() const`

#### struct `IBuffer2DView`  
`template<typename T> struct IBuffer2DView`  
_L195-205_
- L198 _public prototype_ `virtual void CopyTo(T* Dest, int32 Count) const = 0;` — copy up to Count elements to Dest, in X then Y order (standard image order)
- L201 _public prototype_ `virtual bool CopyToAndCalcIsAllZero(T* Dest, int32 Count) const = 0;` — copy up to Count elements to Dest, in X then Y order (standard image order)
- L204 _public prototype_ `virtual int32 Num() const = 0;` — return the total number of elements

#### struct `FLandscapeComponentGrassData`  
`struct FLandscapeComponentGrassData`  
_L207-273_
- L215 _public member_ `TArray<FGuid, TInlineAllocator<2>> MaterialStateIds_DEPRECATED;` — `UE_DEPRECATED(all, "GenerationHash is now used")` — Guid per material instance in the hierarchy between the assigned landscape material (instance) and the root UMaterial used to detect changes to material instance parameters or the root material that could affect the grass maps
- L219 _public member_ `FQuat RotationForWPO_DEPRECATED;` — `UE_DEPRECATED(all, "GenerationHash is now used")` — cached component rotation when material world-position-offset is used, as this will affect the direction of world-position-offset deformation (included in the HeightData below)
- L222 _public member_ `uint32 GenerationHash = 0;` — Variable used to detect when grass data needs to be regenerated:
- L227 _public member_ `TMap<int32, TArray<uint16>> HeightMipData;` — Height data for LODs 1+, keyed on LOD index
- L230 _public member_ `static constexpr int32 UnknownNumElements = -1;`
- L233 _public member_ `int32 NumElements = UnknownNumElements;` — Elements per contiguous array: for validation and also to indicate whether the grass data is valid (NumElements >= 0, meaning 0 elements is valid but the grass data is all zero and therefore empty) or not known yet (== UnknownNumElements)
- L235 _public member_ `TMap<FName, int32> WeightOffsets;` — Serialized in one block to prevent Slack waste
- L236 _public member_ `TArray<uint8> HeightWeightData;`
- L240 _public prototype_ `FLandscapeComponentGrassData() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables
- L241 _public prototype_ `FLandscapeComponentGrassData(ULandscapeComponent* Component);`
- L242 _public prototype_ `~FLandscapeComponentGrassData() = default;`
- L243 _public prototype_ `FLandscapeComponentGrassData(const FLandscapeComponentGrassData&) = default;`
- L244 _public prototype_ `FLandscapeComponentGrassData(FLandscapeComponentGrassData&&) = default;`
- L245 _public prototype_ `FLandscapeComponentGrassData& operator=(const FLandscapeComponentGrassData&) = default;`
- L246 _public prototype_ `FLandscapeComponentGrassData& operator=(FLandscapeComponentGrassData&&) = default;`
- L250 _public prototype_ `bool HasValidData() const;` — Returns whether grass data has been computed (or serialized) yet. Returns true even if the data is completely empty (e.g. all-zero weightmap data)
- L253 _public prototype_ `bool HasData() const;` — Returns whether the data is completely empty (e.g. all-zero weightmap data). Returns false if the data just wasn't computed yet :
- L257 _public prototype_ `void InitializeFrom(const TArray<uint16>& HeightData, const TMap<ULandscapeGrassType*, TArray<uint8>>& WeightData);` — Initialize function meant for deserializing from old data : the new format doesn't take ULandscapeGrassType* but FName :
- L258 _public prototype_ `void FixupFallbackGrassNames(const TMap<FName, TObjectPtr<ULandscapeGrassType>>& InNamedGrassTypes);`
- L260 _public prototype_ `void InitializeFrom(IBuffer2DView<uint16>* HeightData, TMap<FName, IBuffer2DView<uint8>*>& WeightData, bool bStripEmptyWeights);`
- L262 _public prototype_ `bool HasWeightData() const;`
- L263 _public prototype_ `TArrayView<uint8> GetWeightData(const FName& GrassName);`
- L264 _public prototype_ `bool Contains(const FName& GrassName) const;`
- L265 _public prototype_ `TArrayView<uint16> GetHeightData();`
- L267 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L270 _public prototype_ `void ConditionalDiscardDataOnLoad(const TMap<FName, TObjectPtr<ULandscapeGrassType>>& InNamedGrassTypes);` — Check whether we can discard any data not needed with current scalability settings

#### struct `FLandscapeComponentMaterialOverride`  
`struct UE_DEPRECATED(all, "FLandscapeComponentMaterialOverride is deprecated; please use FLandscapePerLODMaterialOverride instead") FLandscapeComponentMaterialOverride`  
_L276-285_
- reflection: `USTRUCT(NotBlueprintable, meta = (Deprecated = "5.1"))`
- L281 _public member_ `FPerPlatformInt LODIndex;` — `UPROPERTY(EditAnywhere, Category = LandscapeComponent, meta=(UIMin=0, UIMax=8, ClampMin=0, ClampMax=8))`
- L284 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY(EditAnywhere, Category = LandscapeComponent)`

#### struct `FLandscapePerLODMaterialOverride`  
`struct FLandscapePerLODMaterialOverride`  
_L288-303_
- reflection: `USTRUCT(NotBlueprintable)`
- L293 _public member_ `int32 LODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = Material, meta = (UIMin = 0, UIMax = 8, ClampMin = 0, ClampMax = 8))`
- L296 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY(EditAnywhere, Category = Material)`
- L298 _public function_ `bool operator == (const FLandscapePerLODMaterialOverride & InOther) const`

#### struct `FWeightmapData`  
`struct FWeightmapData`  
_L306-318_
- reflection: `USTRUCT(NotBlueprintable)`
- L311 _public member_ `TArray<TObjectPtr<UTexture2D>> Textures;` — `UPROPERTY()`
- L314 _public member_ `TArray<FWeightmapLayerAllocationInfo> LayerAllocations;` — `UPROPERTY()`
- L317 _public member_ `TArray<TObjectPtr<ULandscapeWeightmapUsage>> TextureUsages;` — `UPROPERTY(Transient, NonTransactional)`

#### struct `FHeightmapData`  
`struct FHeightmapData`  
_L321-327_
- reflection: `USTRUCT(NotBlueprintable)`
- L326 _public member_ `TObjectPtr<UTexture2D> Texture = nullptr;` — `UPROPERTY()`

#### struct `FLandscapeLayerComponentData`  
`struct FLandscapeLayerComponentData`  
_L330-356_
- reflection: `USTRUCT(NotBlueprintable)`
- L334 _public prototype_ `FLandscapeLayerComponentData() = default;`
- L337 _public function_ `FLandscapeLayerComponentData(const FName& InDebugName) : DebugName(InDebugName)`
- L346 _public member_ `FName DebugName;` — `UPROPERTY()` — Edit layers are referenced by Guid, this name is just there to provide some insights as to what edit layer name this layer data corresponded to in case of a missing edit layer guid
- L350 _public member_ `FHeightmapData HeightmapData;` — `UPROPERTY()`
- L353 _public member_ `FWeightmapData WeightmapData;` — `UPROPERTY()`
- L355 _public function_ `bool IsInitialized() const`

#### enum `ELandscapeComponentUpdateFlag`  
`enum ELandscapeComponentUpdateFlag : uint32`  
_L359-373_
- L362 _public enumerator_ `Component_Update_Heightmap_Collision = 1 << 0` — Will call UpdateCollisionHeightData, UpdateCacheBounds, UpdateComponentToWorld on Component
- L364 _public enumerator_ `Component_Update_Weightmap_Collision = 1 << 1` — Will call UdateCollisionLayerData on Component
- L366 _public enumerator_ `Component_Update_Recreate_Collision = 1 << 2` — Will call RecreateCollision on Component
- L368 _public enumerator_ `Component_Update_Client = 1 << 3` — Will update Component clients: Navigation data, Foliage, Grass, etc.
- L370 _public enumerator_ `Component_Update_Client_Editing = 1 << 4` — Will update Component clients while editing
- L372 _public enumerator_ `Component_Update_Approximated_Bounds = 1 << 5` — Will compute component approximated bounds

#### enum `ELandscapeLayerUpdateMode`  
`enum ELandscapeLayerUpdateMode : uint32`  
_L386-410_
- desc: ELandscapeLayerUpdateMode flags relate to types of updates to landscape layer data.  Stored on the ALandscape and on ULandscapeComponent to indicate pending changes.  Stored on FLandscapeEditLayerComponentReadbackResult to indicate what type of change triggered the creation of the new data. Update_All_Components on ALandscape or passed to RequestLayersContentUpdate will cause all components to be enqueued for layer merging, rather than only those components carrying relevant flags of their own. See IsUpdateFlagEnabledForModes, where these flags are translated to ELandscapeComponentUpdateFlag, that indicate specific tasks.
- L389 _public enumerator_ `Update_None = 0` — No Update
- L391 _public enumerator_ `Update_Heightmap_All_Modes = 1 << 0` — Update types
- L392 _public enumerator_ `Update_Heightmap_Editing = 1 << 1`
- L393 _public enumerator_ `Update_Heightmap_Editing_NoCollision = 1 << 2`
- L394 _public enumerator_ `Update_Weightmap_All_Modes = 1 << 3`
- L395 _public enumerator_ `Update_Weightmap_Editing = 1 << 4`
- L396 _public enumerator_ `Update_Weightmap_Editing_NoCollision = 1 << 5`
- L397 _public enumerator_ `Update_All_Components = 1 << 6`
- L399 _public enumerator_ `Update_Heightmap_All = Update_Heightmap_All_Modes | Update_All_Components` — Combinations
- L400 _public enumerator_ `Update_Weightmap_All = Update_Weightmap_All_Modes | Update_All_Components`
- L401 _public enumerator_ `Update_All = Update_Weightmap_All | Update_Heightmap_All`
- L402 _public enumerator_ `Update_All_Editing = Update_Weightmap_Editing | Update_Heightmap_Editing`
- L403 _public enumerator_ `Update_All_Editing_NoCollision = Update_Weightmap_Editing_NoCollision | Update_Heightmap_Editing_NoCollision`
- L404 _public enumerator_ `Update_Heightmap_Types = Update_Heightmap_All_Modes | Update_Heightmap_Editing | Update_Heightmap_Editing_NoCollision`
- L405 _public enumerator_ `Update_Weightmap_Types = Update_Weightmap_All_Modes | Update_Weightmap_Editing | Update_Weightmap_Editing_NoCollision`
- L407 _public enumerator_ `Update_Client_Deferred = 1 << 7` — In cases where we couldn't update the clients right away this flag will be set in RegenerateLayersContent
- L409 _public enumerator_ `Update_Client_Editing = 1 << 8` — Update landscape component clients while editing

#### enum `ELandscapeClearMode`  
`enum UE_DEPRECATED(5.7, "Use ELandscapeToolTargetTypeFlags instead.") ELandscapeClearMode : int`  
_L417-422_
- reflection: `UENUM()`
- L419 _public enumerator_ `Clear_Weightmap = 1 << 0 UMETA(DisplayName = "Paint")`
- L420 _public enumerator_ `Clear_Heightmap = 1 << 1 UMETA(DisplayName = "Sculpt")`
- L421 _public enumerator_ `Clear_All = Clear_Weightmap | Clear_Heightmap UMETA(DisplayName = "All")`

#### class `ULandscapeLODStreamingProxy_DEPRECATED`  
`class ULandscapeLODStreamingProxy_DEPRECATED : public UStreamableRenderAsset`  
_L425-428_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UStreamableRenderAsset`

#### class `ULandscapeComponent`  
`class ULandscapeComponent : public UPrimitiveComponent`  
_L431-1346_
- reflection: `UCLASS(hidecategories=(Display, Attachment, Physics, Debug, Collision, Movement, Rendering, PrimitiveComponent, Object, Transform, Mobility, VirtualTexture), showcategories=("Rendering|Material"), MinimalAPI, Within=LandscapeProxy)`
- inherits: `UPrimitiveComponent`
- L437 _private member_ `int32 SectionBaseX;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=LandscapeComponent)` — X offset from global components grid origin (in quads)
- L441 _private member_ `int32 SectionBaseY;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=LandscapeComponent)` — Y offset from global components grid origin (in quads)
- L445 _private member_ `int32 ComponentSizeQuads;` — `UPROPERTY()` — Total number of quads for this component, has to be >0
- L449 _private member_ `int32 SubsectionSizeQuads;` — `UPROPERTY()` — Number of quads for a subsection of the component. SubsectionSizeQuads+1 must be a power of two.
- L453 _private member_ `int32 NumSubsections;` — `UPROPERTY()` — Number of subsections in X or Y axis
- L456 _private member_ `TObjectPtr<UMaterialInterface> OverrideMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=LandscapeComponent)`
- L459 _private member_ `TObjectPtr<UMaterialInterface> OverrideHoleMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=LandscapeComponent, AdvancedDisplay)`
- L465 _private member_ `TArray<FLandscapeComponentMaterialOverride> OverrideMaterials_DEPRECATED;` — `UE_DEPRECATED(all, "OverrideMaterials has been deprecated, use PerLODOverrideMaterials instead.")` — `UPROPERTY()`
- L470 _private member_ `TObjectPtr<UMaterialInstanceConstant> MaterialInstance_DEPRECATED;` — `UE_DEPRECATED(all, "MaterialInstance has been deprecated, use MaterialInstances instead.")` — `UPROPERTY()`
- L474 _private member_ `TArray<TObjectPtr<UMaterialInstanceConstant>> MaterialInstances;` — `UPROPERTY(TextExportTransient)`
- L477 _private member_ `TArray<TObjectPtr<UMaterialInstanceDynamic>> MaterialInstancesDynamic;` — `UPROPERTY(Transient, TextExportTransient)`
- L481 _private member_ `TArray<int8> LODIndexToMaterialIndex;` — `UPROPERTY(TextExportTransient)` — Mapping between LOD and Material Index
- L485 _private member_ `TObjectPtr<UTexture2D> XYOffsetmapTexture_DEPRECATED;` — `UE_DEPRECATED(5.7, "RetopologizeTool/XYOffset deprecated with the removal of non-edit layer landscapes")` — `UPROPERTY()`
- L489 _private member_ `FVector4 WeightmapScaleBias;` — `UPROPERTY()` — UV offset to component's weightmap data from component local coordinates
- L493 _private member_ `float WeightmapSubsectionOffset;` — `UPROPERTY()` — U or V offset into the weightmap for the first subsection, in texture UV space
- L497 _private member_ `FVector4 HeightmapScaleBias;` — `UPROPERTY()` — UV offset to Heightmap data from component local coordinates
- L501 _private member_ `FBox CachedLocalBox;` — `UPROPERTY()` — Cached local-space bounding box, created at heightmap update time
- L512 _private member_ `TArray<double> MipToMipMaxDeltas;` — `UPROPERTY()` — Maximum deltas between vertices and their counterparts from other mips. This mip-to-mip data is laid out in a contiguous array following the following pattern : Say, we have 5 "relevant" mips and [N -> M] is the delta from mip N to M (where M > N and M < (NumRelevantMips - 1)) then the array will contain : [0 -> 1], [0 -> 2], [0 -> 3], [1 -> 2], [1 -> 3], [2 -> 3] i.e. for mip 0 : (NumRelevantMips - 1) deltas, then for mip 1 : (NumRelevantMips - 2) deltas, until mip == (NumRelevantMips - 2) : 1 delta Note: a "relevant" mip is one with more than 1 vertex. i.e.: - In the case of a 1x1 subsection, the last mip index (NumMips - 1) has a single pixel and is therefore not relevant (we cannot draw a landscape component with a single vertex!), hence the last relevant mip index will be NumMips - 2 - In the case of 2x2 subsections, the penultimate mip index (NumMips - 2) has 4 pixels, which means 4 subsections, each with a single pixel, and is therefore not relevant either, hence the last relevant mip index will be NumMips - 3
- L518 _private member_ `TLazyObjectPtr<ULandscapeHeightfieldCollisionComponent> CollisionComponent_DEPRECATED;` — `UE_DEPRECATED(all, "CollisionComponent has been deprecated")` — `UPROPERTY()`
- L525 _private member_ `TObjectPtr<ULandscapeHeightfieldCollisionComponent> CollisionComponentRef;` — `UPROPERTY()` — Reference to associated collision component
- L529 _private member_ `bool bUserTriggeredChangeRequested = false;` — `UPROPERTY(Transient, NonTransactional)` — Store
- L532 _private member_ `bool bNaniteActive;` — `UPROPERTY(Transient)`
- L537 _private member_ `FGuid LightingGuid;` — `UPROPERTY()` — Unique ID for this component, used for caching during distributed lighting
- L541 _private member_ `TMap<FGuid, FLandscapeLayerComponentData> LayersData;` — `UPROPERTY()` — Edit Layers that have data for this component store it here
- L546 _private member_ `TMap<FGuid, FLandscapeLayerComponentData> ObsoleteEditLayerData;` — `UPROPERTY(Transient)` — Obsolete edit layers (Edit layers not tracked by ALandscape). During registration, moves obsolete layer data out of active LayersData into this transient storage. When obsolete layers exists, creates an additional duplicate of the final merged data on initial registration mapped to FGuid()
- L550 _private member_ `TArray<TObjectPtr<ULandscapeWeightmapUsage>> WeightmapTexturesUsage;` — `UPROPERTY(Transient)` — Final layer data
- L553 _private member_ `uint32 LayerUpdateFlagPerMode;` — `UPROPERTY(Transient, NonTransactional)`
- L556 _private member_ `bool bPendingCollisionDataUpdate;` — `UPROPERTY(Transient)`
- L559 _private member_ `bool bPendingLayerCollisionDataUpdate;` — `UPROPERTY(Transient)`
- L561 _private member_ `bool bUndoChangedWeightmapAllocs = false;`
- L564 _private member_ `bool bPendingPhysicalMaterialInvalidation = false;` — Physical material has been invalidated and no new physical material task has been started since then
- L567 _private member_ `FIntRect LayerDirtyCollisionHeightData;` — Dirtied collision height region when painting (only used by Landscape Layer System)
- L572 _private member_ `TObjectPtr<UTexture2D> HeightmapTexture;` — `UPROPERTY()` — Heightmap texture reference
- L576 _private member_ `TArray<FWeightmapLayerAllocationInfo> WeightmapLayerAllocations;` — `UPROPERTY()` — List of layers, and the weightmap and channel they are stored
- L580 _private member_ `TArray<TObjectPtr<UTexture2D>> WeightmapTextures;` — `UPROPERTY()` — Weightmap texture reference
- L583 _private member_ `TArray<FLandscapePerLODMaterialOverride> PerLODOverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = LandscapeComponent)`
- L587 _private member_ `uint32 GrassTypesCRC = 0;` — A CRC of everything that can lead NamedGrassTypes to be changed (e.g. the material changing, or grass type overrides changing)
- L590 _private member_ `TArray<TObjectPtr<ULandscapeGrassType>> GrassTypes_DEPRECATED;` — `UPROPERTY()`
- L598 _private member_ `TMap<FName, TObjectPtr<ULandscapeGrassType>> NamedGrassTypes;` — `UPROPERTY()` — Cached list of grass types supported by the component's material. This is needed in a cooked build, as the grass types list is not available on the cooked material. Call UpdateGrassTypes() to ensure this array is up to date
- L609 _public member_ `FGrassTypeSummary GrassTypeSummary;`
- L610 _public function_ `inline bool IsGrassTypeSummaryValid()`
- L613 _public prototype_ `void InvalidateGrassTypeSummary();` — Invalidate the grass type summary.  Call whenever grass types are changed to indicate that the summary values are out of date.
- L617 _public member_ `FGuid MapBuildDataId;` — `UPROPERTY()` — Uniquely identifies this component's built map data.
- L621 _public member_ `int32 CollisionMipLevel;` — `UPROPERTY(EditAnywhere, Category=LandscapeComponent)` — Heightfield mipmap used to generate collision
- L625 _public member_ `int32 SimpleCollisionMipLevel;` — `UPROPERTY(EditAnywhere, Category=LandscapeComponent)` — Heightfield mipmap used to generate simple collision
- L630 _public member_ `float NegativeZBoundsExtension;` — `UPROPERTY(EditAnywhere, Category=LandscapeComponent)` — Allows overriding the landscape bounds. This is useful if you distort the landscape with world-position-offset, for example Extension value in the negative Z axis, positive value increases bound size
- L635 _public member_ `float PositiveZBoundsExtension;` — `UPROPERTY(EditAnywhere, Category=LandscapeComponent)` — Allows overriding the landscape bounds. This is useful if you distort the landscape with world-position-offset, for example Extension value in the positive Z axis, positive value increases bound size
- L639 _public member_ `float StaticLightingResolution;` — `UPROPERTY(EditAnywhere, Category=LandscapeComponent, meta=(ClampMax = 4096))` — StaticLightingResolution overriding per component, default value 0 means no overriding
- L643 _public member_ `int32 ForcedLOD;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=LandscapeComponent)` — Forced LOD level to use when rendering
- L647 _public member_ `int32 LODBias;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=LandscapeComponent)` — LOD level Bias to use when rendering
- L655 _public member_ `TObjectPtr<ULandscapeHeightmapTextureEdgeFixup> RegisteredEdgeFixup;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — When the component has registered a heightmap texture edge fixup, a reference to the edge fixup and the group are stored here for easy access (the fixup is also referenced via the heightmap AssetUserDatas, and the group can be accessed via the ULandcapeSubsystem)
- L656 _public member_ `FLandscapeGroup* RegisteredLandscapeGroup;`
- L662 _public member_ `TArray<FGuid> IrrelevantLights_DEPRECATED;` — `UE_DEPRECATED(all, "IrrelevantLights is officially deprecated now")` — `UPROPERTY()` — Legacy irrelevant lights
- L666 _public member_ `int32 LightingLODBias;` — `UPROPERTY(EditAnywhere, Category=LandscapeComponent)` — LOD level Bias to use when lighting building via lightmass, -1 Means automatic LOD calculation based on ForcedLOD + LODBias
- L670 _public member_ `TArray<TObjectPtr<ULandscapeLayerInfoObject>> LayerAllowList;` — `UPROPERTY(EditAnywhere, Category=LandscapeComponent)` — List of layers allowed to be painted on this component
- L674 _public member_ `FLandscapeEditToolRenderData EditToolRenderData;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — Pointer to data shared with the render thread, used by the editor tools
- L678 _public member_ `FGuid MobileDataSourceHash;` — `UPROPERTY(NonPIEDuplicateTransient)` — Hash of source for mobile generated data. Used determine if we need to re-generate mobile pixel data.
- L682 _public member_ `TMap<TObjectPtr<UMaterialInterface>, int8> MaterialPerLOD;` — `UPROPERTY(NonPIEDuplicateTransient)` — Represent the chosen material for each LOD
- L685 _public member_ `uint32 WeightmapsHash;` — Represents hash of last weightmap usage update
- L688 _public member_ `uint32 SplineHash;` — `UPROPERTY()`
- L692 _public member_ `uint32 PhysicalMaterialHash;` — `UPROPERTY()` — Represents hash for last PhysicalMaterialTask
- L696 _public member_ `uint32 LastSavedPhysicalMaterialHash;` — `UPROPERTY(Transient)` — Represents last saved hash for PhysicalMaterialTask
- L700 _public member_ `TObjectPtr<UMaterialInterface> MobileMaterialInterface_DEPRECATED;` — `UE_DEPRECATED(all, "MobileMaterialInterface has been deprecated and will be removed in a future version")` — `UPROPERTY(NonPIEDuplicateTransient)`
- L704 _public member_ `TObjectPtr<UMaterialInstanceConstant> MobileCombinationMaterialInstance_DEPRECATED;` — `UE_DEPRECATED(all, "MobileCombinationMaterialInstance has been deprecated and will be removed in a future version")` — `UPROPERTY(NonPIEDuplicateTransient)`
- L709 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MobileMaterialInterfaces;` — `UPROPERTY(NonPIEDuplicateTransient)` — Material interfaces used for mobile
- L714 _public member_ `TArray<TObjectPtr<UTexture2D>> MobileWeightmapTextures;` — `UPROPERTY(NonPIEDuplicateTransient)` — Generated weightmap textures used for mobile. The first entry is also used for the normal map. Serialized only when cooking or loading cooked builds.
- L717 _public member_ `TObjectPtr<UTexture2DArray> MobileWeightmapTextureArray;` — `UPROPERTY(NonPIEDuplicateTransient)`
- L721 _public member_ `TArray<FWeightmapLayerAllocationInfo> MobileWeightmapLayerAllocations;` — `UPROPERTY()` — Layer allocations used by mobile.
- L727 _public member_ `TArray<TObjectPtr<UMaterialInstanceConstant>> MobileCombinationMaterialInstances;` — `UPROPERTY(NonPIEDuplicateTransient)` — The editor needs to save out the combination MIC we'll use for mobile, because we cannot generate it at runtime for standalone PIE games
- L732 _public member_ `TSharedRef<FLandscapeComponentGrassData, ESPMode::ThreadSafe> GrassData;` — Grass data for generation
- L747 _public member_ `TArray<FExcludeBox> ActiveExcludedBoxes;`
- L748 _public member_ `uint32 ChangeTag;`
- L752 _public member_ `FLandscapePhysicalMaterialRenderTask PhysicalMaterialTask;` — Physical material update task
- L753 _public prototype_ `uint32 CalculatePhysicalMaterialTaskHash() const;`
- L759 _public prototype_ `bool GetRenderPhysicalMaterials(TArray<UPhysicalMaterial*>& OutPhysicalMaterials) const;` — Get the physical materials that are configured by the landscape component graphical material. Returns false if there are no non-null physical materials. (We probably don't want to use if no physical material connections are bound.)
- L763 _public prototype_ `virtual void PostInitProperties() override;`
- L764 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L765 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L766 _public prototype_ `virtual void BeginDestroy() override;`
- L767 _public prototype_ `virtual void PostLoad() override;`
- L769 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L773 _public prototype_ `virtual void BeginCacheForCookedPlatformData(const ITargetPlatform* TargetPlatform) override;`
- L774 _public prototype_ `virtual void PreEditUndo() override;`
- L775 _public prototype_ `virtual void PostEditUndo() override;`
- L776 _public prototype_ `virtual void PreEditChange(FProperty* PropertyThatWillChange) override;`
- L777 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L780 _public prototype_ `void UpdateEditToolRenderData();`
- L783 _public prototype_ `void FixupWeightmaps();` — Fix up component layers, weightmaps
- L784 _public prototype_ `void FixupWeightmaps(const FGuid& InEditLayerGuid);`
- L787 _public prototype_ `TArray<UTexture*> RepairInvalidTextures();` — Repair invalid texture data that might have been introduced by a faulty version. Returns the list of repaired textures
- L790 _public prototype_ `void UpdateLayerAllowListFromPaintedLayers();` — Update layer allow list to include the currently painted layers
- L793 _public prototype_ `virtual bool GetLightMapResolution( int32& Width, int32& Height ) const override;`
- L794 _public prototype_ `virtual int32 GetStaticLightMapResolution() const override;`
- L795 _public prototype_ `virtual void GetLightAndShadowMapMemoryUsage( int32& LightMapMemoryUsage, int32& ShadowMapMemoryUsage ) const override;`
- L796 _public prototype_ `virtual void GetStaticLightingInfo(FStaticLightingPrimitiveInfo& OutPrimitiveInfo,const TArray<ULightComponent*>& InRelevantLights,const FLightingBuildOptions& Options) override;`
- L797 _public prototype_ `virtual void AddMapBuildDataGUIDs(TSet<FGuid>& InGUIDs) const override;`
- L799 _public prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L800 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L801 _public prototype_ `virtual ELightMapInteractionType GetStaticLightingType() const override;`
- L802 _public prototype_ `virtual void GetStreamingRenderAssetInfo(FStreamingTextureLevelContext& LevelContext, TArray<FStreamingRenderAssetPrimitiveInfo>& OutStreamingRenderAssets) const override;`
- L803 _public prototype_ `virtual bool IsPrecomputedLightingValid() const override;`
- L804 _public prototype_ `virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType TeleportType) override;`
- L806 _public prototype_ `virtual TArray<URuntimeVirtualTexture*> const& GetRuntimeVirtualTextures() const override;`
- L807 _public prototype_ `virtual ERuntimeVirtualTextureMainPassType GetVirtualTextureRenderPassType() const override;`
- L810 _public prototype_ `UTexture2D* GetHeightmap(bool InReturnEditingHeightmap = false) const;` — Returns the heightmap for this component. If InReturnEditingHeightmap is passed, returns the currently active edit layer's heightmap :
- L812 _public prototype_ `UTexture2D* GetHeightmap(const FGuid& InLayerGuid) const;` — Returns the heightmap for this component and the edit layer specified by InLayerGuid. If InLayerGuid is invalid, returns the final (base) heightmap :
- L813 _public prototype_ `TArray<TObjectPtr<UTexture2D>>& GetWeightmapTextures(bool InReturnEditingWeightmap = false);`
- L814 _public prototype_ `const TArray<UTexture2D*>& GetWeightmapTextures(bool InReturnEditingWeightmap = false) const;`
- L815 _public prototype_ `TArray<TObjectPtr<UTexture2D>>& GetWeightmapTextures(const FGuid& InLayerGuid);`
- L816 _public prototype_ `const TArray<UTexture2D*>& GetWeightmapTextures(const FGuid& InLayerGuid) const;`
- L817 _public prototype_ `const TArray<UTexture2D*>& GetRenderedWeightmapTexturesForFeatureLevel(ERHIFeatureLevel::Type FeatureLevel) const;`
- L819 _public prototype_ `TArray<FWeightmapLayerAllocationInfo>& GetWeightmapLayerAllocations(bool InReturnEditingWeightmap = false);`
- L820 _public prototype_ `const TArray<FWeightmapLayerAllocationInfo>& GetWeightmapLayerAllocations(bool InReturnEditingWeightmap = false) const;`
- L821 _public prototype_ `TArray<FWeightmapLayerAllocationInfo>& GetWeightmapLayerAllocations(const FGuid& InLayerGuid);`
- L822 _public prototype_ `const TArray<FWeightmapLayerAllocationInfo>& GetWeightmapLayerAllocations(const FGuid& InLayerGuid) const;`
- L824 _public prototype_ `const TArray<UTexture2D*>& GetCurrentRuntimeWeightmapTextures() const;`
- L825 _public prototype_ `TArray<FWeightmapLayerAllocationInfo>& GetCurrentRuntimeWeightmapLayerAllocations();`
- L826 _public prototype_ `const TArray<FWeightmapLayerAllocationInfo>& GetCurrentRuntimeWeightmapLayerAllocations() const;`
- L828 _public function_ `const TArray<FLandscapePerLODMaterialOverride>& GetPerLODOverrideMaterials() const`
- L829 _public function_ `void SetPerLODOverrideMaterials(const TArray<FLandscapePerLODMaterialOverride>& InValue)`
- L831 _public prototype_ `void SetHeightmap(UTexture2D* NewHeightmap);`
- L832 _public prototype_ `void SetWeightmapTextures(const TArray<UTexture2D*>& InNewWeightmapTextures, bool InApplyToEditingWeightmap = false);`
- L833 _public prototype_ `void SetWeightmapTexturesInternal(const TArray<UTexture2D*>& InNewWeightmapTextures, const FGuid& InEditLayerGuid);`
- L836 _public prototype_ `void SetWeightmapLayerAllocations(const TArray<FWeightmapLayerAllocationInfo>& InNewWeightmapLayerAllocations);`
- L837 _public prototype_ `uint32 ComputeLayerHash(bool InReturnEditingHash = true) const;`
- L839 _public prototype_ `void SetWeightmapTexturesUsage(const TArray<ULandscapeWeightmapUsage*>& InNewWeightmapTexturesUsage, bool InApplyToEditingWeightmap = false);`
- L840 _public prototype_ `void SetWeightmapTexturesUsageInternal(const TArray<ULandscapeWeightmapUsage*>& InNewWeightmapTexturesUsage, const FGuid& InEditLayerGuid);`
- L842 _public prototype_ `TArray<TObjectPtr<ULandscapeWeightmapUsage>>& GetWeightmapTexturesUsage(bool InReturnEditingWeightmap = false);`
- L843 _public prototype_ `const TArray<ULandscapeWeightmapUsage*>& GetWeightmapTexturesUsage(bool InReturnEditingWeightmap = false) const;`
- L844 _public prototype_ `TArray<TObjectPtr<ULandscapeWeightmapUsage>>& GetWeightmapTexturesUsage(const FGuid& InLayerGuid);`
- L845 _public prototype_ `const TArray<ULandscapeWeightmapUsage*>& GetWeightmapTexturesUsage(const FGuid& InLayerGuid) const;`
- L846 _public prototype_ `void InitializeLayersWeightmapUsage(const FGuid& InLayerGuid);`
- L848 _public prototype_ `bool HasLayersData() const;`
- L849 _public prototype_ `const FLandscapeLayerComponentData* GetLayerData(const FGuid& InLayerGuid) const;`
- L850 _public prototype_ `FLandscapeLayerComponentData* GetLayerData(const FGuid& InLayerGuid);`
- L852 _public prototype_ `void CopyComponentDataToEditLayer(const FGuid& InSourceEditLayerGuid, const FGuid& InDestEditLayerGuid, bool bInUseObsoleteLayerData, TSet<UTexture2D*>& OutProcessedHeightmaps, TSet<UTexture2D*>& OutProcessedWeightmaps);`
- L855 _public prototype_ `const TMap<FGuid, FLandscapeLayerComponentData>& GetObsoleteEditLayersData() const;` — Obsolete edit layer helpers
- L856 _public prototype_ `const FLandscapeLayerComponentData* GetObsoleteEditLayerData(const FGuid& InLayerGuid) const;`
- L857 _public prototype_ `void RemoveObsoleteEditLayerData(const FGuid& InLayerGuid);`
- L858 _public prototype_ `void InitializeObsoleteEditLayerData(const TSet<FGuid>& InParentEditLayerGuids);`
- L860 _public prototype_ `void AddLayerData(const FGuid& InLayerGuid, const FLandscapeLayerComponentData& InData);`
- L861 _public prototype_ `void AddDefaultLayerData(const FGuid& InLayerGuid, const TArray<ULandscapeComponent*>& InComponentsUsingHeightmap, TMap<UTexture2D*, UTexture2D*>& InOutCreatedHeightmapTextures);`
- L862 _public prototype_ `void RemoveLayerData(const FGuid& InLayerGuid);`
- L863 _public prototype_ `void ForEachLayer(TFunctionRef<void(const FGuid&, struct FLandscapeLayerComponentData&)> Fn);`
- L866 _public prototype_ `FLandscapeLayerComponentData* GetEditingLayer();` — Get the Landscape Actor's editing layer data
- L867 _public prototype_ `const FLandscapeLayerComponentData* GetEditingLayer() const;`
- L870 _public prototype_ `FGuid GetEditingLayerGUID() const;` — Get the Landscape Actor's editing layer GUID
- L872 _public function_ `void SetPendingCollisionDataUpdate(bool bInPendingCollisionDataUpdate)`
- L873 _public function_ `bool GetPendingCollisionDataUpdate() const`
- L874 _public function_ `void SetPendingLayerCollisionDataUpdate(bool bInPendingLayerCollisionDataUpdate)`
- L875 _public function_ `bool GetPendingLayerCollisionDataUpdate() const`
- L877 _public function_ `void SetUndoChangedWeightmapAllocs(bool bInVal)`
- L878 _public function_ `bool GetUndoChangedWeightmapAllocs() const`
- L881 _public prototype_ `virtual bool IsShown(const FEngineShowFlags& ShowFlags) const override;`
- L884 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L885 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;`
- L886 _public prototype_ `virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;`
- L887 _public prototype_ `virtual void PreFeatureLevelChange(ERHIFeatureLevel::Type PendingFeatureLevel) override;`
- L891 _public prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams) override;` — Collect all the PSO precache data used by the landscape component
- L896 _public prototype_ `virtual bool GetMaterialPropertyPath(int32 ElementIndex, UObject*& OutOwner, FString& OutPropertyPath, FProperty*& OutProperty) override;`
- L898 _public prototype_ `virtual void DestroyComponent(bool bPromoteChildren = false) override;`
- L899 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L903 _public prototype_ `virtual void OnRegister() override;`
- L904 _public prototype_ `virtual void OnUnregister() override;`
- L906 _public prototype_ `virtual void InvalidateLightingCacheDetailed(bool bInvalidateBuildEnqueuedLighting, bool bTranslationOnly) override;`
- L908 _public prototype_ `virtual void PropagateLightingScenarioChange() override;`
- L909 _public prototype_ `virtual bool IsHLODRelevant() const override;`
- L913 _public prototype_ `ULandscapeInfo* GetLandscapeInfo() const;` — Gets the landscape info object for this landscape
- L916 _public prototype_ `TArray<ULandscapeGrassType*> GetGrassTypesBP() const;` — `UFUNCTION(BlueprintCallable, Category = "Landscape|Grass", meta=(DisplayName = "GetGrassTypes", Tooltip = "Returns the grass types used by the landscape material on this component"))`
- L920 _public prototype_ `TArray<TObjectPtr<ULandscapeGrassType>> GetGrassTypes() const;` — `UE_DEPRECATED(5.8, "Use GetNamedGrassTypes")` — Returns the array of grass types used by the landscape material. Call UpdateGrassTypes first to ensure this array is up to date.
- L922 _public function_ `const TMap<FName, TObjectPtr<ULandscapeGrassType>>& GetNamedGrassTypes() const`
- L925 _public function_ `void SetNamedGrassTypes(const TMap<FName, TObjectPtr<ULandscapeGrassType>>& InNamedGrassTypes)` — Temporarily sets the grass type for this component. Any call to UpdateGrassTypes may override what has been set using this method.
- L931 _public function_ `bool MaterialHasGrass() const`
- L933 _public function_ `double GetGrassTypesMaxDiscardDistance() const`
- L934 _public function_ `void SetGrassTypesMaxDiscardDistance(const float InGrassTypesMaxDiscardDistance)`
- L937 _public prototype_ `bool UpdateGrassTypes(bool bForceUpdate = false);` — If the LandscapeMaterial has changed, updates the GrassTypes array. Returns true if the GrassTypes array was updated.
- L957 _public prototype_ `ULandscapeHeightmapTextureEdgeFixup* InstallOrUpdateTextureUserDatas(bool bUseEdgeFixup, bool bUseCompression = false, bool bUpdateSnapshotNow = true, int32 HeightmapCompressionMipThreshold = 32);` — Installs new or updates existing TextureUserDatas for this component: up to one ULandscapeHeightmapTextureEdgeFixup and up to one UTextureMipDataProviderFactory (either ULandscapeTextureStorageProviderFactory or ULandscapeTextureMipEdgeOverrideFactory). The edge fixup class ULandscapeHeightmapTextureEdgeFixup is used to store edge snapshots and manage edge blending with neighboring heightmap textures. ULandscapeTextureStorageProviderFactory is used to stream custom-compressed heightmap texture mip data, and it supports also applying edge blending from the edge fixup class while streaming its mips. If bUseEdgeFixup is enabled, but bUseCompression is not, the ULandscapeTextureMipEdgeOverrideFactory is used to apply the edge blending on top of the standard built-in texture mip streaming. This function will ensure an edge fixup class exists if bUseEdgeFixup is true, or it will remove any existing ones otherwise. [EDITOR ONLY] It will capture a new snapshot for the edge fixup, when bUpdateSnapshotNow is true.  Ignored in non-editor builds. [EDITOR ONLY] It will compress heightmaps to a ULandscapeTextureStorageProviderFactory when bUseCompression is true.  Ignored in non-editor builds. NOTE: It will NOT remove an existing one if false -- applying compression is a one-way street, and should only be used in cooked content.
- L961 _public prototype_ `bool DeleteLayerIfAllZero(const FGuid& InEditLayerGuid, const uint8* const TexDataPtr, int32 TexSize, int32 LayerIdx, bool bShouldDirtyPackage);` — Deletes a layer from this component if it does not contain data, calling DeleteLayerAllocation.
- L964 _public prototype_ `void DeleteLayer(ULandscapeLayerInfoObject* LayerInfo, FLandscapeEditDataInterface& LandscapeEdit);` — Deletes a material layer from the current edit layer on this component, removing all its data, adjusting other layer's weightmaps if necessary, etc.
- L967 _public prototype_ `void DeleteLayerInternal(ULandscapeLayerInfoObject* LayerInfo, FLandscapeEditDataInterface& LandscapeEdit, const FGuid& InEditLayerGuid);` — Deletes a material layer from the specified edit layer on this component, removing all its data, adjusting other layer's weightmaps if necessary, etc.
- L970 _public prototype_ `void DeleteLayerAllocation(const FGuid& InEditLayerGuid, int32 InLayerAllocationIdx, bool bInShouldDirtyPackage);` — Deletes a layer from this component, but doesn't do anything else (assumes the user knows what he's doing, use DeleteLayer otherwise)
- L973 _public prototype_ `void FillLayer(ULandscapeLayerInfoObject* LayerInfo, FLandscapeEditDataInterface& LandscapeEdit);` — Fills a layer to 100% on this component, adding it if needed and removing other layers that get painted away.  Uses the edit layer specified by LandscapeEdit.
- L976 _public prototype_ `void ReplaceLayer(ULandscapeLayerInfoObject* FromLayerInfo, ULandscapeLayerInfoObject* ToLayerInfo, FLandscapeEditDataInterface& LandscapeEdit);` — Replaces one layerinfo on this component with another
- L977 _public prototype_ `void ReplaceLayerInternal(ULandscapeLayerInfoObject* FromLayerInfo, ULandscapeLayerInfoObject* ToLayerInfo, FLandscapeEditDataInterface& LandscapeEdit, const FGuid& InEditLayerGUID);`
- L982 _public prototype_ `void RemoveGrassMap();` — Destroys grass map data stored on the component
- L985 _public prototype_ `bool CanRenderGrassMap() const;` — Could a grassmap currently be generated, disregarding whether our textures are streamed in?
- L989 _public prototype_ `uint32 ComputeGrassMapGenerationHash() const;` — Computes a hash representing the state of the material and grasstypes used by this component.
- L992 _public prototype_ `bool IsGrassMapOutdated() const;` — Returns true if the component HAS grass data, but it is not up to date
- L995 _public prototype_ `TArray<uint16> RenderWPOHeightmap(int32 LOD);` — Renders the heightmap of this component (including material world-position-offset) at the specified LOD
- L998 _public prototype_ `void SerializeStateHashes(FArchive& Ar);` — Serialize all hashes/guids that record the current state of this component
- L1001 _public prototype_ `void GenerateMobileWeightmapLayerAllocations();` — Generates mobile platform data for this component
- L1002 _public prototype_ `void GenerateMobilePlatformPixelData(bool bIsCooking, const ITargetPlatform* TargetPlatform);`
- L1005 _public prototype_ `void CheckGenerateMobilePlatformData(bool bIsCooking, const ITargetPlatform* TargetPlatform);` — Generate mobile data if it's missing or outdated
- L1007 _public prototype_ `virtual TSubclassOf<class UHLODBuilder> GetCustomHLODBuilderClass() const override;`
- L1010 _public prototype_ `int32 GetCurrentRuntimeMaterialInstanceCount() const;`
- L1011 _public prototype_ `class UMaterialInterface* GetCurrentRuntimeMaterialInterface(int32 InIndex) const;`
- L1013 _public prototype_ `int32 GetMaterialInstanceCount(bool InDynamic = true) const;`
- L1014 _public prototype_ `class UMaterialInstance* GetMaterialInstance(int32 InIndex, bool InDynamic = true) const;`
- L1018 _public prototype_ `class UMaterialInstanceDynamic* GetMaterialInstanceDynamic(int32 InIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Landscape|Runtime|Material")` — Gets the landscape material instance dynamic for this component
- L1022 _public prototype_ `float EditorGetPaintLayerWeightAtLocation(const FVector& InLocation, ULandscapeLayerInfoObject* PaintLayer);` — `UFUNCTION(BlueprintCallable, Category = "Landscape|Editor")` — Gets the landscape paint layer weight value at the given position using LandscapeLayerInfo . Returns 0 in case it fails.
- L1026 _public prototype_ `float EditorGetPaintLayerWeightByNameAtLocation(const FVector& InLocation, const FName InPaintLayerName);` — `UFUNCTION(BlueprintCallable, Category = "Landscape|Editor")` — Gets the landscape paint layer weight value at the given position using layer name. Returns 0 in case it fails.
- L1029 _public prototype_ `ALandscape* GetLandscapeActor() const;` — Get the landscape actor associated with this component.
- L1032 _public prototype_ `ULevel* GetLevel() const;` — Get the level in which the owning actor resides
- L1036 _public prototype_ `void GetGeneratedTexturesAndMaterialInstances(TArray<UObject*>& OutTexturesAndMaterials) const;` — Returns all generated textures and material instances used by this component.
- L1037 _public prototype_ `TArray<UTexture*> GetGeneratedTextures() const;`
- L1038 _public prototype_ `TArray<UMaterialInstance*> GetGeneratedMaterialInstances() const;`
- L1042 _public prototype_ `ALandscapeProxy* GetLandscapeProxy() const;` — Gets the landscape proxy actor which owns this component
- L1045 _public function_ `FIntPoint GetSectionBase() const` — @return Component section base as FIntPoint
- L1051 _public function_ `FIntPoint GetComponentKey() const` — @return the component's coordinates (aka index, aka component key) in the entire landscape
- L1057 _public prototype_ `FString GetDebugName() const;` — @return a user-friendly name to easily identify this component when dumping debug info, for example
- L1060 _public function_ `void SetSectionBase(FIntPoint InSectionBase)` — @param InSectionBase new section base for a component
- L1071 _public prototype_ `int32 GetNumRelevantMips() const;` — Computes the number of mips that are actually usable, i.e.: - For 1x1 subsection, the last mip is not usable (it has a single vertex) - For 2x2 subsections, the last 2 mips are not usable (a single vertex per subsection)
- L1074 _public function_ `const FGuid& GetLightingGuid() const` — @todo document
- L1085 _public function_ `void SetLightingGuid()` — @todo document
- L1092 _public function_ `FGuid GetMapBuildDataId() const`
- L1097 _public prototype_ `const FMeshMapBuildData* GetMeshMapBuildData() const;`
- L1100 _public prototype_ `void Init(int32 InBaseX, int32 InBaseY, int32 InComponentSizeQuads, int32 InNumSubsections, int32 InSubsectionSizeQuads);` — Initialize the landscape component
- L1103 _public prototype_ `UMaterialInterface* GetLandscapeMaterial(int8 InLODIndex = INDEX_NONE) const;` — Returns the component's LandscapeMaterial, or the Component's OverrideLandscapeMaterial if set
- L1106 _public prototype_ `UMaterialInterface* GetLandscapeHoleMaterial() const;` — Returns the components's LandscapeHoleMaterial, or the Component's OverrideLandscapeHoleMaterial if set
- L1112 _public prototype_ `void RetrieveAllLandscapeMaterials(TSet<UMaterialInterface*>& OutMaterials) const;` — Retrieve the list of all materials that might be used by this landscape component (LandscapeMaterial, LandscapeHoleMaterial, etc.) @param OutMaterials list of unique materials retrieved. The materials found will be appended to the list
- L1114 _public prototype_ `FBox ComputeApproximateBounds();`
- L1120 _public prototype_ `bool UpdateCachedBounds(bool bInApproximateBounds = false);` — Recalculate cached bounds using height values.  Returns true when the bounds were changed.
- L1126 _public prototype_ `void UpdateMaterialInstances();` — Update the MaterialInstance parameters to match the layer and weightmaps for this component Creates the MaterialInstance if it doesn't exist.
- L1127 _public prototype_ `void UpdateMaterialInstances(FMaterialUpdateContext& InOutMaterialContext, TArray<class FComponentRecreateRenderStateContext>& InOutRecreateRenderStateContext);`
- L1130 _public prototype_ `void UpdateMaterialInstances_Internal(FMaterialUpdateContext& Context);` — Internal implementation of UpdateMaterialInstances, not safe to call directly
- L1133 _public prototype_ `UMaterialInstanceConstant* GetCombinationMaterial(FMaterialUpdateContext* InMaterialUpdateContext, const TArray<FWeightmapLayerAllocationInfo>& Allocations, int8 InLODIndex, bool bMobile = false) const;` — Helper function for UpdateMaterialInstance to get Material without set parameters
- L1145 _public prototype_ `void GenerateHeightmapMips(TArray<FColor*>& HeightmapTextureMipData, int32 ComponentX1=0, int32 ComponentY1=0, int32 ComponentX2=MAX_int32, int32 ComponentY2=MAX_int32, FLandscapeTextureDataInfo* TextureDataInfo=nullptr);` — Generate mipmaps for height and tangent data. @param HeightmapTextureMipData - array of pointers to the locked mip data. This should only include the mips that are generated directly from this component's data ie where each subsection has at least 2 vertices. @param ComponentX1 - region of texture to update in component space, MAX_int32 meant end of X component in ALandscape::Import() @param ComponentY1 - region of texture to update in component space, MAX_int32 meant end of Y component in ALandscape::Import() @param ComponentX2 (optional) - region of texture to update in component space @param ComponentY2 (optional) - region of texture to update in component space @param TextureDataInfo - FLandscapeTextureDataInfo pointer, to notify of the mip data region updated.
- L1152 _public prototype_ `static void CreateEmptyTextureMips(UTexture2D* Texture, ELandscapeTextureUsage TextureUsage, ELandscapeTextureType TextureType, bool bClear = false);` — if bClear is true, clears all mips on the specified texture to zero if bClear is false, clears all mips EXCEPT MIP 0 to zero Updates the texture hash appropriately for the given usage and texture type
- L1162 _public prototype_ `static void GenerateMipsTempl(int32 InNumSubsections, int32 InSubsectionSizeQuads, UTexture2D* WeightmapTexture, DataType* BaseMipData);` — @todo document
- L1165 _public prototype_ `static void GenerateWeightmapMips(int32 InNumSubsections, int32 InSubsectionSizeQuads, UTexture2D* WeightmapTexture, FColor* BaseMipData);` — @todo document
- L1173 _public prototype_ `static void UpdateMipsTempl(int32 InNumSubsections, int32 InSubsectionSizeQuads, UTexture2D* WeightmapTexture, TArray<DataType*>& WeightmapTextureMipData, int32 ComponentX1=0, int32 ComponentY1=0, int32 ComponentX2=MAX_int32, int32 ComponentY2=MAX_int32, FLandscapeTextureDataInfo* TextureDataInfo=nullptr);` — @todo document
- L1176 _public prototype_ `static void UpdateWeightmapMips(int32 InNumSubsections, int32 InSubsectionSizeQuads, UTexture2D* WeightmapTexture, TArray<FColor*>& WeightmapTextureMipData, int32 ComponentX1=0, int32 ComponentY1=0, int32 ComponentX2=MAX_int32, int32 ComponentY2=MAX_int32, FLandscapeTextureDataInfo* TextureDataInfo=nullptr);` — @todo document
- L1179 _public prototype_ `static void UpdateDataMips(int32 InNumSubsections, int32 InSubsectionSizeQuads, UTexture2D* Texture, TArray<uint8*>& TextureMipData, int32 ComponentX1=0, int32 ComponentY1=0, int32 ComponentX2=MAX_int32, int32 ComponentY2=MAX_int32, FLandscapeTextureDataInfo* TextureDataInfo=nullptr);` — @todo document
- L1187 _public prototype_ `void UpdateCollisionHeightData(const FColor* HeightmapTextureMipData, const FColor* SimpleCollisionHeightmapTextureData, int32 ComponentX1=0, int32 ComponentY1=0, int32 ComponentX2=MAX_int32, int32 ComponentY2=MAX_int32, bool bUpdateBounds=false, bool bInUpdateHeightfieldRegion=true);` — Create or updates collision component height data @param HeightmapTextureMipData: heightmap data @param ComponentX1, ComponentY1, ComponentX2, ComponentY2: region to update @param bUpdateBounds: Whether to update bounds from render component.
- L1192 _public prototype_ `void DestroyCollisionData();` — Deletes Collision Component
- L1196 _public prototype_ `void UpdateCollisionData(bool bInUpdateHeightfieldRegion = true);` — Updates collision component height data for the entire component, locking and unlocking heightmap textures
- L1199 _public prototype_ `void UpdateDirtyCollisionHeightData(FIntRect Region);` — Cumulates component's dirtied collision region that will need to be updated (used by Layer System)
- L1202 _public prototype_ `void ClearDirtyCollisionHeightData();` — Clears component's dirtied collision region (used by Layer System)
- L1210 _public prototype_ `void UpdateCollisionLayerData(const FColor* const* WeightmapTextureMipData, const FColor* const* const SimpleCollisionWeightmapTextureMipData, int32 ComponentX1=0, int32 ComponentY1=0, int32 ComponentX2=MAX_int32, int32 ComponentY2=MAX_int32);` — Update collision component dominant layer data @param WeightmapTextureMipData: weightmap data @param ComponentX1, ComponentY1, ComponentX2, ComponentY2: region to update @param Whether to update bounds from render component.
- L1215 _public prototype_ `void UpdateCollisionLayerData();` — Update collision component dominant layer data for the whole component, locking and unlocking the weightmap textures.
- L1218 _public prototype_ `void InvalidatePhysicalMaterial();` — Invalidate current or pending physical material data
- L1220 _public prototype_ `bool CanUpdatePhysicalMaterial();` — Returns true if we can currently update physical materials.
- L1222 _public prototype_ `void UpdatePhysicalMaterialTasks();` — Update physical material render tasks.
- L1224 _public prototype_ `void FinalizePhysicalMaterial(bool bInImmediatePhysicsRebuild);` — Write the physical materials into the LandscapeComponent from the Render & Immediately Rebuild physics if requested
- L1226 _public prototype_ `void UpdateCollisionPhysicalMaterialData(TArray<UPhysicalMaterial*> const& InPhysicalMaterials, TArray<uint8> const& InMaterialIds);` — Update collision component physical materials from render task results.
- L1231 _public prototype_ `TArray<UTexture*> ReallocateWeightmaps(FLandscapeEditDataInterface* DataInterface, const FGuid& InEditLayerGuid, bool bInSaveToTransactionBuffer, bool bInForceReallocate, ALandscapeProxy* InTargetProxy, const TSet<ULandscapeComponent*>* InRestrictSharingToComponents);` — Create weightmaps for this component for the layers specified in the WeightmapLayerAllocations array, works in the specified edit layer
- L1234 _public prototype_ `bool IsLandscapeHoleMaterialValid() const;` — Returns true if the component has a valid LandscapeHoleMaterial
- L1237 _public prototype_ `bool ComponentHasVisibilityPainted() const;` — Returns true if this component has visibility painted
- L1239 _public prototype_ `ULandscapeLayerInfoObject* GetVisibilityLayer() const;`
- L1244 _public prototype_ `static FString GetLayerAllocationKey(const TArray<FWeightmapLayerAllocationInfo>& Allocations, UMaterialInterface* LandscapeMaterial, bool bMobile = false);` — Generate a key for a component's layer allocations to use with MaterialInstanceConstantMap.
- L1246 _public prototype_ `bool ValidateCombinationMaterial(UMaterialInstanceConstant* InCombinationMaterial) const;`
- L1249 _public prototype_ `void GetLayerDebugColorKey(int32& R, int32& G, int32& B) const;` — @todo document
- L1252 _public prototype_ `void RemoveInvalidWeightmaps();` — @todo document
- L1253 _public prototype_ `void RemoveInvalidWeightmaps(const FGuid& InEditLayerGuid);`
- L1256 _public prototype_ `void InitHeightmapData(TArray<FColor>& Heights, bool bUpdateCollision);` — @todo document
- L1259 _public prototype_ `void InitWeightmapData(TArray<ULandscapeLayerInfoObject*>& LayerInfos, TArray<TArray<uint8> >& Weights);` — @todo document
- L1262 _public prototype_ `float GetLayerWeightAtLocation( const FVector& InLocation, ULandscapeLayerInfoObject* LayerInfo, TArray<uint8>* LayerCache = NULL, bool bUseEditingWeightmap = false);` — @todo document
- L1265 _public prototype_ `void GetComponentExtent(int32& MinX, int32& MinY, int32& MaxX, int32& MaxY) const;` — Extends passed region with this component's 2D bounds (values are in landscape quads)
- L1268 _public prototype_ `FIntRect GetComponentExtent() const;` — returns the 2D bounds of this component (in landscape quads)
- L1270 _public prototype_ `void ClearUpdateFlagsForModes(uint32 InModeMask);`
- L1271 _public prototype_ `void RequestWeightmapUpdate(bool bUpdateAll = false, bool bUpdateCollision = true, bool bInUserTriggered = false);`
- L1272 _public prototype_ `void RequestHeightmapUpdate(bool bUpdateAll = false, bool bUpdateCollision = true, bool bInUserTriggered = false);`
- L1273 _public prototype_ `void RequestEditingClientUpdate(bool bInUserTriggered = false);`
- L1274 _public prototype_ `void RequestDeferredClientUpdate();`
- L1275 _public function_ `uint32 GetLayerUpdateFlagPerMode() const`
- L1276 _public prototype_ `uint32 ComputeWeightmapsHash();`
- L1278 _public prototype_ `void GetUsedPaintLayers(const FGuid& InLayerGuid, TArray<ULandscapeLayerInfoObject*>& OutUsedLayerInfos) const;`
- L1280 _public prototype_ `void GetLandscapeComponentNeighborsToRender(TSet<ULandscapeComponent*>& NeighborComponents) const;`
- L1281 _public prototype_ `void GetLandscapeComponentWeightmapsToRender(TSet<ULandscapeComponent*>& WeightmapComponents) const;`
- L1282 _public prototype_ `void GetLandscapeComponentNeighbors3x3(TStaticArray<ULandscapeComponent*, 9>& OutNeighborComponents) const;`
- L1286 _public prototype_ `void UpdateNavigationRelevance();` — Updates navigation properties to match landscape actor's
- L1289 _public prototype_ `void UpdateRejectNavmeshUnderneath();` — Updates the reject navmesh underneath flag in the collision component
- L1292 _public prototype_ `void UpdatedSharedPropertiesFromActor();` — Updates the values of component-level properties exposed by the Landscape Actor
- L1297 _public prototype_ `void SetLOD(bool bForced, int32 InLODValue);`
- L1300 _public prototype_ `void SetForcedLOD(int32 InForcedLOD);` — `UFUNCTION(BlueprintCallable, Category = "LandscapeComponent")`
- L1303 _public prototype_ `void SetLODBias(int32 InLODBias);` — `UFUNCTION(BlueprintCallable, Category = "LandscapeComponent")`
- L1305 _public prototype_ `void SetNaniteActive(bool bValue);`
- L1307 _public function_ `inline bool IsNaniteActive() const`
- L1312 _public function_ `ULandscapeHeightfieldCollisionComponent* GetCollisionComponent() const`
- L1313 _public function_ `void SetCollisionComponent(ULandscapeHeightfieldCollisionComponent* InCollisionComponent)`
- L1315 _public function_ `void SetUserTriggeredChangeRequested(bool bInUserTriggeredChangeRequested)`
- L1320 _public function_ `bool GetUserTriggeredChangeRequested() const`
- L1328 _protected prototype_ `void RecreateCollisionComponent(bool bUseSimpleCollision);`
- L1329 _protected prototype_ `void UpdateCollisionHeightBuffer(int32 InComponentX1, int32 InComponentY1, int32 InComponentX2, int32 InComponentY2, int32 InCollisionMipLevel, int32 InHeightmapSizeU, int32 InHeightmapSizeV, const FColor* const InHeightmapTextureMipData, uint16* CollisionHeightData, uint16* GrassHeightData);`
- L1331 _protected prototype_ `void UpdateDominantLayerBuffer(int32 InComponentX1, int32 InComponentY1, int32 InComponentX2, int32 InComponentY2, int32 InCollisionMipLevel, int32 InWeightmapSizeU, int32 InVisibilityLayerIdx, const TArray<uint8*>& InCollisionDataPtrs, const TArray<ULandscapeLayerInfoObject*>& InLayerInfos, uint8* DominantLayerData);`
- L1335 _protected function_ `virtual bool SupportsStaticLighting() const override` — Whether the component type supports static lighting.
- L1343 _public member_ `static uint32 UndoRedoModifiedComponentCount;` — Records the ULandscapeComponents that are modified in any undo/redo operation that is being applied currently
- L1344 _public member_ `static TMap<ULandscapeComponent*, uint32> UndoRedoModifiedComponents;`

#### struct `ULandscapeComponent::FGrassTypeSummary`  
`struct FGrassTypeSummary`  
_L603-608_
- desc: Non-serialized runtime cache of values derived from the assigned grass types. Call ALandscapeProxy::UpdateGrassTypeSummary() to update.
- L605 _public member_ `bool bInvalid = true;`
- L606 _public member_ `bool bHasAnyGrass = true;`
- L607 _public member_ `double MaxInstanceDiscardDistance = DBL_MAX;`

#### struct `ULandscapeComponent::FExcludeBox`  
`struct FExcludeBox`  
_L735-746_
- desc: This wrapper is needed to filter out exclude boxes that are completely inside of another exclude box
- L737 _public member_ `FBox Box;`
- L739 _public prototype_ `FExcludeBox() = default;`
- L740 _public function_ `FExcludeBox(const FBox& InBox) : Box(InBox)`
- L742 _public function_ `bool operator==(const FExcludeBox& Other) const`

#### Free symbols / members of external scopes

- L189 _function_ `inline uint32 GetTypeHash(const FWeightmapLayerAllocationInfo& InAllocInfo)`
- L412 _variable_ `static const uint32 DefaultSplineHash = 0xFFFFFFFF;`

### `Source/Runtime/Landscape/Classes/LandscapeEdgeFixup.h` (Public)


#### enum `UE::Landscape::EDirectionIndex`  
`enum class EDirectionIndex : uint8`  
_L21-43_
- desc: Enumerates directions, for the edges or neighbors of a tile in the the landscape group grid. When specifically referencing an edge or a neighbor, use EEdgeIndex or ENeighborIndex
- L23 _public enumerator_ `Bottom = 0`
- L24 _public enumerator_ `BottomRight = 1`
- L25 _public enumerator_ `Right = 2`
- L26 _public enumerator_ `TopRight = 3`
- L27 _public enumerator_ `Top = 4`
- L28 _public enumerator_ `TopLeft = 5`
- L29 _public enumerator_ `Left = 6`
- L30 _public enumerator_ `BottomLeft = 7`
- L32 _public enumerator_ `First = 0`
- L33 _public enumerator_ `Last = 7`
- L34 _public enumerator_ `Count = 8`
- L36 _public enumerator_ `FirstEdge = 0`
- L37 _public enumerator_ `LastEdge = 6`
- L38 _public enumerator_ `EdgeCount = 4`
- L40 _public enumerator_ `FirstCorner = 1`
- L41 _public enumerator_ `LastCorner = 7`
- L42 _public enumerator_ `CornerCount = 4`

#### enum `UE::Landscape::EDirectionFlags`  
`enum class EDirectionFlags : uint8`  
_L46-61_
- desc: Specifies a set of edges or neighbors.
- L48 _public enumerator_ `Bottom = 0x00000001`
- L49 _public enumerator_ `BottomRight = 0x00000002`
- L50 _public enumerator_ `Right = 0x00000004`
- L51 _public enumerator_ `TopRight = 0x00000008`
- L52 _public enumerator_ `Top = 0x00000010`
- L53 _public enumerator_ `TopLeft = 0x00000020`
- L54 _public enumerator_ `Left = 0x00000040`
- L55 _public enumerator_ `BottomLeft = 0x00000080`
- L57 _public enumerator_ `None = 0`
- L58 _public enumerator_ `AllCorners = BottomRight | TopRight | TopLeft | BottomLeft`
- L59 _public enumerator_ `AllEdges = Bottom | Right | Top | Left`
- L60 _public enumerator_ `All = AllEdges | AllCorners`

#### struct `UE::Landscape::FHeightmapTexel`  
`struct FHeightmapTexel`  
_L68-110_
- L85 _public function_ `uint32 GetHeight16() const`
- L90 _public function_ `void SetHeight16(uint16 NewHeight)`
- L96 _public function_ `void SetNormal(const FVector& NewNormal)`
- L105 _public function_ `bool IsSameHeight(const FHeightmapTexel& Other) const`

#### union `UE::Landscape::FHeightmapTexel::(anonymous)`  
``  
_L73-83_

#### struct `UE::Landscape::FHeightmapTexel::__anon8afc5362010a::(anonymous)`  
``  
_L77-82_

#### struct `UE::Landscape::FNeighborSnapshots`  
`struct FNeighborSnapshots`  
_L113-120_
- desc: states required to perform edge patching
- L115 _public member_ `ENeighborFlags ExistingNeighbors;`
- L116 _public member_ `EEdgeFlags EdgesWithAnyModifiedNeighbor;`
- L117 _public member_ `FHeightmapTextureEdgeSnapshot* NeighborSnapshots[8];`
- L118 _public member_ `FHeightmapTextureEdgeSnapshot* LocalSnapshot;`
- L119 _public member_ `TStaticArray<uint32, 8> GPUEdgeHashes;`

#### struct `FHeightmapTextureEdgeSnapshot`  
`struct FHeightmapTextureEdgeSnapshot`  
_L146-196_
- reflection: `USTRUCT()`
- desc: The snapshots contain a copy of the heightmap edge texels (both height and normal info). It is filled out in editor or at cook time, to make available at runtime for dynamic edge fixup.
- L152 _private member_ `int32 EdgeLength = 0;` — edge length for recorded edge data here - when up to date, should match texture resolution (width AND height)
- L153 _private member_ `TArray<uint32> EdgeData;` — height and normal data for each edge & mip (in heightmap texture format 32bpp). Use GetEdgeData() to access specific edges and mips.
- L154 _private member_ `TStaticArray<uint32, 8> SnapshotEdgeHashes;` — hash of each edge / corner (at full resolution) in the EdgeData
- L155 _private member_ `TStaticArray<uint32, 8> InitialEdgeHashes;` — hash of each edge / corner (at full resolution) in the GPU Texture Resource (at initial unpatched state)
- L158 _private member_ `FGuid TextureSourceID;` — used to detect when this is out of date with texture sourcesource
- L165 _public prototype_ `TArrayView<UE::Landscape::FHeightmapTexel> GetEdgeData(UE::Landscape::EEdgeIndex InEdgeIndex, int32 InMipIndex);` — Return edge snapshot data for this component, for the specified neighbor direction and mip. Horizontal edges are stored left to right, and vertical edges bottom to top.
- L166 _public prototype_ `UE::Landscape::FHeightmapTexel GetCornerData(UE::Landscape::EEdgeIndex InEdgeIndex);`
- L170 _public prototype_ `static TSharedPtr<FHeightmapTextureEdgeSnapshot> CreateEdgeSnapshotFromHeightmapSource(UTexture2D* InHeightmap, const FVector& LandscapeGridScale);` — Create a snapshot from the heightmap source
- L174 _public prototype_ `UE::Landscape::EEdgeFlags CompareEdges(const FHeightmapTextureEdgeSnapshot& OldSnapshot) const;` — Return the set of edges that are different (according to edge hashes) -- i.e. changes that could cause neighbors to patch
- L178 _public function_ `FString GetTextureSourceIDAsString()`
- L188 _private prototype_ `void ResizeForEdgeLength(const int32 InEdgeLength);`
- L192 _private prototype_ `void CaptureEdgeDataFromTextureData_Internal(const TArrayView64<UE::Landscape::FHeightmapTexel>& InHeightmapTextureData, int32 InEdgeLength, const FVector& LandscapeGridScale, const FGuid& InTextureSourceID);` — This function is not thread safe to call on existing snapshots it should only be used on a newly allocated FHeightmapTextureEdgeSnapshot
- L195 _private prototype_ `void CaptureSingleEdgeDataAndComputeNormalsAndHashes(const UE::Landscape::FHeightmapTexel* TextureData, const UE::Landscape::EEdgeIndex EdgeOrCorner, const FVector& LandscapeGridScale);` — must call ResizeForEdgeLength to set the texture size before calling CopyTextureEdgeDataAndRecomputeNormals

#### class `ULandscapeHeightmapTextureEdgeFixup`  
`class ULandscapeHeightmapTextureEdgeFixup : public UAssetUserData`  
_L202-299_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, Within = Texture2D)`
- inherits: `UAssetUserData`
- desc: This UAssetUserData is attached to landscape heightmap UTexture2D's and tracks the heightmap texture's edge fixup state This is used by mip providers to apply edge fixup on mip streaming/creation, and also used by runtime dynamic fixup when neighboring landscape components are pulled in
- L212 _private member_ `TSharedRef<FHeightmapTextureEdgeSnapshot, ESPMode::ThreadSafe> EdgeSnapshot;` — SERIALIZED snapshot of the heightmap edge data COPY-ON-WRITE so we can use it safely from other threads. do not modify an existing snapshot, create a new snapshot and replace this reference.
- L215 _private member_ `TObjectPtr<UTexture2D> HeightmapTexture;` — transient runtime tracking data
- L217 _private member_ `TObjectPtr<ULandscapeComponent> ActiveComponent;` — the active component, that is patching HeightmapTexture
- L218 _private member_ `FLandscapeGroup* ActiveGroup = nullptr;` — the active group, that is patching HeightmapTexture
- L220 _private member_ `TStaticArray<uint32, 8> GPUEdgeHashes;` — hash for the current GPU edge state, initialized on first registration
- L221 _private member_ `UE::Landscape::EEdgeFlags GPUEdgeModifiedFlags =` — edges that have been patched / modified from the initial state
- L225 _private member_ `bool bDoNotPatchUntilGPUEdgeHashesUpdated = false;`
- L226 _private member_ `bool bUpdateGPUEdgeHashes = false;`
- L230 _private member_ `bool bMapped = false;` — per-group settings (apply to the active group/component)
- L231 _private member_ `bool bForceUpdateSnapshot = true;` — set to true initially so that we do a force update on the very first request
- L232 _private member_ `FIntPoint GroupCoord = FIntPoint::ZeroValue;` — coordinate of this heightmap in the active group (when bMapped)
- L238 _private member_ `TArray<TWeakObjectPtr<ULandscapeComponent>> DisabledComponents;` — components that also want to use this heightmap & edge fixup, but were disabled as we can only support one active component at a time. these must be weak object pointers, as they can be unregistered while still in this list, and can be garbage collected out from under us. Note that this array is generally empty except in scenarios where there are multiple active worlds sharing the same landscape textures (PIE) so the expense of accessing the TWeakObjectPtr is a PIE-only cost.
- L241 _public function_ `inline bool IsActive()`
- L242 _public function_ `inline UTexture2D* GetHeightmapTexture()`
- L243 _public function_ `inline bool IsComponentActive(ULandscapeComponent* Component)`
- L244 _public function_ `inline const FIntPoint& GetGroupCoord()`
- L247 _public function_ `inline bool IsTextureEdgePatchingPaused()`
- L248 _public function_ `inline void PauseTextureEdgePatchingUntilGPUEdgeHashesUpdated()`
- L251 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L252 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L255 _public prototype_ `static ULandscapeHeightmapTextureEdgeFixup* FindOrCreateFor(UTexture2D* TargetTexture);` — [main thread] -- Find or Create an edge fixup class for the given heightmap texture.  Will only create in editor (the data used to create is only available in editor)
- L258 _public prototype_ `void SetHeightmapTexture(UTexture2D* InHeightmapTexture);` — set the heightmap texture (can only be called once)
- L262 _public prototype_ `void SetActiveComponent(ULandscapeComponent* InComponent, FLandscapeGroup* InGroup, const bool bDisableCurrentActive = true);` — set the active landscape component, handling unmapping the old, and mapping the new. if bDisableCurrentActive, it will move the current active component, if any, to the disabled list.
- L265 _public prototype_ `void RequestEdgeTexturePatchingForNeighbors(UE::Landscape::ENeighborFlags NeighborsNeedingPatching);` — Request edge texture patching on a set of neighbors.
- L272 _public prototype_ `void RequestEdgeSnapshotUpdateFromHeightmapSource(bool bUpdateGPUEdgeHashes = false);` — Request an update to the edge snapshot (capturing from the heightmap source). When bUpdateGPUEdgeHashes is true, it will also update the GPU Edge Hashes to match. This is set when we know the heightmap source exactly reflects the GPU texture state i.e. after reading back from GPU to CPU after a layer merge, or after UpdateResource().
- L275 _public prototype_ `UE::Landscape::EEdgeFlags UpdateEdgeSnapshotFromHeightmapSource(const FVector& LandscapeGridScale, bool bForceUpdate = false, bool* bOutSuccess = nullptr);` — Update the edge snapshot from heightmap source.  Returns the set of edges that changed since the previous snapshot.
- L280 _public prototype_ `int32 CheckAndPatchTextureEdgesFromEdgeSnapshots();` — Patch the GPU texture edges if needed, using the current snapshot and corresponding neighbor snapshots as source data. Returns the number of edges patched.
- L284 _public prototype_ `void GetNeighborSnapshots(UE::Landscape::FNeighborSnapshots& OutSnapshots);` — Get the set of neighbor snapshots (nullptr if they don't exist), and gather existence and modified flags this is the data necessary to perform patching on a component
- L289 _public prototype_ `static int32 PatchTextureEdgesForSingleMip(int32 MipIndex, FTextureMipInfo& DestMipInfo, const UE::Landscape::FNeighborSnapshots& NeighborSnapshots);` — Patch all of the edges for a single texture mip. Called during streaming operations to patch a newly streamed mip in flight. Returns the number of edges and corners patched
- L290 _public prototype_ `static int32 PatchTextureEdgesForStreamingMips(int32 FirstMipIndexInclusive, int32 LastMipIndexExclusive, FTextureMipInfoArray& DestMipInfos, const UE::Landscape::FNeighborSnapshots& NeighborSnapshots);`
- L293 _private prototype_ `void PatchTextureEdge_Internal(UE::Landscape::EEdgeIndex EdgeIndex);`
- L294 _private prototype_ `void PatchTextureCorner_Internal(UE::Landscape::EEdgeIndex CornerIndex, UE::Landscape::FHeightmapTexel Texel);`
- L297 _private prototype_ `static void BlendEdgeData(FHeightmapTextureEdgeSnapshot& EdgeSnapshot, UE::Landscape::EEdgeIndex EdgeIndex, int32 MipIndex, FHeightmapTextureEdgeSnapshot& NeighborEdgeSnapshot, TStridedView<UE::Landscape::FHeightmapTexel>& OutDestView);` — Helper functions that generate blended edge or corner data from snapshots, to use in texture patching
- L298 _private prototype_ `static void BlendCornerData(UE::Landscape::FHeightmapTexel& OutTexel, UE::Landscape::EEdgeIndex CornerIndex, const UE::Landscape::FNeighborSnapshots& NeighborSnapshots);`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Landscape` (scope `UE`)
- L63 _typedef_ `typedef EDirectionIndex EEdgeIndex;` (scope `UE::Landscape`) — EEdgeIndex specifies an edge or corner on the local landscape component.
- L64 _typedef_ `typedef EDirectionFlags EEdgeFlags;` (scope `UE::Landscape`) — EEdgeFlags specifies a set of edges and corners on the local landscape component.
- L65 _typedef_ `typedef EDirectionIndex ENeighborIndex;` (scope `UE::Landscape`) — ENeighborIndex specifies a neighbor landscape component, relative to a local landscape component.
- L66 _typedef_ `typedef EDirectionFlags ENeighborFlags;` (scope `UE::Landscape`) — ENeighborFlags specifies a set of neighboring landscape components.
- L74 _member_ `uint32 Data32;` (scope `UE::Landscape::FHeightmapTexel::__anon8afc5362010a`)
- L75 _member_ `uint8 Data[4];` (scope `UE::Landscape::FHeightmapTexel::__anon8afc5362010a`)
- L78 _member_ `uint8 NormalX;` (scope `UE::Landscape::FHeightmapTexel::__anon8afc5362010a::__anon8afc53620208`)
- L79 _member_ `uint8 HeightL;` (scope `UE::Landscape::FHeightmapTexel::__anon8afc5362010a::__anon8afc53620208`) — low 8 bits
- L80 _member_ `uint8 HeightH;` (scope `UE::Landscape::FHeightmapTexel::__anon8afc5362010a::__anon8afc53620208`) — high 8 bits
- L81 _member_ `uint8 NormalY;` (scope `UE::Landscape::FHeightmapTexel::__anon8afc5362010a::__anon8afc53620208`)
- L122 _prototype_ `ENUM_RANGE_BY_FIRST_AND_LAST(UE::Landscape::EDirectionIndex, UE::Landscape::EDirectionIndex::First, UE::Landscape::EDirectionIndex::Last);`
- L123 _prototype_ `ENUM_CLASS_FLAGS(UE::Landscape::EDirectionFlags);`
- L125 _namespace_ `namespace UE`
- L125 _namespace_ `namespace Landscape` (scope `UE`)
- L128 _prototype_ `FIntPoint GetNeighborRelativePosition(ENeighborIndex NeighborIndex);` (scope `UE::Landscape`) — Returns the relative offset (in group tile coords) of a neighbor
- L131 _prototype_ `ENeighborFlags EdgesToAffectedNeighbors(EEdgeFlags LocalEdgeFlags);` (scope `UE::Landscape`) — Returns the set of neighbors that blend with any local edge in EdgeFlags
- L134 _prototype_ `EDirectionFlags ToFlag(EDirectionIndex Index);` (scope `UE::Landscape`) — Converts a neighbor index to a neighbor flag (or an edge index to an edge flag)
- L137 _prototype_ `const FString& GetDirectionString(EDirectionIndex Index);` (scope `UE::Landscape`) — Returns a debug string describing the neighbor (or edge) direction

### `Source/Runtime/Landscape/Classes/LandscapeEditLayer.h` (Public)


#### struct `FOnLandscapeEditLayerDataChangedParams`  
`struct FOnLandscapeEditLayerDataChangedParams`  
_L14-35_
- L16 _public function_ `FOnLandscapeEditLayerDataChangedParams(const FPropertyChangedEvent& InPropertyChangedEvent = FPropertyChangedEvent( nullptr)) : PropertyChangedEvent(InPropertyChangedEvent)`
- L21 _public member_ `FPropertyChangedEvent PropertyChangedEvent;` — Provides some additional context about how data has changed (property, type of change...)
- L24 _public member_ `bool bUserTriggered = false;` — Indicates a user-initiated property change
- L27 _public member_ `bool bRequiresLandscapeUpdate = true;` — Indicates the change requires a full landscape update (e.g. parameter affecting heightmap or weightmap...)
- L34 _public member_ `bool bHasValueChanged = true;` — The delegate is triggered each time a data change is requested, even when the data didn't actually change. This indicates that the was actually modified. This can occur for example when several EPropertyChangeType::Interactive changes are triggered because of the user manipulating a slider : this will be followed by a final EPropertyChangeType::ValueSet but when this occurs, the data usually is not actually modified so, to be consistent, we'll still trigger the delegate but indicate that the value didn't actually change, to let the user react appropriately

#### class `ULandscapeEditLayerBase`  
`class ULandscapeEditLayerBase : public UObject #if CPP && WITH_EDITOR , public UE::Landscape::EditLayers::IEditLayerRendererProvider #endif`  
_L42-376_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UObject,UE::Landscape::EditLayers::IEditLayerRendererProvider`
- desc: Base class for all landscape edit layers. By implementing the various virtual functions, we are able to customize the behavior of the edit layer wrt the landscape tools in a generic way (e.g. does it support sculpting tools? painting tools? can it be collapsed?, etc.)
- L112 _public prototype_ `virtual bool SupportsTargetType(ELandscapeToolTargetType InType) const PURE_VIRTUAL(ULandscapeEditLayerBase::SupportsTargetType, return true; );` — @param InType : tool target type (Heightmap, Weightmap, Visibility) @return true if the this edit layer has support for the target type (heightmap, weightmap, visibility)
- L118 _public prototype_ `virtual bool NeedsPersistentTextures() const PURE_VIRTUAL(ULandscapeEditLayerBase::NeedsPersistentTextures, return false; );` — @return true if the edit layer can store heightmaps/weightmaps in the ALandscapeProxy (e.g. should return false for purely procedural layers, to avoid allocating textures)
- L124 _public prototype_ `virtual bool SupportsEditingTools() const PURE_VIRTUAL(ULandscapeEditLayerBase::SupportsEditingTools, return true; );` — @return true if the edit layer can be manually edited via the landscape editing tools :
- L130 _public prototype_ `virtual bool SupportsMultiple() const PURE_VIRTUAL(ULandscapeEditLayerBase::SupportsMultiple, return true; );` — @return true if it's allowed to have more than one edit layer of this type at a time
- L136 _public prototype_ `virtual bool SupportsBeingCollapsedAway() const PURE_VIRTUAL(ULandscapeEditLayerBase::SupportsBeingCollapsedAway, return true; );` — @return true if the layer supports a layer above being collapsed onto it
- L142 _public prototype_ `virtual bool SupportsCollapsingTo() const PURE_VIRTUAL(ULandscapeEditLayerBase::SupportsCollapsingTo, return true; );` — @return true if the layer supports being collapsed onto a layer underneath
- L148 _public prototype_ `virtual bool SupportsBlueprintBrushes() const PURE_VIRTUAL(ULandscapeEditLayerBase::SupportsBlueprintBrushes(), return false; );` — @return true if the layer supports blueprint brushes
- L154 _public prototype_ `virtual FString GetDefaultName() const PURE_VIRTUAL(ULandscapeEditLayerBase::GetDefaultName, return FString(); );` — @return the default name to use when creating a new layer of this type
- L162 _public prototype_ `virtual bool SupportsAlphaForTargetType(ELandscapeToolTargetType InType) const;` — @param InType : tool target type (Heightmap, Weightmap, Visibility) @return true if the layer supports alpha for a given target type
- L171 _public prototype_ `virtual void SetAlphaForTargetType(ELandscapeToolTargetType InType, float InNewValue, bool bInModify, EPropertyChangeType::Type InChangeType);` — Sets the alpha value for a given target type @param InType : the type of target (Heightmap, Weightmap) on which to set the alpha @param InNewValue : the new alpha value @param bInModify : true when Modify() needs to be called @param InChangeType : type of change (normal, interactive, ...)
- L178 _public prototype_ `virtual float GetAlphaForTargetType(ELandscapeToolTargetType InType) const;` — Gets the alpha value for a given target type @param InType : tool target type (Heightmap, Weightmap, Visibility) @return the alpha value for a given target type
- L183 _public prototype_ `virtual FFloatInterval GetAlphaRangeForTargetType(ELandscapeToolTargetType InType) const;` — @return the valid alpha value interval for a given target type
- L190 _public prototype_ `virtual void SetGuid(const FGuid& InGuid, bool bInModify);` — Sets the layer's Guid value @param InGuid : the new Guid value @param bInModify : true when Modify() needs to be called
- L192 _public prototype_ `virtual const FGuid& GetGuid() const;`
- L199 _public prototype_ `virtual void SetName(FName InName, bool bInModify);` — Sets the layer's Name value @param InName : the new Name value @param bInModify : true when Modify() needs to be called
- L201 _public prototype_ `virtual FName GetName() const;`
- L208 _public prototype_ `virtual void SetVisible(bool bInVisible, bool bInModify);` — Sets the layer's visibility value @param bInVisible : true to set visible, false to set invisible @param bInModify : true when Modify() needs to be called
- L210 _public prototype_ `virtual bool IsVisible() const;`
- L217 _public prototype_ `virtual void SetLocked(bool bInLocked, bool bInModify);` — Sets the layer's locked value @param bInLocked : true to lock layer, false to unlock @param bInModify : true when Modify() needs to be called
- L219 _public prototype_ `virtual bool IsLocked() const;`
- L225 _public prototype_ `UE_INTERNAL virtual ELandscapeBlendMode GetBlendMode() const;` — @return the layer's BlendMode - LSBM_AdditiveBlend by default Marked as UE_INTERNAL to prevent external usage before blend refactor with the introduction of blend groups and premultiplied alpha blending
- L234 _public prototype_ `UE_INTERNAL virtual bool RemoveAndCopyWeightmapAllocationLayerBlend(TObjectPtr<ULandscapeLayerInfoObject> InKey, bool& bOutValue, bool bInModify);` — Remove and Copy a weightmap layer allocation for a given LayerInfoObj @param InKey : the ULandscapeLayerInfoObj key to be removed @param bOutValue: the layer allocation value stored in the map for InKey @param bInModify : true when Modify() needs to be called Marked as UE_INTERNAL to prevent external usage before blend refactor with the introduction of blend groups and premultiplied alpha blending
- L243 _public prototype_ `UE_INTERNAL virtual void AddOrUpdateWeightmapAllocationLayerBlend(TObjectPtr<ULandscapeLayerInfoObject> InKey, bool InValue, bool bInModify);` — Updates the value of an existing layer allocation or adds a weightmap layer allocation if no entry is found @param InKey : the ULandscapeLayerInfoObj map key @param bInValue: the new allocation value @param bInModify : true when Modify() needs to be called Marked as UE_INTERNAL to prevent external usage before blend refactor with the introduction of blend groups and premultiplied alpha blending
- L249 _public prototype_ `UE_INTERNAL virtual const TMap<TObjectPtr<ULandscapeLayerInfoObject>, bool>& GetWeightmapLayerAllocationBlend() const;` — @return the layer's weightmap layer allocation blend map. Layers do not have an entry in the map until a user sets the blend mode (selects Subtractive) Marked as UE_INTERNAL to prevent external usage before blend refactor with the introduction of blend groups and premultiplied alpha blending
- L257 _public prototype_ `UE_INTERNAL virtual void SetWeightmapLayerAllocationBlend(const TMap<TObjectPtr<ULandscapeLayerInfoObject>, bool>& InWeightmapLayerAllocationBlend, bool bInModify);` — Sets the layers WeightmapLayerAllocation map @param InWeightmapLayerAllocationBlend : the new WeightmapLayerAllocation map @param bInModify : true when Modify() needs to be called Marked as UE_INTERNAL to prevent external usage before blend refactor with the introduction of blend groups and premultiplied alpha blending
- L267 _public prototype_ `FName GetNameBP() const;` — `UFUNCTION(BlueprintCallable, DisplayName = GetName, Category = "Landscape|Editor", meta = (DevelopmentOnly))` — @return the name of the edit layer (editor-only : returns an invalid name at runtime)
- L271 _public function_ `virtual TArray<FEditLayerAction> GetActions() const PRAGMA_ENABLE_DEPRECATION_WARNINGS` — `UE_DEPRECATED(5.7, "Register custom context menu actions using RegisterCustomEditLayerClassLayout from ILandscapeEditorModule")`
- L282 _public function_ `virtual void GetRenderDependencies(TSet<UObject*>& OutDependencies) const` — @return a list of UObjects that this layers needs in order to render properly. This is necessary to avoid trying to render a layer while some of its resources are not fully ready. These can be UTexture (requires all mips to be fully loaded) or UMaterialInterface (requires shader maps to be fully compiled)
- L288 _public function_ `virtual void OnLayerRemoved()` — Called by landscape after removing this layer from its list so that the layer can do any cleanup that it might need to do. TODO: Should this be protected and then we friend ALandscape?
- L295 _public function_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRendererState> GetEditLayerRendererStates(const UE::Landscape::EditLayers::FMergeContext* InMergeContext)` — By default this does nothing in a landscape edit layer, but subclasses can override it if they would like to provide additional renderers.
- L300 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLayerDataChanged, const FOnLandscapeEditLayerDataChangedParams& );` — Delegate triggered whenever a change occurred on the edit layer's data
- L301 _public function_ `FOnLayerDataChanged::RegistrationType& OnLayerDataChanged() const`
- L309 _public prototype_ `virtual ELandscapeToolTargetTypeFlags GetEnabledTargetTypeMask() const;` — @return the mask of the target types currently enabled on this edit layer
- L315 _protected prototype_ `virtual void PostLoad() override;`
- L316 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L317 _protected prototype_ `virtual void PostEditUndo() override;`
- L318 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L324 _protected prototype_ `void SetGuidInternal(const FGuid& InGuid);` — `UPROPERTY(should be used for blueprint setters eventually)`
- L325 _protected prototype_ `void SetNameInternal(FName InName);`
- L326 _protected prototype_ `void SetVisibleInternal(bool bInVisible);`
- L327 _protected prototype_ `void SetLockedInternal(bool bInLocked);`
- L328 _protected prototype_ `void SetHeightmapAlphaInternal(float InNewValue);`
- L329 _protected prototype_ `void SetWeightmapAlphaInternal(float InNewValue);`
- L331 _protected prototype_ `UE_INTERNAL void SetWeightmapLayerAllocationBlendInternal(const TMap<TObjectPtr<ULandscapeLayerInfoObject>, bool>& InWeightmapLayerAllocationBlend);` — Marked as UE_INTERNAL to prevent external usage before blend refactor with the introduction of blend groups and premultiplied alpha blending
- L336 _protected prototype_ `float& GetAlphaForTargetTypeRef(ELandscapeToolTargetType InType);` — Internal function that returns a reference to the alpha value corresponding to a given target type (HeightmapAlpha, WeightmapAlpha, ...)
- L338 _protected prototype_ `FProperty* GetAlphaPropertyForTargetType(ELandscapeToolTargetType InType) const;` — Internal function that returns the alpha FProperty corresponding to a given target type (HeightmapAlpha, WeightmapAlpha, ...)
- L340 _protected prototype_ `void BroadcastOnLayerDataChanged(const FPropertyChangedEvent& InPropertyChangeEvent, bool bInUserTriggered, bool bRequiresLandscapeUpdate, bool bInHasValueChanged);` — Internal function meant to be called whenever the edit layer data changes, broadcast the OnLayerDataChanged event
- L345 _protected member_ `FGuid Guid = FGuid::NewGuid();` — `UPROPERTY(Setter = "SetGuidInternal", meta = (EditCondition = "!bLocked"))`
- L348 _protected member_ `FName LayerName = NAME_None;` — `UPROPERTY(Setter = "SetNameInternal", meta = (EditCondition = "!bLocked"))`
- L351 _protected member_ `bool bVisible = true;` — `UPROPERTY(Category = "Edit Layer", EditAnywhere, Setter = "SetVisibleInternal", meta = (EditCondition = "!bLocked"))`
- L354 _protected member_ `bool bLocked = false;` — `UPROPERTY(Category = "Edit Layer", EditAnywhere, Setter = "SetLockedInternal")`
- L357 _protected member_ `float HeightmapAlpha = 1.0f;` — `UPROPERTY(Category = "Edit Layer", EditAnywhere, Setter = "SetHeightmapAlphaInternal", meta = (UIMin = "-1.0", UIMax = "1.0", ClampMin = "-1.0", ClampMax = "1.0", EditCondition = "!bLocked"))`
- L360 _protected member_ `float WeightmapAlpha = 1.0f;` — `UPROPERTY(Category = "Edit Layer", EditAnywhere, Setter = "SetWeightmapAlphaInternal", meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0", EditCondition = "!bLocked"))`
- L364 _protected member_ `TWeakObjectPtr<ALandscape> OwningLandscape;` — `UPROPERTY()` — TODO: This might be removed once more things are moved from FLandscapeLayer to ULandscapeLayer
- L369 _private prototype_ `void SetBackPointer(ALandscape* Landscape);`
- L371 _private member_ `mutable FOnLayerDataChanged OnLayerDataChangedDelegate;`
- L374 _private member_ `TMap<TObjectPtr<ULandscapeLayerInfoObject>, bool> WeightmapLayerAllocationBlend;` — `UPROPERTY(Setter = "SetWeightmapLayerAllocationBlendInternal", meta = (EditCondition = "!bLocked"))` — True -> Substractive, False -> Add

#### class `ULandscapeEditLayerBase::FEditLayerAction`  
`class UE_DEPRECATED(5.7, "Expose custom actions to the editor with IEditLayerCustomization and RegisterCustomEditLayerClassLayout") FEditLayerAction`  
_L50-105_
- L52 _private prototype_ `FEditLayerAction() = delete;`
- L88 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FExecuteResult, FExecuteDelegate, const FExecuteParams& );`
- L89 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanExecuteDelegate, const FExecuteParams& , FText& );`
- L91 _public function_ `FEditLayerAction(const FText& InLabel, const FExecuteDelegate& InExecuteDelegate, const FCanExecuteDelegate& InCanExecuteDelegate) : Label(InLabel) , ExecuteDelegate(InExecuteDelegate) , CanExecuteDelegate(InCanExecuteDelegate)`
- L97 _public function_ `inline const FText& GetLabel() const`
- L98 _public function_ `inline const FExecuteDelegate& GetExecuteDelegate() const`
- L99 _public function_ `inline const FCanExecuteDelegate& GetCanExecuteDelegate() const`
- L102 _private member_ `FText Label;`
- L103 _private member_ `FExecuteDelegate ExecuteDelegate;`
- L104 _private member_ `FCanExecuteDelegate CanExecuteDelegate;`

#### class `ULandscapeEditLayerBase::FEditLayerAction::FExecuteParams`  
`class UE_DEPRECATED(5.7, "Expose custom actions to the editor with IEditLayerCustomization and RegisterCustomEditLayerClassLayout") FExecuteParams`  
_L55-74_
- L57 _private prototype_ `FExecuteParams() = delete;`
- L60 _public function_ `FExecuteParams(const ULandscapeEditLayerBase* InEditLayer, ALandscape* InLandscape) : EditLayer(InEditLayer) , Landscape(InLandscape)`
- L67 _public function_ `inline const ULandscapeEditLayerBase* GetEditLayer() const`
- L68 _public function_ `inline ALandscape* GetLandscape() const`
- L71 _private member_ `const ULandscapeEditLayerBase* EditLayer = nullptr;`
- L72 _private member_ `const FLandscapeLayer* Layer = nullptr;`
- L73 _private member_ `ALandscape* Landscape = nullptr;`

#### struct `ULandscapeEditLayerBase::FEditLayerAction::FExecuteResult`  
`struct UE_DEPRECATED(5.7, "Expose custom actions to the editor with IEditLayerCustomization and RegisterCustomEditLayerClassLayout") FExecuteResult`  
_L76-86_
- L78 _public prototype_ `FExecuteResult() = default;`
- L79 _public function_ `FExecuteResult(bool bInSuccess, const FText& InReason = FText()) : bSuccess(bInSuccess) , Reason(InReason)`
- L84 _public member_ `bool bSuccess = true;`
- L85 _public member_ `FText Reason;`

#### class `ULandscapeEditLayerPersistent`  
`class ULandscapeEditLayerPersistent : public ULandscapeEditLayerBase , public ILandscapeEditLayerRenderer`  
_L382-405_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `ULandscapeEditLayerBase,ILandscapeEditLayerRenderer`
- desc: Base class for persistent layers, i.e. layers that have a set of backing textures (heightmaps, weightmaps) and can therefore be rendered in a similar fashion
- L389 _public function_ `virtual bool NeedsPersistentTextures() const override`
- L390 _public function_ `virtual bool SupportsCollapsingTo() const override` — If the layer has persistent textures, it can be collapsed to another layer (one that supports being collapsed away, that is)
- L391 _public function_ `virtual bool SupportsBlueprintBrushes() const override`
- L396 _public prototype_ `virtual void GetRendererStateInfo(const UE::Landscape::EditLayers::FMergeContext* InMergeContext, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutSupportedTargetTypeState, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutEnabledTargetTypeState, TArray<UE::Landscape::EditLayers::FTargetLayerGroup>& OutTargetLayerGroups) const override;`
- L398 _public prototype_ `virtual UE::Landscape::EditLayers::ERenderFlags GetRenderFlags(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L399 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRenderItem> GetRenderItems(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L400 _public prototype_ `virtual bool RenderLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override;`
- L401 _public prototype_ `virtual void BlendLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override;`
- L402 _public prototype_ `virtual FString GetEditLayerRendererDebugName() const override;`

#### class `ULandscapeEditLayer`  
`class ULandscapeEditLayer : public ULandscapeEditLayerPersistent`  
_L411-427_
- reflection: `UCLASS(MinimalAPI, meta = (ShortToolTip = "Standard edit layer"))`
- inherits: `ULandscapeEditLayerPersistent`
- desc: This is the standard type of edit layer. It can be manually authored (sculpted, painted, etc.) in the landscape editor
- L417 _public prototype_ `virtual bool SupportsTargetType(ELandscapeToolTargetType InType) const override;`
- L418 _public function_ `virtual bool SupportsEditingTools() const override`
- L419 _public function_ `virtual bool SupportsMultiple() const override`
- L420 _public function_ `virtual bool SupportsBeingCollapsedAway() const override`
- L421 _public function_ `virtual bool SupportsBlueprintBrushes() const override`
- L422 _public function_ `virtual FString GetDefaultName() const`

#### class `ULandscapeEditLayerProcedural`  
`class ULandscapeEditLayerProcedural : public ULandscapeEditLayerBase`  
_L433-444_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `ULandscapeEditLayerBase`
- desc: Base class for procedural layers. Procedural layers cannot be edited through standard editing tools
- L439 _public function_ `virtual bool SupportsEditingTools() const override` — procedural layers cannot be edited through standard editing tools
- L440 _public function_ `virtual bool SupportsCollapsingTo() const override` — for now, don't support collapsing to a layer underneath for a procedural layer (this may become unneeded if we make the collapse happen on the GPU)
- L441 _public function_ `virtual bool SupportsBeingCollapsedAway() const override` — this is a procedural and therefore cannot be collapsed
- L442 _public function_ `virtual bool SupportsBlueprintBrushes() const override`

#### class `ULandscapeEditLayerSplines`  
`class ULandscapeEditLayerSplines : public ULandscapeEditLayerPersistent`  
_L450-471_
- reflection: `UCLASS(MinimalAPI, meta = (ShortToolTip = "Special edit layer for landscape splines"))`
- inherits: `ULandscapeEditLayerPersistent`
- desc: Procedural edit layer that lets the user manipulate its content using landscape splines (Splines tool in the Manage panel)
- L456 _public function_ `virtual bool SupportsEditingTools() const override` — procedural layers cannot be edited through standard editing tools
- L457 _public prototype_ `virtual bool SupportsTargetType(ELandscapeToolTargetType InType) const override;`
- L458 _public function_ `virtual bool NeedsPersistentTextures() const override` — it's a layer computed on the CPU and outputting to persistent textures
- L459 _public function_ `virtual bool SupportsMultiple() const override` — only one layer of this type is allowed
- L460 _public function_ `virtual bool SupportsBeingCollapsedAway() const override` — this is a procedural and therefore cannot be collapsed
- L461 _public function_ `virtual FString GetDefaultName() const override`
- L463 _public function_ `virtual ELandscapeBlendMode GetBlendMode() const override`
- L464 _public function_ `bool SupportsAlphaForTargetType(ELandscapeToolTargetType InType) const override`
- L465 _public function_ `virtual float GetAlphaForTargetType(ELandscapeToolTargetType InType) const override`
- L466 _public function_ `virtual void SetAlphaForTargetType(ELandscapeToolTargetType InType, float InNewValue, bool bInModify, EPropertyChangeType::Type InChangeType) override`

#### Free symbols / members of external scopes

- L88 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FExecuteResult, FExecuteDelegate, const FExecuteParams& );`
- L89 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FCanExecuteDelegate, const FExecuteParams& , FText& );`
- L300 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLayerDataChanged, const FOnLandscapeEditLayerDataChangedParams& );` — Delegate triggered whenever a change occurred on the edit layer's data

### `Source/Runtime/Landscape/Classes/LandscapeGizmoActiveActor.h` (Public)


#### enum `ELandscapeGizmoType`  
`enum ELandscapeGizmoType : int`  
_L19-25_
- reflection: `UENUM()`
- L21 _public enumerator_ `LGT_None`
- L22 _public enumerator_ `LGT_Height`
- L23 _public enumerator_ `LGT_Weight`
- L24 _public enumerator_ `LGT_MAX`

#### enum `ELandscapeGizmoSnapType`  
`enum class ELandscapeGizmoSnapType`  
_L28-38_
- reflection: `UENUM()`
- L31 _public enumerator_ `None` — No snapping of the gizmo
- L34 _public enumerator_ `Component` — Snap the gizmo to the closest landscape component bounds
- L37 _public enumerator_ `Texel` — Snap the gizmo to the closest landscape texel (vertex)

#### struct `FGizmoSelectData`  
`struct FGizmoSelectData`  
_L41-64_
- reflection: `USTRUCT()`
- L47 _public member_ `float Ratio;` — `UPROPERTY()`
- L50 _public member_ `float HeightData;` — `UPROPERTY()`
- L53 _public member_ `TMap<ULandscapeLayerInfoObject*, float> WeightDataMap;`
- L55 _public function_ `FGizmoSelectData() #if WITH_EDITORONLY_DATA : Ratio(0.0f) , HeightData(0.0f) , WeightDataMap() #endif`

#### class `ALandscapeGizmoActiveActor`  
`class ALandscapeGizmoActiveActor : public ALandscapeGizmoActor`  
_L67-216_
- reflection: `UCLASS(notplaceable, MinimalAPI)`
- inherits: `ALandscapeGizmoActor`
- L76 _private member_ `TObjectPtr<UTexture2D> GizmoTexture;` — `UPROPERTY(Transient)`
- L79 _private member_ `FVector2D TextureScale;` — `UPROPERTY()`
- L82 _private member_ `TArray<FVector> SampledHeight;` — `UPROPERTY()`
- L85 _private member_ `TArray<FVector> SampledNormal;` — `UPROPERTY()`
- L88 _private member_ `int32 SampleSizeX;` — `UPROPERTY()`
- L91 _private member_ `int32 SampleSizeY;` — `UPROPERTY()`
- L94 _private member_ `float CachedWidth;` — `UPROPERTY()`
- L97 _private member_ `float CachedHeight;` — `UPROPERTY()`
- L100 _private member_ `float CachedScaleXY;` — `UPROPERTY()`
- L103 _private member_ `FVector FrustumVerts[8];` — `UPROPERTY(Transient)`
- L106 _private member_ `TObjectPtr<UMaterial> GizmoMaterial;` — `UPROPERTY()`
- L109 _private member_ `TObjectPtr<UMaterialInstance> GizmoDataMaterial;` — `UPROPERTY()`
- L112 _private member_ `TObjectPtr<UMaterial> GizmoMeshMaterial;` — `UPROPERTY()`
- L115 _private member_ `TArray<TObjectPtr<ULandscapeLayerInfoObject>> LayerInfos;` — `UPROPERTY(Category=LandscapeGizmoActiveActor, VisibleAnywhere)`
- L118 _private member_ `ELandscapeGizmoSnapType SnapType = ELandscapeGizmoSnapType::None;` — `UPROPERTY(transient)`
- L121 _private member_ `bool bFollowTerrainHeight = true;` — `UPROPERTY(transient)`
- L124 _private member_ `FRotator UnsnappedRotation;` — `UPROPERTY(transient)`
- L128 _public member_ `TMap<FIntPoint, FGizmoSelectData> SelectedData;`
- L132 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L133 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L136 _public prototype_ `virtual FVector SnapToLandscapeGrid(const FVector& GizmoLocation) const;`
- L137 _public prototype_ `virtual FRotator SnapToLandscapeGrid(const FRotator& GizmoRotation) const;`
- L139 _public prototype_ `virtual void EditorApplyTranslation(const FVector& DeltaTranslation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;`
- L140 _public prototype_ `virtual void EditorApplyRotation(const FRotator& DeltaRotation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;`
- L141 _public prototype_ `virtual void EditorApplyScale(const FVector& DeltaScale, const FVector* PivotLocation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;`
- L148 _public prototype_ `ALandscapeGizmoActor* SpawnGizmoActor();` — Whenever the decal actor has moved: - Copy the actor rot/pos info over to the decal component - Trigger updates on the decal component to recompute its matrices and generate new geometry.
- L151 _public prototype_ `void ClearGizmoData();` — @todo document
- L154 _public prototype_ `void FitToSelection();` — @todo document
- L157 _public prototype_ `void FitMinMaxHeight();` — @todo document
- L160 _public prototype_ `void SetTargetLandscape(ULandscapeInfo* LandscapeInfo);` — @todo document
- L163 _public prototype_ `void CalcNormal();` — @todo document
- L166 _public prototype_ `void SampleData(int32 SizeX, int32 SizeY);` — @todo document
- L169 _public prototype_ `void ExportToClipboard();` — @todo document
- L172 _public prototype_ `void ImportFromClipboard();` — @todo document
- L175 _public prototype_ `void Import(int32 VertsX, int32 VertsY, uint16* HeightData, TArray<ULandscapeLayerInfoObject*> ImportLayerInfos, uint8* LayerDataPointers[] );` — @todo document
- L178 _public prototype_ `void Export(int32 Index, TArray<FString>& Filenames);` — @todo document
- L181 _public prototype_ `float GetNormalizedHeight(uint16 LandscapeHeight) const;` — @todo document
- L184 _public prototype_ `float GetLandscapeHeight(float NormalizedHeight) const;` — @todo document
- L187 _public function_ `float GetWidth() const` — @todo document
- L193 _public function_ `float GetHeight() const` — @todo document
- L199 _public function_ `float GetLength() const` — @todo document
- L205 _public function_ `void SetLength(float WorldLength)` — @todo document
- L210 _public member_ `static const int32 DataTexSize = 128;`
- L214 _private prototype_ `FORCEINLINE float GetWorldHeight(float NormalizedHeight) const;` — @todo document

### `Source/Runtime/Landscape/Classes/LandscapeGizmoActor.h` (Public)


#### class `ALandscapeGizmoActor`  
`class ALandscapeGizmoActor : public AActor`  
_L15-65_
- reflection: `UCLASS(notplaceable, MinimalAPI, NotBlueprintable)`
- inherits: `AActor`
- L21 _private member_ `float Width;` — `UPROPERTY(EditAnywhere, Category=Gizmo)`
- L24 _private member_ `float Height;` — `UPROPERTY(EditAnywhere, Category=Gizmo)`
- L27 _private member_ `float LengthZ;` — `UPROPERTY(EditAnywhere, Category=Gizmo)`
- L30 _private member_ `float MarginZ;` — `UPROPERTY(EditAnywhere, Category=Gizmo)`
- L33 _private member_ `float MinRelativeZ;` — `UPROPERTY(EditAnywhere, Category=Gizmo)`
- L36 _private member_ `float RelativeScaleZ;` — `UPROPERTY(EditAnywhere, Category=Gizmo)`
- L39 _private member_ `TWeakObjectPtr<ULandscapeInfo> TargetLandscapeInfo;` — `UPROPERTY(EditAnywhere, transient, Category=Gizmo)`
- L43 _private member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY()`
- L49 _public function_ `virtual bool ShouldExport() override` — Prevent copy-pasting
- L50 _public prototype_ `virtual void Duplicate(ALandscapeGizmoActor* Gizmo);`
- L52 _public function_ `bool EditorCanAttachTo(const AActor* InParent, FText& OutReason) const override`
- L58 _public function_ `virtual bool IsLevelBoundsRelevant() const override` — Indicates whether this actor should participate in level bounds calculations
- L63 _public prototype_ `UBillboardComponent* GetSpriteComponent() const;` — Returns SpriteComponent subobject

### `Source/Runtime/Landscape/Classes/LandscapeGizmoRenderComponent.h` (Public)


#### class `ULandscapeGizmoRenderComponent`  
`class ULandscapeGizmoRenderComponent : public UPrimitiveComponent`  
_L14-27_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UPrimitiveComponent`
- L19 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L21 _private prototype_ `virtual void GetUsedMaterials(TArray<UMaterialInterface*>& OutMaterials, bool bGetDebugMaterials = false) const override;`
- L25 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`

### `Source/Runtime/Landscape/Classes/LandscapeGrassType.h` (Public)


#### enum `EGrassScaling`  
`enum class EGrassScaling : uint8`  
_L20-28_
- reflection: `UENUM()`
- L23 _public enumerator_ `Uniform` — Grass instances will have uniform X, Y and Z scales.
- L25 _public enumerator_ `Free` — Grass instances will have random X, Y and Z scales.
- L27 _public enumerator_ `LockXY` — X and Y will be the same random scale, Z will be another

#### struct `FGrassVariety`  
`struct FGrassVariety`  
_L31-168_
- reflection: `USTRUCT(BlueprintType)`
- L35 _public prototype_ `FGrassVariety();`
- L38 _public member_ `TObjectPtr<UStaticMesh> GrassMesh;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass)`
- L41 _public member_ `TArray<TObjectPtr<class UMaterialInterface>> OverrideMaterials;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass, meta = (ToolTip = "Material Overrides."))`
- L45 _public member_ `FPerPlatformFloat GrassDensity;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass, meta = (UIMin = 0, ClampMin = 0, UIMax = 1000, ClampMax = 1000))` — Instances per 10 square meters.
- L48 _public member_ `FPerQualityLevelFloat GrassDensityQuality;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass, meta = (UIMin = 0, ClampMin = 0, UIMax = 1000, ClampMax = 1000))`
- L52 _public member_ `bool bUseGrid;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass)` — If true, use a jittered grid sequence for placement, otherwise use a halton sequence.
- L55 _public member_ `float PlacementJitter;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass, meta = (EditCondition = "bUseGrid", UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))`
- L59 _public member_ `FPerPlatformInt StartCullDistance;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass, meta = (UIMin = 0, ClampMin = 0, UIMax = 1000000, ClampMax = 1000000))` — The distance where instances will begin to fade out if using a PerInstanceFadeAmount material node. 0 disables.
- L62 _public member_ `FPerQualityLevelInt StartCullDistanceQuality;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass, meta = (UIMin = 0, ClampMin = 0, UIMax = 1000000, ClampMax = 1000000))`
- L69 _public member_ `FPerPlatformInt EndCullDistance;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass, meta = (UIMin = 0, ClampMin = 0, UIMax = 1000000, ClampMax = 1000000))` — The distance where instances will have completely faded out when using a PerInstanceFadeAmount material node. 0 disables. When the entire cluster is beyond this distance, the cluster is completely culled and not rendered at all.
- L72 _public member_ `FPerQualityLevelInt EndCullDistanceQuality;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass, meta = (UIMin = 0, ClampMin = 0, UIMax = 1000000, ClampMax = 1000000))`
- L79 _public member_ `int32 MinLOD;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass, meta = (UIMin = -1, ClampMin = -1, UIMax = 8, ClampMax = 8))` — Specifies the smallest LOD that will be used for this component. If -1 (default), the MinLOD of the static mesh asset will be used instead.
- L83 _public member_ `FFloatInterval AllowedDensityRange;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass, meta = (UIMin = 0.0, ClampMin = 0.0, UIMax = 1.0, ClampMax = 1.0))` — Specifies the density range where the grass variety is allowed to be spawned ([0,1] represents the entire range).
- L87 _public member_ `EGrassScaling Scaling;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass)` — Specifies grass instance scaling type
- L91 _public member_ `FFloatInterval ScaleX;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass)` — Specifies the range of scale, from minimum to maximum, to apply to a grass instance's X Scale property
- L95 _public member_ `FFloatInterval ScaleY;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass, meta = (EditCondition = "Scaling == EGrassScaling::Free"))` — Specifies the range of scale, from minimum to maximum, to apply to a grass instance's Y Scale property
- L99 _public member_ `FFloatInterval ScaleZ;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass, meta = (EditCondition = "Scaling == EGrassScaling::Free || Scaling == EGrassScaling::LockXY"))` — Specifies the range of scale, from minimum to maximum, to apply to a grass instance's Z Scale property
- L103 _public member_ `bool bWeightAttenuatesMaxScale = false;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = Grass)` — If enabled the the scale of instances is reduced as the weight (density) decreases
- L107 _public member_ `float MaxScaleWeightAttenuation = 0.5f;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = Grass, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1, EditCondition = "bWeightAttenuatesMaxScale == true"))` — Modulate the scale of the instances based on weight (normalized density). The weight range (ScaleWeightAttenuation, 1.0) maps to (scaleMin, scaleMax), weight values less than ScaleWeightAttenuation are set to minScale
- L111 _public member_ `bool RandomRotation;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass)` — Whether the grass instances should be placed at random rotation (true) or all at the same rotation (false)
- L115 _public member_ `bool AlignToSurface;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass)` — Whether the grass instances should be tilted to the normal of the landscape (true), or always vertical (false)
- L119 _public member_ `bool bAlignToTriangleNormals;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass, meta = (EditCondition = "AlignToSurface && bUseGrid"))` — When aligning to the surface when using grid mode, whether we should align to triangle normal (true) or a smooth grid-based normal (false).  Halton always uses triangle normal.
- L123 _public member_ `bool bUseLandscapeLightmap;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass)` — Whether to use the landscape's lightmap when rendering the grass.
- L130 _public member_ `FLightingChannels LightingChannels;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, AdvancedDisplay, Category = Grass)` — Lighting channels that the grass will be assigned. Lights with matching channels will affect the grass. These channels only apply to opaque materials, direct lighting, and dynamic lighting and shadowing.
- L134 _public member_ `bool bReceivesDecals;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass)` — Whether the grass instances should receive decals.
- L138 _public member_ `bool bAffectDistanceFieldLighting;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass)` — Controls whether the primitive should affect dynamic distance field lighting methods.
- L142 _public member_ `bool bCastDynamicShadow;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass)` — Whether the grass should cast shadows when using non-precomputed shadowing.
- L146 _public member_ `bool bCastContactShadow;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass)` — Whether the grass should cast contact shadows.
- L150 _public member_ `bool bKeepInstanceBufferCPUCopy;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass)` — Whether we should keep a cpu copy of the instance buffer. This should be set to true if you plan on using GetOverlappingXXXXCount functions of the component otherwise it won't return any data.
- L154 _public member_ `uint32 InstanceWorldPositionOffsetDisableDistance;` — `UPROPERTY(EditAnywhere, Category = Grass)` — Distance at which to grass instances should disable WPO for performance reasons
- L158 _public member_ `EShadowCacheInvalidationBehavior ShadowCacheInvalidationBehavior;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Grass, AdvancedDisplay)` — Control shadow invalidation behavior, in particular with respect to Virtual Shadow Maps and material effects like World Position Offset.
- L160 _public prototype_ `bool IsGrassQualityLevelEnable() const;`
- L162 _public prototype_ `int32 GetStartCullDistance() const;`
- L164 _public prototype_ `int32 GetEndCullDistance() const;`
- L166 _public prototype_ `float GetDensity() const;`

#### class `ULandscapeGrassType`  
`class ULandscapeGrassType : public UObject`  
_L171-222_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject`
- L176 _private member_ `TArray<FGrassVariety> GrassVarieties;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Grass)`
- L183 _private member_ `uint32 bEnableDensityScaling : 1;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Scalability)` — Whether this grass type should be affected by the Engine Scalability system's Foliage grass.DensityScale setting. This is enabled by default but can be disabled should this grass type be important for gameplay reasons.
- L186 _private member_ `uint32 StateHash = 0;` — `UPROPERTY()`
- L189 _private member_ `TObjectPtr<UStaticMesh> GrassMesh_DEPRECATED;` — `UPROPERTY()`
- L191 _private member_ `float GrassDensity_DEPRECATED;` — `UPROPERTY()`
- L193 _private member_ `float PlacementJitter_DEPRECATED;` — `UPROPERTY()`
- L195 _private member_ `int32 StartCullDistance_DEPRECATED;` — `UPROPERTY()`
- L197 _private member_ `int32 EndCullDistance_DEPRECATED;` — `UPROPERTY()`
- L199 _private member_ `bool RandomRotation_DEPRECATED;` — `UPROPERTY()`
- L201 _private member_ `bool AlignToSurface_DEPRECATED;` — `UPROPERTY()`
- L204 _private prototype_ `virtual void PostLoad() override;`
- L206 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L210 _private prototype_ `uint32 ComputeStateHash();`
- L217 _private function_ `inline FName GetGrassNameFallback() const` — Return a FName that corresponds to this grass type. It used to be that grass types were unique for spawning grass on a given component. Nowadays, we use named "slots" for each grass type (the GrassName being the slot's name in the landscape material). This function here returns a fallback name for when serializing old data that was grass type-based only.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LANDSCAPE_API`

### `Source/Runtime/Landscape/Classes/LandscapeHeightfieldCollisionComponent.h` (Public)


#### enum `EHeightfieldSource`  
`enum class EHeightfieldSource`  
_L32-38_
- L34 _public enumerator_ `None`
- L35 _public enumerator_ `Simple`
- L36 _public enumerator_ `Complex`
- L37 _public enumerator_ `Editor`

#### class `ULandscapeHeightfieldCollisionComponent`  
`class ULandscapeHeightfieldCollisionComponent : public UPrimitiveComponent`  
_L41-365_
- reflection: `UCLASS(MinimalAPI, Within=LandscapeProxy)`
- inherits: `UPrimitiveComponent`
- L47 _private prototype_ `ULandscapeHeightfieldCollisionComponent(FVTableHelper& Helper);`
- L48 _private prototype_ `virtual ~ULandscapeHeightfieldCollisionComponent();`
- L52 _private member_ `TArray<TObjectPtr<ULandscapeLayerInfoObject>> ComponentLayerInfos;` — `UPROPERTY()` — List of layers painted on this component. Matches the WeightmapLayerAllocations array in the LandscapeComponent.
- L56 _private member_ `int32 SectionBaseX;` — `UPROPERTY()` — Offset of component in landscape quads
- L59 _private member_ `int32 SectionBaseY;` — `UPROPERTY()`
- L63 _private member_ `int32 CollisionSizeQuads;` — `UPROPERTY()` — Size of component in collision quads
- L67 _private member_ `float CollisionScale;` — `UPROPERTY()` — Collision scale: (ComponentSizeQuads) / (CollisionSizeQuads)
- L71 _private member_ `int32 SimpleCollisionSizeQuads;` — `UPROPERTY()` — Size of component's "simple collision" in collision quads
- L73 _private member_ `bool bCookedCollisionDataWasDeleted = false;`
- L77 _private member_ `TArray<uint8> CollisionQuadFlags;` — `UPROPERTY()` — The flags for each collision quad. See ECollisionQuadFlags.
- L81 _private member_ `FGuid HeightfieldGuid;` — `UPROPERTY()` — Guid used to share Physics heightfield objects in the editor
- L85 _private member_ `FBox CachedLocalBox;` — `UPROPERTY()` — Cached local-space bounding box, created at heightmap update time
- L91 _private member_ `TLazyObjectPtr<ULandscapeComponent> RenderComponent_DEPRECATED;` — `UPROPERTY()` — Reference to render component
- L98 _private member_ `TObjectPtr<ULandscapeComponent> RenderComponentRef;` — `UPROPERTY()` — Reference to render component
- L101 _private member_ `TArray<FBox> DeferredSnapFoliageInstanceBoxes;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient, NonTransactional)`
- L106 _public prototype_ `ULandscapeComponent* GetRenderComponent() const;` — `UFUNCTION(BlueprintCallable, Category = "Landscape")` — Returns associated landscape component
- L130 _public member_ `uint32 CollisionHash = 0;` — `UPROPERTY()`
- L133 _public member_ `FWordBulkData CollisionHeightData;` — The collision height values. Stripped from cooked content
- L136 _public member_ `FByteBulkData DominantLayerData;` — Indices into the ComponentLayers array for the per-vertex dominant layer. Stripped from cooked content
- L139 _public member_ `FByteBulkData PhysicalMaterialRenderData;` — Indices for physical materials generated by the render material. Stripped from cooked content
- L143 _public member_ `TArray<TObjectPtr<UPhysicalMaterial>> PhysicalMaterialRenderObjects;` — `UPROPERTY()` — Physical materials objects referenced by the indices in PhysicalMaterialRenderData. Stripped from cooked content
- L146 _public member_ `TArray<uint8> CookedCollisionDataEd;` — Cooked editor specific heightfield data, never serialized
- L153 _public member_ `mutable bool bShouldSaveCookedDataToDDC[2];` — Flag to indicate that the next time we cook data, we should save it to the DDC. Used to ensure DDC is populated when loading content for the first time. For editor and full version of collision objects
- L159 _public member_ `mutable TSharedPtr<FAsyncPreRegisterDDCRequest> SpeculativeDDCRequest;` — Async DCC load for cooked collision representation. We speculatively load this to remove hitch when streaming
- L167 _public member_ `TArray<uint8> CookedCollisionData;` — Cooked HeightField data. Serialized only with cooked content Stored as array instead of BulkData to take advantage of precaching during async loading
- L171 _public member_ `TArray<TObjectPtr<UPhysicalMaterial>> CookedPhysicalMaterials;` — `UPROPERTY()` — This is a list of physical materials that is actually used by a cooked HeightField
- L174 _public member_ `TRefCountPtr<FHeightfieldGeometryRef> HeightfieldRef;` — Physics engine version of heightfield data.
- L178 _public member_ `Chaos::FHeightFieldPtr LocalHeightfieldGeometryRef;` — local non-serialized ref counted pointers to keep the chaos heightfields alive between Unregister() and actual destruction of the component. this allows us to re-use them if the component gets a call to Register() again
- L179 _public member_ `Chaos::FHeightFieldPtr LocalHeightfieldSimpleGeometryRef;`
- L182 _public member_ `int32 HeightfieldRowsCount;` — Cached PxHeightFieldSamples values for navmesh generation. Note that it's being used only if navigation octree is set up for lazy geometry exporting
- L183 _public member_ `int32 HeightfieldColumnsCount;`
- L185 _public member_ `mutable FRWLock CachedHeightFieldSamplesLock;`
- L186 _public member_ `FNavHeightfieldSamples CachedHeightFieldSamples;`
- L197 _private member_ `bool bEnableCollisionHashOptim = false;`
- L202 _protected prototype_ `virtual void OnCreatePhysicsState() override;`
- L203 _protected prototype_ `virtual void OnDestroyPhysicsState() override;`
- L206 _public prototype_ `virtual void ApplyWorldOffset(const FVector& InOffset, bool bWorldShift) override;`
- L210 _public prototype_ `virtual void DestroyComponent(bool bPromoteChildren = false) override;`
- L211 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform &BoundTransform) const override;`
- L213 _public prototype_ `virtual ECollisionEnabled::Type GetCollisionEnabled() const override;`
- L214 _public prototype_ `virtual ECollisionResponse GetCollisionResponseToChannel(ECollisionChannel Channel) const override;`
- L215 _public prototype_ `virtual ECollisionChannel GetCollisionObjectType() const override;`
- L216 _public prototype_ `virtual const FCollisionResponseContainer& GetCollisionResponseToChannels() const override;`
- L217 _public prototype_ `virtual void OnRegister() override;`
- L218 _public prototype_ `virtual void OnUnregister() override;`
- L219 _public prototype_ `virtual bool AllowsAsyncPhysicsStateCreation() const override;`
- L223 _public prototype_ `virtual bool DoCustomNavigableGeometryExport(FNavigableGeometryExport& GeomExport) const override;`
- L224 _public prototype_ `virtual bool IsShown(const FEngineShowFlags& ShowFlags) const override;`
- L228 _public function_ `virtual bool SupportsGatheringGeometrySlices() const override`
- L229 _public prototype_ `virtual void GatherGeometrySlice(FNavigableGeometryExport& GeomExport, const FBox& SliceBox) const override;`
- L230 _public prototype_ `virtual ENavDataGatheringMode GetGeometryGatheringMode() const override;`
- L231 _public prototype_ `virtual void PrepareGeometryExportSync() override;`
- L235 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L236 _public prototype_ `virtual void BeginDestroy() override;`
- L237 _public prototype_ `virtual void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize) override;`
- L238 _public prototype_ `virtual void PostLoad() override;`
- L239 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L241 _public prototype_ `virtual bool NeedsLoadForClient() const override;`
- L242 _public prototype_ `virtual bool NeedsLoadForServer() const override;`
- L243 _public prototype_ `virtual void ExportCustomProperties(FOutputDevice& Out, uint32 Indent) override;`
- L244 _public prototype_ `virtual void ImportCustomProperties(const TCHAR* SourceText, FFeedbackContext* Warn) override;`
- L248 _public prototype_ `void SpeculativelyLoadAsyncDDCCollsionData();` — We speculatively async load collision object from DDC to remove hitch when streaming
- L253 _public prototype_ `bool GenerateCollisionObjects(const FName& Format, bool bUseDefaultMaterialOnly, Chaos::FHeightFieldPtr& OutHeightField, bool bGenerateSimpleCollision, Chaos::FHeightFieldPtr& OutSimpleHeightField, TArray<UPhysicalMaterial*>& InOutMaterials) const;` — Cooks raw height data into collision object binary stream
- L254 _public prototype_ `virtual bool CookCollisionData(const FName& Format, bool bUseDefaultMaterialOnly, bool bCheckDDC, TArray<uint8>& OutCookedData, TArray<UPhysicalMaterial*>& InOutMaterials) const;`
- L257 _public prototype_ `void UpdateHeightfieldRegion(int32 ComponentX1, int32 ComponentY1, int32 ComponentX2, int32 ComponentY2);` — Modify a sub-region of the physics heightfield. Note that this does not update the physical material
- L260 _public prototype_ `virtual uint32 ComputeCollisionHash() const;` — Computes a hash of all the data that will impact final collision
- L262 _public prototype_ `void MarkAreaForSnapFoliageInstances(const FBox& InBox);`
- L272 _public prototype_ `FCollisionSampleInfo GetCollisionSampleInfo() const;`
- L292 _public prototype_ `FWriteRuntimeDataParams MakeWriteRuntimeDataParams(bool bUseDefaultMaterialOnly) const;` — Set up params to call WriteRuntimeData using editor data members.
- L296 _public prototype_ `bool WriteRuntimeData(const FWriteRuntimeDataParams& Params, TArray<uint8>& OutHeightfieldData, TArray<UPhysicalMaterial*>& InOutMaterials) const;` — Writes to a cooked data buffer using raw heightfield data
- L298 _public prototype_ `bool GenerateCollisionData(const FWriteRuntimeDataParams& Params, Chaos::FHeightFieldPtr& OutHeightField, bool bGenerateSimpleCollision, Chaos::FHeightFieldPtr& OutSimpleHeightField, TArray<UPhysicalMaterial*>& InOutMaterials) const;`
- L301 _public prototype_ `ULandscapeInfo* GetLandscapeInfo() const;` — Gets the landscape info object for this landscape
- L305 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;` — The scene proxy is only for debug purposes :
- L309 _public prototype_ `virtual void CreateCollisionObject();` — Creates collision object from a cooked collision data
- L312 _public prototype_ `void CreateCollisionObject( bool bUseDefaultMaterialOnly, TArrayView<const uint16> Heights, TArrayView<const uint16> SimpleHeights, TArrayView<const uint8> PhysicalMaterialIds, TArrayView<const uint8> SimplePhysicalMaterialIds, TArrayView<const TObjectPtr<UPhysicalMaterial>> PhysicalMaterialObjects);` — Creates collision object from raw runtime data.  Data is assumed at this point to contain valid physical material indices with visibility layer set to 0xFF
- L319 _public prototype_ `ALandscapeProxy* GetLandscapeProxy() const;` — Return the landscape actor associated with this component.
- L322 _public prototype_ `FIntPoint GetSectionBase() const;` — @return Component section base as FIntPoint
- L325 _public prototype_ `void SetSectionBase(FIntPoint InSectionBase);` — @param InSectionBase new section base for a component
- L328 _public prototype_ `virtual bool RecreateCollision();` — Recreate heightfield and restart physics
- L332 _private prototype_ `void DeferredDestroyCollision(const TRefCountPtr<FHeightfieldGeometryRef>& HeightfieldRefLifetimeExtender);` — @todo(chaos): remove when implicit objects are ref counted
- L338 _public prototype_ `void SnapFoliageInstances();` — `UE_DEPRECATED(5.8, "Use the method taking a ESnapFoliageInstancesFlags parameter")` — Foliage snapping functions : called from editor code to manage foliage instances on landscape.
- L345 _public prototype_ `FRIEND_ENUM_CLASS_FLAGS(ESnapFoliageInstancesFlags);`
- L347 _public prototype_ `void SnapFoliageInstances(ESnapFoliageInstancesFlags InFlags);` — Snap foliage instances overlapping with the component
- L349 _public prototype_ `void SnapFoliageInstances(const FBox& InInstanceBox);` — Snap foliage instances overlapping with the specified area only
- L353 _public function_ `void SetRenderComponent(ULandscapeComponent* InRenderComponent)`
- L356 _public prototype_ `TOptional<float> GetHeight(float X, float Y, EHeightfieldSource HeightFieldSource);`
- L357 _public prototype_ `UPhysicalMaterial* GetPhysicalMaterial(float X, float Y, EHeightfieldSource HeightFieldSource);`
- L363 _public prototype_ `bool FillHeightTile(TArrayView<float> Heights, int32 Offset, int32 Stride) const;` — Populates a supplied array with the heights from the heightfield.  Samples are placed in a tile defined by the starting point (Offset) and the stride/row
- L364 _public prototype_ `bool FillMaterialIndexTile(TArrayView<uint8> Materials, int32 Offset, int32 Stride) const;`

#### struct `ULandscapeHeightfieldCollisionComponent::FHeightfieldGeometryRef`  
`struct FHeightfieldGeometryRef : public UE::Private::FQueryableRefCountedObject`  
_L108-124_
- inherits: `UE::Private::FQueryableRefCountedObject`
- L110 _public member_ `FGuid Guid;`
- L112 _public member_ `TArray<Chaos::FMaterialHandle> UsedChaosMaterials;`
- L113 _public member_ `Chaos::FHeightFieldPtr HeightfieldGeometry;`
- L114 _public member_ `Chaos::FHeightFieldPtr HeightfieldSimpleGeometry;`
- L117 _public member_ `Chaos::FHeightFieldPtr EditorHeightfieldGeometry;`
- L120 _public prototype_ `FHeightfieldGeometryRef(FGuid& InGuid);`
- L121 _public prototype_ `virtual ~FHeightfieldGeometryRef();`
- L123 _public prototype_ `void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize);`

#### enum `ULandscapeHeightfieldCollisionComponent::ECollisionQuadFlags`  
`enum ECollisionQuadFlags : uint8`  
_L188-193_
- L190 _public enumerator_ `QF_PhysicalMaterialMask = 63` — Mask value for the physical material index, stored in the lower 6 bits.
- L191 _public enumerator_ `QF_EdgeTurned = 64` — This quad's diagonal has been turned.
- L192 _public enumerator_ `QF_NoCollision = 128` — This quad has no collision.

#### struct `ULandscapeHeightfieldCollisionComponent::FCollisionSampleInfo`  
`struct FCollisionSampleInfo`  
_L265-271_
- L267 _public member_ `int32 CollisionSizeVerts = 0;`
- L268 _public member_ `int32 SimpleCollisionSizeVerts = 0;`
- L269 _public member_ `int32 NumSamples = 0;`
- L270 _public member_ `int32 NumSimpleSamples = 0;`

#### struct `ULandscapeHeightfieldCollisionComponent::FWriteRuntimeDataParams`  
`struct FWriteRuntimeDataParams`  
_L274-288_
- L276 _public member_ `bool bUseDefaultMaterialOnly = false;`
- L277 _public member_ `bool bProcessRenderIndices = true;`
- L278 _public member_ `bool bProcessVisibilityLayer = true;`
- L279 _public member_ `TArrayView<const uint16> Heights;`
- L280 _public member_ `TArrayView<const uint16> SimpleHeights;`
- L281 _public member_ `TArrayView<const uint8> DominantLayers;`
- L282 _public member_ `TArrayView<const uint8> SimpleDominantLayers;`
- L283 _public member_ `TArrayView<const uint8> RenderPhysicalMaterialIds;`
- L284 _public member_ `TArrayView<const uint8> SimpleRenderPhysicalMaterialIds;`
- L285 _public member_ `TArrayView<const TObjectPtr<UPhysicalMaterial>> PhysicalMaterialRenderObjects;`
- L286 _public member_ `TArrayView<const TObjectPtr<ULandscapeLayerInfoObject>> ComponentLayerInfos;`
- L287 _public member_ `int32 VisibilityLayerIndex = INDEX_NONE;`

#### enum `ULandscapeHeightfieldCollisionComponent::ESnapFoliageInstancesFlags`  
`enum class ESnapFoliageInstancesFlags`  
_L340-344_
- L342 _public enumerator_ `ForceAll = 1 << 0` — Force-snap foliage instances across the entire component
- L343 _public enumerator_ `MarkedAreasOnly = 1 << 1` — Only update the areas that have already been marked for snapping via MarkAreaForSnapFoliageInstances

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace Chaos`

### `Source/Runtime/Landscape/Classes/LandscapeInfo.h` (Public)


#### struct `FLandscapeAddCollision`  
`struct FLandscapeAddCollision`  
_L39-47_
- L41 _public member_ `FVector Corners[4];`
- L43 _public function_ `FLandscapeAddCollision()`

#### struct `FLandscapeDirtyOnlyInModeScope`  
`struct FLandscapeDirtyOnlyInModeScope`  
_L52-62_
- L54 _public prototype_ `FLandscapeDirtyOnlyInModeScope() = delete;`
- L55 _public prototype_ `FLandscapeDirtyOnlyInModeScope(ULandscapeInfo* InLandscapeInfo);`
- L56 _public prototype_ `FLandscapeDirtyOnlyInModeScope(ULandscapeInfo* InLandscapeInfo, bool bInOverrideDirtyMode);`
- L57 _public prototype_ `~FLandscapeDirtyOnlyInModeScope();` — FLandscapeDirtyOnlyInModeScope(ULandscapeInfo* InLandscapeInfo, bool bInOverrideDirtyMode);   Override the dirtying in Landscape mode behaviour
- L60 _private member_ `ULandscapeInfo* LandscapeInfo;`
- L61 _private member_ `bool bDirtyOnlyInModePrevious;`

#### struct `FLandscapeInfoLayerSettings`  
`struct FLandscapeInfoLayerSettings`  
_L66-106_
- reflection: `USTRUCT()`
- L71 _public member_ `TObjectPtr<ULandscapeLayerInfoObject> LayerInfoObj;` — `UPROPERTY()`
- L74 _public member_ `FName LayerName;` — `UPROPERTY()`
- L78 _public member_ `TObjectPtr<UMaterialInstanceConstant> ThumbnailMIC;` — `UPROPERTY(transient)`
- L81 _public member_ `TWeakObjectPtr<ALandscapeProxy> Owner;` — `UPROPERTY()`
- L84 _public member_ `int32 DebugColorChannel;` — `UPROPERTY(transient)`
- L87 _public function_ `FLandscapeInfoLayerSettings() : LayerInfoObj(nullptr) , LayerName(NAME_None) #if WITH_EDITORONLY_DATA , ThumbnailMIC(nullptr) , Owner(nullptr) , DebugColorChannel(0) #endif`
- L98 _public prototype_ `FLandscapeInfoLayerSettings(ULandscapeLayerInfoObject* InLayerInfo, ALandscapeProxy* InProxy);`
- L99 _public prototype_ `FLandscapeInfoLayerSettings(FName InPlaceholderLayerName, ALandscapeProxy* InProxy);`
- L101 _public prototype_ `FName GetLayerName() const;`
- L104 _public prototype_ `const FLandscapeTargetLayerSettings& GetTargetLayerSettings() const;`

#### struct `FTargetLayerBlendGroup`  
`struct FTargetLayerBlendGroup`  
_L109-148_
- reflection: `USTRUCT()`
- L116 _public prototype_ `FTargetLayerBlendGroup() = default;`
- L117 _public function_ `FTargetLayerBlendGroup(const FName& InName, ELandscapeTargetLayerBlendMethod InBlendMethod, const TSet<ULandscapeLayerInfoObject*>& InTargetLayers) : Name(InName) , BlendMethod(InBlendMethod) , TargetLayers(ObjectPtrWrap(InTargetLayers))`
- L124 _public function_ `const FName& GetName() const`
- L129 _public function_ `ELandscapeTargetLayerBlendMethod GetBlendMethod() const`
- L134 _public function_ `const TSet<TObjectPtr<ULandscapeLayerInfoObject>>& GetTargetLayers() const`
- L141 _private member_ `FName Name;` — `UPROPERTY()`
- L144 _private member_ `ELandscapeTargetLayerBlendMethod BlendMethod = ELandscapeTargetLayerBlendMethod::Count;` — `UPROPERTY()`
- L147 _private member_ `TSet<TObjectPtr<ULandscapeLayerInfoObject>> TargetLayers;` — `UPROPERTY()`

#### class `ULandscapeInfo`  
`class ULandscapeInfo : public UObject`  
_L151-527_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L158 _private member_ `TWeakObjectPtr<ALandscape> LandscapeActor;` — `UPROPERTY()`
- L161 _private member_ `FGuid LandscapeGuid;` — `UPROPERTY()`
- L164 _private member_ `int32 ComponentSizeQuads;` — `UPROPERTY()`
- L167 _private member_ `int32 SubsectionSizeQuads;` — `UPROPERTY()`
- L170 _private member_ `int32 ComponentNumSubsections;` — `UPROPERTY()`
- L175 _private member_ `bool bDrawScaleSetByActor = false;` — `UPROPERTY()` — True when the draw scale has been set by the landscape Actor (false if default or set by a streaming proxy)
- L178 _private member_ `FVector DrawScale = FVector(100.0);` — `UPROPERTY()`
- L181 _private member_ `TArray<FLandscapeInfoLayerSettings> Layers;` — `UPROPERTY()`
- L184 _private member_ `int32 RegionSizeInComponents;` — `UPROPERTY()`
- L189 _public member_ `TMap<FIntPoint, ULandscapeComponent*> XYtoComponentMap;` — Map of the offsets (in component space) to the component. Valid in editor only.
- L191 _public member_ `TMap<FIntPoint, ULandscapeHeightfieldCollisionComponent*> XYtoCollisionComponentMap;` — Map of the offsets (in component space) to the collision components. Should always be valid.
- L196 _public member_ `TMap<FIntPoint, FLandscapeAddCollision> XYtoAddCollisionMap;` — Lookup map used by the "add component" tool. Only available near valid LandscapeComponents. only for use by the "add component" tool. Todo - move into the tool?
- L201 _public member_ `TArray<TWeakObjectPtr<ALandscapeStreamingProxy>> StreamingProxies_DEPRECATED;` — `UE_DEPRECATED(5.7, "StreamingProxies rely on a sorted state and should not be modified outside of ULandscapeInfo. Use GetSortedStreamingProxies instead.")` — `UPROPERTY()`
- L207 _private member_ `TArray<TScriptInterface<ILandscapeSplineInterface>> SplineActors;` — `UPROPERTY()` — SORTED list of all actors implementing the spline interface that are registered with this landscape info
- L210 _private member_ `TSet<TWeakObjectPtr<UPackage>, TWeakObjectPtrSetKeyFuncs<TWeakObjectPtr<UPackage>>> ModifiedPackages;` — Not properties since these shouldn't be modified through transactions (no undo/redo)
- L211 _private member_ `TSet<TWeakObjectPtr<AActor>, TWeakObjectPtrSetKeyFuncs<TWeakObjectPtr<AActor>>> ActorsToDelete;`
- L213 _private member_ `bool bDirtyOnlyInMode;`
- L218 _private member_ `TSet<ULandscapeComponent*> SelectedComponents;`
- L220 _private member_ `TSet<ULandscapeComponent*> SelectedRegionComponents;`
- L222 _private member_ `FIntRect XYComponentBounds;`
- L225 _public member_ `TMap<FIntPoint,float> SelectedRegion;`
- L228 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L231 _public prototype_ `FBox GetLoadedBounds() const;`
- L234 _public prototype_ `FBox GetCompleteBounds() const;`
- L240 _public prototype_ `bool SupportsLandscapeEditing() const;` — @todo document all below.
- L242 _public prototype_ `bool IsLandscapeEditableWorld() const;` — False if landscape editing not supported, in PIE world, or in a Commandlet
- L244 _public prototype_ `bool AreAllComponentsRegistered() const;`
- L245 _public prototype_ `void GetComponentsInRegion(int32 X1, int32 Y1, int32 X2, int32 Y2, TSet<ULandscapeComponent*>& OutComponents, bool bOverlap = true) const;`
- L246 _public prototype_ `bool HasUnloadedComponentsInRegion(int32 X1, int32 Y1, int32 X2, int32 Y2) const;`
- L247 _public prototype_ `bool GetLandscapeExtent(ALandscapeProxy* Proxy, FIntRect& ProxyExtent) const;`
- L248 _public prototype_ `bool GetLandscapeExtent(FIntRect& LandscapeExtent) const;`
- L249 _public prototype_ `bool GetLandscapeExtent(int32& MinX, int32& MinY, int32& MaxX, int32& MaxY) const;`
- L250 _public prototype_ `FIntRect GetCompleteLandscapeExtent() const;`
- L251 _public prototype_ `bool GetLandscapeXYComponentBounds(FIntRect& OutXYComponentBounds) const;`
- L252 _public prototype_ `void ForAllLandscapeComponents(TFunctionRef<void(ULandscapeComponent*)> Fn) const;`
- L253 _public prototype_ `void ExportHeightmap(const FString& Filename);`
- L254 _public prototype_ `void ExportHeightmap(const FString& Filename, const FIntRect& ExportRegion);`
- L255 _public prototype_ `void ExportLayer(ULandscapeLayerInfoObject* LayerInfo, const FString& Filename);`
- L256 _public prototype_ `void ExportLayer(ULandscapeLayerInfoObject* LayerInfo, const FString& Filename, const FIntRect& ExportRegion);`
- L258 _public prototype_ `bool ApplySplines(bool bOnlySelected, TSet<TObjectPtr<ULandscapeComponent>>* OutModifiedComponents = nullptr, bool bMarkPackageDirty = true);` — `UE_DEPRECATED(5.7, "Use ApplySplines without bOnlySelected. Edit layer landscapes update all splines regardless of selection state")`
- L259 _public prototype_ `bool ApplySplines(TSet<TObjectPtr<ULandscapeComponent>>* OutModifiedComponents = nullptr, bool bMarkPackageDirty = true);`
- L261 _public prototype_ `bool GetSelectedExtent(int32& MinX, int32& MinY, int32& MaxX, int32& MaxY) const;`
- L262 _public prototype_ `FVector GetLandscapeCenterPos(float& LengthZ, int32 MinX = MAX_int32, int32 MinY = MAX_int32, int32 MaxX = MIN_int32, int32 MaxY = MIN_int32);`
- L263 _public prototype_ `bool IsValidPosition(int32 X, int32 Y);`
- L264 _public prototype_ `void DeleteLayer(ULandscapeLayerInfoObject* LayerInfo, const FName& LayerName);`
- L265 _public prototype_ `void ReplaceLayer(ULandscapeLayerInfoObject* FromLayerInfo, ULandscapeLayerInfoObject* ToLayerInfo);`
- L266 _public prototype_ `void GetUsedPaintLayers(const FGuid& InLayerGuid, TArray<ULandscapeLayerInfoObject*>& OutUsedLayerInfos) const;`
- L268 _public prototype_ `void UpdateDebugColorMaterial();`
- L270 _public prototype_ `TSet<ULandscapeComponent*> GetSelectedComponents() const;`
- L271 _public prototype_ `TSet<ULandscapeComponent*> GetSelectedRegionComponents() const;`
- L272 _public prototype_ `void UpdateSelectedComponents(TSet<ULandscapeComponent*>& NewComponents, bool bIsComponentwise = true);`
- L273 _public prototype_ `void ClearSelectedRegion(bool bIsComponentwise = true);`
- L276 _public prototype_ `void UpdateAllAddCollisions();` — only for use by the "add component" tool. Todo - move into the tool?
- L277 _public prototype_ `void UpdateAddCollision(FIntPoint LandscapeKey);`
- L279 _public prototype_ `const FLandscapeTargetLayerSettings& GetTargetLayerSettings(ULandscapeLayerInfoObject* LayerInfo) const;`
- L281 _public prototype_ `void CreateTargetLayerSettingsFor(ULandscapeLayerInfoObject* LayerInfo);`
- L283 _public prototype_ `ULandscapeLayerInfoObject* GetLayerInfoByName(FName LayerName, ALandscapeProxy* Owner = nullptr) const;`
- L284 _public prototype_ `int32 GetLayerInfoIndex(FName LayerName, ALandscapeProxy* Owner = nullptr) const;`
- L285 _public prototype_ `int32 GetLayerInfoIndex(ULandscapeLayerInfoObject* LayerInfo, ALandscapeProxy* Owner = nullptr) const;`
- L286 _public prototype_ `bool UpdateLayerInfoMap(ALandscapeProxy* Proxy = nullptr, bool bInvalidate = false);`
- L288 _public prototype_ `bool CanDeleteLandscape(FText& OutReason) const;`
- L295 _public prototype_ `ALandscapeProxy* GetLandscapeProxyForLevel(ULevel* Level) const;` — Returns the landscape proxy of this landscape info in the given level (if it exists) @param  Level  Level to look in @return        Landscape or landscape proxy found in the given level, or null if none
- L297 _public prototype_ `bool GetDirtyOnlyInMode() const;`
- L299 _public prototype_ `void OnModifiedPackageSaved(UPackage* InPackage);`
- L300 _public prototype_ `int32 GetModifiedPackageCount() const;`
- L301 _public prototype_ `TArray<UPackage*> GetModifiedPackages() const;`
- L302 _public prototype_ `bool IsPackageModified(UPackage* InPackage) const;`
- L308 _public prototype_ `int32 MarkModifiedPackagesAsDirty();` — Goes through the list of modified packages (as in IsPackageModified) and marks them as dirty @return the number of packages effectively dirtied
- L321 _public prototype_ `bool ModifyObject(UObject* InObject, bool bAlwaysMarkDirty = true);` — See UObject::Modify @param InObject Object being modified. Must be either a ALandscapeProxy or one of its inner objects @param bAlwaysMarkDirty if true, marks the package dirty even if we aren't currently recording an active undo/redo transaction @return true if the object could not be marked dirty but has been added to the list of ModifiedPackages
- L330 _public prototype_ `bool MarkObjectDirty(UObject* InObject, bool bInForceResave = false, const ALandscape* InLandscapeOverride = nullptr);` — See UObjectBaseUtility::MarkPackageDirty @param InObject Object to mark dirty. @param bInForceResave passed to true in order to bypass the bDirtyOnlyInMode and force the object into the list of modified packages. This ensures the object is marked as needing resaving in case we want to help the user re-save its landscape actors (e.g. following a data fixup) @param InLandscapeOverride if set, MarkObjectDirty will use this ALandscape instead of the local one in the method. @return true if the object could not be marked dirty but has been added to the list of ModifiedPackages
- L337 _public prototype_ `void DeleteActorWhenApplyingModifiedStatus(AActor* InActor, bool bInAllowUI);` — Enqueue an actor to be deleted when deferred dirty status from MarkObjectDirty is finally applied. @param InActor Actor to delete. @param bInAllowUI allows the standard delete actors UX to be displayed, allowing the user to remove lingering reference to these actors, etc.
- L342 _public prototype_ `void DirtyRuntimeVirtualTextureForLandscapeArea(int32 X1, int32 Y1, int32 X2, int32 Y2) const;` — Helper function to invalidate the runtime virtual texture data associated with the specified landscape region. This forces the dirtied RVT pages to be updated in priority
- L350 _public prototype_ `ALandscapeProxy* GetCurrentLevelLandscapeProxy(bool bRegistered) const;` — Returns landscape which is spawned in the current level that was previously added to this landscape info object @param	bRegistered		Whether to consider only registered(visible) landscapes @return					Landscape or landscape proxy found in the current level
- L356 _public prototype_ `ALandscapeProxy* GetLandscapeProxy() const;` — returns shared landscape or landscape proxy, mostly for transformations @todo: should be removed
- L361 _public prototype_ `void Reset();` — Resets all actors, proxies, components registrations
- L366 _public prototype_ `static void RecreateLandscapeInfo(UWorld* InWorld, bool bMapCheck, bool bKeepRegistrationStatus = false);` — Recreate all LandscapeInfo objects in given world @param  bMapCheck	Whether to warn about landscape errors
- L374 _public prototype_ `void FixupProxiesTransform(bool bDirty = false);` — Fixes up proxies relative position to landscape actor basically makes sure that each LandscapeProxy RootComponent transform reflects LandscapeSectionOffset value requires LandscapeActor to be loaded Does not work in World composition mode!
- L377 _public prototype_ `void UpdateComponentLayerAllowList();` — Update per-component layer allow list to include the currently painted layers
- L379 _public prototype_ `void RecreateCollisionComponents();`
- L381 _public prototype_ `void RemoveXYOffsets();`
- L385 _public prototype_ `bool CanHaveLayersContent() const;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")` — Will tell if the landscape actor can have some content related to the layer system
- L388 _public prototype_ `void ClearDirtyData();` — Will clear all component dirty data
- L391 _public prototype_ `ALandscapeProxy* MoveComponentsToLevel(const TArray<ULandscapeComponent*>& InComponents, ULevel* TargetLevel, FName NewProxyName = NAME_None);` — Moves Components to target level. Creates ALandscapeProxy if needed.
- L394 _public prototype_ `ALandscapeProxy* MoveComponentsToProxy(const TArray<ULandscapeComponent*>& InComponents, ALandscapeProxy* LandscapeProxy, bool bSetPositionAndOffset = false, ULevel* TargetLevel = nullptr);` — Moves Components to target proxy.
- L397 _public prototype_ `void MoveSplineToLevel(ULandscapeSplineControlPoint* InControlPoint, ULevel* TargetLevel);` — Moves Splines connected to this control point to target level. Creates ULandscapeSplinesComponent if needed.
- L400 _public prototype_ `void MoveSplinesToLevel(ULandscapeSplinesComponent* InSplineComponent, ULevel* TargetLevel);` — Moves all Splines to target level. Creates ULandscapeSplinesComponent if needed.
- L403 _public prototype_ `void MoveSplineToProxy(ULandscapeSplineControlPoint* InControlPoint, ALandscapeProxy* InLandscapeProxy);` — Moves Splines connected to this control point to target Proxy. Creates ULandscapeSplinesComponent if needed.
- L406 _public prototype_ `void MoveSplinesToProxy(ULandscapeSplinesComponent* InSplineComponent, ALandscapeProxy* InLandscapeProxy);` — Moves all Splines to target Proxy. Creates ULandscapeSplineComponent if needed
- L409 _public prototype_ `void MoveSpline(ULandscapeSplineControlPoint* InControlPoint, TScriptInterface<ILandscapeSplineInterface> InNewOwner);` — Moves Splines connected to this control point to target Proxy. Creates ULandscapeSplinesComponent if needed.
- L412 _public prototype_ `void MoveSplines(ULandscapeSplinesComponent* InSplineComponent, TScriptInterface<ILandscapeSplineInterface> InNewOwner);` — Moves all Splines to target Spline owner. Creates ULandscapeSplinesComponent if needed.
- L415 _public prototype_ `void UpdateAllComponentMaterialInstances(bool bInInvalidateCombinationMaterials = false);` — Will call UpdateAllComponentMaterialInstances on all LandscapeProxies
- L418 _public prototype_ `uint32 GetGridSize(uint32 InGridSizeInComponents) const;` — Returns LandscapeStreamingProxy Cell Size in WorldPartition
- L421 _public prototype_ `bool AreNewLandscapeActorsSpatiallyLoaded() const;` — Returns true if new Landscape actors should be spatially loaded in WorldPartition (LandscapeStreamingProxy & LandscapeSplineActor)
- L423 _public prototype_ `static ULandscapeInfo* Find(UWorld* InWorld, const FGuid& LandscapeGuid);`
- L424 _public prototype_ `static ULandscapeInfo* FindOrCreate(UWorld* InWorld, const FGuid& LandscapeGuid);`
- L425 _public prototype_ `static int32 RemoveLandscapeInfo(UWorld* InWorld, const FGuid& LandscapeGuid);`
- L428 _public prototype_ `void Initialize(UWorld* InWorld, const FGuid& InLandscapeGuid);` — Called after creating object so that it can initialize its state
- L431 _public prototype_ `const TArray<TWeakObjectPtr<ALandscapeStreamingProxy>>& GetSortedStreamingProxies() const;` — Returns a const reference to the sorted registered streaming proxies
- L441 _public prototype_ `void ForEachLandscapeProxy(TFunctionRef<bool(ALandscapeProxy*)> Fn) const;` — Runs the given function on the root landscape actor and all streaming proxies, with the possibility of early exit Most easily used with a lambda as follows: ForEachLandscapeProxy([](ALandscapeProxy* Proxy) -> bool { return continueLoop ? true : false; });
- L443 _public prototype_ `void UpdateNanite(const ITargetPlatform* InTargetPlatform);`
- L449 _public prototype_ `void RegisterActor(ALandscapeProxy* Proxy, bool bMapCheck = false, bool bUpdateAllAddCollisions = true);` — Associates passed actor with this info object @param	Proxy		Landscape actor to register @param  bMapCheck	Whether to warn about landscape errors
- L452 _public prototype_ `void UnregisterActor(ALandscapeProxy* Proxy);` — Deassociates passed actor with this info object
- L455 _public prototype_ `bool IsRegistered(const ALandscapeProxy* Proxy) const;` — Returns true if the Proxy is currently registered with this ULandscapeInfo
- L461 _public prototype_ `void RegisterActorComponent(ULandscapeComponent* Component, bool bMapCheck = false);` — Associates passed landscape component with this info object @param	Component	Landscape component to register @param  bMapCheck	Whether to warn about landscape errors
- L464 _public prototype_ `void UnregisterActorComponent(ULandscapeComponent* Component);` — Deassociates passed landscape component with this info object
- L467 _public prototype_ `void RegisterCollisionComponent(ULandscapeHeightfieldCollisionComponent* Component);` — Server doesn't have ULandscapeComponent use CollisionComponents instead to get height on landscape
- L468 _public prototype_ `void UnregisterCollisionComponent(ULandscapeHeightfieldCollisionComponent* Component);`
- L483 _public prototype_ `bool GetOverlappedComponents(const FTransform& InAreaWorldTransform, const FBox2D& InAreaExtents, TMap<FIntPoint, ULandscapeComponent*>& OutOverlappedComponents, FIntRect& OutComponentIndicesBoundingRect);` — TODO [jonathan.bard] : There should be multiple versions of this. 1. This currently performs AABB to AABB checks and is therefore not optimal (but faster than OOBB to OOBB could ever be, which is why we might need 2 versions) : 2. Returning a TMap<> is a bit overkill, since the component key can be retrieved trivially from the component
- L486 _public prototype_ `TArray<FTargetLayerBlendGroup> GetTargetLayerBlendGroups() const;`
- L487 _public prototype_ `TOptional<FTargetLayerBlendGroup> GetBlendGroupForTargetLayer(ULandscapeLayerInfoObject* InLayerInfo) const;`
- L489 _public prototype_ `ALandscapeSplineActor* CreateSplineActor(const FVector& Location);`
- L491 _public prototype_ `void ForAllSplineActors(TFunctionRef<void(TScriptInterface<ILandscapeSplineInterface>)> Fn) const;`
- L492 _public prototype_ `TArray<TScriptInterface<ILandscapeSplineInterface>> GetSplineActors() const;`
- L494 _public prototype_ `void RegisterSplineActor(TScriptInterface<ILandscapeSplineInterface> SplineActor);`
- L495 _public prototype_ `void UnregisterSplineActor(TScriptInterface<ILandscapeSplineInterface> SplineActor);`
- L499 _public prototype_ `static void UpdateRegistrationForSplineActor(UWorld* InWorld, TScriptInterface<ILandscapeSplineInterface> InSplineActor);` — Updates the spline registrations (with ALL landscape infos) when a spline has changed the landscape it is targeting
- L501 _public prototype_ `void RequestSplineLayerUpdate();`
- L502 _public prototype_ `void ForceLayersFullUpdate();`
- L504 _public function_ `static void SetForceNonSpatiallyLoadedByDefault(bool bInForceNonSpatiallyLoadedByDefault)`
- L507 _private member_ `inline static bool bForceNonSpatiallyLoadedByDefault = false;`
- L509 _private prototype_ `bool ApplySplinesInternal(TScriptInterface<ILandscapeSplineInterface> SplineOwner, TSet<TObjectPtr<ULandscapeComponent>>* OutModifiedComponents, bool bMarkPackageDirty, int32 LandscapeMinX, int32 LandscapeMinY, int32 LandscapeMaxX, int32 LandscapeMaxY, TFunctionRef<TSharedPtr<FModulateAlpha>(ULandscapeLayerInfoObject*)> GetOrCreateModulate);`
- L510 _private prototype_ `void MoveSegment(ULandscapeSplineSegment* InSegment, TScriptInterface<ILandscapeSplineInterface> From, TScriptInterface<ILandscapeSplineInterface> To);`
- L511 _private prototype_ `void MoveControlPoint(ULandscapeSplineControlPoint* InControlPoint, TScriptInterface<ILandscapeSplineInterface> From, TScriptInterface<ILandscapeSplineInterface> To);`
- L512 _private prototype_ `bool UpdateLayerInfoMapInternal(ALandscapeProxy* Proxy);`
- L513 _private prototype_ `bool TryAddToModifiedPackages(UPackage* InPackage, const ALandscape* InLandscapeOverride = nullptr);`
- L514 _private prototype_ `void ProcessDeferredDeletions();`
- L516 _private prototype_ `void OnMarkPackageDirty(UPackage* InPackage, bool bIsDirty);`
- L520 _private prototype_ `void RegisterLandscapeActorWithProxyInternal(ALandscapeProxy* Proxy, bool bMapCheck);`
- L523 _private prototype_ `void SortStreamingProxies();` — Sorts registered streaming proxies by their section base offset
- L526 _private member_ `TArray<TWeakObjectPtr<ALandscapeStreamingProxy>> SortedStreamingProxies;` — `UPROPERTY()`

### `Source/Runtime/Landscape/Classes/LandscapeInfoMap.h` (Public)


#### class `ULandscapeInfoMap`  
`class ULandscapeInfoMap : public UObject`  
_L16-39_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _public prototype_ `void BeginDestroy() override;`
- L22 _public prototype_ `void PostDuplicate(bool bDuplicateForPIE) override;`
- L23 _public prototype_ `void Serialize(FArchive& Ar) override;`
- L25 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L27 _public member_ `TMap<FGuid, TObjectPtr<ULandscapeInfo>> Map;`
- L28 _public member_ `TWeakObjectPtr<UWorld> World;`
- L37 _public prototype_ `static ULandscapeInfoMap& GetLandscapeInfoMap(const UWorld* World);` — Gets landscape-specific data for given world. @param World A pointer to world that return data should be associated with. @returns Landscape-specific data associated with given world.
- L38 _public prototype_ `static ULandscapeInfoMap* FindLandscapeInfoMap(const UWorld* World);`

### `Source/Runtime/Landscape/Classes/LandscapeLayerInfoObject.h` (Public)


#### struct `FOnLandscapeLayerInfoDataChangedParams`  
`struct FOnLandscapeLayerInfoDataChangedParams`  
_L16-42_
- L18 _public function_ `FOnLandscapeLayerInfoDataChangedParams(const ULandscapeLayerInfoObject& InLayerInfoObject, const FPropertyChangedEvent& InPropertyChangedEvent = FPropertyChangedEvent( nullptr)) : PropertyChangedEvent(InPropertyChangedEvent) , LayerInfoObject(&InLayerInfoObject)`
- L25 _public member_ `FPropertyChangedEvent PropertyChangedEvent;` — Provides some additional context about how data has changed (property, type of change...)
- L28 _public member_ `bool bUserTriggered = false;` — Indicates a user-initiated property change
- L31 _public member_ `bool bRequiresLandscapeUpdate = true;` — Indicates the change requires a full landscape update (e.g. parameter affecting heightmap or weightmap...)
- L38 _public member_ `bool bHasValueChanged = true;` — The delegate is triggered each time a data change is requested, even when the data didn't actually change. This indicates that the was actually modified. This can occur for example when several EPropertyChangeType::Interactive changes are triggered because of the user manipulating a slider : this will be followed by a final EPropertyChangeType::ValueSet but when this occurs, the data usually is not actually modified so, to be consistent, we'll still trigger the delegate but indicate that the value didn't actually change, to let the user react appropriately
- L41 _public member_ `const ULandscapeLayerInfoObject* LayerInfoObject = nullptr;` — Pointer to the ULandscapeLayerInfoObject that broadcast the data change event

#### enum `ESplineModulationColorMask`  
`enum class ESplineModulationColorMask : uint8`  
_L47-53_
- reflection: `UENUM()`
- L49 _public enumerator_ `Red`
- L50 _public enumerator_ `Green`
- L51 _public enumerator_ `Blue`
- L52 _public enumerator_ `Alpha`

#### class `ULandscapeLayerInfoObject`  
`class ULandscapeLayerInfoObject : public UObject`  
_L59-268_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L65 _private member_ `FName LayerName;` — `UE_DEPRECATED(5.7, "Property will be made private. Use public Getters/Setter instead.")` — `UPROPERTY(VisibleAnywhere, Category = LandscapeLayerInfoObject, AssetRegistrySearchable)`
- L69 _private member_ `TObjectPtr<UPhysicalMaterial> PhysMaterial;` — `UE_DEPRECATED(5.7, "Property will be made private. Use public Getters/Setter instead.")` — `UPROPERTY(EditAnywhere, Category = LandscapeLayerInfoObject, Meta = (DisplayName = "Physical Material", Tooltip = "Physical material to use when this layer is the predominant one at a given location. Note: this is ignored if the Landscape Physical Material node is used in the landscape material. "))`
- L73 _private member_ `float Hardness = 0.0f;` — `UE_DEPRECATED(5.7, "Property will be made private. Use public Getters/Setter instead.")` — `UPROPERTY(EditAnywhere, Category = LandscapeLayerInfoObject, Meta = (ClampMin = "0", ClampMax = "1", Tooltip = "Defines how much 'resistance' areas painted with this layer will offer to the Erosion tool. A hardness of 0 means the layer is fully affected by erosion, while 1 means fully unaffected."))`
- L78 _private member_ `float MinimumCollisionRelevanceWeight = 0.0f;` — `UE_DEPRECATED(5.7, "Property will be made private. Use public Getters/Setter instead.")` — `UPROPERTY(EditAnywhere, Category = LandscapeLayerInfoObject, Meta = (ClampMin = "0", ClampMax = "1", Tooltip = "The minimum weight that needs to be painted for that layer to be picked up as the dominant physical layer."))`
- L82 _private member_ `uint32 bNoWeightBlend_DEPRECATED:1;` — `UE_DEPRECATED(5.7, "bNoWeightBlend has been replaced by BlendMethod (false is ELandscapeTargetLayerBlendMethod::FinalWeightBlending, true is ELandscapeTargetLayerBlendMethod::None)")` — `UPROPERTY()`
- L86 _private member_ `TObjectPtr<UTexture2D> SplineFalloffModulationTexture;` — `UE_DEPRECATED(5.7, "Property will be made private. Use public Getters/Setter instead.")` — `UPROPERTY(EditAnywhere, Category = SplineFalloffModulation, Meta = (DisplayName="Texture", Tooltip = "Texture to modulate the Splines Falloff Layer Alpha"))`
- L90 _private member_ `ESplineModulationColorMask SplineFalloffModulationColorMask = ESplineModulationColorMask::Red;` — `UE_DEPRECATED(5.7, "Property will be made private. Use public Getters/Setter instead.")` — `UPROPERTY(EditAnywhere, Category = SplineFalloffModulation, Meta = (DisplayName = "Color Mask", Tooltip = "Defines which channel of the Spline Falloff Modulation Texture to use."))`
- L94 _private member_ `float SplineFalloffModulationTiling = 1.0f;` — `UE_DEPRECATED(5.7, "Property will be made private. Use public Getters/Setter instead.")` — `UPROPERTY(EditAnywhere, Category = SplineFalloffModulation, Meta = (DisplayName = "Tiling", ClampMin = "0.01", Tooltip = "Defines the tiling to use when sampling the Spline Falloff Modulation Texture."))`
- L98 _private member_ `float SplineFalloffModulationBias = 0.5f;` — `UE_DEPRECATED(5.7, "Property will be made private. Use public Getters/Setter instead.")` — `UPROPERTY(EditAnywhere, Category = SplineFalloffModulation, Meta = (DisplayName = "Bias", ClampMin = "0", Tooltip = "Defines the offset to use when sampling the Spline Falloff Modulation Texture."))`
- L102 _private member_ `float SplineFalloffModulationScale = 1.0f;` — `UE_DEPRECATED(5.7, "Property will be made private. Use public Getters/Setter instead.")` — `UPROPERTY(EditAnywhere, Category = SplineFalloffModulation, Meta = (DisplayName = "Scale", ClampMin = "0", Tooltip = "Allows to scale the value sampled from the Spline Falloff Modulation Texture."))`
- L108 _private member_ `bool IsReferencedFromLoadedData = false;` — `UE_DEPRECATED(5.7, "This property will be removed in a future release.")` — `UPROPERTY(NonTransactional, Transient)` — TODO [jared.ritchie] Property is used to hide the unused target layers in the UX when ShowUnusedLayers is false. This data should be per-landscape, so it's not valid to store it in the layer object Two landscapes can loaded and reference the same layer info object with one of them saying "there is data associated with this layer" and the other, the contrary
- L113 _private member_ `FLinearColor LayerUsageDebugColor;` — `UE_DEPRECATED(5.7, "Property will be made private. Use public Getters/Setter instead.")` — `UPROPERTY(EditAnywhere, Category = LandscapeLayerInfoObject, Meta = (Tooltip = "The color to use for layer usage debug"))`
- L116 _public function_ `inline ELandscapeTargetLayerBlendMethod GetBlendMethod() const`
- L120 _public function_ `static FName GetBlendMethodMemberName()`
- L124 _public prototype_ `void SetBlendMethod(ELandscapeTargetLayerBlendMethod InBlendMethod, bool bInModify);`
- L126 _public prototype_ `FName GetBlendGroup() const;`
- L127 _public function_ `static FName GetBlendGroupMemberName()`
- L131 _public prototype_ `void SetBlendGroup(const FName& InBlendGroup, bool bInModify);`
- L135 _public function_ `inline const FName& GetLayerName() const` — TODO [jared.ritchie] in 5.9 when public properties are made private, re-enable deprecation warnings
- L139 _public function_ `static FName GetLayerNameMemberName()`
- L143 _public prototype_ `void SetLayerName(const FName& InLayerName, bool bInModify);`
- L145 _public function_ `inline TObjectPtr<UPhysicalMaterial> GetPhysicalMaterial() const`
- L149 _public function_ `static FName GetPhysicalMaterialMemberName()`
- L153 _public prototype_ `void SetPhysicalMaterial(TObjectPtr<UPhysicalMaterial> InPhysicalMaterial, bool bInModify);`
- L155 _public function_ `inline float GetHardness() const`
- L159 _public function_ `static FName GetHardnessMemberName()`
- L163 _public prototype_ `void SetHardness(float InHardness, bool bInModify, EPropertyChangeType::Type InChangeType);`
- L165 _public function_ `inline const FLinearColor& GetLayerUsageDebugColor() const`
- L169 _public function_ `static FName GetLayerUsageDebugColorMemberName()`
- L173 _public prototype_ `void SetLayerUsageDebugColor(const FLinearColor& InLayerUsageDebugColor, bool bInModify, EPropertyChangeType::Type InChangeType);`
- L176 _public function_ `inline float GetMinimumCollisionRelevanceWeight() const`
- L180 _public function_ `static FName GetMinimumCollisionRelevanceWeightMemberName()`
- L184 _public prototype_ `void SetMinimumCollisionRelevanceWeight(float InMinimumCollisionRelevanceWeight, bool bInModify, EPropertyChangeType::Type InChangeType);`
- L186 _public function_ `inline TObjectPtr<UTexture2D> GetSplineFalloffModulationTexture() const`
- L190 _public function_ `static FName GetSplineFalloffModulationTextureMemberName()`
- L194 _public prototype_ `void SetSplineFalloffModulationTexture(TObjectPtr<UTexture2D> InSplineFalloffModulationTexture, bool bInModify);`
- L196 _public function_ `inline ESplineModulationColorMask GetSplineFalloffModulationColorMask() const`
- L200 _public function_ `static FName GetSplineFalloffModulationColorMaskMemberName()`
- L204 _public prototype_ `void SetSplineFalloffModulationColorMask(ESplineModulationColorMask InSplineFalloffModulationColorMask, bool bInModify);`
- L206 _public function_ `inline float GetSplineFalloffModulationTiling() const`
- L210 _public function_ `static FName GetSplineFalloffModulationTilingMemberName()`
- L214 _public prototype_ `void SetSplineFalloffModulationTiling(float InSplineFalloffModulationTiling, bool bInModify, EPropertyChangeType::Type InChangeType);`
- L216 _public function_ `inline float GetSplineFalloffModulationBias() const`
- L220 _public function_ `static FName GetSplineFalloffModulationBiasMemberName()`
- L224 _public prototype_ `void SetSplineFalloffModulationBias(float InSplineFalloffModulationBias, bool bInModify, EPropertyChangeType::Type InChangeType);`
- L226 _public function_ `inline float GetSplineFalloffModulationScale() const`
- L230 _public function_ `static FName GetSplineFalloffModulationScaleMemberName()`
- L234 _public prototype_ `void SetSplineFalloffModulationScale(float InSplineFalloffModulationScale, bool bInModify, EPropertyChangeType::Type InChangeType);`
- L238 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L242 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L243 _public prototype_ `virtual void PostLoad() override;`
- L247 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLayerInfoDataChanged, const FOnLandscapeLayerInfoDataChangedParams& );` — Delegate triggered whenever a change occurrs in the layer info object data
- L248 _public function_ `FOnLayerInfoDataChanged::RegistrationType& OnLayerInfoChanged() const`
- L253 _public prototype_ `void BroadcastOnLayerInfoObjectDataChanged(FName InPropertyName, bool bInUserTriggered, bool bInRequiresLandscapeUpdate, bool bInHasValueChanged, EPropertyChangeType::Type InChangeType);`
- L256 _public prototype_ `FLinearColor GenerateLayerUsageDebugColor() const;`
- L260 _private member_ `ELandscapeTargetLayerBlendMethod BlendMethod = ELandscapeTargetLayerBlendMethod::None;` — `UPROPERTY(EditAnywhere, Category = LandscapeLayerInfoObject, Meta = (Tooltip = "Allows this layer's final weight to be adjusted against others."))`
- L263 _private member_ `FName BlendGroup;` — `UPROPERTY(EditAnywhere, Category = LandscapeLayerInfoObject, Meta = (EditCondition = "BlendMethod == ELandscapeTargetLayerBlendMethod::PremultipliedAlphaBlending", Tooltip = "Only available for Advanced Weight Blending. Allows target layers from the same group only to have their weight adjusted against one another."))`
- L266 _private member_ `mutable FOnLayerInfoDataChanged OnLayerInfoObjectChangedDelegate;`

#### Free symbols / members of external scopes

- L247 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnLayerInfoDataChanged, const FOnLandscapeLayerInfoDataChangedParams& );` — Delegate triggered whenever a change occurrs in the layer info object data

### `Source/Runtime/Landscape/Classes/LandscapeMaterialInstanceConstant.h` (Public)


#### struct `FLandscapeMaterialTextureStreamingInfo`  
`struct FLandscapeMaterialTextureStreamingInfo`  
_L11-24_
- reflection: `USTRUCT()`
- L15 _public function_ `FLandscapeMaterialTextureStreamingInfo() : TexelFactor(0.0f)`
- L20 _public member_ `FName TextureName;` — `UPROPERTY()`
- L23 _public member_ `float TexelFactor;` — `UPROPERTY()`

#### class `ULandscapeMaterialInstanceConstant`  
`class ULandscapeMaterialInstanceConstant : public UMaterialInstanceConstant`  
_L27-62_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMaterialInstanceConstant`
- L32 _private member_ `TArray<FLandscapeMaterialTextureStreamingInfo> TextureStreamingInfo;` — `UPROPERTY()`
- L35 _private member_ `uint32 bIsLayerThumbnail:1;` — `UPROPERTY()`
- L38 _private member_ `uint32 bDisableTessellation_DEPRECATED:1;` — `UPROPERTY()`
- L41 _private member_ `uint32 bMobile:1;` — `UPROPERTY()`
- L44 _private member_ `uint32 bEditorToolUsage:1;` — `UPROPERTY()`
- L46 _private prototype_ `virtual bool WritesToRuntimeVirtualTexture() const override;`
- L48 _private prototype_ `virtual void PostLoad() override;`
- L50 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L52 _private prototype_ `virtual FMaterialResource* AllocatePermutationResource() override;`
- L53 _private prototype_ `virtual bool HasOverridenBaseProperties() const override;`
- L56 _private prototype_ `FLandscapeMaterialTextureStreamingInfo& AcquireTextureStreamingInfo(const FName& TextureName);`
- L57 _private prototype_ `void UpdateCachedTextureStreaming();`
- L61 _public prototype_ `float GetLandscapeTexelFactor(const FName& TextureName) const;`

### `Source/Runtime/Landscape/Classes/LandscapeMeshCollisionComponent.h` (Public)


#### class `ULandscapeMeshCollisionComponent_DEPRECATED`  
`class UE_DEPRECATED(5.7, "RetopologizeTool/XYOffset deprecated with the removal of non-edit layer landscapes") ULandscapeMeshCollisionComponent_DEPRECATED : public ULandscapeHeightfieldCollisionComponent`  
_L24-57_
- reflection: `UCLASS()`
- inherits: `ULandscapeHeightfieldCollisionComponent`
- L30 _public member_ `FGuid MeshGuid;` — `UPROPERTY()`
- L52 _public member_ `FWordBulkData CollisionXYOffsetData;` — The collision mesh values.
- L56 _public member_ `TRefCountPtr<FTriMeshGeometryRef> MeshRef;` — Physics engine version of heightfield data.

#### struct `ULandscapeMeshCollisionComponent_DEPRECATED::FTriMeshGeometryRef`  
`struct UE_DEPRECATED(5.7, "RetopologizeTool/XYOffset deprecated with the removal of non-edit layer landscapes") FTriMeshGeometryRef : public FRefCountedObject`  
_L32-48_
- inherits: `FRefCountedObject`
- L34 _public member_ `FGuid Guid;`
- L36 _public member_ `TArray<Chaos::FMaterialHandle> UsedChaosMaterials;`
- L37 _public member_ `Chaos::FTriangleMeshImplicitObjectPtr TrimeshGeometry;`
- L40 _public member_ `Chaos::FTriangleMeshImplicitObjectPtr EditorTrimeshGeometry;`
- L43 _public prototype_ `FTriMeshGeometryRef();`
- L44 _public prototype_ `FTriMeshGeometryRef(FGuid& InGuid);`
- L45 _public prototype_ `virtual ~FTriMeshGeometryRef();`
- L47 _public prototype_ `void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize);`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace Chaos`

### `Source/Runtime/Landscape/Classes/LandscapeMeshProxyActor.h` (Public)


#### class `ALandscapeMeshProxyActor`  
`class ALandscapeMeshProxyActor : public AActor`  
_L12-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L18 _private member_ `TObjectPtr<class ULandscapeMeshProxyComponent> LandscapeMeshProxyComponent;` — `UPROPERTY(Category = LandscapeMeshProxyActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh", AllowPrivateAccess = "true"))`
- L22 _public function_ `class ULandscapeMeshProxyComponent* GetLandscapeMeshProxyComponent() const` — Returns StaticMeshComponent subobject

### `Source/Runtime/Landscape/Classes/LandscapeMeshProxyComponent.h` (Public)


#### class `ULandscapeMeshProxyComponent`  
`class ULandscapeMeshProxyComponent : public UStaticMeshComponent`  
_L16-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UStaticMeshComponent`
- L21 _public prototype_ `ULandscapeMeshProxyComponent(const FObjectInitializer& ObjectInitializer);`
- L26 _private member_ `FGuid LandscapeGuid;` — `UPROPERTY()` — The landscape this proxy was generated for
- L30 _private member_ `TArray<FIntPoint> ProxyComponentBases;` — `UPROPERTY()` — The section coordinates of the landscape components that this proxy was generated for.  Used to register with LandscapeRender when LODGroupKey == 0
- L34 _private member_ `TArray<FVector> ProxyComponentCentersObjectSpace;` — `UPROPERTY()` — The center of the landscape components that this proxy was generated for, in local component space.  Used to register with LandscapeRender when LODGroupKey != 0
- L37 _private member_ `FVector ComponentXVectorObjectSpace;` — `UPROPERTY()`
- L40 _private member_ `FVector ComponentYVectorObjectSpace;` — `UPROPERTY()`
- L43 _private member_ `int32 ComponentResolution;` — `UPROPERTY()`
- L47 _private member_ `int8 ProxyLOD;` — `UPROPERTY()` — LOD level this proxy was generated for
- L50 _private member_ `uint32 LODGroupKey;` — `UPROPERTY()`
- L53 _public prototype_ `void InitializeForLandscape(ALandscapeProxy* Landscape, int8 InProxyLOD);`
- L55 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L56 _public prototype_ `virtual void PostLoad() override;`

### `Source/Runtime/Landscape/Classes/LandscapeNaniteComponent.h` (Public)


#### struct `UE::Landscape::Nanite::FAsyncComponentData`  
`struct FAsyncComponentData`  
_L25-31_
- desc: Copy of Component level data required to generate Nanite asynchronously
- L27 _public member_ `TArray<FColor> HeightAndNormalData;`
- L28 _public member_ `TArray<uint8> Visibility;`
- L29 _public member_ `TSharedPtr<FLandscapeComponentDataInterfaceBase> ComponentDataInterface;`
- L30 _public member_ `int32 Stride = 0;`

#### struct `UE::Landscape::Nanite::FAsyncBuildData`  
`struct FAsyncBuildData`  
_L35-78_
- desc: Context for an Async Static Mesh (nanite) build Also serving double duty as input parameter bag for ExportToRawMeshDataCopy
- L37 _public typedef_ `using ComponentDataMap = TMap<ULandscapeComponent*, FAsyncComponentData>;`
- L38 _public member_ `ComponentDataMap ComponentData;`
- L40 _public member_ `TWeakObjectPtr<ALandscapeProxy> LandscapeWeakRef;`
- L41 _public member_ `TWeakObjectPtr<ULandscapeSubsystem> LandscapeSubSystemWeakRef;`
- L43 _public member_ `TStrongObjectPtr<UStaticMesh> NaniteStaticMesh;`
- L44 _public member_ `FMeshDescription* NaniteMeshDescription = nullptr;`
- L46 _public member_ `TArray<UMaterialInterface*, TInlineAllocator<4>> InputMaterials;`
- L47 _public member_ `TArray<FName, TInlineAllocator<4>> InputMaterialSlotNames;`
- L48 _public member_ `TInlineComponentArray<ULandscapeComponent*> InputComponents;`
- L49 _public member_ `FStaticMeshSourceModel* SourceModel = nullptr;`
- L50 _public member_ `TSharedPtr<FStaticMeshAttributes> MeshAttributes;`
- L53 _public member_ `FGraphEventRef BuildCompleteEvent;` — event triggered when this build is complete (only used in the async case)
- L55 _public member_ `int32 LOD = 0;`
- L57 _public member_ `std::atomic<bool> bExportResult = false;`
- L58 _public member_ `std::atomic<bool> bIsComplete = false;`
- L59 _public member_ `std::atomic<bool> bCancelled = false;`
- L60 _public member_ `std::atomic<bool> bStaticMeshNeedsToCallPostMeshBuild = false;` — true if we are waiting for the UStaticMesh PostMeshBuild async callback
- L61 _public member_ `FDelegateHandle PostMeshBuildDelegateHandle;` — post mesh build delegate handle (so we can remove it cleanly)
- L63 _public member_ `bool bWarnedStall = false;` — true if we've notified the user of a stall on this task
- L65 _public member_ `double TimeStamp_Requested = -1.0;` — when the Nanite build was requested
- L66 _public member_ `double TimeStamp_ExportMeshStart = -1.0;` — start of the export mesh task
- L67 _public member_ `double TimeStamp_ExportMeshEnd = -1.0;` — end of the export mesh task
- L68 _public member_ `double TimeStamp_StaticMeshBuildStart = -1.0;` — start of the mesh build task
- L69 _public member_ `double TimeStamp_StaticMeshBatchBuildStart = -1.0;` — call to UStaticMesh::BatchBuild
- L70 _public member_ `double TimeStamp_StaticMeshBatchBuildPostMeshBuildCall = -1.0;` — when we received the async PostMeshBuild callback (if async) - may be out of order
- L71 _public member_ `double TimeStamp_StaticMeshBuildEnd = -1.0;` — end of the mesh build task
- L72 _public member_ `double TimeStamp_LandscapeUpdateStart = -1.0;` — start of the LandscapeUpdate / CompleteStaticMesh call
- L73 _public member_ `double TimeStamp_LandscapeUpdateEnd = -1.0;` — end of the LandscapeUpdate / CompleteStaticMesh call
- L74 _public member_ `double TimeStamp_Complete = -1.0;` — time we marked the task bIsComplete
- L75 _public member_ `double TimeStamp_Cancelled = -1.0;` — first time that the pipeline realized the task was cancelled
- L77 _public prototype_ `bool CheckForStallAndWarn();`

#### class `ULandscapeNaniteComponent`  
`class ULandscapeNaniteComponent : public UStaticMeshComponent`  
_L82-166_
- reflection: `UCLASS(hidecategories = (Display, Attachment, Physics, Debug, Collision, Movement, Rendering, PrimitiveComponent, Object, Transform, Mobility, VirtualTexture), showcategories = ("Rendering|Material"), MinimalAPI, Within = LandscapeProxy)`
- inherits: `UStaticMeshComponent`
- L87 _public prototype_ `ULandscapeNaniteComponent(const FObjectInitializer& ObjectInitializer);`
- L89 _public prototype_ `virtual void PostLoad() override;`
- L92 _public prototype_ `ALandscapeProxy* GetLandscapeProxy() const;` — Gets the landscape proxy actor which owns this component
- L95 _public prototype_ `ALandscape* GetLandscapeActor() const;` — Get the landscape actor associated with this component.
- L97 _public function_ `inline const FGuid& GetProxyContentId() const`
- L102 _public function_ `void SetProxyContentId(const FGuid& InProxyContentId)`
- L107 _public prototype_ `void UpdatedSharedPropertiesFromActor();`
- L109 _public prototype_ `void SetEnabled(bool bValue);`
- L111 _public function_ `inline bool IsEnabled() const`
- L116 _public function_ `virtual bool NeedsLoadForServer() const override`
- L117 _public prototype_ `virtual bool NeedsLoadForTargetPlatform(const class ITargetPlatform* TargetPlatform) const override;`
- L120 _public prototype_ `void UpdateMaterials();` — Copy the materials from the source ULandscapeComponents to this ULandscapeNaniteComponent's StaticMesh
- L122 _public function_ `inline const TArray<TObjectPtr<ULandscapeComponent>>& GetSourceLandscapeComponents() const`
- L123 _public prototype_ `void SetSourceLandscapeComponents(const TArray<ULandscapeComponent*>& InSourceLandscapeComponents);`
- L127 _private prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams) override;` — Collect all the PSO precache data used by the static mesh component
- L131 _private member_ `FGuid ProxyContentId;` — `UPROPERTY()` — The landscape proxy identity this Nanite representation was generated for
- L134 _private member_ `bool bEnabled;` — `UPROPERTY(Transient)`
- L138 _private member_ `TArray<TObjectPtr<ULandscapeComponent>> SourceLandscapeComponents;` — `UPROPERTY()` — Landscape Components which were used to generate this ULandscapeNaniteComponent
- L149 _public prototype_ `bool InitializeForLandscape(ALandscapeProxy* Landscape, const FGuid& NewProxyContentId, const TArray<ULandscapeComponent*>& InComponentsToExport, int32 InNaniteComponentIndex);` — Generates the Nanite static mesh, stores the content Id. @param Landscape Proxy to generate the mesh for @param NewProxyContentId Hash of the content that this mesh corresponds to @return true if the Nanite mesh creation was successful
- L151 _public prototype_ `FGraphEventRef InitializeForLandscapeAsync(ALandscapeProxy* Landscape, const FGuid& NewProxyContentId, const TArray<ULandscapeComponent*>& InComponentsToExport, int32 InNaniteComponentIndex);`
- L160 _public prototype_ `bool InitializePlatformForLandscape(ALandscapeProxy* Landscape, const ITargetPlatform* TargetPlatform);` — Ensures the cooked cached platform data of the Nanite static mesh is finished. It is necessary to ensure that StreamablePages are loaded from DDC @param Landscape Proxy for this Nanite landscape component @param TargetPlatform info about the platform being cooked @return true if the Nanite mesh creation was successful
- L163 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L165 _public prototype_ `virtual bool IsHLODRelevant() const override;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Landscape` (scope `UE`)
- L22 _namespace_ `namespace Nanite` (scope `UE::Landscape`)

### `Source/Runtime/Landscape/Classes/LandscapePhysicalMaterial.h` (Public)


#### class `FLandscapePhysicalMaterialRenderTask`  
`class FLandscapePhysicalMaterialRenderTask`  
_L16-61_
- desc: A single task for calculating the landscape physical material. The work uses the GPU so this object handles reading back the data without stalling. We need to call Tick() until IsComplete() returns true. We need to call Release() after use to prevent leaking of internal objects. All calls are expected to be made on the game thread only.
- L19 _public function_ `FLandscapePhysicalMaterialRenderTask()`
- L22 _public function_ `~FLandscapePhysicalMaterialRenderTask()`
- L28 _public prototype_ `bool Init(class ULandscapeComponent const* LandscapeComponent, uint32 InHash);` — Initialize the task for a component. A task in progress can safely call Init() again to rekick the task. Returns false if no physical material needs to be rendered.
- L30 _public prototype_ `void Release();` — Release the task. After calling this IsValid() will return false until we call Init() again.
- L33 _public prototype_ `bool IsValid() const;` — Returns true if Init() has been called without a Release().
- L35 _public prototype_ `bool IsComplete() const;` — Returns true if the task is complete and the result is available.
- L37 _public prototype_ `bool IsInProgress() const;` — Is this Task in progress (valid and incomplete)
- L41 _public prototype_ `void Tick();` — Update a task. Does nothing if the task is complete.
- L43 _public prototype_ `void Flush();` — Flush a task to completion. This may stall waiting for completion.
- L46 _public prototype_ `TArray<uint8> const& GetResultIds() const;` — Get the result data. Assumes that IsComplete() is true. This doesn't Release() the data.
- L48 _public prototype_ `TArray <class UPhysicalMaterial* > const& GetResultMaterials() const;` — Get the result data. Assumes that IsComplete() is true. This doesn't Release() the data.
- L50 _public function_ `uint32 GetHash() const`
- L52 _private prototype_ `void UpdateInternal(bool bInFlush);`
- L55 _private member_ `int32 PoolHandle = -1;`
- L58 _private prototype_ `FLandscapePhysicalMaterialRenderTask(FLandscapePhysicalMaterialRenderTask const&);`
- L60 _private member_ `uint32 Hash = 0;`

#### Free symbols / members of external scopes

- L63 _namespace_ `namespace LandscapePhysicalMaterial`
- L66 _prototype_ `void GarbageCollectTasks();` (scope `LandscapePhysicalMaterial`) — Optional call to allow garbage collection of any FLandscapePhysicalMaterialRenderTask resources and check for leaks.

### `Source/Runtime/Landscape/Classes/LandscapeProxy.h` (Public)


#### struct `FOnLandscapeProxyMaterialChangedParams`  
`struct FOnLandscapeProxyMaterialChangedParams`  
_L71-73_

#### struct `FOnLandscapeProxyFixupSharedDataParams`  
`struct FOnLandscapeProxyFixupSharedDataParams`  
_L76-82_
- L79 _public member_ `ALandscape* Landscape = nullptr;` — Parent landscape actor for the landscape proxy on which OnLandscapeProxyFixupSharedData is triggered
- L81 _public member_ `bool bUpgradeSharedPropertiesPerformed = false;` — Indicates whether UpgradeSharedProperties has been called on this proxy already (before this call)

#### struct `FLandscapeGrassName`  
`struct FLandscapeGrassName`  
_L91-114_
- reflection: `USTRUCT()`
- desc: This struct is a FName wrapper.It's just a little trick to be able to customize the display of the grass name in such a way that it can work as a TMap's key.
- L95 _public prototype_ `FLandscapeGrassName() = default;`
- L96 _public function_ `FLandscapeGrassName(const FName& InName) : Name(InName)`
- L101 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category=Grass)`
- L104 _public function_ `inline bool operator==(FLandscapeGrassName const& Other) const` — Used so we can have a TMap of this struct

#### struct `FLandscapeTargetLayerSettings`  
`struct FLandscapeTargetLayerSettings`  
_L119-143_
- reflection: `USTRUCT()`
- L124 _public member_ `TObjectPtr<ULandscapeLayerInfoObject> LayerInfoObj;` — `UPROPERTY(Category = "General", EditAnywhere)`
- L128 _public member_ `FString ReimportLayerFilePath;` — `UPROPERTY()`
- L130 _public prototype_ `FLandscapeTargetLayerSettings() = default;`
- L132 _public function_ `explicit FLandscapeTargetLayerSettings(ULandscapeLayerInfoObject* InLayerInfo, const FString& InFilePath = FString()) : LayerInfoObj(InLayerInfo) , ReimportLayerFilePath(InFilePath)`
- L138 _public function_ `bool operator==(const FLandscapeTargetLayerSettings& Other) const`

#### struct `FLandscapeEditorLayerSettings`  
`struct UE_DEPRECATED(all, "FLandscapeEditorLayerSettings is deprecated; please use FLandscapeTargetLayerSettings instead") FLandscapeEditorLayerSettings`  
_L146-175_
- reflection: `USTRUCT()`
- L152 _public member_ `TObjectPtr<ULandscapeLayerInfoObject> LayerInfoObj;` — `UPROPERTY()`
- L155 _public member_ `FString ReimportLayerFilePath;` — `UPROPERTY()`
- L157 _public function_ `FLandscapeEditorLayerSettings() : LayerInfoObj(nullptr) , ReimportLayerFilePath()`
- L163 _public function_ `explicit FLandscapeEditorLayerSettings(ULandscapeLayerInfoObject* InLayerInfo, const FString& InFilePath = FString()) : LayerInfoObj(InLayerInfo) , ReimportLayerFilePath(InFilePath)`
- L170 _public function_ `bool operator==(const ULandscapeLayerInfoObject* LayerInfo) const` — To allow FindByKey etc

#### enum `ELandscapeImportAlphamapType`  
`enum class ELandscapeImportAlphamapType : uint8`  
_L178-189_
- reflection: `UENUM()`
- L183 _public enumerator_ `Additive` — Three layers blended 50/30/20 represented as 0.5, 0.3, and 0.2 in the alpha maps All alpha maps for blended layers total to 1.0 This is the style used by UE internally for blended layers
- L188 _public enumerator_ `Layered` — Three layers blended 50/30/20 represented as 0.5, 0.6, and 1.0 in the alpha maps Each alpha map only specifies the remainder from previous layers, so the last layer used will always be 1.0 Some other tools use this format

#### struct `FLandscapeImportLayerInfo`  
`struct FLandscapeImportLayerInfo`  
_L193-221_
- reflection: `USTRUCT()`
- desc: Structure storing Layer Data for import
- L199 _public member_ `FName LayerName;` — `UPROPERTY(Category="Import", VisibleAnywhere)`
- L202 _public member_ `TObjectPtr<ULandscapeLayerInfoObject> LayerInfo;` — `UPROPERTY(Category="Import", EditAnywhere, meta=(NoCreate))`
- L205 _public member_ `FString SourceFilePath;` — `UPROPERTY(Category="Import", EditAnywhere, meta=(DisplayName="Layer File"))` — Optional
- L208 _public member_ `TArray<uint8> LayerData;` — Raw weightmap data
- L212 _public function_ `FLandscapeImportLayerInfo(FName InLayerName = NAME_None) : LayerName(InLayerName) , LayerInfo(nullptr) , SourceFilePath("")`
- L219 _public prototype_ `FLandscapeImportLayerInfo(const FLandscapeInfoLayerSettings& InLayerSettings);`

#### enum `ELandscapeLayerPaintingRestriction`  
`enum class ELandscapeLayerPaintingRestriction : uint8`  
_L227-240_
- reflection: `UENUM()`
- desc: this is only here because putting it in LandscapeEditorObject.h (where it belongs) results in Engine being dependent on LandscapeEditor, as the actual landscape editing code (e.g. LandscapeEdit.h) is in /Engine/ for some reason...
- L230 _public enumerator_ `None UMETA(DisplayName="None")` — No restriction, can paint anywhere (default).
- L233 _public enumerator_ `UseMaxLayers UMETA(DisplayName="Limit Layer Count")` — Uses the MaxPaintedLayersPerComponent setting from the LandscapeProxy.
- L236 _public enumerator_ `ExistingOnly UMETA(DisplayName="Existing Layers Only")` — Restricts painting to only components that already have this layer.
- L239 _public enumerator_ `UseComponentAllowList UMETA(DisplayName="Component Allow List")` — Restricts painting to only components that have this layer in their allow list.

#### enum `ELandscapeLayerDisplayMode`  
`enum class ELandscapeLayerDisplayMode : uint8`  
_L243-256_
- reflection: `UENUM()`
- L246 _public enumerator_ `Default` — Material sorting display mode
- L249 _public enumerator_ `Alphabetical` — Alphabetical sorting display mode
- L252 _public enumerator_ `UserSpecific` — User specific sorting display mode
- L255 _public enumerator_ `ByBlendMethod` — By blend type sorting display mode

#### enum `ELandscapeHLODTextureSizePolicy`  
`enum class ELandscapeHLODTextureSizePolicy : uint8`  
_L259-266_
- reflection: `UENUM()`
- L262 _public enumerator_ `AutomaticSize` — Automatic texture size, based on the expected HLOD draw distance and the landscape size.
- L265 _public enumerator_ `SpecificSize` — User specified texture size.

#### enum `ELandscapeHLODMeshSourceLODPolicy`  
`enum class ELandscapeHLODMeshSourceLODPolicy : uint8`  
_L269-279_
- reflection: `UENUM()`
- L272 _public enumerator_ `AutomaticLOD` — Automatic LOD selection, based on the expected HLOD draw distance and the landscape LOD Distribution settings.
- L275 _public enumerator_ `SpecificLOD` — User specified landscape LOD.
- L278 _public enumerator_ `LowestDetailLOD` — Use the lowest detailed LOD of this landscape.

#### enum `ELandscapeLODFalloff::Type`  
`enum Type : int`  
_L284-290_
- L287 _public enumerator_ `Linear UMETA(DisplayName = "Linear")` — Default mode.
- L289 _public enumerator_ `SquareRoot UMETA(DisplayName = "Square Root")` — Square Root give more natural transition, and also keep the same LOD.

#### struct `FCachedLandscapeFoliage`  
`struct FCachedLandscapeFoliage`  
_L293-390_
- L332 _public function_ `friend uint32 GetTypeHash(const FGrassCompKey& Key)`
- L383 _public typedef_ `typedef TSet<FGrassComp, FGrassCompKeyFuncs> TGrassSet;`
- L384 _public member_ `TSet<FGrassComp, FGrassCompKeyFuncs> CachedGrassComps;`
- L386 _public function_ `void ClearCache()`

#### struct `FCachedLandscapeFoliage::FGrassCompKey`  
`struct FGrassCompKey`  
_L295-337_
- L297 _public member_ `TWeakObjectPtr<ULandscapeComponent> BasedOn;`
- L300 _public member_ `TWeakObjectPtr<ULandscapeGrassType> GrassType;` — We store both the GrassName and GrassType in the key, since they're not entirely synonymous anymore : A given grass type can be used by 2 different grass names now. They will be treated as 2 separate entries in the foliage cache
- L301 _public member_ `FName GrassName;`
- L302 _public member_ `int32 SqrtSubsections;`
- L303 _public member_ `int32 CachedMaxInstancesPerComponent;`
- L304 _public member_ `int32 SubsectionX;`
- L305 _public member_ `int32 SubsectionY;`
- L306 _public member_ `int32 NumVarieties;`
- L307 _public member_ `int32 VarietyIndex;`
- L309 _public function_ `FGrassCompKey() : SqrtSubsections(0) , CachedMaxInstancesPerComponent(0) , SubsectionX(0) , SubsectionY(0) , NumVarieties(0) , VarietyIndex(-1)`
- L318 _public function_ `inline bool operator==(const FGrassCompKey& Other) const`

#### struct `FCachedLandscapeFoliage::FGrassComp`  
`struct FGrassComp`  
_L339-363_
- L341 _public member_ `FGrassCompKey Key;`
- L342 _public member_ `TWeakObjectPtr<UHierarchicalInstancedStaticMeshComponent> Foliage;`
- L343 _public member_ `TWeakObjectPtr<UHierarchicalInstancedStaticMeshComponent> PreviousFoliage;`
- L344 _public member_ `TArray<FBox> ExcludedBoxes;`
- L345 _public member_ `uint32 LastUsedFrameNumber;`
- L346 _public member_ `uint32 ExclusionChangeTag;`
- L347 _public member_ `double LastUsedTime;`
- L348 _public member_ `bool Pending;`
- L349 _public member_ `bool PendingRemovalRebuild;`
- L351 _public function_ `FGrassComp() : ExclusionChangeTag(0) , Pending(true) , PendingRemovalRebuild(false)`
- L358 _public function_ `void Touch()`

#### struct `FCachedLandscapeFoliage::FGrassCompKeyFuncs`  
`struct FGrassCompKeyFuncs : BaseKeyFuncs<FGrassComp,FGrassCompKey>`  
_L365-381_
- inherits: `BaseKeyFuncs<FGrassComp,FGrassCompKey>`
- L367 _public function_ `static KeyInitType GetSetKey(const FGrassComp& Element)`
- L372 _public function_ `static bool Matches(KeyInitType A, KeyInitType B)`
- L377 _public function_ `static uint32 GetKeyHash(KeyInitType Key)`

#### class `FAsyncGrassTask`  
`class FAsyncGrassTask : public FNonAbandonableTask`  
_L392-408_
- inherits: `FNonAbandonableTask`
- L395 _public member_ `FAsyncGrassBuilder* Builder;`
- L396 _public member_ `FCachedLandscapeFoliage::FGrassCompKey Key;`
- L397 _public member_ `TWeakObjectPtr<UHierarchicalInstancedStaticMeshComponent> Foliage;`
- L399 _public prototype_ `FAsyncGrassTask(FAsyncGrassBuilder* InBuilder, const FCachedLandscapeFoliage::FGrassCompKey& InKey, UHierarchicalInstancedStaticMeshComponent* InFoliage);`
- L400 _public prototype_ `void DoWork();`
- L402 _public function_ `FORCEINLINE TStatId GetStatId() const`
- L407 _public prototype_ `~FAsyncGrassTask();`

#### struct `FLandscapeProxyMaterialOverride`  
`struct UE_DEPRECATED(all, "FLandscapeProxyMaterialOverride is deprecated; please use FLandscapePerLODMaterialOverride instead") FLandscapeProxyMaterialOverride`  
_L411-420_
- reflection: `USTRUCT(meta = (Deprecated = "5.1"))`
- L416 _public member_ `FPerPlatformInt LODIndex;` — `UPROPERTY()`
- L419 _public member_ `TObjectPtr<UMaterialInterface> Material = nullptr;` — `UPROPERTY()`

#### struct `FAsyncWorkMonitor`  
`struct FAsyncWorkMonitor`  
_L426-447_
- desc: Tracks delayed updates triggered by landscape updates. It's responsible for preventing expensive async operations while the user is still editing the landscape
- L435 _public prototype_ `bool CheckIfUpdateTriggeredAndClear(EAsyncWorkType WorkType);`
- L436 _public prototype_ `void SetDelayedUpdateTimer(EAsyncWorkType WorkType, float InSecondsUntilDelayedUpdateTrigger);`
- L437 _public prototype_ `void Tick(float Detaltime);`
- L446 _private member_ `TStaticArray<FAsyncWorkTypeInfo, static_cast<uint32>(EAsyncWorkType::Max)> WorkTypeInfos;` — [static_cast<uint32>(EAsyncWorkType::Max)] ;

#### enum `FAsyncWorkMonitor::EAsyncWorkType`  
`enum class EAsyncWorkType : uint8`  
_L429-433_
- L431 _public enumerator_ `BuildNaniteMeshes`
- L432 _public enumerator_ `Max`

#### struct `FAsyncWorkMonitor::FAsyncWorkTypeInfo`  
`struct FAsyncWorkTypeInfo`  
_L440-444_
- L442 _public member_ `bool bUpdateTriggered = false;`
- L443 _public member_ `float SecondsUntilDelayedUpdateTrigger = 0.0f;`

#### class `ALandscapeProxy`  
`class ALandscapeProxy : public APartitionActor, public ILandscapeSplineInterface`  
_L450-1746_
- reflection: `UCLASS(Abstract, MinimalAPI, NotBlueprintable, NotPlaceable, hidecategories=(Display, Attachment, Physics, Debug, Lighting), showcategories=(Lighting, Rendering, Transformation), hidecategories=(Mobility))`
- inherits: `APartitionActor,ILandscapeSplineInterface`
- L455 _public prototype_ `ALandscapeProxy(const FObjectInitializer& ObjectInitializer);`
- L457 _public prototype_ `virtual ~ALandscapeProxy();`
- L469 _protected member_ `TSet<FWorldPartitionReference> ActorDescReferences;` — Hard refs to actors that need to be loaded when this proxy is loaded. It is currently used for 2 cases : 1- ALandscapeStreamingProxy forces the loading of its intersecting ALandscapeSplineActor. 2- ALandscape forces the loading of its child landscape proxies when the Landscape has Layer brushes. This is a temporary solution until landscape layer brushes support partial landscape loading.
- L475 _protected member_ `TObjectPtr<ULandscapeSplinesComponent> SplineComponent;` — `UPROPERTY()`
- L481 _protected member_ `FGuid LandscapeGuid;` — `UPROPERTY(meta = (LandscapeInherited))` — Guid for LandscapeEditorInfo, all proxies that belong to the same landscape should have the same LandscapeGuid, even if split across world partitions Note that this value may change when the landscape is instanced (or in PIE) in order to allow multiple instances of the same landscape to exist.
- L487 _protected member_ `FGuid OriginalLandscapeGuid;` — `UPROPERTY(Transient, DuplicateTransient, meta = (LandscapeInherited))` — The original unmutated LandscapeGuid on the source asset, before instancing modifications.
- L491 _protected member_ `bool bEnableNanite = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Nanite, meta = (LandscapeInherited))` — Use Nanite to render landscape as a mesh on supported platforms.
- L495 _protected member_ `TArray<FLandscapePerLODMaterialOverride> PerLODOverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = Landscape, meta = (LandscapeOverridable))` — Specify an alternate material to use for a given LOD level (for example, to use a simpler material at a distance) This is not effective on Nanite landscape.
- L500 _protected member_ `int32 NaniteLODIndex = 0;` — `UPROPERTY(EditAnywhere, Category = Nanite, AdvancedDisplay, meta = (EditCondition = "bEnableNanite", LandscapeInherited))` — LOD level of the landscape when generating the Nanite mesh. Mostly there for debug reasons, since Nanite is meant to allow high density meshes, we want to use 0 most of the times.
- L503 _protected member_ `bool bNaniteSkirtEnabled = false;` — `UPROPERTY(EditAnywhere, Category = Nanite, AdvancedDisplay, meta = (EditCondition = "bEnableNanite", LandscapeInherited))`
- L506 _protected member_ `float NaniteSkirtDepth = 0.1f;` — `UPROPERTY(EditAnywhere, Category = Nanite, AdvancedDisplay, meta = (EditCondition = "bEnableNanite", LandscapeInherited))`
- L509 _protected member_ `int32 NanitePositionPrecision = 0;` — `UPROPERTY(EditAnywhere, Category = Nanite, AdvancedDisplay, meta = (EditCondition = "bEnableNanite", LandscapeInherited))`
- L512 _protected member_ `float NaniteMaxEdgeLengthFactor = 16.0f;` — `UPROPERTY(EditAnywhere, Category = Nanite, AdvancedDisplay, meta = (EditCondition = "bEnableNanite", LandscapeInherited))`
- L514 _protected member_ `static FOnLandscapeProxyFixupSharedDataDelegate OnLandscapeProxyFixupSharedDataDelegate;`
- L519 _protected member_ `bool bDisableRuntimeGrassMapGeneration = false;` — `UPROPERTY(meta = (LandscapeInherited))` — Disable runtime grass data generation.  If disabled, the grass maps will be serialized at cook time. Do not set directly, use ALandscape::SetDisableRuntimeGrassMapGeneration to ensure it is set on all loaded proxies.
- L524 _public member_ `TMap<FName, TObjectPtr<ULandscapeLayerInfoObject>> TargetLayersForFixup;` — `UPROPERTY()`
- L527 _public member_ `FIntPoint LandscapeSectionOffset;` — `UE_DEPRECATED(5.7, "Use private SectionBase with GetSectionBase instead.")`
- L532 _public member_ `int32 MaxLODLevel;` — `UPROPERTY(EditAnywhere, Category=LOD, meta = (LandscapeInherited))` — Max LOD level to use when rendering, -1 means the max available
- L537 _public member_ `float LODDistanceFactor_DEPRECATED;` — `UE_DEPRECATED(all, "Unused property, replaced by LOD0DistributionSetting and LODDistributionSetting")` — `UPROPERTY()`
- L541 _public member_ `TEnumAsByte<ELandscapeLODFalloff::Type> LODFalloff_DEPRECATED;` — `UE_DEPRECATED(all, "Unused property, replaced by LOD0DistributionSetting and LODDistributionSetting")` — `UPROPERTY()`
- L546 _public member_ `float LOD0ScreenSize = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "LOD Distribution", meta = (EditCondition = "!bUseScalableLODSettings", DisplayName = "LOD 0 Screen Size", ClampMin = "0.1", ClampMax = "10.0", UIMin = "0.1", UIMax = "10.0", LandscapeInherited))` — This is the starting screen size used to calculate the distribution. You can increase the value if you want less LOD0 component, and you use very large landscape component.
- L550 _public member_ `uint32 LODGroupKey = 0;` — `UPROPERTY(EditAnywhere, Category = LOD, AdvancedDisplay, meta = (LandscapeInherited))` — Specifies the LOD Group (Zero is No Group). All landscapes in the same group calculate their LOD together, allowing matching border LODs to fix geometry seams.
- L554 _public member_ `float LOD0DistributionSetting = 1.25f;` — `UPROPERTY(EditAnywhere, Category = "LOD Distribution", meta = (EditCondition = "!bUseScalableLODSettings", DisplayName = "LOD 0", ClampMin = "1.0", ClampMax = "10.0", UIMin = "1.0", UIMax = "10.0", LandscapeInherited))` — The distribution setting used to change the LOD 0 generation, 1.25 is the normal distribution, numbers influence directly the LOD0 proportion on screen.
- L558 _public member_ `float LODDistributionSetting = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "LOD Distribution", meta = (EditCondition = "!bUseScalableLODSettings", DisplayName = "Other LODs", ClampMin = "1.0", ClampMax = "10.0", UIMin = "1.0", UIMax = "10.0", LandscapeInherited))` — The distribution setting used to change the LOD generation, 3 is the normal distribution, small number mean you want your last LODs to take more screen space and big number mean you want your first LODs to take more screen space.
- L562 _public member_ `FPerQualityLevelFloat ScalableLOD0ScreenSize = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "LOD Distribution", meta = (EditCondition = "bUseScalableLODSettings", DisplayName = "Scalable LOD 0 Screen Size", ClampMin = "0.1", ClampMax = "10.0", UIMin = "0.1", UIMax = "10.0", LandscapeInherited))` — Scalable (per-quality) version of 'LOD 0 Screen Size'.
- L566 _public member_ `FPerQualityLevelFloat ScalableLOD0DistributionSetting = 1.25f;` — `UPROPERTY(EditAnywhere, Category = "LOD Distribution", meta = (EditCondition = "bUseScalableLODSettings", DisplayName = "Scalable LOD 0", ClampMin = "1.0", ClampMax = "10.0", UIMin = "1.0", UIMax = "10.0", LandscapeInherited))` — Scalable (per-quality) version of 'LOD 0'.
- L570 _public member_ `FPerQualityLevelFloat ScalableLODDistributionSetting = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "LOD Distribution", meta = (EditCondition = "bUseScalableLODSettings", DisplayName = "Scalable Other LODs", ClampMin = "1.0", ClampMax = "10.0", UIMin = "1.0", UIMax = "10.0", LandscapeInherited))` — Scalable (per-quality) version of 'Other LODs'.
- L574 _public member_ `bool bUseScalableLODSettings = false;` — `UPROPERTY(EditAnywhere, Category = "LOD Distribution", meta = (LandscapeInherited))` — Allows to specify LOD distribution settings per quality level. Using this will ignore the r.LandscapeLOD0DistributionScale CVar.
- L578 _public member_ `float LODBlendRange = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "LOD Distribution", meta = (DisplayName = "Blend Range", ClampMin = "0.01", ClampMax = "1.0", UIMin = "0.01", UIMax = "1.0", LandscapeInherited))` — This controls the area that blends LOD between neighboring sections. At 1.0 it blends across the entire section, and lower numbers reduce the blend region to be closer to the boundary.
- L583 _public member_ `int32 ExportLOD;` — `UPROPERTY(EditAnywhere, Category=LOD, AdvancedDisplay, meta = (LandscapeOverridable))` — LOD level to use when exporting the landscape to obj or FBX
- L588 _public member_ `int32 StaticLightingLOD;` — `UPROPERTY(EditAnywhere, Category=Lighting, meta = (LandscapeOverridable))` — LOD level to use when running lightmass (increase to 1 or 2 for large landscapes to stop lightmass crashing)
- L592 _public member_ `TObjectPtr<UPhysicalMaterial> DefaultPhysMaterial;` — `UPROPERTY(EditAnywhere, Category=Landscape, meta = (LandscapeOverridable))` — Default physical material, used when no per-layer values physical materials
- L600 _public member_ `float StreamingDistanceMultiplier;` — `UPROPERTY(EditAnywhere, Category=Landscape, meta = (LandscapeOverridable))` — Allows artists to adjust the distance where textures using UV 0 are streamed in/out. 1.0 is the default, whereas a higher value increases the streamed-in resolution. Value can be < 0 (from legcay content, or code changes)
- L604 _public member_ `TObjectPtr<UMaterialInterface> LandscapeMaterial;` — `UPROPERTY(EditAnywhere, BlueprintSetter=EditorSetLandscapeMaterial, Category=Landscape, meta=(LandscapeOverridable))` — Combined material used to render the landscape
- L608 _public member_ `TObjectPtr<UMaterialInterface> LandscapeHoleMaterial;` — `UPROPERTY(EditAnywhere, Category=Landscape, AdvancedDisplay, meta = (LandscapeOverridable))` — Material used to render landscape components with holes. If not set, LandscapeMaterial will be used (blend mode will be overridden to Masked if it is set to Opaque)
- L616 _public member_ `TArray<FLandscapeProxyMaterialOverride> LandscapeMaterialsOverride_DEPRECATED;` — `UE_DEPRECATED(all, "LandscapeComponentMaterialOverride has been deprecated, use PerLODOverrideMaterials instead.")` — `UPROPERTY()`
- L626 _public member_ `TArray<TObjectPtr<URuntimeVirtualTexture>> RuntimeVirtualTextures;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VirtualTexture, meta = (DisplayName = "Draw in Virtual Textures", LandscapeOverridable))` — Array of runtime virtual textures into which we draw this landscape. The material also needs to be set up to output to a virtual texture.
- L630 _public member_ `bool bSetCreateRuntimeVirtualTextureVolumes;` — `UPROPERTY(VisibleAnywhere, Transient, Category = VirtualTexture)` — Placeholder for details customization button.
- L638 _public member_ `bool bVirtualTextureRenderWithQuad = false;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = VirtualTexture, meta = (LandscapeOverridable))` — Use a single quad to render this landscape to runtime virtual texture pages. This is the fastest path but it only gives correct results if the runtime virtual texture orientation is aligned with the landscape. If the two are unaligned we need to render to the virtual texture using LODs with sufficient density.
- L645 _public member_ `bool bVirtualTextureRenderWithQuadHQ = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = VirtualTexture, meta = (DisplayName = "High Quality PerPixel Height", EditCondition = "bVirtualTextureRenderWithQuad", LandscapeOverridable))` — Use highest quality heightmap interpolation when using a single quad to render this landscape to runtime virtual texture pages. This also requires the project setting: r.VT.RVT.HighQualityPerPixelHeight.
- L652 _public member_ `int32 VirtualTextureNumLods = 6;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = VirtualTexture, meta = (DisplayName = "Virtual Texture Num LODs", EditCondition = "!bVirtualTextureRenderWithQuad", UIMin = "0", UIMax = "7", LandscapeOverridable))` — Number of mesh levels to use when rendering landscape into runtime virtual texture. Lower values reduce vertex count when rendering to the runtime virtual texture but decrease accuracy when using values that require vertex interpolation.
- L659 _public member_ `int32 VirtualTextureLodBias = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = VirtualTexture, meta = (DisplayName = "Virtual Texture LOD Bias", EditCondition = "!bVirtualTextureRenderWithQuad", UIMin = "0", UIMax = "7", LandscapeOverridable))` — Bias to the LOD selected for rendering to runtime virtual textures. Higher values reduce vertex count when rendering to the runtime virtual texture.
- L663 _public member_ `ERuntimeVirtualTextureMainPassType VirtualTextureRenderPassType = ERuntimeVirtualTextureMainPassType::Always;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetVirtualTextureRenderPassType, Category = VirtualTexture, meta = (DisplayName = "Draw in Main Pass", LandscapeOverridable))` — Controls if this component draws in the main pass as well as in the virtual texture.
- L666 _public prototype_ `void SetVirtualTextureRenderPassType(ERuntimeVirtualTextureMainPassType InType);` — `UFUNCTION(BlueprintSetter)`
- L672 _public member_ `float NegativeZBoundsExtension;` — `UPROPERTY(EditAnywhere, Category=Landscape, meta = (LandscapeOverridable))` — Allows overriding the landscape bounds. This is useful if you distort the landscape with world-position-offset, for example Extension value in the negative Z axis, positive value increases bound size Note that this can also be overridden per-component when the component is selected with the component select tool
- L678 _public member_ `float PositiveZBoundsExtension;` — `UPROPERTY(EditAnywhere, Category=Landscape, meta = (LandscapeOverridable))` — Allows overriding the landscape bounds. This is useful if you distort the landscape with world-position-offset, for example Extension value in the positive Z axis, positive value increases bound size Note that this can also be overridden per-component when the component is selected with the component select tool
- L682 _public member_ `TArray<TObjectPtr<ULandscapeComponent>> LandscapeComponents;` — `UPROPERTY()` — The array of LandscapeComponent that are used by the landscape
- L686 _public member_ `TArray<TObjectPtr<ULandscapeHeightfieldCollisionComponent>> CollisionComponents;` — `UPROPERTY()` — Array of LandscapeHeightfieldCollisionComponent
- L689 _public member_ `TArray<TObjectPtr<UHierarchicalInstancedStaticMeshComponent>> FoliageComponents;` — `UPROPERTY(transient, duplicatetransient)`
- L693 _public member_ `TObjectPtr<ULandscapeNaniteComponent> NaniteComponent_DEPRECATED;` — `UE_DEPRECATED(all, "NaniteComponent has been deprecated, use NaniteComponents instead.")` — `UPROPERTY()`
- L696 _public member_ `TArray<TObjectPtr<ULandscapeNaniteComponent>> NaniteComponents;` — `UPROPERTY(NonTransactional, TextExportTransient, NonPIEDuplicateTransient)`
- L699 _public member_ `FCachedLandscapeFoliage FoliageCache;` — A transient data structure for tracking the grass
- L701 _public member_ `TArray<FAsyncTask<FAsyncGrassTask>* > AsyncFoliageTasks;` — A transient data structure for tracking the grass tasks
- L703 _public member_ `uint32 FrameOffsetForTickInterval;` — Frame offset for tick interval
- L708 _public member_ `float GrassTypesMaxDiscardDistance = 0.0f;` — `UPROPERTY()` — Only used outside of the editor (e.g. in cooked builds) - this value is no longer authoritative TODO [chris.tchou] remove Cached grass max discard distance for all grass types in all landscape components with landscape grass configured
- L722 _public member_ `FGrassTypeSummary GrassTypeSummary;`
- L723 _public function_ `inline bool IsGrassTypeSummaryValid()`
- L724 _public function_ `inline void InvalidateGrassTypeSummary()`
- L725 _public prototype_ `void UpdateGrassTypeSummary();`
- L727 _public function_ `inline bool GetDisableRuntimeGrassMapGeneration()`
- L728 _public function_ `inline void SetDisableRuntimeGrassMapGenerationProxyOnly(bool bInDisableRuntimeGrassMapGeneration)`
- L731 _public prototype_ `bool ShouldGenerateGrass() const;` — Whether grass primitives should be generated for this landscape.
- L739 _public member_ `float StaticLightingResolution;` — `UPROPERTY(EditAnywhere, Category=Lighting, meta = (LandscapeOverridable))` — The resolution to cache lighting at, in texels/quad in one axis Total resolution would be changed by StaticLightingResolution*StaticLightingResolution Automatically calculate proper value for removing seams
- L743 _public member_ `uint8 CastShadow : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lighting, meta = (LandscapeOverridable))` — Controls whether the primitive component should cast a shadow or not.
- L747 _public member_ `uint8 bCastDynamicShadow : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lighting, AdvancedDisplay, meta = (EditCondition = "CastShadow", DisplayName = "Dynamic Shadow", LandscapeOverridable))` — Controls whether the primitive should cast shadows in the case of non precomputed shadowing.  This flag is only used if CastShadow is true.
- L751 _public member_ `uint8 bCastStaticShadow : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lighting, AdvancedDisplay, meta = (EditCondition = "CastShadow", DisplayName = "Static Shadow", LandscapeOverridable))` — Whether the object should cast a static shadow from shadow casting lights.  This flag is only used if CastShadow is true.
- L755 _public member_ `EShadowCacheInvalidationBehavior ShadowCacheInvalidationBehavior;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lighting, AdvancedDisplay, meta=(EditCondition="CastShadow", LandscapeOverridable))` — Control shadow invalidation behavior, in particular with respect to Virtual Shadow Maps and material effects like World Position Offset.
- L759 _public member_ `uint8 bCastContactShadow : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lighting, AdvancedDisplay, meta = (EditCondition = "CastShadow", DisplayName = "Contact Shadow", LandscapeOverridable))` — Whether the object should cast contact shadows. This flag is only used if CastShadow is true.
- L763 _public member_ `uint32 bCastFarShadow : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = Lighting, meta = (EditCondition = "CastShadow", DisplayName = "Far Shadow", LandscapeOverridable))` — When enabled, the component will be rendering into the far shadow cascades(only for directional lights).  This flag is only used if CastShadow is true.
- L767 _public member_ `uint8 bCastHiddenShadow : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = Lighting, meta = (EditCondition = "CastShadow", DisplayName = "Hidden Shadow", LandscapeOverridable))` — If true, the primitive will cast shadows even if bHidden is true.  Controls whether the primitive should cast shadows when hidden.  This flag is only used if CastShadow is true.
- L771 _public member_ `uint32 bCastShadowAsTwoSided : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = Lighting, meta = (EditCondition = "CastShadow", DisplayName = "Shadow Two Sided", LandscapeOverridable))` — Whether this primitive should cast dynamic shadows as if it were a two sided material.  This flag is only used if CastShadow is true.
- L775 _public member_ `uint8 bAffectDistanceFieldLighting:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Lighting, AdvancedDisplay, meta = (EditCondition = "CastShadow", LandscapeOverridable))` — Controls whether the primitive should affect dynamic distance field lighting methods.  This flag is only used if CastShadow is true.
- L779 _public member_ `uint8 bAffectDynamicIndirectLighting:1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Lighting, AdvancedDisplay, meta=(LandscapeOverridable), Interp)` — Controls whether the primitive should influence indirect lighting.
- L783 _public member_ `uint8 bAffectIndirectLightingWhileHidden:1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=Lighting, meta=(EditCondition="bAffectDynamicIndirectLighting", DisplayName = "Affect Indirect Lighting While Hidden", LandscapeOverridable), Interp)` — Controls whether the primitive should affect indirect lighting when hidden. This flag is only used if bAffectDynamicIndirectLighting is true.
- L790 _public member_ `FLightingChannels LightingChannels;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = Lighting, meta = (LandscapeOverridable))` — Channels that this Landscape should be in.  Lights with matching channels will affect the Landscape. These channels only apply to opaque materials, direct lighting, and dynamic lighting and shadowing.
- L794 _public member_ `uint32 bUseMaterialPositionOffsetInStaticLighting:1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Lighting, meta = (LandscapeInherited))` — Whether to use the landscape material's vertical world position offset when calculating static lighting. Z (vertical) offset is supported
- L799 _public member_ `float NonNaniteVirtualShadowMapConstantDepthBias = 150.0f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Lighting, meta = (LandscapeOverridable))` — Constant bias to handle the worst artifacts of the continuous LOD morphing when rendering to VSM. Only applies when using non-Nanite landscape and VSM.
- L806 _public member_ `float NonNaniteVirtualShadowMapInvalidationHeightErrorThreshold = 250.0f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Lighting, meta = (LandscapeOverridable, UIMin = 0.0, ClampMin = 0.0))` — For non-Nanite landscape, cached VSM pages need to be invalidated when continuous LOD morphing introduces a height difference that is too large between the current landscape component's profile and the one that was used when the shadow was shadow was last cached. This height threshold (in Unreal units) controls this invalidation rate (a smaller threshold will reduce the likeliness of shadow artifacts, but will make the invalidations occur more frequently, which is not desirable in terms of performance. Disabled if 0.0. Only applies when using non-Nanite landscape and VSM.
- L815 _public member_ `float NonNaniteVirtualShadowMapInvalidationScreenSizeLimit = 0.2f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Lighting, meta = (LandscapeOverridable, ClampMin = "0.0", ClampMax = "10.0", UIMin = "0.0", UIMax = "10.0"))` — Screen size under which VSM invalidation stops occurring. As the height difference between 2 mip levels increases when the LOD level increases (because of undersampling), VSM pages tend to be invalidated more frequently even though it's getting less and less relevant to do so, since this will mean that the screen size of the landscape section decreases, thus the artifacts actually become less noticeable. We therefore artificially attenuate the VSM invalidation rate as the screen size decreases, to avoid invalidating VSM pages too often, as it becomes less and less impactful. A higher value will accentuate this attenuation (better performance but more artifacts) and vice versa. If 0.0, the attenuation of the VSM invalidation rate will be disabled entirely. Only applies when using non-Nanite landscape and VSM.
- L819 _public member_ `uint8 bHoldout : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Rendering, meta=(LandscapeOverridable), Interp)` — If this is True, this primitive will render black with an alpha of 0, but all secondary effects (shadows, reflections, indirect lighting) remain. This feature requires the project settings "Alpha Output" and "Support Primitive Alpha Holdout".
- L823 _public member_ `uint32 bRenderCustomDepth:1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = Rendering, meta=(DisplayName = "Render CustomDepth Pass", LandscapeOverridable))` — If true, the Landscape will be rendered in the CustomDepth pass (usually used for outlines)
- L827 _public member_ `ERendererStencilMask CustomDepthStencilWriteMask;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category = Rendering, meta = (editcondition = "bRenderCustomDepth", LandscapeOverridable))` — Mask used for stencil buffer writes.
- L831 _public member_ `int32 CustomDepthStencilValue;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=Rendering, meta=(UIMin = "0", UIMax = "255", editcondition = "bRenderCustomDepth", DisplayName = "CustomDepth Stencil Value", LandscapeOverridable))` — Optionally write this 0-255 value to the stencil buffer in CustomDepth pass (Requires project setting or r.CustomDepth == 3)
- L835 _public member_ `float LDMaxDrawDistance;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category=Rendering, meta = (DisplayName = "Desired Max Draw Distance", LandscapeOverridable))` — Max draw distance exposed to LDs. The real max draw distance is the min (disregarding 0) of this and volumes affecting this object.
- L839 _public member_ `FLightmassPrimitiveSettings LightmassSettings;` — `UPROPERTY(EditAnywhere, Category=Lightmass, meta = (LandscapeInherited))` — The Lightmass settings for this object.
- L843 _public member_ `TMap<FLandscapeGrassName, TObjectPtr<ULandscapeGrassType>> GrassTypesOverrides;` — `UPROPERTY(EditAnywhere, Category=Grass, meta = (LandscapeOverridable, ForceInlineRow))` — Specify alternate landscape grass types for some specific grass map names. This allows to reuse a given material's grass outputs, but change the grass meshes it spawns in the context of a specific landscape actor.
- L847 _public member_ `int32 CollisionMipLevel;` — `UPROPERTY(EditAnywhere, Category=Collision, meta = (LandscapeOverridable))` — Landscape LOD to use for collision tests. Higher numbers use less memory and process faster, but are much less accurate
- L851 _public member_ `int32 SimpleCollisionMipLevel;` — `UPROPERTY(EditAnywhere, Category=Collision, meta = (LandscapeOverridable))` — If set higher than the "Collision Mip Level", this specifies the Landscape LOD to use for "simple collision" tests, otherwise the "Collision Mip Level" is used for both simple and complex collision.
- L855 _public member_ `FBodyInstance BodyInstance;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (LandscapeOverridable))` — Collision profile settings for this landscape
- L865 _public member_ `uint32 bGenerateOverlapEvents : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (LandscapeOverridable))` — If true, Landscape will generate overlap events when other components are overlapping it (eg Begin Overlap). Both the Landscape and the other component must have this flag enabled for overlap events to occur. @see [Overlap Events](https://docs.unrealengine.com/InteractiveExperiences/Physics/Collision/Overview#overlapandgenerateoverlapevents) @see UpdateOverlaps(), BeginComponentOverlap(), EndComponentOverlap()
- L869 _public member_ `uint32 bBakeMaterialPositionOffsetIntoCollision:1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Collision, meta = (LandscapeInherited))` — Whether to bake the landscape material's vertical world position offset into the collision heightfield. Only z (vertical) offset is supported.
- L874 _public member_ `TArray<TObjectPtr<ULandscapeLayerInfoObject>> EditorCachedLayerInfos_DEPRECATED;` — `UE_DEPRECATED(all, "TargetLayers will be used instead")` — `UPROPERTY()`
- L877 _public member_ `FString ReimportHeightmapFilePath;` — `UPROPERTY()`
- L881 _public member_ `FGuid ReimportDestinationLayerGuid;` — `UPROPERTY()` — Height and weightmap import destination layer guid
- L886 _public member_ `TArray<FLandscapeEditorLayerSettings> EditorLayerSettings_DEPRECATED;` — `UE_DEPRECATED(all, "TargetLayers will be used instead")` — `UPROPERTY()`
- L889 _public member_ `TMap<UTexture2D*, FLandscapeEditLayerReadback*> HeightmapsCPUReadback;`
- L890 _public member_ `TMap<UTexture2D*, FLandscapeEditLayerReadback*> WeightmapsCPUReadback;`
- L894 _public member_ `TMap<TObjectPtr<UTexture2D>, TObjectPtr<ULandscapeWeightmapUsage>> WeightmapUsageMap;` — `UPROPERTY(Transient, NonTransactional)` — Map of weightmap usage
- L897 _public member_ `uint32 CurrentVersion = 1;` — CurrentVersion is bumped whenever a landscape component has an undo/redo operation applied. This lets us detect when the weightmap fixup needs to be run.
- L898 _public member_ `uint32 WeightmapFixupVersion = 0;`
- L900 _public member_ `uint32 RegistrationCount = 0;` — Tracks the number of times this Proxy has been registered since load
- L903 _public member_ `bool bIsRegisteredWithLandscapeInfo : 1 = false;` — True when this Proxy is registered with the LandscapeInfo
- L906 _public member_ `bool bNeedsWeightmapUsagesUpdate : 1 = false;` — Set to true when on undo, when it's necessary to completely regenerate weightmap usages (since some weightmap allocations are transactional and others not, e.g. splines edit layer)
- L909 _public member_ `bool bTemporarilyDisableWeightmapUsagesValidation : 1 = false;` — Set to true when we know that weightmap usages are being reconstructed and might be temporarily invalid as a result (ValidateProxyLayersWeightmapUsage should be called after setting this back to false)
- L913 _public member_ `bool bIsLandscapeActorRegisteredWithLandscapeInfo : 1 = false;` — True when this Proxy's LandscapeActor has registered with the LandscapeInfo, (and our shared properties are fully updated)
- L916 _public member_ `bool bIsRegisteredWithSubsystem : 1 = false;` — True when this Proxy is registered with the ULandscapeSubsystem
- L920 _public member_ `TObjectPtr<ULandscapeSubsystem> RegisteredToSubsystem;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional, SkipSerialization)` — Used to detect incorrect registration/unregistration behavior
- L924 _public member_ `int32 ComponentSizeQuads;` — `UPROPERTY(meta = (LandscapeInherited))` — Data set at creation time
- L927 _public member_ `int32 SubsectionSizeQuads;` — `UPROPERTY(meta = (LandscapeInherited))` — Number of quads for a subsection of a component. SubsectionSizeQuads+1 must be a power of two.
- L930 _public member_ `int32 NumSubsections;` — `UPROPERTY(meta = (LandscapeInherited))` — Number of subsections in X and Y axis
- L934 _public member_ `uint32 bUsedForNavigation:1;` — `UPROPERTY(EditAnywhere, Category=Navigation, meta = (LandscapeOverridable))` — Hints navigation system whether this landscape will ever be navigated on. true by default, but make sure to set it to false for faraway, background landscapes
- L938 _public member_ `uint32 bFillCollisionUnderLandscapeForNavmesh:1;` — `UPROPERTY(EditAnywhere, Category = Navigation, meta = (LandscapeOverridable))` — Set to true to prevent navmesh generation under the terrain geometry
- L941 _public member_ `ENavDataGatheringMode NavigationGeometryGatheringMode;` — `UPROPERTY(EditAnywhere, Category = Navigation, AdvancedDisplay, meta = (LandscapeOverridable))`
- L945 _public member_ `bool bUseDynamicMaterialInstance;` — `UPROPERTY(EditAnywhere, Category = Landscape, meta = (LandscapeOverridable))` — When set to true it will generate MaterialInstanceDynamic for each components, so material can be changed at runtime
- L949 _public member_ `int32 MaxPaintedLayersPerComponent;` — `UPROPERTY(EditAnywhere, Category=Landscape, meta = (LandscapeOverridable))` — 0 = disabled
- L954 _public member_ `bool bUseLandscapeForCullingInvisibleHLODVertices;` — `UPROPERTY(EditAnywhere, Category = HLOD, meta = (LandscapeOverridable))` — Flag whether or not this Landscape's surface can be used for culling hidden triangles
- L959 _public member_ `ELandscapeHLODTextureSizePolicy HLODTextureSizePolicy;` — `UPROPERTY(EditAnywhere, Category = HLOD, meta = (DisplayName = "HLOD Texture Size Policy", LandscapeOverridable, EditCondition = "HLODMaterialOverride == nullptr"))` — Specify how to choose the texture size of the resulting HLOD mesh. Specifying an HLOD Material Override will disable this option as no texture will be baked.
- L963 _public member_ `int32 HLODTextureSize;` — `UPROPERTY(EditAnywhere, Category = HLOD, meta = (DisplayName = "HLOD Texture Size", LandscapeOverridable, EditCondition = "HLODMaterialOverride == nullptr && HLODTextureSizePolicy == ELandscapeHLODTextureSizePolicy::SpecificSize", ClampMin = "16", ClampMax = "8192"))` — Specify the texture size to use for the HLOD mesh if HLODTextureSizePolicy is set to SpecificSize. Specifying an HLOD Material Override will disable this option as no texture will be baked.
- L967 _public member_ `TObjectPtr<UMaterialInterface> HLODMaterialOverride;` — `UPROPERTY(EditAnywhere, Category = HLOD, meta = (DisplayName = "HLOD Material Override", LandscapeOverridable))` — Specify a custom HLOD material to apply to the HLOD mesh. Specifying an HLOD Material Override will result in no texture being baked for the HLOD mesh.
- L971 _public member_ `ELandscapeHLODMeshSourceLODPolicy HLODMeshSourceLODPolicy;` — `UPROPERTY(EditAnywhere, Category = HLOD, meta = (DisplayName = "HLOD Mesh Source LOD Policy", LandscapeOverridable))` — Specify how to choose the LOD used as input for the HLOD mesh.
- L975 _public member_ `int32 HLODMeshSourceLOD;` — `UPROPERTY(EditAnywhere, Category = HLOD, meta = (DisplayName = "HLOD Mesh Source LOD", LandscapeOverridable, EditCondition = "HLODMeshSourceLODPolicy == ELandscapeHLODMeshSourceLODPolicy::SpecificLOD", ClampMin = "0"))` — Specify which LOD to use for the HLOD mesh if HLODMeshSourceLODPolicy is set to SpecificLOD.
- L980 _public member_ `bool bHasLayersContent_DEPRECATED = false;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")` — `UPROPERTY()`
- L983 _public member_ `TOptional<bool> HadLayersContentAtPostLoadTime;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")`
- L987 _public member_ `bool bStripPhysicsWhenCookedClient = false;` — `UPROPERTY(EditAnywhere, Category = Landscape, AdvancedDisplay, meta = (LandscapeOverridable))` — Strip Physics/collision components when cooked for client
- L991 _public member_ `bool bStripPhysicsWhenCookedServer = false;` — `UPROPERTY(EditAnywhere, Category = Landscape, AdvancedDisplay, meta = (LandscapeOverridable))` — Strip Physics/collision components when cooked for server
- L995 _public member_ `bool bStripGrassWhenCookedClient = false;` — `UPROPERTY(EditAnywhere, Category = Landscape, AdvancedDisplay, meta = (LandscapeOverridable))` — Strip Grass data when cooked for client
- L999 _public member_ `bool bStripGrassWhenCookedServer = false;` — `UPROPERTY(EditAnywhere, Category = Landscape, AdvancedDisplay, meta = (LandscapeOverridable))` — Strip Grass data when cooked for server
- L1002 _public member_ `static ULandscapeLayerInfoObject* VisibilityLayer;`
- L1007 _public member_ `TMap<FString, TObjectPtr<UMaterialInstanceConstant>> MaterialInstanceConstantMap;` — Map of material instance constants used to for the components. Key is generated with ULandscapeComponent::GetLayerAllocationKey()
- L1014 _public prototype_ `virtual void ChangeLODDistanceFactor(float InLODDistanceFactor);` — `UFUNCTION(BlueprintCallable, Category = "Rendering", meta=(DeprecatedFunction, DeprecationMessage = "This value can't be changed anymore, you should edit the property LODDistributionSetting of the Landscape"))` — Change the Level of Detail distance factor
- L1017 _public prototype_ `virtual void ChangeComponentScreenSizeToUseSubSections(float InComponentScreenSizeToUseSubSections);` — `UFUNCTION(BlueprintCallable, Category = "Rendering", meta = (DeprecatedFunction, DeprecationMessage = "This value can't be changed anymore and has been ineffective for several versions now. Please stop using it"))`
- L1021 _public prototype_ `void EditorSetLandscapeMaterial(UMaterialInterface* NewLandscapeMaterial);` — `UFUNCTION(BlueprintSetter)` — Setter for LandscapeMaterial. Has no effect outside the editor.
- L1040 _public prototype_ `void EditorApplySpline(USplineComponent* InSplineComponent, float StartWidth = 200, float EndWidth = 200, float StartSideFalloff = 200, float EndSideFalloff = 200, float StartRoll = 0, float EndRoll = 0, int32 NumSubdivisions = 20, bool bRaiseHeights = true, bool bLowerHeights = true, ULandscapeLayerInfoObject* PaintLayer = nullptr, FName EditLayerName = TEXT(""));` — `UFUNCTION(BlueprintCallable, Category = "Landscape|Editor")` — Deform landscape using a given spline @param InSplineComponent - The component containing the spline data @param StartWidth - Width of the spline at the start node, in Spline Component local space @param EndWidth   - Width of the spline at the end node, in Spline Component local space @param StartSideFalloff - Width of the falloff at either side of the spline at the start node, in Spline Component local space @param EndSideFalloff - Width of the falloff at either side of the spline at the end node, in Spline Component local space @param StartRoll - Roll applied to the spline at the start node, in degrees. 0 is flat @param EndRoll - Roll applied to the spline at the end node, in degrees. 0 is flat @param NumSubdivisions - Number of triangles to place along the spline when applying it to the landscape. Higher numbers give better results, but setting it too high will be slow and may cause artifacts @param bRaiseHeights - Allow the landscape to be raised up to the level of the spline. If both bRaiseHeights and bLowerHeights are false, no height modification of the landscape will be performed @param bLowerHeights - Allow the landscape to be lowered down to the level of the spline. If both bRaiseHeights and bLowerHeights are false, no height modification of the landscape will be performed @param PaintLayer - LayerInfo to paint, or none to skip painting. The landscape must be configured with the same layer info in one of its layers or this will do nothing! @param EditLayerName - Nam
- L1044 _public prototype_ `void SetLandscapeMaterialTextureParameterValue(FName ParameterName, class UTexture* Value);` — `UFUNCTION(BlueprintCallable, Category = "Landscape|Runtime|Material")` — Set an MID texture parameter value for all landscape components.
- L1048 _public prototype_ `void SetLandscapeMaterialVectorParameterValue(FName ParameterName, FLinearColor Value);` — `UFUNCTION(BlueprintCallable, meta = (Keywords = "SetColorParameterValue"), Category = "Landscape|Runtime|Material")` — Set an MID vector parameter value for all landscape components.
- L1052 _public prototype_ `void SetLandscapeMaterialScalarParameterValue(FName ParameterName, float Value);` — `UFUNCTION(BlueprintCallable, meta = (Keywords = "SetFloatParameterValue"), Category = "Landscape|Runtime|Material")` — Set a MID scalar (float) parameter value for all landscape components.
- L1057 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L1058 _public prototype_ `virtual void UnregisterAllComponents(bool bForReregister = false) override;`
- L1059 _public function_ `virtual bool IsLevelBoundsRelevant() const override`
- L1061 _public prototype_ `virtual void PostInitProperties() override;`
- L1062 _public prototype_ `virtual void FinishDestroy() override;`
- L1065 _public function_ `virtual void RerunConstructionScripts() override`
- L1066 _public prototype_ `virtual void Destroyed() override;`
- L1067 _public prototype_ `virtual void EditorApplyScale(const FVector& DeltaScale, const FVector* PivotLocation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;`
- L1068 _public prototype_ `virtual void EditorApplyMirror(const FVector& MirrorScale, const FVector& PivotLocation) override;`
- L1069 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L1070 _public prototype_ `virtual void OnLoadedActorRemovedFromLevel() override;`
- L1073 _public function_ `virtual uint32 GetDefaultGridSize(UWorld* InWorld) const override`
- L1074 _public function_ `virtual FGuid GetGridGuid() const override`
- L1075 _public prototype_ `virtual TUniquePtr<class FWorldPartitionActorDesc> CreateClassActorDesc() const override;`
- L1076 _public function_ `virtual bool EditorCanAttachTo(const AActor* InParent, FText& OutReason) const override`
- L1077 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L1078 _public function_ `virtual bool IsNaniteEnabled() const`
- L1079 _public function_ `virtual int32 GetNaniteLODIndex() const`
- L1080 _public function_ `virtual bool IsNaniteSkirtEnabled() const`
- L1081 _public function_ `virtual float GetNaniteSkirtDepth() const`
- L1082 _public function_ `virtual int32 GetNanitePositionPrecision() const`
- L1083 _public function_ `virtual float GetNaniteMaxEdgeLengthFactor() const`
- L1084 _public prototype_ `virtual UE::Landscape::EOutdatedDataFlags GetOutdatedDataFlags() const;`
- L1086 _public prototype_ `void UpdateNaniteSharedPropertiesFromActor();`
- L1087 _public prototype_ `void RemoveNaniteComponents();`
- L1088 _public prototype_ `void ClearNaniteTransactional();`
- L1089 _public member_ `static constexpr int32 NaniteComponentMaxSide = 8;`
- L1090 _public member_ `static constexpr int32 NaniteMaxComponents = NaniteComponentMaxSide * NaniteComponentMaxSide;`
- L1091 _public function_ `int32 NumNaniteRequiredComponents() const`
- L1094 _public prototype_ `bool AreNaniteComponentsValid(const FGuid& InProxyContentId) const;`
- L1095 _public function_ `bool HasNaniteComponents() const`
- L1096 _public prototype_ `TSet<FPrimitiveComponentId> GetNanitePrimitiveComponentIds() const;`
- L1098 _public prototype_ `bool AuditNaniteMaterials() const;`
- L1099 _public prototype_ `void EnableNaniteComponents(bool bInNaniteActive);`
- L1101 _public prototype_ `TOptional<float> GetHeightAtLocation(FVector Location, EHeightfieldSource HeightFieldSource = EHeightfieldSource::Complex) const;`
- L1102 _public prototype_ `UPhysicalMaterial* GetPhysicalMaterialAtLocation(FVector Location, EHeightfieldSource HeightFieldSOurce = EHeightfieldSource::Complex) const;`
- L1105 _public prototype_ `void GetHeightValues(int32& SizeX, int32& SizeY, TArray<float>& ArrayValue) const;` — Fills an array with height values
- L1111 _public function_ `virtual FGuid GetLandscapeGuid() const override` — Return the landscape guid, used to identify landscape proxies (and splines) that belong to the same landscape, even across world partitions. Also used as the world partition grid guid.  This value may be modified when the landscape is instanced, to allow multiple instances of the same landscape to exist simultaneously.  If you want the original (uninstanced) value, use GetOriginalLandscapeGuid().
- L1112 _public function_ `void SetLandscapeGuid(const FGuid& Guid, bool bValidateGuid = true)`
- L1121 _public prototype_ `uint32 ComputeLandscapeKey() const;` — Computes the rendering key for this landscape proxy
- L1122 _public prototype_ `static uint32 ComputeLandscapeKey(const UWorld* World, uint32 InLODGroupKey, FGuid InLandscapeGuid);`
- L1127 _public function_ `const FGuid& GetOriginalLandscapeGuid() const` — Return the original landscape guid, before it was modified by instancing. When not instanced, this value is equal to LandscapeGuid.
- L1129 _public prototype_ `void SetLODGroupKeyInternal(uint32 InLODGroupKey);`
- L1132 _public function_ `virtual ALandscape* GetLandscapeActor() PURE_VIRTUAL(GetLandscapeActor, return nullptr;) virtual const ALandscape* GetLandscapeActor() const PURE_VIRTUAL(GetLandscapeActor, return nullptr;) const TArray<FLandscapePerLODMaterialOverride>& GetPerLODOverrideMaterials() const` — `UFUNCTION(BlueprintCallable, Category = "Landscape|Runtime")`
- L1136 _public prototype_ `void SetPerLODOverrideMaterials(const TArray<FLandscapePerLODMaterialOverride>& InValue);`
- L1138 _public function_ `static void SetGrassUpdateInterval(int32 Interval)`
- L1141 _public function_ `FORCEINLINE bool ShouldTickGrass() const` — Determine whether we should update dynamic grass instances this update tick
- L1160 _public prototype_ `void ProcessAsyncGrassInstanceTasks(bool bWaitAsyncTasks, bool bForceSync, const TSet<UHierarchicalInstancedStaticMeshComponent*>& StillUsed);`
- L1165 _public prototype_ `void FlushGrassComponents(const TSet<ULandscapeComponent*>* OnlyForComponents = nullptr, bool bFlushGrassMaps = true);` — Flush the grass cache, removing grass instances on the given components (or all proxy components if the component set is not specified). bFlushGrassMaps will delete the grass data / density maps on the components as well, but only in editor mode, and only if the grass maps are renderable (i.e. they can be regenerated).
- L1173 _public prototype_ `void UpdateGrass(const TArray<FVector>& Cameras, int32& InOutNumComponentsCreated, bool bForceSync = false);` — Update Grass -- Builds grass instances given the camera locations @param Cameras to use for culling, if empty, then NO culling @param InOutNumComponentsCreated, value can increase if components were created, it is also used internally to limit the number of creations @param bForceSync if true, block and finish all work so that grass is fully populated for the given cameras
- L1174 _public prototype_ `void UpdateGrass(const TArray<FVector>& Cameras, bool bForceSync = false);`
- L1183 _public prototype_ `static void AddExclusionBox(FWeakObjectPtr Owner, const FBox& BoxToRemove);` — TODO [jonathan.bard] : Rename to "AddGrassExclusionBox" + no reason for any of this to be static
- L1188 _public prototype_ `static void RemoveExclusionBox(FWeakObjectPtr Owner);` — Unregisters a previously-registered exclusion box. Landscape grass will be able to be spawned again in this area after the operation @param Owner Identifier of the box to remove (see AddExclusionBox)
- L1193 _public prototype_ `static void RemoveAllExclusionBoxes();` — Unregisters all existing exclusion boxes.
- L1195 _public prototype_ `static void RemoveInvalidExclusionBoxes();`
- L1197 _public prototype_ `static void DebugDrawExclusionBoxes(const UWorld* World);`
- L1200 _public prototype_ `static void InvalidateGeneratedComponentData(const TSet<ULandscapeComponent*>& Components, bool bInvalidateLightingCache = false);` — Invalidate the precomputed grass and baked texture data for the specified components
- L1201 _public prototype_ `static void InvalidateGeneratedComponentData(const TArray<ULandscapeComponent*>& Components, bool bInvalidateLightingCache = false);`
- L1204 _public prototype_ `void InvalidateGeneratedComponentData(bool bInvalidateLightingCache = false);` — Invalidate the precomputed grass and baked texture data on all components
- L1206 _public prototype_ `void UpdateRenderingMethod();`
- L1215 _public prototype_ `bool UpdatePhysicalMaterialTasks(bool bInShouldMarkDirty = false);` — Update the landscape physical material render tasks @param bInShouldMarkDirty indicates whether the proxy should be marked as dirty if anything was built @return true if anything was built on this proxy
- L1216 _public prototype_ `void UpdatePhysicalMaterialTasksStatus(TSet<ULandscapeComponent*>* OutdatedComponents, int32* OutdatedComponentsCount) const;`
- L1219 _public prototype_ `void OnFeatureLevelChanged(ERHIFeatureLevel::Type NewFeatureLevel);` — Editor notification when changing feature level
- L1222 _public member_ `FDelegateHandle FeatureLevelChangedDelegateHandle;` — Handle so we can unregister the delegate
- L1224 _public prototype_ `FGuid GetNaniteContentId() const;`
- L1226 _public prototype_ `void ValidateGrassTypeOverrides();`
- L1231 _public prototype_ `virtual void CheckForErrors() override;`
- L1232 _public prototype_ `virtual void BeginCacheForCookedPlatformData(const ITargetPlatform* TargetPlatform) override;`
- L1233 _public prototype_ `virtual void OnCookEvent(UE::Cook::ECookEvent CookEvent, UE::Cook::FCookEventContext& CookContext) override;`
- L1236 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L1237 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L1238 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L1239 _public prototype_ `virtual void PostLoad() override;`
- L1242 _public prototype_ `ULandscapeInfo* CreateLandscapeInfo(bool bMapCheck = false, bool bUpdateAllAddCollisions = true);` — Creates the LandscapeInfo if necessary, then registers this proxy with it
- L1243 _public prototype_ `virtual ULandscapeInfo* GetLandscapeInfo() const override;`
- L1246 _public prototype_ `virtual FTransform LandscapeActorToWorld() const override;` — Get the LandcapeActor-to-world transform with respect to landscape section offset
- L1249 _public prototype_ `FBox GetProxyBounds() const;` — Differs from GetActorBounds as it only considers LandscapeComponents/CollisionComponents bounds
- L1259 _public prototype_ `bool LandscapeExportHeightmapToRenderTarget(UTextureRenderTarget2D* InRenderTarget, bool InExportHeightIntoRGChannel = false, bool InExportLandscapeProxies = true);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Landscape Export Heightmap to RenderTarget", Keywords = "Push Landscape Heightmap to RenderTarget", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Output a landscape heightmap to a render target @param InRenderTarget - Valid render target with a format of RTF_RGBA16f, RTF_RGBA32f or RTF_RGBA8 @param InExportHeightIntoRGChannel - Tell us if we should export the height that is internally stored as R & G (for 16 bits) to a single R channel of the render target (the format need to be RTF_RGBA16f or RTF_RGBA32f) Note that using RTF_RGBA16f with InExportHeightIntoRGChannel == false, could have precision loss. @param InExportLandscapeProxies - Option to also export components of all proxies of Landscape actor (if LandscapeProxy is the Landscape Actor)
- L1262 _public prototype_ `FIntPoint GetSectionBaseOffset() const;` — `UE_DEPRECATED(5.7, "Use GetSectionBase instead.")`
- L1265 _public prototype_ `FIntPoint GetSectionBase() const;` — Get landscape position in section space
- L1268 _public function_ `virtual ULandscapeSplinesComponent* GetSplinesComponent() const override` — ILandscapeSplineInterface
- L1269 _public prototype_ `virtual void UpdateSharedProperties(ULandscapeInfo* InLandscapeInfo) override;`
- L1270 _public function_ `virtual bool IsSplineOwnerValid() const override`
- L1273 _public prototype_ `TArray<float> GetLODScreenSizeArray() const;` — Retrieve the screen size at which each LOD should be rendered
- L1277 _public prototype_ `void CopySharedProperties(ALandscapeProxy* InLandscape, bool bInExecutePostEditChangeProperty = false);` — Copy properties from parent Landscape actor
- L1285 _public prototype_ `TArray<FName> SynchronizeSharedProperties(ALandscapeProxy* InLandscape, bool bInExecutePostEditChangeProperty = false);` — Enforce property sharing and requirements related to the parent Landscape actor @param InLandscape the parent landscape to use as a template. @param bInExecutePostEditChangeProperty When true, executes PostEditChangeProperty for each property synchronized @return An array containing all synchronized properties names (properties that were different from the provided landscape).
- L1288 _public prototype_ `bool IsSharedProperty(const FName& InPropertyName) const;` — Returns true if the property is shared.
- L1291 _public prototype_ `bool IsSharedProperty(const FProperty* InProperty) const;` — Returns true if the property is shared.
- L1294 _public prototype_ `bool IsPropertyInherited(const FProperty* InProperty) const;` — Returns true if the property is inherited.
- L1297 _public prototype_ `bool IsPropertyOverridable(const FProperty* InProperty) const;` — Returns true if the property is overridable
- L1300 _public function_ `virtual bool IsSharedPropertyOverridden(const FName& InPropertyName) const` — Returns true if the shared property is overridden by the object.
- L1303 _public function_ `virtual void SetSharedPropertyOverride(const FName& InPropertyName, const bool bIsOverriden, const bool bInExecutePostEditChangeProperty = true)` — Modifies the override state of the property given as argument.
- L1306 _public function_ `static FOnLandscapeProxyFixupSharedDataDelegate::RegistrationType& OnLandscapeProxyFixupSharedData()` — Delegate that will be called whenever FixupSharedData is called, to inject some custom logic
- L1310 _public prototype_ `virtual UMaterialInterface* GetLandscapeMaterial(int8 InLODIndex = INDEX_NONE) const;` — Get Landscape Material assigned to this Landscape
- L1313 _public prototype_ `virtual UMaterialInterface* GetLandscapeHoleMaterial() const;` — Get Hole Landscape Material assigned to this Landscape
- L1319 _public prototype_ `void RetrieveAllLandscapeMaterials(TSet<UMaterialInterface*>& OutMaterials) const;` — Retrieve the list of all materials that might be used by this landscape proxy or its components (LandscapeMaterial, LandscapeHoleMaterial, component overrides, etc.) @param OutMaterials list of unique materials retrieved. The materials found will be appended to the list
- L1321 _public function_ `inline TMap<FLandscapeGrassName, TObjectPtr<ULandscapeGrassType>> GetGrassTypesOverrides() const`
- L1328 _public prototype_ `void SerializeStateHashes(FArchive& Ar);` — Serialize all hashes/guids that record the current state of this proxy
- L1330 _public function_ `void SetSplinesComponent(ULandscapeSplinesComponent* InSplineComponent)`
- L1332 _public function_ `virtual bool SupportsForeignSplineMesh() const override`
- L1334 _public prototype_ `int32 GetOutdatedGrassMapCount() const;`
- L1335 _public prototype_ `void BuildGrassMaps();`
- L1341 _public prototype_ `bool BuildPhysicalMaterial();` — Builds the physical materials on the components of this proxy @return true if anything has been built
- L1342 _public prototype_ `void InvalidatePhysicalMaterial();`
- L1343 _public prototype_ `int32 GetOudatedPhysicalMaterialComponentsCount() const;`
- L1344 _public prototype_ `virtual void CreateSplineComponent() override;`
- L1345 _public prototype_ `virtual void CreateSplineComponent(const FVector& Scale3D) override;`
- L1347 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L1348 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L1349 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L1350 _public prototype_ `virtual void PostEditImport() override;`
- L1351 _public prototype_ `virtual void PostEditUndo() override;`
- L1354 _public prototype_ `void InitializeProxyLayersWeightmapUsage();`
- L1355 _public prototype_ `void ValidateProxyLayersWeightmapUsage() const;`
- L1356 _public prototype_ `void UpdateProxyLayersWeightmapUsage();`
- L1357 _public prototype_ `void RequestProxyLayersWeightmapUsageUpdate();`
- L1360 _public prototype_ `static const TArray<FName> GetLayersFromMaterial(UMaterialInterface* Material);` — `UE_DEPRECATED(5.8, "Use UE::Landscape::RetrieveTargetLayerNamesFromMaterial")`
- L1362 _public prototype_ `const TArray<FName> GetLayersFromMaterial() const;` — `UE_DEPRECATED(5.8, "Use RetrieveTargetLayerNamesFromMaterials")`
- L1365 _public prototype_ `TArray<FName> RetrieveTargetLayerNamesFromMaterials(bool bIncludeVisibilityLayer = true) const;` — Get all Layer names used by the materials assigned the proxy and components (Proxy Material, Component, Component LOD Material and Hole Material)
- L1368 _public prototype_ `TMap<FName, ULandscapeLayerInfoObject*> RetrieveTargetLayerInfosFromAllocations() const;` — Query all the LandscapeLayerInfo Objects from the weight layers allocated on this proxy.
- L1371 _public prototype_ `void FixupWeightmaps();` — Fix up component layers, weightmaps
- L1374 _public prototype_ `void RepairInvalidTextures();` — Repair invalid texture data that might have been introduced by a faulty version :
- L1377 _public prototype_ `void RemoveInvalidWeightmaps();` — Remove Invalid weightmaps
- L1380 _public prototype_ `void ChangedPhysMaterial();` — Changed Physical Material
- L1383 _public prototype_ `void UpgradeSharedProperties(ALandscape* InParentLandscape, const bool bInExecutePostEditChangeProperty = true);` — Converts shared properties overridden before explicit override, asking the user how to proceed.
- L1387 _public prototype_ `void DisplayObsoleteEditLayerMapCheck(ALandscape* InParentLandscape);` — Displays the obsolete edit layers within the LandscapeComponents in a actionable MapCheck log Asks users to copy obsolete layer data or delete for good.
- L1390 _public prototype_ `void FixupSharedData(ALandscape* Landscape, bool bMapCheck = false, const bool bInExecutePostEditChangeProperty = true);` — Assign only mismatching data and mark proxy package dirty
- L1393 _public prototype_ `void SetAbsoluteSectionBase(FIntPoint SectionOffset);` — `UE_DEPRECATED(5.7, "Use SetSectionBase instead.")`
- L1396 _public prototype_ `void SetSectionBase(FIntPoint SectionOffset);` — Set landscape location in section space
- L1399 _public prototype_ `void RecreateComponentsState();` — Recreate all components rendering and collision states
- L1402 _public prototype_ `void RecreateComponentsRenderState(TFunctionRef<void(ULandscapeComponent*)> Fn);` — Recreate all component rendering states after applying a given function to each
- L1405 _public prototype_ `void RecreateCollisionComponents();` — Recreate all collision components based on render component
- L1408 _public prototype_ `void RemoveXYOffsets();` — Remove all XYOffset values
- L1411 _public prototype_ `void UpdateNaniteMaterials();` — Ensure the Update the Materials on the Nanite Static Meshes from the source ULandscapeComponent
- L1414 _public prototype_ `void UpdateNaniteMaterialUsage();` — Ensure MATUSAGE_Nanite is set on the materials the Nanite representation of this proxy renders with. Does nothing if Nanite is disabled on this proxy.
- L1417 _public prototype_ `void UpdateAllComponentMaterialInstances(bool bInInvalidateCombinationMaterials = false);` — Update the material instances for all the landscape components
- L1418 _public prototype_ `void UpdateAllComponentMaterialInstances(FMaterialUpdateContext& InOutMaterialContext, TArray<class FComponentRecreateRenderStateContext>& InOutRecreateRenderStateContext, bool bInInvalidateCombinationMaterials = false);`
- L1421 _public prototype_ `void Import(const FGuid& InGuid, int32 InMinX, int32 InMinY, int32 InMaxX, int32 InMaxY, int32 InNumSubsections, int32 InSubsectionSizeQuads, const TMap<FGuid, TArray<uint16>>& InImportHeightData, const TCHAR* const InHeightmapFileName, const TMap<FGuid, TArray<FLandscapeImportLayerInfo>>& InImportMaterialLayerInfos, ELandscapeImportAlphamapType InImportMaterialLayerType, const TArrayView<const struct FLandscapeLayer>& InImportLayers);` — Import the given Height/Weight data into this landscape
- L1509 _public prototype_ `bool ExportToRawMesh(const FRawMeshExportParams& InExportParams, FMeshDescription& OutRawMesh) const;` — Exports landscape geometry into a raw mesh according to the export params @param InExportParams - Details about what should be exported and how @param OutRawMesh - Resulting raw mesh @return true if successful
- L1511 _public prototype_ `TSharedRef<UE::Landscape::Nanite::FAsyncBuildData> MakeAsyncNaniteBuildData(int32 InLODToExport, const TArray<ULandscapeComponent*>& ComponentsToExport) const;`
- L1513 _public prototype_ `bool ExportToRawMeshDataCopy(const FRawMeshExportParams& InExportParams, FMeshDescription& OutRawMesh, const UE::Landscape::Nanite::FAsyncBuildData& AsyncData) const;`
- L1515 _public prototype_ `void CheckGenerateMobilePlatformData(bool bIsCooking, const ITargetPlatform* TargetPlatform);`
- L1518 _public prototype_ `bool IsNaniteMeshUpToDate() const;` — Returns true if the Nanite representation is missing or outdated
- L1524 _public prototype_ `void UpdateNaniteRepresentation(const ITargetPlatform* InTargetPlatform);` — Update Nanite representation if it's missing or outdated. Important note : despite what the name might imply when compared with UpdateNaniteRepresentationAsync, this is not necessarily a synchronous call. If waiting for completion is absolutely needed, it should be performed by ULandscapeSubsystem::FinishAllNaniteBuildsInFlightNow.
- L1527 _public prototype_ `FGraphEventRef UpdateNaniteRepresentationAsync(const ITargetPlatform* InTargetPlatform);` — Update Nanite representation if it's missing or outdated Async
- L1534 _public prototype_ `void InvalidateNaniteRepresentation(bool bInCheckContentId);` — Invalidate and disable Nanite representation until a subsequent rebuild occurs @param bInCheckContentId - If true, only invalidate when the content Id of the proxy mismatches with the Nanite representation
- L1541 _public prototype_ `void InvalidateOrUpdateNaniteRepresentation(bool bInCheckContentId, const ITargetPlatform* InTargetPlatform);` — Invalidate Nanite representation or rebuild it in case live update is active : @param bInCheckContentId - If true, only invalidate when the content Id of the proxy mismatches with the Nanite representation
- L1544 _public prototype_ `FIntRect GetBoundingRect() const;` — @return Current size of bounding rectangle in quads space
- L1547 _public prototype_ `UTexture2D* CreateLandscapeTexture(int32 InSizeX, int32 InSizeY, TextureGroup InLODGroup, ETextureSourceFormat InFormat, UObject* OptionalOverrideOuter = nullptr, bool bCompress = false, bool bMipChain = true) const;` — Creates a Texture2D for use by this landscape proxy or one of its components. If OptionalOverrideOuter is not specified, the proxy is used.
- L1550 _public prototype_ `UTexture2DArray* CreateLandscapeTextureArray(int32 InSizeX, int32 InSizeY, int32 Slices, TextureGroup InLODGroup, ETextureSourceFormat InFormat, UObject* OptionalOverrideOuter = nullptr);` — Creates a Texture2DArray for use by this landscape proxy or one of its components. If OptionalOverrideOuter is not specified, the proxy is used.
- L1553 _public prototype_ `UTexture2D* CreateLandscapeToolTexture(int32 InSizeX, int32 InSizeY, TextureGroup InLODGroup, ETextureSourceFormat InFormat) const;` — Creates a Texture2D for use by this landscape proxy or one of its components for tools .
- L1556 _public prototype_ `ULandscapeWeightmapUsage* CreateWeightmapUsage();` — Creates a LandscapeWeightMapUsage object outered to this proxy.
- L1559 _public prototype_ `void RemoveOverlappingComponent(ULandscapeComponent* Component);` — remove an overlapping component. Called from MapCheck.
- L1565 _public prototype_ `static TArray<FLinearColor> SampleRTData(UTextureRenderTarget2D* InRenderTarget, FLinearColor InRect);` — Samples an array of values from a Texture Render Target 2D. Only works in the editor
- L1575 _public prototype_ `bool LandscapeImportHeightmapFromRenderTarget(UTextureRenderTarget2D* InRenderTarget, bool InImportHeightFromRGChannel = false, int32 InEditLayerIndex = 0);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Landscape Import Heightmap from RenderTarget", Keywords = "Push RenderTarget to Landscape Heightmap", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Overwrites a landscape heightmap with render target data @param InRenderTarget - Valid render target with a format of RTF_RGBA16f, RTF_RGBA32f or RTF_RGBA8 @param InImportHeightFromRGChannel - Only relevant when using format RTF_RGBA16f or RTF_RGBA32f, and will tell us if we should import the height data from the R channel only of the Render target or from R & G. Note that using RTF_RGBA16f with InImportHeightFromRGChannel == false, could have precision loss Only works in the editor
- L1582 _public prototype_ `bool LandscapeImportWeightmapFromRenderTarget(UTextureRenderTarget2D* InRenderTarget, FName InLayerName, int32 InEditLayerIndex = 0);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Landscape Import Weightmap from RenderTarget", Keywords = "Push RenderTarget to Landscape Weightmap", UnsafeDuringActorConstruction = "true"), Category = Rendering)` — Overwrites a landscape weightmap with render target data Only works in the editor
- L1586 _public prototype_ `bool LandscapeExportWeightmapToRenderTarget(UTextureRenderTarget2D* InRenderTarget, FName InLayerName);` — `UE_DEPRECATED(5.7, "Deprecating placeholder function. Not needed after non-edit layer landscape deprecation. ")` — `UFUNCTION()`
- L1589 _public prototype_ `virtual bool HasLayersContent() const;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")`
- L1592 _public prototype_ `bool CanHaveLayersContent() const;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")`
- L1595 _public prototype_ `virtual void UpdateCachedHasLayersContent(bool InCheckComponentDataIntegrity = false);` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")`
- L1597 _public function_ `FAsyncWorkMonitor& GetAsyncWorkMonitor()`
- L1603 _public prototype_ `virtual void DeleteUnusedLayers();` — `UFUNCTION(BlueprintCallable, Category = "Landscape")` — Delete all unused layers in components. Warning: any update of the component could re-introduce them.
- L1609 _public prototype_ `FLandscapeTargetLayerSettings& AddTargetLayer();` — Add a TargetLayer with a unique name and no layer object info
- L1612 _public prototype_ `FLandscapeTargetLayerSettings& AddTargetLayer(const FName& Name, const FLandscapeTargetLayerSettings& TargetLayerSettings, bool bPostEditChange = true);` — Add a TargetLayer with the given name or a generated unique name if the given name is invalid
- L1615 _public prototype_ `const FName GenerateUniqueTargetLayerName() const;` — Generate a unique TargetLayer name
- L1618 _public prototype_ `bool UpdateTargetLayer(const FName& Name, const FLandscapeTargetLayerSettings& TargetLayerSettings, bool bPostEditChange = true);` — Update a existing Target Layer
- L1622 _public prototype_ `bool RemoveTargetLayer(const FName& Name, bool bPostEditChange = true);` — Remove Named TargetLayer, Returns true if a layer has been removed.
- L1625 _public prototype_ `bool HasTargetLayer(const FName& Name) const;` — Query if a TargetLayer exists by Name or by checking the ULandscapeLayerInfoObject in  TargetLayerSettings
- L1626 _public prototype_ `bool HasTargetLayer(const FLandscapeTargetLayerSettings& TargetLayerSettings) const;`
- L1627 _public prototype_ `bool HasTargetLayer(const ULandscapeLayerInfoObject* LayerInfoObject) const;`
- L1630 _public prototype_ `const TMap<FName, FLandscapeTargetLayerSettings>& GetTargetLayers() const;` — All the Target layers
- L1631 _public prototype_ `TSet<ULandscapeLayerInfoObject*> GetValidTargetLayerObjects() const;`
- L1641 _protected prototype_ `bool AddLayer(const FGuid& InLayerGuid);` — Add Layer if it doesn't exist yet. @return True if layer was added.
- L1645 _protected prototype_ `void DeleteLayer(const FGuid& InLayerGuid);` — Delete Layer.
- L1651 _protected prototype_ `bool RemoveObsoleteEditLayers(bool bShowMapCheckWarning);` — Removes Obsolete Edit layer data from all landscape components @param bShowMapCheckWarning When true, opens MapCheck to display a log for each edit layer removed @return True if some layers were removed.
- L1654 _protected prototype_ `bool RemoveObsoleteLayers(const TSet<FGuid>& InExistingLayers);` — `UE_DEPRECATED(5.7, "Use RemoveObsoleteEditLayers based on ALandscape or use DeleteLayer to directly remove layers")`
- L1657 _protected prototype_ `TMap<FGuid, FName> GetObsoleteEditLayersInComponents();` — Returns a map of this Proxy's LandscapeComponents obsolete edit layers Guids to Debug Names
- L1660 _protected prototype_ `void InitializeLayerWithEmptyContent(const FGuid& InLayerGuid);` — Initialize Layer with empty content if it hasn't been initialized yet.
- L1663 _protected function_ `virtual void FixupOverriddenSharedProperties()` — Fixup any internal representation for shared properties. Will be used when deprecating or renaming a property.
- L1666 _protected function_ `virtual void CheckOverriddenSharedProperties()` — Validates that overridden shared properties are properly setup. Only run on load and MapCheck since it's just to inform the user that something is not properly setup
- L1673 _protected prototype_ `virtual TArray<FName> SynchronizeUnmarkedSharedProperties(ALandscapeProxy* InLandscape);` — Synchronizes all shared properties that cannot be marked by regular meta tags. @param The landscape to use as a template. @return An array containing all synchronized properties.
- L1678 _protected member_ `bool bUpgradeSharedPropertiesPerformed = false;` — Used to know if the deprecation of shared properties modified before the enforcement system introduction has been performed on load.
- L1683 _private member_ `TMap<FName, FLandscapeTargetLayerSettings> TargetLayers;` — `UPROPERTY(Category = "Target Layers", VisibleAnywhere, meta = (NoResetToDefault, LandscapeInherited))`
- L1686 _private function_ `FORCEINLINE int32 GetGrassUpdateInterval() const` — Returns Grass Update interval
- L1697 _private member_ `static int32 GrassUpdateInterval;`
- L1699 _private prototype_ `FName GenerateUniqueLandscapeTextureName(UObject* InOuter, TextureGroup InLODGroup) const;`
- L1703 _private prototype_ `void CreateNaniteComponents(int32 NumComponents);` — Create Blank Nanite Component
- L1709 _private prototype_ `void SetSourceComponentsForNaniteComponents(bool bSetEmptyComponentsOnly = false) const;` — Sets the source landscape components for each nanite component in this proxy @param bSetEmptyComponentsOnly When true, only update nanite components with no source landscape components
- L1711 _private prototype_ `void OnLayerInfoObjectDataChanged(const FOnLandscapeLayerInfoDataChangedParams& InParams);`
- L1714 _private prototype_ `void PostLoadFixupLandscapeGuidsIfInstanced();`
- L1717 _private prototype_ `void InstallOrUpdateTextureUserDatas(const ITargetPlatform* TargetPlatform);`
- L1722 _public function_ `static const TArray<ALandscapeProxy*>& GetLandscapeProxies()`
- L1724 _public function_ `inline bool HasEditLayersDataOnLoad() const`
- L1731 _private member_ `static TArray<ALandscapeProxy*> LandscapeProxies;` — Maintain list of Proxies for faster iteration
- L1732 _private member_ `FAsyncWorkMonitor AsyncWorkMonitor;`
- L1737 _private member_ `FIntPoint SectionBase = FIntPoint::ZeroValue;` — `UPROPERTY()` — Offset in quads from global components grid origin (in quads)
- L1740 _private member_ `bool bHasEditLayersOnLoad = false;` — True if this proxy's first component has edit layer data on load. When false, proxy has no components or is part of a legacy non-edit layer landscape and needs to be auto-converted
- L1743 _private member_ `static constexpr TCHAR const* LandscapeInheritedTag = TEXT("Lan`
- L1744 _private member_ `static constexpr TCHAR const* LandscapeOverridableTag = TEXT("Lan`

#### struct `ALandscapeProxy::FGrassTypeSummary`  
`struct FGrassTypeSummary`  
_L712-721_
- desc: Non-serialized runtime cache of values derived from the assigned grass types. Call ALandscapeProxy::UpdateGrassTypeSummary() to update.
- L717 _public member_ `int32 LandscapeComponentCount = -1;` — Used to track validity of these values, as it automatically invalidates if you add or remove a component. If you do both add AND remove, then the add should also trigger UpdateGrassTypes() which will invalidate this cache. Negative is the invalid state.
- L719 _public member_ `bool bHasAnyGrass = true;`
- L720 _public member_ `double MaxInstanceDiscardDistance = DBL_MAX;`

#### struct `ALandscapeProxy::FRawMeshExportParams`  
`struct FRawMeshExportParams`  
_L1425-1500_
- L1427 _public member_ `static constexpr int32 MaxUVCount = 6;`
- L1468 _public prototype_ `FRawMeshExportParams() = default;`
- L1469 _public prototype_ `const FUVConfiguration& GetUVConfiguration(int32 InComponentIndex) const;`
- L1470 _public prototype_ `const FName& GetMaterialSlotName(int32 InComponentIndex) const;`
- L1471 _public prototype_ `int32 GetNumUVChannelsNeeded() const;`
- L1475 _public member_ `int32 ExportLOD = INDEX_NONE;` — LOD level to export. If none specified, LOD 0 will be used
- L1478 _public member_ `FUVConfiguration UVConfiguration;` — Describes what each UV channel should contain.
- L1481 _public member_ `EExportCoordinatesType ExportCoordinatesType = EExportCoordinatesType::Absolute;` — Referential for the vertex coordinates.
- L1484 _public member_ `FName MaterialSlotName = "La` — Name of the default polygon group's material slot in the mesh.
- L1487 _public member_ `TOptional<FBoxSphereBounds> ExportBounds;` — Box/Sphere bounds which limits the geometry exported out into OutRawMesh (optional: if none specified, the entire mesh is exported)
- L1490 _public member_ `TOptional<float> SkirtDepth;` — Depth of a one quad skirt to generate around the Proxy
- L1493 _public member_ `TOptional<TArrayView<ULandscapeComponent*>> ComponentsToExport;` — List of components from the proxy to actually export (optional : if none specified, all landscape components will be exported)
- L1496 _public member_ `TOptional<TArrayView<FUVConfiguration>> ComponentsUVConfiguration;` — Per-component UV configuration, in case ComponentsToExport is specified (optional: if none specified, all UV channels will contain the same information, as specified by UVConfiguration + there must be as many elements as there are in ComponentsToExport
- L1499 _public member_ `TOptional<TArrayView<FName>> ComponentsMaterialSlotName;` — Per-component material slot name (optional : if specified, one polygon group per component will be assigned the corresponding material slot's name, otherwise, MaterialSlotName will be used.

#### enum `ALandscapeProxy::FRawMeshExportParams::EUVMappingType`  
`enum class EUVMappingType : uint8`  
_L1430-1445_
- desc: Describes what information the export will write in a given UV channel
- L1432 _public enumerator_ `None`
- L1435 _public enumerator_ `RelativeToProxyBoundsUV` — TODO [jonathan.bard] : RelativeToComponentsBoundsUV,   Only valid when ComponentsToExport is set : normalized UVs spanning the ComponentToExport's bounds, i.e. (0,0) at the bottom left corner of those components' lower left component -> (1,1) at the top right corner of those components' upper right component
- L1437 _public enumerator_ `HeightmapUV` — TODO[jonathan.bard] : RelativeToLandscapeBoundsUV,   Normalized UVs spanning the entire landscape bounds, i.e. (0,0) at the bottom left corner of the landscape's lower left landscape component -> (1,1) at the top right corner of the landscape's upper right component
- L1438 _public enumerator_ `WeightmapUV` — HeightmapUV,			  Export the heightmaps' UV mapping
- L1439 _public enumerator_ `TerrainCoordMapping_XY` — WeightmapUV,			  Export the weightmaps' UV mapping
- L1440 _public enumerator_ `TerrainCoordMapping_XZ` — TerrainCoordMapping_XY,   Similar to ETerrainCoordMappingType::TCMT_XY
- L1441 _public enumerator_ `TerrainCoordMapping_YZ` — TerrainCoordMapping_XZ,   Similar to ETerrainCoordMappingType::TCMT_XZ
- L1442 _public enumerator_ `LightmapUV` — TerrainCoordMapping_YZ,   Similar to ETerrainCoordMappingType::TCMT_YZ
- L1444 _public enumerator_ `Num`

#### struct `ALandscapeProxy::FRawMeshExportParams::FUVConfiguration`  
`struct FUVConfiguration`  
_L1448-1456_
- desc: Describes what to export on each UV channel
- L1450 _public prototype_ `FUVConfiguration();`
- L1451 _public prototype_ `int32 GetNumUVChannelsNeeded() const;`
- L1455 _public member_ `TArray<EUVMappingType> ExportUVMappingTypes;` — Index 0 = UVChannel 0, Index 1 = UVChannel 1...

#### enum `ALandscapeProxy::FRawMeshExportParams::EExportCoordinatesType`  
`enum class EExportCoordinatesType : uint8`  
_L1458-1465_
- L1460 _public enumerator_ `Absolute`
- L1461 _public enumerator_ `RelativeToProxy`

#### class `FLandscapePhysicalMaterialBuilder`  
`class FLandscapePhysicalMaterialBuilder`  
_L1753-1762_
- desc: Helper class used to Build or monitor Landscape Physical Material
- L1756 _public prototype_ `FLandscapePhysicalMaterialBuilder(UWorld* InWorld);`
- L1757 _public prototype_ `void Build(UE::Landscape::EBuildFlags InBuildFlags);`
- L1758 _public prototype_ `int32 GetOudatedPhysicalMaterialComponentsCount();`
- L1760 _private member_ `UWorld* World;`
- L1761 _private member_ `int32 OudatedPhysicalMaterialComponentsCount;`

#### class `FLandscapeProxyComponentDataChangedParams`  
`class FLandscapeProxyComponentDataChangedParams`  
_L1767-1776_
- desc: Helper class to store proxy changes information
- L1770 _public prototype_ `FLandscapeProxyComponentDataChangedParams(const TSet<ULandscapeComponent*>& InComponents);`
- L1771 _public prototype_ `void ForEachComponent(TFunctionRef<void(const ULandscapeComponent*)> Func) const;`
- L1772 _public function_ `const TArray<ULandscapeComponent*>& GetComponents() const`
- L1775 _private member_ `TArray<ULandscapeComponent*> Components;`

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace UE`
- L54 _namespace_ `namespace Landscape` (scope `UE`)
- L59 _namespace_ `namespace Nanite` (scope `UE::Landscape`)
- L66 _externvar_ `extern bool GLandscapeEditModeActive;`
- L67 _externvar_ `extern int32 GGrassMapUseRuntimeGeneration;`
- L69 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLandscapeProxyComponentDataChanged, ALandscapeProxy*, const FLandscapeProxyComponentDataChangedParams&);`
- L69 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLandscapeProxyComponentDataChanged, ALandscapeProxy*, const FLandscapeProxyComponentDataChangedParams&);`
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLandscapeProxyMaterialChanged, ALandscapeProxy*, const FOnLandscapeProxyMaterialChangedParams&);`
- L74 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLandscapeProxyMaterialChanged, ALandscapeProxy*, const FOnLandscapeProxyMaterialChangedParams&);`
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLandscapeProxyFixupSharedDataDelegate, ALandscapeProxy* , const FOnLandscapeProxyFixupSharedDataParams& );`
- L83 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLandscapeProxyFixupSharedDataDelegate, ALandscapeProxy* , const FOnLandscapeProxyFixupSharedDataParams& );`
- L110 _function_ `inline friend uint32 GetTypeHash(const FLandscapeGrassName& InGrassName)` — Used so we can have a TMap of this struct
- L282 _namespace_ `namespace ELandscapeLODFalloff`
- L1778 _prototype_ `DEFINE_ACTORDESC_TYPE(ALandscapeProxy, FLandscapeActorDesc);`

### `Source/Runtime/Landscape/Classes/LandscapeSplineActor.h` (Public)


#### class `ALandscapeSplineActor`  
`class ALandscapeSplineActor : public AActor, public ILandscapeSplineInterface`  
_L14-62_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, NotPlaceable, hidecategories = (Display, Attachment, Physics, Debug, Lighting, Input))`
- inherits: `AActor,ILandscapeSplineInterface`
- L21 _protected member_ `FGuid LandscapeGuid;` — `UPROPERTY()` — Guid for LandscapeInfo
- L26 _protected member_ `TObjectPtr<ALandscape> LandscapeActor;` — `UPROPERTY(EditAnywhere, Category = "Target Landscape")` — Landscape
- L30 _public function_ `virtual FGuid GetLandscapeGuid() const override`
- L31 _public prototype_ `virtual ULandscapeSplinesComponent* GetSplinesComponent() const override;`
- L32 _public prototype_ `virtual FTransform LandscapeActorToWorld() const override;`
- L33 _public prototype_ `virtual ULandscapeInfo* GetLandscapeInfo() const override;`
- L34 _public prototype_ `virtual void UpdateSharedProperties(ULandscapeInfo* InLandscapeInfo) override;`
- L35 _public prototype_ `virtual bool IsSplineOwnerValid() const override;`
- L38 _public prototype_ `bool ShouldPartitionSpline() const;`
- L39 _public prototype_ `bool HasGeneratedLandscapeSplineMeshesActors() const;`
- L40 _public prototype_ `void SetLandscapeGuid(const FGuid& InGuid);`
- L41 _public prototype_ `virtual void GetActorDescProperties(FPropertyPairsMap& PropertyPairsMap) const override;`
- L43 _public prototype_ `void GetSharedProperties(ULandscapeInfo* InLandscapeInfo);`
- L45 _public prototype_ `virtual void Destroyed() override;`
- L46 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L47 _public prototype_ `virtual void UnregisterAllComponents(bool bForReregister = false) override;`
- L48 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L49 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _public function_ `virtual bool EditorCanAttachTo(const AActor* InParent, FText& OutReason) const override`
- L51 _public prototype_ `virtual AActor* GetSceneOutlinerParent() const;`
- L52 _public function_ `virtual bool SupportsForeignSplineMesh() const override`
- L55 _public function_ `virtual void CreateSplineComponent() override` — Interface existes for backward compatibility. Should already be created since its this actor's root component.
- L56 _public function_ `virtual void CreateSplineComponent(const FVector& Scale3D) override`
- L59 _private prototype_ `void SetLandscapeActor(ALandscape* InLandscapeActor);`

### `Source/Runtime/Landscape/Classes/LandscapeSplineControlPoint.h` (Public)


#### struct `FLandscapeSplineConnection`  
`struct FLandscapeSplineConnection`  
_L20-47_
- reflection: `USTRUCT()`
- L24 _public function_ `FLandscapeSplineConnection() : Segment(nullptr), End(0)`
- L26 _public function_ `FLandscapeSplineConnection(ULandscapeSplineSegment* InSegment, int32 InEnd) : Segment(InSegment) , End(InEnd)`
- L32 _public function_ `bool operator == (const FLandscapeSplineConnection& rhs) const`
- L39 _public member_ `TObjectPtr<ULandscapeSplineSegment> Segment;` — `UPROPERTY()` — Segment connected to this control point
- L43 _public member_ `uint32 End:1;` — `UPROPERTY()` — Which end of the segment is connected to this control point
- L45 _public prototype_ `FLandscapeSplineSegmentConnection& GetNearConnection() const;`
- L46 _public prototype_ `FLandscapeSplineSegmentConnection& GetFarConnection() const;`

#### class `ULandscapeSplineControlPoint`  
`class ULandscapeSplineControlPoint : public UObject`  
_L50-303_
- reflection: `UCLASS(Within=LandscapeSplinesComponent,autoExpandCategories=LandscapeSplineControlPoint,MinimalAPI)`
- inherits: `UObject`
- L57 _private member_ `FVector Location;` — `UPROPERTY(EditAnywhere, Category=LandscapeSpline)` — Location in Landscape-space
- L61 _private member_ `FRotator Rotation;` — `UPROPERTY(EditAnywhere, Category=LandscapeSpline)` — Rotation of tangent vector at this point (in landscape-space)
- L65 _private member_ `float Width;` — `UPROPERTY(EditAnywhere, Category=LandscapeSpline, meta = (DisplayName = "Half-Width"))` — Half-Width of the spline at this point.
- L69 _private member_ `float LayerWidthRatio = 1.f;` — `UPROPERTY(EditAnywhere, Category = LandscapeSpline)` — Layer Width ratio of the spline at this point.
- L73 _private member_ `float SideFalloff;` — `UPROPERTY(EditAnywhere, Category=LandscapeSpline)` — Falloff at the sides of the spline at this point.
- L76 _private member_ `float LeftSideFalloffFactor = 1.f;` — `UPROPERTY(EditAnywhere, Category = LandscapeSpline, meta=(UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))`
- L79 _private member_ `float RightSideFalloffFactor = 1.f;` — `UPROPERTY(EditAnywhere, Category = LandscapeSpline, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))`
- L82 _private member_ `float LeftSideLayerFalloffFactor = 0.5f;` — `UPROPERTY(EditAnywhere, Category = LandscapeSpline, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))`
- L85 _private member_ `float RightSideLayerFalloffFactor = 0.5f;` — `UPROPERTY(EditAnywhere, Category = LandscapeSpline, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))`
- L89 _private member_ `float EndFalloff;` — `UPROPERTY(EditAnywhere, Category=LandscapeSpline)` — Falloff at the start/end of the spline (if this point is a start or end point, otherwise ignored).
- L94 _private member_ `float SegmentMeshOffset;` — `UPROPERTY(EditAnywhere, Category=LandscapeSpline, meta=(DisplayName="Mesh Vertical Offset"))` — Vertical offset of the spline segment mesh. Useful for a river's surface, among other things.
- L101 _private member_ `FName LayerName;` — `UPROPERTY(EditAnywhere, Category=LandscapeDeformation)` — Name of blend layer to paint when applying spline to landscape If "none", no layer is painted
- L105 _private member_ `uint32 bRaiseTerrain:1;` — `UPROPERTY(EditAnywhere, Category=LandscapeDeformation)` — If the spline is above the terrain, whether to raise the terrain up to the level of the spline when applying it to the landscape.
- L109 _private member_ `uint32 bLowerTerrain:1;` — `UPROPERTY(EditAnywhere, Category=LandscapeDeformation)` — If the spline is below the terrain, whether to lower the terrain down to the level of the spline when applying it to the landscape.
- L113 _private member_ `TObjectPtr<UStaticMesh> Mesh;` — `UPROPERTY(EditAnywhere, Category=Mesh)` — Mesh to use on the control point
- L117 _private member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialOverrides;` — `UPROPERTY(EditAnywhere, Category=Mesh)` — Overrides mesh's materials
- L121 _private member_ `FVector MeshScale;` — `UPROPERTY(EditAnywhere, Category=Mesh)` — Scale of the control point mesh
- L124 _private member_ `uint32 bEnableCollision_DEPRECATED:1;` — `UPROPERTY()`
- L127 _private member_ `FName CollisionProfileName_DEPRECATED;` — `UPROPERTY()`
- L131 _private member_ `uint32 bCastShadow:1;` — `UPROPERTY(EditAnywhere, Category=Mesh)` — Whether the Control Point Mesh should cast a shadow.
- L135 _private member_ `uint8 bHiddenInGame : 1;` — `UPROPERTY(EditAnywhere, Category = Mesh, AdvancedDisplay)` — Whether to hide the mesh in game
- L139 _private member_ `uint32 bPlaceSplineMeshesInStreamingLevels : 1;` — `UPROPERTY(EditAnywhere, Category = Mesh, AdvancedDisplay)` — Whether control point mesh should be placed in landscape proxy streaming level (true) or the spline's level (false)
- L143 _private member_ `float LDMaxDrawDistance;` — `UPROPERTY(EditAnywhere, Category=Mesh, AdvancedDisplay, meta=(DisplayName="Max Draw Distance"))` — Max draw distance for the mesh used on this control point
- L154 _private member_ `int32 TranslucencySortPriority;` — `UPROPERTY(EditAnywhere, Category=Mesh, AdvancedDisplay)` — Translucent objects with a lower sort priority draw behind objects with a higher priority. Translucent objects with the same priority are rendered from back-to-front based on their bounds origin. This setting is also used to sort objects being drawn into a runtime virtual texture. Ignored if the object is not translucent.  The default priority is zero. Warning: This should never be set to a non-default value unless you know what you are doing, as it will prevent the renderer from sorting correctly.
- L158 _private member_ `uint8 bRenderCustomDepth : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Mesh, meta = (DisplayName = "Render CustomDepth Pass"))` — If true, this component will be rendered in the CustomDepth pass (usually used for outlines)
- L162 _private member_ `ERendererStencilMask CustomDepthStencilWriteMask;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Mesh, meta = (editcondition = "bRenderCustomDepth"))` — Mask used for stencil buffer writes.
- L166 _private member_ `int32 CustomDepthStencilValue;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Mesh, meta = (UIMin = "0", UIMax = "255", editcondition = "bRenderCustomDepth", DisplayName = "CustomDepth Stencil Value"))` — Optionally write this 0-255 value to the stencil buffer in CustomDepth pass (Requires project setting or r.CustomDepth == 3)
- L173 _private member_ `TArray<TObjectPtr<URuntimeVirtualTexture>> RuntimeVirtualTextures;` — `UPROPERTY(EditAnywhere, Category = VirtualTexture, meta = (DisplayName = "Draw in Virtual Textures"))` — Array of runtime virtual textures into which we draw the spline segment. The material also needs to be set up to output to a virtual texture.
- L177 _private member_ `int32 VirtualTextureLodBias = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = VirtualTexture, meta = (DisplayName = "Virtual Texture LOD Bias", UIMin = "-7", UIMax = "8"))` — Lod bias for rendering to runtime virtual texture.
- L185 _private member_ `int32 VirtualTextureCullMips = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = VirtualTexture, meta = (DisplayName = "Virtual Texture Skip Mips", UIMin = "0", UIMax = "7"))` — Number of lower mips in the runtime virtual texture to skip for rendering this primitive. Larger values reduce the effective draw distance in the runtime virtual texture. This culling method doesn't take into account primitive size or virtual texture size.
- L189 _private member_ `float VirtualTextureMainPassMaxDrawDistance = 0.f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = VirtualTexture, meta = (DisplayName = "Max Draw Distance in Main Pass"))` — Desired cull distance in the main pass if we are rendering to both the virtual texture AND the main pass. A value of 0 has no effect.
- L193 _private member_ `ERuntimeVirtualTextureMainPassType VirtualTextureRenderPassType = ERuntimeVirtualTextureMainPassType::Exclusive;` — `UPROPERTY(EditAnywhere, Category = VirtualTexture, meta = (DisplayName = "Draw in Main Pass"))` — Controls if this component draws in the main pass as well as in the virtual texture.
- L197 _private member_ `FBodyInstance BodyInstance;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (ShowOnlyInnerProperties))` — Mesh Collision Settings
- L201 _private member_ `TObjectPtr<UHLODLayer> HLODLayerOverrideForSplinePartitioning;` — `UPROPERTY(EditAnywhere, Category = HLOD, AdvancedDisplay)` — Custom HLOD layer to use for this spline control point. Only relevant when using World Partition with spline partitioning.
- L205 _protected member_ `uint32 bSelected : 1;` — `UPROPERTY(Transient)`
- L208 _protected member_ `uint32 bNavDirty : 1;` — `UPROPERTY(Transient)`
- L214 _public member_ `TArray<FLandscapeSplineConnection> ConnectedSegments;` — `UPROPERTY(TextExportTransient)`
- L219 _protected member_ `TArray<FLandscapeSplineInterpPoint> Points;` — `UPROPERTY()` — Spline points
- L223 _protected member_ `FBox Bounds;` — `UPROPERTY()` — Bounds of points
- L227 _protected member_ `TObjectPtr<UControlPointMeshComponent> LocalMeshComponent;` — `UPROPERTY(TextExportTransient)` — Control point mesh
- L232 _protected member_ `TSoftObjectPtr<UWorld> ForeignWorld;` — `UPROPERTY(TextExportTransient, NonPIEDuplicateTransient)` — World reference for if mesh component is stored in another streaming level
- L236 _protected member_ `FGuid ModificationKey;` — `UPROPERTY(TextExportTransient, NonPIEDuplicateTransient)` — Key for tracking whether this segment has been modified relative to the mesh component stored in another streaming level
- L240 _public function_ `const FBox& GetBounds() const`
- L241 _public function_ `const TArray<FLandscapeSplineInterpPoint>& GetPoints() const`
- L244 _public prototype_ `bool SupportsForeignSplineMesh() const;`
- L247 _public prototype_ `virtual FName GetBestConnectionTo(FVector Destination) const;` — Get the name of the best connection point (socket) to use for a particular destination
- L250 _public prototype_ `virtual void GetConnectionLocalLocationAndRotation(FName SocketName, OUT FVector& OutLocation, OUT FRotator& OutRotation) const;` — Get the location and rotation of a connection point (socket) in spline space
- L253 _public prototype_ `virtual void GetConnectionLocationAndRotation(FName SocketName, OUT FVector& OutLocation, OUT FRotator& OutRotation) const;` — Get the location and rotation of a connection point (socket) in spline space
- L255 _public function_ `bool IsSplineSelected() const`
- L256 _public prototype_ `virtual void SetSplineSelected(bool bInSelected);`
- L259 _public prototype_ `virtual void AutoCalcRotation(bool bAlwaysRotateForward);` — Calculates rotation from connected segments
- L262 _public prototype_ `virtual void AutoFlipTangents();`
- L264 _public prototype_ `virtual void AutoSetConnections(bool bIncludingValid);`
- L266 _public prototype_ `TMap<ULandscapeSplinesComponent*, UControlPointMeshComponent*> GetForeignMeshComponents();`
- L269 _public prototype_ `virtual void UpdateSplinePoints(bool bUpdateCollision = true, bool bUpdateAttachedSegments = true, bool bUpdateMeshLevel = false);` — Update spline points
- L272 _public prototype_ `virtual void UpdateSplineMeshSelectionState();` — Update spline mesh selection state
- L275 _public prototype_ `virtual void DeleteSplinePoints();` — Delete spline points
- L277 _public function_ `const TSoftObjectPtr<UWorld>& GetForeignWorld() const`
- L278 _public function_ `FGuid GetModificationKey() const`
- L280 _public prototype_ `FName GetCollisionProfileName() const;`
- L284 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L285 _public prototype_ `virtual void PostLoad() override;`
- L287 _public prototype_ `virtual void PostEditUndo() override;`
- L288 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L289 _public prototype_ `virtual void PostEditImport() override;`
- L290 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L291 _public function_ `virtual bool IsCapturingAsRootObjectForTransaction() const override`
- L297 _public prototype_ `ULandscapeSplinesComponent* GetOuterSafe() const;` — Use GetOuterSafe instead of GetOuterULandscapeSplinesComponent if there is any danger that this point has been deleted (via DeleteSplinePoints). This will return nullptr in that case, because the outer is no longer a ULandscapeSplinesComponent
- L299 _public prototype_ `ULandscapeSplinesComponent* GetOuterChecked() const;` — Use GetOuterChecked when the call is always expected to succeed.  Will assert if it fails.

### `Source/Runtime/Landscape/Classes/LandscapeSplineMeshesActor.h` (Public)


#### class `ALandscapeSplineMeshesActor`  
`class ALandscapeSplineMeshesActor : public APartitionActor`  
_L15-55_
- reflection: `UCLASS(NotPlaceable, NotBlueprintable, hideCategories = (Input), showCategories = ("Input|MouseInput", "Input|TouchInput"), ConversionRoot, ComponentWrapperClass, meta = (ChildCanTick), MinimalAPI)`
- inherits: `APartitionActor`
- desc: This class is only intended to be used by UWorldPartitionLandscapeSplineMeshesBuilder which extracts and clones landscape spline and control point static meshes into partitioned actors This serves as an optimization as these actors will be streamed at runtime
- L21 _private member_ `TArray<TObjectPtr<class UStaticMeshComponent>> StaticMeshComponents;` — `UPROPERTY(Category = PartitionSplineMeshActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh,Components|SplineMesh", AllowPrivateAccess = "true"))`
- L26 _public prototype_ `class UStaticMeshComponent* CreateStaticMeshComponent(const TSubclassOf<class UStaticMeshComponent>& InComponentClass);`
- L27 _public prototype_ `void ClearStaticMeshComponents();`
- L30 _public prototype_ `virtual void CheckForErrors() override;`
- L31 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L32 _public function_ `virtual bool IsRuntimeOnly() const override`
- L36 _public prototype_ `virtual uint32 GetDefaultGridSize(UWorld* InWorld) const override;`
- L37 _public function_ `virtual FGuid GetGridGuid() const override`
- L40 _public function_ `void SetGridGuid(const FGuid& InGuid)`
- L43 _public prototype_ `const TArray<class UStaticMeshComponent*>& GetStaticMeshComponents() const;`
- L47 _protected prototype_ `virtual FString GetDetailedInfoInternal() const override;`
- L53 _private member_ `FGuid GridGuid;` — `UPROPERTY()`

### `Source/Runtime/Landscape/Classes/LandscapeSplineSegment.h` (Public)


#### struct `FLandscapeSplineInterpPoint`  
`struct FLandscapeSplineInterpPoint`  
_L22-94_
- reflection: `USTRUCT()`
- L28 _public member_ `FVector Center;` — `UPROPERTY()` — Center Point
- L32 _public member_ `FVector Left;` — `UPROPERTY()` — Left Point
- L36 _public member_ `FVector Right;` — `UPROPERTY()` — Right Point
- L40 _public member_ `FVector FalloffLeft;` — `UPROPERTY()` — Left Falloff Point
- L44 _public member_ `FVector FalloffRight;` — `UPROPERTY()` — Right FalloffPoint
- L48 _public member_ `FVector LayerLeft;` — `UPROPERTY()` — Layer Left Point
- L52 _public member_ `FVector LayerRight;` — `UPROPERTY()` — Layer Right Point
- L56 _public member_ `FVector LayerFalloffLeft;` — `UPROPERTY()` — Left Layer Falloff Point
- L60 _public member_ `FVector LayerFalloffRight;` — `UPROPERTY()` — Right Layer FalloffPoint
- L65 _public member_ `float StartEndFalloff;` — `UPROPERTY()` — Start/End Falloff fraction
- L67 _public function_ `FLandscapeSplineInterpPoint() : Center(ForceInitToZero) , Left(ForceInitToZero) , Right(ForceInitToZero) , FalloffLeft(ForceInitToZero) , FalloffRight(ForceInitToZero) , LayerLeft(ForceInitToZero) , LayerRight(ForceInitToZero) , LayerFalloffLeft(ForceInitToZero) , LayerFalloffRight(ForceInitToZero) , StartEndFalloff(0.0f)`
- L81 _public function_ `FLandscapeSplineInterpPoint(FVector InCenter, FVector InLeft, FVector InRight, FVector InFalloffLeft, FVector InFalloffRight, FVector InLayerLeft, FVector InLayerRight, FVector InLayerFalloffLeft, FVector InLayerFalloffRight, float InStartEndFalloff) : Center(InCenter), Left(InLeft), Right(InRight), FalloffLeft(InFalloffLeft), FalloffRight(InFalloffRight), LayerLeft(InLayerLeft), LayerRight(InLayerRight), LayerFalloffLeft(InLayerFalloffLeft), LayerFalloffRight(InLayerFalloffRight), StartEndFalloff(InStartEndFalloff)`

#### struct `FLandscapeSplineSegmentConnection`  
`struct FLandscapeSplineSegmentConnection`  
_L97-119_
- reflection: `USTRUCT()`
- L103 _public member_ `TObjectPtr<ULandscapeSplineControlPoint> ControlPoint;` — `UPROPERTY()` — Control point connected to this end of the segment
- L107 _public member_ `float TangentLen;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineSegmentConnection)` — Tangent length of the connection
- L111 _public member_ `FName SocketName;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineSegmentConnection)` — Socket on the control point that we are connected to
- L113 _public function_ `FLandscapeSplineSegmentConnection() : ControlPoint(nullptr) , TangentLen(0.0f) , SocketName(NAME_None)`

#### enum `LandscapeSplineMeshOrientation`  
`enum LandscapeSplineMeshOrientation : int`  
_L123-128_
- reflection: `UENUM()`
- desc: Deprecated
- L125 _public enumerator_ `LSMO_XUp`
- L126 _public enumerator_ `LSMO_YUp`
- L127 _public enumerator_ `LSMO_MAX`

#### struct `FLandscapeSplineMeshEntry`  
`struct FLandscapeSplineMeshEntry`  
_L131-190_
- reflection: `USTRUCT()`
- L137 _public member_ `TObjectPtr<UStaticMesh> Mesh;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshEntry)` — Mesh to use on the spline
- L141 _public member_ `TArray<TObjectPtr<UMaterialInterface>> MaterialOverrides;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshEntry, AdvancedDisplay)` — Overrides mesh's materials
- L145 _public member_ `uint32 bCenterH:1;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshEntry, meta=(DisplayName="Center Horizontally"))` — Whether to automatically center the mesh horizontally on the spline
- L149 _public member_ `FVector2D CenterAdjust;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshEntry, AdvancedDisplay, meta=(DisplayName="Center Adjust"))` — Tweak to center the mesh correctly on the spline
- L153 _public member_ `uint32 bScaleToWidth:1;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshEntry)` — Whether to scale the mesh to fit the width of the spline
- L157 _public member_ `uint32 bNoZScaling:1;` — `UPROPERTY(EditAnywhere, Category = LandscapeSplineMeshEntry, meta = (EditCondition = "bScaleToWidth"))` — Disables scale to width on the mesh Z coordinate
- L161 _public member_ `FVector Scale;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshEntry)` — Scale of the spline mesh, (Z=Forwards)
- L165 _public member_ `TEnumAsByte<LandscapeSplineMeshOrientation> Orientation_DEPRECATED;` — `UPROPERTY()` — Orientation of the spline mesh, X=Up or Y=Up
- L169 _public member_ `TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshEntry)` — Chooses the forward axis for the spline mesh orientation
- L173 _public member_ `TEnumAsByte<ESplineMeshAxis::Type> UpAxis;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshEntry)` — Chooses the up axis for the spline mesh orientation
- L175 _public function_ `FLandscapeSplineMeshEntry() : Mesh(nullptr), MaterialOverrides(), bCenterH(true), CenterAdjust(0, 0), bScaleToWidth(true), bNoZScaling(false), Scale(1,1,1), Orientation_DEPRECATED(LSMO_YUp), ForwardAxis(ESplineMeshAxis::X), UpAxis(ESplineMeshAxis::Z)`
- L189 _public prototype_ `bool IsValid() const;`

#### class `ULandscapeSplineSegment`  
`class ULandscapeSplineSegment : public UObject`  
_L194-401_
- reflection: `UCLASS(Within=LandscapeSplinesComponent,autoExpandCategories=(LandscapeSplineSegment,LandscapeSplineMeshes),MinimalAPI)`
- inherits: `UObject`
- L200 _private member_ `FLandscapeSplineSegmentConnection Connections[2];` — `UPROPERTY(EditAnywhere, EditFixedSize, Category=LandscapeSplineSegment)` — Directly editable data:
- L208 _private member_ `FName LayerName;` — `UPROPERTY(EditAnywhere, Category=LandscapeDeformation)` — Name of blend layer to paint when applying spline to landscape If "none", no layer is painted
- L212 _private member_ `uint32 bRaiseTerrain:1;` — `UPROPERTY(EditAnywhere, Category=LandscapeDeformation)` — If the spline is above the terrain, whether to raise the terrain up to the level of the spline when applying it to the landscape.
- L216 _private member_ `uint32 bLowerTerrain:1;` — `UPROPERTY(EditAnywhere, Category=LandscapeDeformation)` — If the spline is below the terrain, whether to lower the terrain down to the level of the spline when applying it to the landscape.
- L220 _private member_ `TArray<FLandscapeSplineMeshEntry> SplineMeshes;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshes)` — Spline meshes from this list are used in random order along the spline.
- L223 _private member_ `uint32 bEnableCollision_DEPRECATED:1;` — `UPROPERTY()`
- L226 _private member_ `FName CollisionProfileName_DEPRECATED;` — `UPROPERTY()`
- L230 _private member_ `uint32 bCastShadow:1;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshes)` — Whether the Spline Meshes should cast a shadow.
- L234 _private member_ `uint32 bHiddenInGame : 1;` — `UPROPERTY(EditAnywhere, Category = LandscapeSplineMeshes, AdvancedDisplay)` — Whether to hide the mesh in game
- L238 _private member_ `uint32 bPlaceSplineMeshesInStreamingLevels : 1;` — `UPROPERTY(EditAnywhere, Category = LandscapeSplineMeshes, AdvancedDisplay)` — Whether spline meshes should be placed in landscape proxy streaming levels (true) or the spline's level (false)
- L242 _private member_ `int32 RandomSeed;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshes, AdvancedDisplay)` — Random seed used for choosing which order to use spline meshes. Ignored if only one mesh is set.
- L246 _private member_ `float LDMaxDrawDistance;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshes, AdvancedDisplay, meta=(DisplayName="Max Draw Distance"))` — Max draw distance for all the mesh pieces used in this spline
- L257 _private member_ `int32 TranslucencySortPriority;` — `UPROPERTY(EditAnywhere, Category=LandscapeSplineMeshes, AdvancedDisplay)` — Translucent objects with a lower sort priority draw behind objects with a higher priority. Translucent objects with the same priority are rendered from back-to-front based on their bounds origin. This setting is also used to sort objects being drawn into a runtime virtual texture. Ignored if the object is not translucent.  The default priority is zero. Warning: This should never be set to a non-default value unless you know what you are doing, as it will prevent the renderer from sorting correctly.
- L261 _private member_ `uint8 bRenderCustomDepth : 1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = LandscapeSplineMeshes, meta = (DisplayName = "Render CustomDepth Pass"))` — If true, this component will be rendered in the CustomDepth pass (usually used for outlines)
- L265 _private member_ `ERendererStencilMask CustomDepthStencilWriteMask;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = LandscapeSplineMeshes, meta = (editcondition = "bRenderCustomDepth"))` — Mask used for stencil buffer writes.
- L269 _private member_ `int32 CustomDepthStencilValue;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = LandscapeSplineMeshes, meta = (UIMin = "0", UIMax = "255", editcondition = "bRenderCustomDepth", DisplayName = "CustomDepth Stencil Value"))` — Optionally write this 0-255 value to the stencil buffer in CustomDepth pass (Requires project setting or r.CustomDepth == 3)
- L276 _private member_ `TArray<TObjectPtr<URuntimeVirtualTexture>> RuntimeVirtualTextures;` — `UPROPERTY(EditAnywhere, Category = VirtualTexture, meta = (DisplayName = "Draw in Virtual Textures"))` — Array of runtime virtual textures into which we draw the spline segment. The material also needs to be set up to output to a virtual texture.
- L280 _private member_ `int32 VirtualTextureLodBias = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = VirtualTexture, meta = (DisplayName = "Virtual Texture LOD Bias", UIMin = "-7", UIMax = "8"))` — Lod bias for rendering to runtime virtual texture.
- L288 _private member_ `int32 VirtualTextureCullMips = 0;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = VirtualTexture, meta = (DisplayName = "Virtual Texture Skip Mips", UIMin = "0", UIMax = "7"))` — Number of lower mips in the runtime virtual texture to skip for rendering this primitive. Larger values reduce the effective draw distance in the runtime virtual texture. This culling method doesn't take into account primitive size or virtual texture size.
- L292 _private member_ `float VirtualTextureMainPassMaxDrawDistance = 0.f;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = VirtualTexture, meta = (DisplayName = "Max Draw Distance in Main Pass"))` — Desired cull distance in the main pass if we are rendering to both the virtual texture AND the main pass. A value of 0 has no effect.
- L296 _private member_ `ERuntimeVirtualTextureMainPassType VirtualTextureRenderPassType = ERuntimeVirtualTextureMainPassType::Exclusive;` — `UPROPERTY(EditAnywhere, Category = VirtualTexture, meta = (DisplayName = "Draw in Main Pass"))` — Controls if this component draws in the main pass as well as in the virtual texture.
- L300 _private member_ `FBodyInstance BodyInstance;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (ShowOnlyInnerProperties))` — Mesh Collision Settings
- L304 _private member_ `TObjectPtr<UHLODLayer> HLODLayerOverrideForSplinePartitioning;` — `UPROPERTY(EditAnywhere, Category = HLOD, AdvancedDisplay)` — Custom HLOD layer to use for this spline segment. Only relevant when using World Partition with spline partitioning.
- L308 _protected member_ `uint32 bSelected : 1;` — `UPROPERTY(Transient)`
- L311 _protected member_ `uint32 bNavDirty : 1;` — `UPROPERTY(Transient)`
- L318 _protected member_ `FInterpCurveVector SplineInfo;` — `UPROPERTY()` — Actual data for spline.
- L322 _protected member_ `TArray<FLandscapeSplineInterpPoint> Points;` — `UPROPERTY()` — Spline points
- L326 _protected member_ `FBox Bounds;` — `UPROPERTY()` — Bounds of points
- L330 _protected member_ `TArray<TObjectPtr<USplineMeshComponent>> LocalMeshComponents;` — `UPROPERTY(TextExportTransient)` — Spline meshes
- L335 _protected member_ `TArray<TSoftObjectPtr<UWorld>> ForeignWorlds;` — `UPROPERTY(TextExportTransient, NonPIEDuplicateTransient)` — World references for mesh components stored in other streaming levels
- L339 _protected member_ `FGuid ModificationKey;` — `UPROPERTY(TextExportTransient, NonPIEDuplicateTransient)` — Key for tracking whether this segment has been modified relative to the mesh components stored in other streaming levels
- L343 _public function_ `const FBox& GetBounds() const`
- L344 _public function_ `const TArray<FLandscapeSplineInterpPoint>& GetPoints() const`
- L347 _public prototype_ `bool SupportsForeignSplineMesh() const;`
- L349 _public function_ `bool IsSplineSelected() const`
- L350 _public prototype_ `virtual void SetSplineSelected(bool bInSelected);`
- L352 _public prototype_ `virtual void AutoFlipTangents();`
- L354 _public prototype_ `TMap<ULandscapeSplinesComponent*, TArray<USplineMeshComponent*>> GetForeignMeshComponents();`
- L355 _public prototype_ `TArray<USplineMeshComponent*> GetLocalMeshComponents() const;`
- L357 _public prototype_ `virtual void UpdateSplinePoints(bool bUpdateCollision = true, bool bUpdateMeshLevel = false);`
- L358 _public prototype_ `virtual void UpdateSplineMeshSelectionState();`
- L359 _public prototype_ `void UpdateSplineEditorMesh();`
- L360 _public prototype_ `virtual void DeleteSplinePoints();`
- L362 _public prototype_ `FName GetCollisionProfileName() const;`
- L364 _public function_ `const TArray<TSoftObjectPtr<UWorld>>& GetForeignWorlds() const`
- L365 _public function_ `FGuid GetModificationKey() const`
- L368 _public prototype_ `virtual void FindNearest(const FVector& InLocation, float& t, FVector& OutLocation, FVector& OutTangent);`
- L371 _public prototype_ `FFloatInterval GetKeyInterval() const;` — Return the key interval for the segment curve points
- L374 _public prototype_ `FVector Evaluate(const float Key, const FVector& Default = FVector::ZeroVector) const;` — Evaluate the output for an arbitrary input value. For keys outside the range, the first/last key value is assumed.
- L377 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L378 _public prototype_ `virtual void PostLoad() override;`
- L380 _public prototype_ `virtual void PostEditUndo() override;`
- L381 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L382 _public prototype_ `virtual void PostEditImport() override;`
- L383 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L384 _public function_ `virtual bool IsCapturingAsRootObjectForTransaction() const override`
- L387 _protected prototype_ `virtual void PostInitProperties() override;`
- L389 _private prototype_ `void UpdateMeshCollisionProfile(USplineMeshComponent* MeshComponent);`
- L395 _public prototype_ `ULandscapeSplinesComponent* GetOuterSafe() const;` — Use GetOuterSafe instead of GetOuterULandscapeSplinesComponent if there is any danger that this segment has been deleted (via DeleteSplinePoints). This will return nullptr in that case, because the outer is no longer a ULandscapeSplinesComponent
- L397 _public prototype_ `ULandscapeSplinesComponent* GetOuterChecked() const;` — Use GetOuterChecked when the call is always expected to succeed.  Will assert if it fails.

### `Source/Runtime/Landscape/Classes/LandscapeSplinesComponent.h` (Public)


#### struct `FForeignControlPointData`  
`struct FForeignControlPointData`  
_L27-46_
- reflection: `USTRUCT()`
- desc: structs for ForeignWorldSplineDataMap these are editor-only, but we don't have the concept of an editor-only USTRUCT
- L33 _public member_ `FGuid ModificationKey;` — `UPROPERTY()`
- L36 _public member_ `TObjectPtr<UControlPointMeshComponent> MeshComponent = nullptr;` — `UPROPERTY()`
- L39 _public member_ `TLazyObjectPtr<ULandscapeSplineControlPoint> Identifier;` — `UPROPERTY()`

#### struct `FForeignSplineSegmentData`  
`struct FForeignSplineSegmentData`  
_L49-68_
- reflection: `USTRUCT()`
- L55 _public member_ `FGuid ModificationKey;` — `UPROPERTY()`
- L58 _public member_ `TArray<TObjectPtr<USplineMeshComponent>> MeshComponents;` — `UPROPERTY()`
- L61 _public member_ `TLazyObjectPtr<ULandscapeSplineSegment> Identifier;` — `UPROPERTY()`

#### struct `FForeignWorldSplineData`  
`struct FForeignWorldSplineData`  
_L71-99_
- reflection: `USTRUCT()`
- L78 _public member_ `TMap<TLazyObjectPtr<ULandscapeSplineControlPoint>, FForeignControlPointData> ForeignControlPointDataMap_DEPRECATED;` — `UPROPERTY()`
- L82 _public member_ `TArray<FForeignControlPointData> ForeignControlPointData;` — `UPROPERTY()`
- L86 _public member_ `TMap<TLazyObjectPtr<ULandscapeSplineSegment>, FForeignSplineSegmentData> ForeignSplineSegmentDataMap_DEPRECATED;` — `UPROPERTY()`
- L90 _public member_ `TArray<FForeignSplineSegmentData> ForeignSplineSegmentData;` — `UPROPERTY()`
- L94 _public prototype_ `bool IsEmpty();`
- L96 _public prototype_ `FForeignControlPointData* FindControlPoint(ULandscapeSplineControlPoint* InIdentifer);`
- L97 _public prototype_ `FForeignSplineSegmentData* FindSegmentData(ULandscapeSplineSegment* InIdentifer);`

#### class `ULandscapeSplinesComponent`  
`class ULandscapeSplinesComponent : public UPrimitiveComponent`  
_L106-261_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPrimitiveComponent`
- L113 _private member_ `float SplineResolution;` — `UPROPERTY()` — Resolution of the spline, in distance per point
- L117 _private member_ `FColor SplineColor;` — `UPROPERTY()` — Color to use to draw the splines
- L121 _private member_ `TObjectPtr<UTexture2D> ControlPointSprite;` — `UPROPERTY()` — Sprite used to draw control points
- L125 _private member_ `TObjectPtr<UStaticMesh> SplineEditorMesh;` — `UPROPERTY()` — Mesh used to draw splines that have no mesh
- L129 _private member_ `uint32 bShowSplineEditorMesh:1;` — `UPROPERTY(NonTransactional, Transient)` — Whether we are in-editor and showing spline editor meshes
- L134 _protected member_ `TArray<TObjectPtr<ULandscapeSplineControlPoint>> ControlPoints;` — `UPROPERTY(TextExportTransient)`
- L137 _protected member_ `TArray<TObjectPtr<ULandscapeSplineSegment>> Segments;` — `UPROPERTY(TextExportTransient)`
- L142 _protected member_ `TMap<TSoftObjectPtr<UWorld>, FForeignWorldSplineData> ForeignWorldSplineDataMap;` — `UPROPERTY(TextExportTransient)` — Serialized
- L145 _protected member_ `TMap<UMeshComponent*, UObject*> MeshComponentLocalOwnersMap;` — Transient - rebuilt on load
- L146 _protected member_ `TMap<UMeshComponent*, TLazyObjectPtr<UObject>> MeshComponentForeignOwnersMap;`
- L152 _protected member_ `TArray<TObjectPtr<UMeshComponent>> CookedForeignMeshComponents;` — `UPROPERTY(TextExportTransient)` — References to components owned by landscape splines in other levels for cooked build (uncooked keeps references via ForeignWorldSplineDataMap)
- L157 _public prototype_ `TArray<USplineMeshComponent*> GetSplineMeshComponents();` — `UFUNCTION(BlueprintCallable, Category = LandscapeSplines)` — Get a list of spline mesh components representing this landscape spline (Editor only)
- L159 _public prototype_ `ILandscapeSplineInterface* GetSplineOwner();`
- L162 _public prototype_ `void CheckSplinesValid();` — Run some ensures on the internal state of the data
- L164 _public prototype_ `bool ModifySplines(bool bAlwaysMarkDirty = true);`
- L166 _public function_ `const TArray<TObjectPtr<ULandscapeSplineControlPoint>>& GetControlPoints() const`
- L167 _public function_ `TArray<TObjectPtr<ULandscapeSplineControlPoint>>& GetControlPoints()`
- L169 _public function_ `const TArray<TObjectPtr<ULandscapeSplineSegment>>& GetSegments() const`
- L170 _public function_ `TArray<TObjectPtr<ULandscapeSplineSegment>>& GetSegments()`
- L173 _public prototype_ `void RequestSplineLayerUpdate();`
- L175 _public function_ `bool HasAnyControlPointsOrSegments() const`
- L177 _public prototype_ `virtual void ShowSplineEditorMesh(bool bShow);`
- L181 _public prototype_ `virtual void RebuildAllSplines(bool bBuildCollision = true);` — Rebuilds all spline points and meshes for all spline control points and segments in this splines component @param bBuildCollision Building collision data is very slow, so during interactive changes pass false to improve user experience (make sure to call with true when done)
- L186 _public prototype_ `ULandscapeSplinesComponent* GetStreamingSplinesComponentByLocation(const FVector& LocalLocation, bool bCreate = true);` — returns a suitable ULandscapeSplinesComponent to place streaming meshes into, given a location falls back to "this" if it can't find another suitable, so never returns nullptr @param bCreate whether to create a component if a suitable actor is found but it has no splines component yet
- L190 _public prototype_ `ULandscapeSplinesComponent* GetStreamingSplinesComponentForLevel(ULevel* Level, bool bCreate = true);` — returns the matching ULandscapeSplinesComponent for a given level, *can return null* @param bCreate whether to create a component if a suitable actor is found but it has no splines component yet
- L193 _public prototype_ `TArray<ULandscapeSplinesComponent*> GetAllStreamingSplinesComponents();` — gathers and returns all currently existing
- L195 _public prototype_ `virtual void UpdateModificationKey(ULandscapeSplineSegment* Owner);`
- L196 _public prototype_ `virtual void UpdateModificationKey(ULandscapeSplineControlPoint* Owner);`
- L197 _public prototype_ `virtual void AddForeignMeshComponent(ULandscapeSplineSegment* Owner, USplineMeshComponent* Component);`
- L198 _public prototype_ `virtual void RemoveForeignMeshComponent(ULandscapeSplineSegment* Owner, USplineMeshComponent* Component);`
- L199 _public prototype_ `virtual void RemoveAllForeignMeshComponents(ULandscapeSplineSegment* Owner);`
- L200 _public prototype_ `virtual void AddForeignMeshComponent(ULandscapeSplineControlPoint* Owner, UControlPointMeshComponent* Component);`
- L201 _public prototype_ `virtual void RemoveForeignMeshComponent(ULandscapeSplineControlPoint* Owner, UControlPointMeshComponent* Component);`
- L202 _public prototype_ `virtual void DestroyOrphanedForeignSplineMeshComponents(UWorld* OwnerWorld);`
- L203 _public prototype_ `virtual void DestroyOrphanedForeignControlPointMeshComponents(UWorld* OwnerWorld);`
- L205 _public prototype_ `void DestroyUnreferencedForeignMeshComponents();`
- L206 _public prototype_ `void ForEachUnreferencedForeignMeshComponent(TFunctionRef<bool(ULandscapeSplineSegment*, USplineMeshComponent*, ULandscapeSplineControlPoint*, UControlPointMeshComponent*)> Func);`
- L208 _public prototype_ `virtual UControlPointMeshComponent* GetForeignMeshComponent(ULandscapeSplineControlPoint* Owner);`
- L209 _public prototype_ `virtual TArray<USplineMeshComponent*> GetForeignMeshComponents(ULandscapeSplineSegment* Owner);`
- L211 _public prototype_ `virtual UObject* GetOwnerForMeshComponent(const UMeshComponent* SplineMeshComponent);`
- L213 _public prototype_ `void AutoFixMeshComponentErrors(UWorld* OtherWorld);`
- L215 _public prototype_ `bool IsUsingEditorMesh(const USplineMeshComponent* SplineMeshComponent) const;`
- L217 _public prototype_ `bool IsUsingLayerInfo(const ULandscapeLayerInfoObject* LayerInfo) const;`
- L220 _public prototype_ `void ForEachControlPoint(TFunctionRef<void(ULandscapeSplineControlPoint*)> Func);` — Iterates throug a copy of the ControlPoints list.
- L227 _public prototype_ `void CopyToSplineComponent(USplineComponent* SplineComponent);` — Converts points along the landscape spline into points on a spline component Works best with landscape splines that contain no intersections or splits @param SplineComponent Spline component to be populated
- L232 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L233 _public prototype_ `virtual void PostLoad() override;`
- L235 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L236 _public prototype_ `virtual void PostEditUndo() override;`
- L238 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L243 _public prototype_ `virtual void CheckForErrors() override;`
- L245 _public prototype_ `virtual void OnRegister() override;`
- L250 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L252 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`

#### Free symbols / members of external scopes

- L41 _function_ `friend bool operator==(const FForeignControlPointData& LHS, const FForeignControlPointData& RHS)`
- L63 _function_ `friend bool operator==(const FForeignSplineSegmentData& LHS, const FForeignSplineSegmentData& RHS)`

### `Source/Runtime/Landscape/Classes/LandscapeStreamingProxy.h` (Public)


#### class `ALandscapeStreamingProxy`  
`class ALandscapeStreamingProxy : public ALandscapeProxy`  
_L20-87_
- reflection: `UCLASS(MinimalAPI, notplaceable)`
- inherits: `ALandscapeProxy`
- L25 _public prototype_ `ALandscapeStreamingProxy(const FObjectInitializer& ObjectInitializer);`
- L30 _public member_ `TLazyObjectPtr<ALandscape> LandscapeActor_DEPRECATED;` — `UPROPERTY()`
- L36 _private member_ `TSoftObjectPtr<ALandscape> LandscapeActorRef;` — `UPROPERTY(EditAnywhere, Category = LandscapeProxy, Meta = (DisplayName = "Landscape Actor"))`
- L39 _private member_ `TSet<FName> OverriddenSharedProperties;` — `UPROPERTY()`
- L44 _private member_ `uint32 DeferredLayerContentUpdateModes = 0;` — `UPROPERTY(Transient, NonTransactional)` — Tracks layer update requests made by this proxy's components when the ALandscape is unreachable. Requests are processed on the next registration once the parent ALandscape is valid
- L50 _public function_ `virtual bool ShouldExport() override`
- L51 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L52 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L53 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L54 _public prototype_ `virtual AActor* GetSceneOutlinerParent() const override;`
- L55 _public prototype_ `virtual bool CanDeleteSelectedActor(FText& OutReason) const override;`
- L56 _public prototype_ `virtual bool GetReferencedContentObjects(TArray<UObject*>& Objects) const override;`
- L57 _public function_ `virtual bool CanChangeIsSpatiallyLoadedFlag() const override`
- L58 _public prototype_ `virtual bool ShouldIncludeGridSizeInName(UWorld* InWorld, const FActorPartitionIdentifier& InIdentifier) const override;`
- L59 _public prototype_ `virtual void GetActorDescProperties(FPropertyPairsMap& PropertyPairsMap) const override;`
- L60 _public prototype_ `virtual void CheckForErrors() override;`
- L65 _public prototype_ `virtual ALandscape* GetLandscapeActor() override;`
- L66 _public prototype_ `virtual const ALandscape* GetLandscapeActor() const override;`
- L67 _public prototype_ `void SetLandscapeActor(ALandscape* InLandscape);`
- L68 _public prototype_ `virtual UMaterialInterface* GetLandscapeMaterial(int8 InLODIndex = INDEX_NONE) const override;`
- L69 _public prototype_ `virtual UMaterialInterface* GetLandscapeHoleMaterial() const override;`
- L73 _public prototype_ `bool IsValidLandscapeActor(ALandscape* Landscape);` — Check input Landscape actor is match for this LandscapeProxy (by GUID)
- L77 _public prototype_ `virtual bool IsSharedPropertyOverridden(const FName& InPropertyName) const override;`
- L78 _public prototype_ `virtual void SetSharedPropertyOverride(const FName& InPropertyName, const bool bIsOverridden, const bool bInExecutePostEditChangeProperty = true) override;`
- L81 _public prototype_ `void RequestDeferredLayerContentUpdateModes(ELandscapeLayerUpdateMode InLayerContentUpdateModes);`
- L82 _public prototype_ `void PerformDeferredLayerContentUpdateModesRequest();`
- L84 _protected prototype_ `virtual void CheckOverriddenSharedProperties() override;`
- L85 _protected prototype_ `virtual void FixupOverriddenSharedProperties() override;`

### `Source/Runtime/Landscape/Classes/LandscapeTextureHash.h` (Public)


#### enum `ELandscapeTextureType`  
`enum class ELandscapeTextureType : uint8`  
_L12-17_
- reflection: `UENUM()`
- L14 _public enumerator_ `Unknown`
- L15 _public enumerator_ `Heightmap`
- L16 _public enumerator_ `Weightmap`

#### enum `ELandscapeTextureUsage`  
`enum class ELandscapeTextureUsage : uint8`  
_L20-25_
- reflection: `UENUM()`
- L22 _public enumerator_ `Unknown`
- L23 _public enumerator_ `EditLayerData` — used as data for an edit layer, input to the layer merge operation
- L24 _public enumerator_ `FinalData` — used for runtime/rendering

#### class `ULandscapeTextureHash`  
`class ULandscapeTextureHash : public UAssetUserData`  
_L28-85_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, Within = Texture2D)`
- inherits: `UAssetUserData`
- L33 _private member_ `FGuid TextureHashGUID;` — `UPROPERTY()`
- L36 _private member_ `FGuid LastSourceID;` — `UPROPERTY()`
- L40 _private member_ `ELandscapeTextureType TextureType = ELandscapeTextureType::Unknown;` — `UPROPERTY()` — heightmap or weightmap.  When unknown, we fallback to using the texture source ID as hash (old behavior)
- L44 _private member_ `ELandscapeTextureUsage TextureUsage = ELandscapeTextureUsage::Unknown;` — `UPROPERTY()` — edit layer data or final data.  When unknown, we fallback to using the texture source ID as hash (old behavior)
- L49 _private member_ `TMap<FGuid, FGuid> RecentlySerializedHashes;` — cache of recently serialized hash values this ensure that if the texture is brought back to match exactly a recently serialized state, it will have exactly the same hash that it was serialized with. This helps us come back to the serialized (presumably cache-friendly) state after no-ops like:  modify + undo, hide layer + unhide layer, etc.
- L55 _public prototype_ `static void SetInitialStateOnPostLoad(UTexture2D* LandscapeTexture, ELandscapeTextureUsage TextureUsage, ELandscapeTextureType TextureType);` — setup initial state on load, if it doesn't yet exist
- L58 _public prototype_ `static void UpdateHash(UTexture2D* LandscapeTexture, ELandscapeTextureUsage TextureUsage = ELandscapeTextureUsage::Unknown, ELandscapeTextureType TextureType = ELandscapeTextureType::Unknown, bool bForceUpdate = false);` — Update the stored hash based on the source data
- L61 _public prototype_ `static void SetHash64(UTexture2D* LandscapeTexture, uint64 NewHash, ELandscapeTextureUsage TextureUsage, ELandscapeTextureType TextureType);` — Explicitly set the hash for the specified LandscapeTexture
- L64 _public prototype_ `static uint64 CalculateTextureHash64(UTexture2D* LandscapeTexture, ELandscapeTextureType TextureType, bool& bOutHashIsValid);` — calculate the texture hash directly from the source mip0 contents
- L65 _public prototype_ `static FGuid CalculateTextureHashGUID(UTexture2D* LandscapeTexture, ELandscapeTextureType TextureType, bool& bOutHashIsValid);`
- L68 _public prototype_ `static uint64 CalculateTextureHash64(const FColor* Mip0Data, int32 PixelCount, ELandscapeTextureType TextureType);` — calculate the texture hash from the Mip0Data buffer
- L71 _public prototype_ `static bool DoesTextureDataChangeExceedThreshold(const FColor* Mip0Data, const FColor* OldMip0Data, int32 PixelCount, ELandscapeTextureType TextureType, uint64 OldHash, uint64 NewHash, TOptional<uint8>& OutChangedWeightmapChannelsMasks);` — check if the Mip0Data is within the change threshold of OldMip0Data
- L74 _public prototype_ `static FGuid GetHash(UTexture2D* LandscapeTexture);` — get the current stored hash for the landscape texture, checking that it is up to date
- L77 _public prototype_ `static void CheckHashIsUpToDate(UTexture2D* LandscapeTexture);` — Check the hash is up to date
- L80 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Interface
- L81 _public function_ `virtual bool IsEditorOnly() const override`
- L82 _public function_ `virtual bool NeedsLoadForClient() const override`
- L83 _public function_ `virtual bool NeedsLoadForServer() const override`

### `Source/Runtime/Landscape/Classes/LandscapeTextureStorageProvider.h` (Public)


#### struct `FLandscapeTexture2DMipMap`  
`struct FLandscapeTexture2DMipMap`  
_L20-37_
- reflection: `USTRUCT()`
- L26 _public member_ `int32 SizeX = 0;` — `UPROPERTY()` — Width of the mip-map.
- L29 _public member_ `int32 SizeY = 0;` — `UPROPERTY()` — Height of the mip-map.
- L32 _public member_ `bool bCompressed = false;` — `UPROPERTY()` — Whether the bulk data is compressed or not
- L34 _public member_ `FByteBulkData BulkData;`
- L36 _public prototype_ `void Serialize(FArchive& Ar, UObject* Owner, uint32 SaveOverrideFlags);`

#### class `FLandscapeTextureStorageMipProvider`  
`class FLandscapeTextureStorageMipProvider : public FTextureMipDataProvider`  
_L39-93_
- inherits: `FTextureMipDataProvider`
- L42 _public prototype_ `FLandscapeTextureStorageMipProvider(ULandscapeTextureStorageProviderFactory* InFactory);`
- L43 _public prototype_ `~FLandscapeTextureStorageMipProvider();`
- L49 _public prototype_ `void Init(const FTextureUpdateContext& Context, const FTextureUpdateSyncOptions& SyncOptions) final override;`
- L50 _public prototype_ `int32 GetMips(const FTextureUpdateContext& Context, int32 StartingMipIndex, const FTextureMipInfoArray& MipInfos, const FTextureUpdateSyncOptions& SyncOptions) final override;`
- L51 _public prototype_ `bool PollMips(const FTextureUpdateSyncOptions& SyncOptions) final override;`
- L52 _public prototype_ `void AbortPollMips() final override;`
- L53 _public prototype_ `void CleanUp(const FTextureUpdateSyncOptions& SyncOptions) final override;`
- L54 _public prototype_ `void Cancel(const FTextureUpdateSyncOptions& SyncOptions) final override;`
- L55 _public prototype_ `ETickThread GetCancelThread() const final override;`
- L59 _private member_ `ULandscapeTextureStorageProviderFactory* Factory = nullptr;` — the Factory (that actually has the mip data)
- L70 _private member_ `TArray<FIORequest, TInlineAllocator<MAX_TEXTURE_MIP_COUNT>> IORequests;` — Pending async requests created in GetMips().
- L73 _private member_ `FTextureMipInfoArray DestMipInfos;` — We make a copy of this, as it is provided in GetMips, and we fill it out in PollMips
- L75 _private member_ `int32 FirstRequestedMipIndex = INDEX_NONE;`
- L78 _private member_ `FName TextureName;` — The asset name, used to log IO errors.
- L80 _private member_ `bool bPrioritizedIORequest = false;` — Whether async read requests must be created with high priority (executes faster).
- L82 _private member_ `bool bIORequestCancelled = false;` — Whether async read requests where cancelled for any reasons.
- L84 _private member_ `bool bIORequestAborted = false;` — Whether async read requests were required to abort through AbortPollMips().
- L87 _private member_ `FBulkDataIORequestCallBack AsyncFileCallBack;` — A callback to be executed once all IO pending requests are completed.
- L90 _private prototype_ `void CreateAsyncFileCallback(const FTextureUpdateSyncOptions& SyncOptions);` — Helper to create the AsyncFileCallBack -- which can handle IO Request completions (and will trigger the next step to be scheduled via SyncOptions.RescheduleCallback())
- L92 _private prototype_ `void ClearIORequests();`

#### struct `FLandscapeTextureStorageMipProvider::FIORequest`  
`struct FIORequest`  
_L62-67_
- desc: A structured with information about which file contains which mips.
- L64 _public member_ `FIoFilenameHash FilenameHash = INVALID_IO_FILENAME_HASH;`
- L65 _public member_ `TUniquePtr<IBulkDataIORequest> BulkDataIORequest;`
- L66 _public member_ `uint8* DestMipData = nullptr;`

#### class `FLandscapeTextureMipEdgeOverrideProvider`  
`class FLandscapeTextureMipEdgeOverrideProvider : public FTextureMipDataProvider`  
_L97-130_
- inherits: `FTextureMipDataProvider`
- L107 _public prototype_ `FLandscapeTextureMipEdgeOverrideProvider(ULandscapeHeightmapTextureEdgeFixup* InEdgeFixup, UTexture2D* InTexture);`
- L108 _public prototype_ `~FLandscapeTextureMipEdgeOverrideProvider();`
- L114 _public prototype_ `void Init(const FTextureUpdateContext& Context, const FTextureUpdateSyncOptions& SyncOptions) final override;`
- L115 _public prototype_ `int32 GetMips(const FTextureUpdateContext& Context, int32 StartingMipIndex, const FTextureMipInfoArray& MipInfos, const FTextureUpdateSyncOptions& SyncOptions) final override;`
- L116 _public prototype_ `bool PollMips(const FTextureUpdateSyncOptions& SyncOptions) final override;`
- L117 _public prototype_ `void CleanUp(const FTextureUpdateSyncOptions& SyncOptions) final override;`
- L118 _public prototype_ `void Cancel(const FTextureUpdateSyncOptions& SyncOptions) final override;`
- L119 _public prototype_ `ETickThread GetCancelThread() const final override;`
- L123 _private member_ `ULandscapeHeightmapTextureEdgeFixup* EdgeFixup = nullptr;` — the Edge Fixup (that actually has the edge override data)
- L126 _private member_ `FTextureMipInfoArray DestMipInfos;` — We make a copy of this, as it is provided in GetMips, and we fill it out in PollMips
- L129 _private member_ `FName TextureName;` — The asset name, used to log IO errors.

#### class `ULandscapeTextureMipEdgeOverrideFactory`  
`class ULandscapeTextureMipEdgeOverrideFactory : public UTextureMipDataProviderFactory`  
_L135-169_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, Within = Texture2D)`
- inherits: `UTextureMipDataProviderFactory`
- desc: serves as a hook into the texture streaming process, allowing us to inject edge data
- L139 _public member_ `TObjectPtr<UTexture2D> Texture;` — should be the same as GetOuter()
- L140 _public member_ `TObjectPtr<ULandscapeHeightmapTextureEdgeFixup> EdgeFixup;` — assigned when the EdgeFixup is Active
- L142 _public prototype_ `static ULandscapeTextureMipEdgeOverrideFactory* AddTo(UTexture2D* TargetTexture);`
- L144 _public prototype_ `void SetupEdgeFixup(ULandscapeHeightmapTextureEdgeFixup* InEdgeFixup);`
- L146 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L147 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L155 _public function_ `virtual FTextureMipDataProvider* AllocateMipDataProvider(UTexture* Asset) override` — Create a FTextureMipDataProvider to handle a single StreamIn mip operation. The object lifetime will be managed by FRenderAssetUpdate. @param InAsset - the texture on which the stream in operation will be performed.
- L165 _public function_ `virtual bool WillProvideMipDataWithoutDisk() const` — Returns true if TextureMipDataProviders allocated by this factory can provide MipData by themselves, even without loading from disk at all, so streaming can be enabled for their textures.

#### class `ULandscapeTextureStorageProviderFactory`  
`class ULandscapeTextureStorageProviderFactory : public UTextureAllMipDataProviderFactory`  
_L173-266_
- reflection: `UCLASS(NotBlueprintable, MinimalAPI, Within = Texture2D)`
- inherits: `UTextureAllMipDataProviderFactory`
- L179 _public member_ `int32 NumNonOptionalMips = 0;`
- L180 _public member_ `int32 NumNonStreamingMips = 0;`
- L181 _public member_ `FVector LandscapeGridScale = FVector(ForceInit);`
- L185 _public member_ `int32 BoundaryOffset = 0;` — `UPROPERTY()` — Tracks the offset of the texture boundaries (defined by number of subsection/multi-components in texture). Each texture has (NumSubsections * NumComponents) - 1 boundaries for each axis
- L189 _public member_ `int32 BoundaryCountX = 0;` — `UPROPERTY()` — Tracks the number of duplicated column boundaries (based on subsection/multi-component texture count)
- L193 _public member_ `int32 BoundaryCountY = 0;` — `UPROPERTY()` — Tracks the number of duplicated row boundaries (based on subsection/multi-component texture count)
- L195 _public member_ `TArray<FLandscapeTexture2DMipMap> Mips;`
- L196 _public member_ `TObjectPtr<UTexture2D> Texture;`
- L200 _public member_ `TObjectPtr<ULandscapeHeightmapTextureEdgeFixup> EdgeFixup;` — Reference to the edge fixup on the Texture, if any.  (This can be null, if edge fixup is disabled) It is set when the Texture's landscape component is registered.
- L203 _public prototype_ `static ULandscapeTextureStorageProviderFactory* ApplyTo(UTexture2D* InTargetTexture, const FVector& InLandsapeGridScale, int32 InHeightmapCompressionMipThreshold, int32 InNumSubsections, int32 InSubsectionSizeQuads);`
- L204 _public prototype_ `void UpdateCompressedDataFromSource(UTexture2D* InTargetTexture, const FVector& InLandsapeGridScale, int32 InHeightmapCompressionMipThreshold, int32 InNumSubsections, int32 InSubsectionSizeQuads);`
- L207 _public prototype_ `void SetupEdgeFixup(ULandscapeHeightmapTextureEdgeFixup* EdgeFixup);`
- L210 _public prototype_ `static void CompressMipToBulkData(int32 MipIndex, int32 MipSizeX, int32 MipSizeY, uint8* SourceData, int32 SourceDataBytes, FByteBulkData& DestBulkData, int32 InMipBoundaryOffset, int32 InBoundaryCountX, int32 InBoundaryCountY);` — compress the mip data.
- L211 _public prototype_ `static void CopyMipToBulkData(int32 MipIndex, int32 MipSizeX, int32 MipSizeY, uint8* SourceData, int32 SourceDataBytes, FByteBulkData& DestBulkData);`
- L214 _public prototype_ `void DecompressMip(uint8* SourceData, int64 SourceDataBytes, uint8* DestData, int64 DestDataBytes, int32 MipIndex);` — decompress the mip data. Currently operates in-place (though this could be changed in the future)
- L215 _public prototype_ `void DecompressMipOriginalUnoptimized(uint8* SourceData, int64 SourceDataBytes, uint8* DestData, int64 DestDataBytes, int32 MipIndex);`
- L217 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L218 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L226 _public function_ `virtual FTextureMipDataProvider* AllocateMipDataProvider(UTexture* Asset) override` — Create a FTextureMipDataProvider to handle a single StreamIn mip operation. The object lifetime will be managed by FRenderAssetUpdate. @param InAsset - the texture on which the stream in operation will be performed.
- L235 _public function_ `virtual bool WillProvideMipDataWithoutDisk() const` — Returns true if TextureMipDataProviders allocated by this factory can provide MipData by themselves, even without loading from disk at all, so streaming can be enabled for their textures.
- L241 _public prototype_ `virtual bool GetInitialMipData(int32 FirstMipToLoad, TArrayView<void*> OutMipData, TArrayView<int64> OutMipSize, FStringView DebugContext) override;` — load mip data (used to access preloaded inline mips for creating the initial version of the texture)
- L244 _public prototype_ `virtual FStreamableRenderResourceState GetResourcePostInitState(const UTexture* Owner, bool bAllowStreaming) override;` — return the initial streaming state of the texture
- L246 _public function_ `bool DoesMipDataExist(int32 MipIndex)`
- L252 _public function_ `const FLandscapeTexture2DMipMap* GetMip(int32 MipIndex)`
- L262 _public function_ `int32 GetTotalBytes() const`

#### Free symbols / members of external scopes

- L264 _function_ `return Algo::TransformAccumulate(Mips, [](const FLandscapeTexture2DMipMap& Mip) -> int32 { return Mip.BulkData.GetBulkDataSize(); }, 0);` (scope `ULandscapeTextureStorageProviderFactory::GetTotalBytes`)

### `Source/Runtime/Landscape/Classes/LandscapeWeightmapUsage.h` (Public)


#### class `ULandscapeWeightmapUsage`  
`class ULandscapeWeightmapUsage : public UObject`  
_L13-74_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable)`
- inherits: `UObject`
- L21 _public member_ `TObjectPtr<ULandscapeComponent> ChannelUsage[NumChannels];` — `UPROPERTY()`
- L24 _public member_ `FGuid LayerGuid;` — `UPROPERTY()`
- L26 _public function_ `int32 FreeChannelCount() const`
- L38 _public function_ `void ClearUsage()`
- L46 _public function_ `void ClearUsage(ULandscapeComponent* Component)`
- L57 _public function_ `bool IsEmpty() const`
- L62 _public function_ `TArray<ULandscapeComponent*, TInlineAllocator<4>> GetUniqueValidComponents() const`

#### enum `ULandscapeWeightmapUsage::(anonymous)`  
`enum`  
_L17-17_

#### Free symbols / members of external scopes

- L17 _enumerator_ `enum { NumChannels = 4 }; public: UPROPERTY() TObjectPtr<ULandscapeComponent> ChannelUsage[NumChannels]; UPROPERTY() FGuid LayerGuid;` (scope `ULandscapeWeightmapUsage::__anonad82f6dc0103`)

### `Source/Runtime/Landscape/Classes/Materials/MaterialExpressionLandscapeGrassOutput.h` (Public)


#### struct `FGrassInput`  
`struct FGrassInput`  
_L17-38_
- reflection: `USTRUCT()`
- L22 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = Grass)`
- L25 _public member_ `TObjectPtr<ULandscapeGrassType> GrassType;` — `UPROPERTY(EditAnywhere, Category = Grass)`
- L28 _public member_ `FExpressionInput Input;` — `UPROPERTY(meta = (RequiredInput = "true"))`
- L30 _public function_ `FGrassInput() : GrassType(nullptr)`
- L34 _public function_ `FGrassInput(FName InName) : Name(InName) , GrassType(nullptr)`

#### class `UMaterialExpressionLandscapeGrassOutput`  
`class UMaterialExpressionLandscapeGrassOutput : public UMaterialExpressionCustomOutput`  
_L41-74_
- reflection: `UCLASS(collapsecategories, hidecategories=Object, MinimalAPI)`
- inherits: `UMaterialExpressionCustomOutput`
- L46 _private member_ `static constexpr int32 MaxGrassTypes = 32;` — Maximum number of supported grass types on a given landscape material. Whenever adjusting this, make sure to update LandscapeGrassWeight.usf accordingly:
- L49 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L50 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L51 _private prototype_ `virtual TArrayView<FExpressionInput*> GetInputsView() override;`
- L52 _private prototype_ `virtual FExpressionInput* GetInput(int32 InputIndex) override;`
- L53 _private prototype_ `virtual FName GetInputName(int32 InputIndex) const override;`
- L54 _private prototype_ `void ValidateInputName(FGrassInput& Input) const;`
- L59 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L62 _private function_ `virtual EMaterialValueType GetInputValueType(int32 InputIndex) override`
- L65 _private function_ `virtual int32 GetNumOutputs() const override`
- L66 _private function_ `virtual int32 GetMaxOutputs() const`
- L67 _private function_ `virtual FString GetFunctionName() const override`
- L70 _private member_ `TArray<FGrassInput> GrassTypes;` — `UPROPERTY(EditAnywhere, Category = UMaterialExpressionLandscapeGrassOutput)`
- L73 _private member_ `static FName PinDefaultName;`

### `Source/Runtime/Landscape/Classes/Materials/MaterialExpressionLandscapeLayerBlend.h` (Public)


#### enum `ELandscapeLayerBlendType`  
`enum ELandscapeLayerBlendType : int`  
_L19-24_
- reflection: `UENUM()`
- L21 _public enumerator_ `LB_WeightBlend`
- L22 _public enumerator_ `LB_AlphaBlend`
- L23 _public enumerator_ `LB_HeightBlend`

#### struct `FLayerBlendInput`  
`struct FLayerBlendInput`  
_L27-61_
- reflection: `USTRUCT()`
- L32 _public member_ `FName LayerName;` — `UPROPERTY(EditAnywhere, Category=LayerBlendInput)`
- L35 _public member_ `TEnumAsByte<ELandscapeLayerBlendType> BlendType;` — `UPROPERTY(EditAnywhere, Category=LayerBlendInput)`
- L38 _public member_ `FExpressionInput LayerInput;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstLayerInput' if not specified"))`
- L41 _public member_ `FExpressionInput HeightInput;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstHeightInput' if not specified"))`
- L44 _public member_ `float PreviewWeight;` — `UPROPERTY(EditAnywhere, Category=LayerBlendInput)`
- L48 _public member_ `FVector ConstLayerInput;` — `UPROPERTY(EditAnywhere, Category = LayerBlendInput)` — only used if LayerInput is not hooked up
- L52 _public member_ `float ConstHeightInput;` — `UPROPERTY(EditAnywhere, Category=LayerBlendInput)` — only used if HeightInput is not hooked up
- L54 _public function_ `FLayerBlendInput() : BlendType(0) , PreviewWeight(0.0f) , ConstLayerInput(0.0f, 0.0f, 0.0f) , ConstHeightInput(0.0f)`

#### class `UMaterialExpressionLandscapeLayerBlend`  
`class UMaterialExpressionLandscapeLayerBlend : public UMaterialExpression`  
_L64-100_
- reflection: `UCLASS(collapsecategories, hidecategories=Object, MinimalAPI)`
- inherits: `UMaterialExpression`
- L69 _private member_ `TArray<FLayerBlendInput> Layers;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerBlend)`
- L72 _private prototype_ `virtual void Serialize(FStructuredArchive::FRecord Record) override;`
- L74 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L78 _private prototype_ `virtual EMaterialValueType GetInputValueType(int32 InputIndex) override;`
- L79 _private function_ `virtual EMaterialValueType GetOutputValueType(int32 InputIndex) override`
- L80 _private prototype_ `virtual bool IsResultMaterialAttributes(int32 OutputIndex) override;`
- L81 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L82 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L83 _private prototype_ `virtual TArrayView<FExpressionInput*> GetInputsView() override;`
- L84 _private prototype_ `virtual FExpressionInput* GetInput(int32 InputIndex) override;`
- L85 _private prototype_ `virtual FName GetInputName(int32 InputIndex) const override;`
- L91 _private prototype_ `virtual void GetLandscapeLayerNames(TArray<FName>& OutLayers) const override;` — Gets the landscape layer names
- L93 _private prototype_ `virtual UObject* GetReferencedTexture() const override;`
- L94 _private prototype_ `virtual ReferencedTextureArray GetReferencedTextures() const override;`
- L95 _private function_ `virtual bool CanReferenceTexture() const override`
- L99 _private prototype_ `int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex, bool bForPreview);`

### `Source/Runtime/Landscape/Classes/Materials/MaterialExpressionLandscapeLayerCoords.h` (Public)


#### enum `ETerrainCoordMappingType`  
`enum ETerrainCoordMappingType : int`  
_L12-19_
- reflection: `UENUM()`
- L14 _public enumerator_ `TCMT_Auto`
- L15 _public enumerator_ `TCMT_XY`
- L16 _public enumerator_ `TCMT_XZ`
- L17 _public enumerator_ `TCMT_YZ`
- L18 _public enumerator_ `TCMT_MAX`

#### enum `ELandscapeCustomizedCoordType`  
`enum ELandscapeCustomizedCoordType : int`  
_L22-32_
- reflection: `UENUM()`
- L25 _public enumerator_ `LCCT_None` — Don't use customized UV, just use original UV.
- L26 _public enumerator_ `LCCT_CustomUV0`
- L27 _public enumerator_ `LCCT_CustomUV1`
- L28 _public enumerator_ `LCCT_CustomUV2`
- L30 _public enumerator_ `LCCT_WeightMapUV` — Use original WeightMapUV, which could not be customized.
- L31 _public enumerator_ `LCCT_MAX`

#### class `UMaterialExpressionLandscapeLayerCoords`  
`class UMaterialExpressionLandscapeLayerCoords : public UMaterialExpression`  
_L35-70_
- reflection: `UCLASS(collapsecategories, hidecategories=Object, MinimalAPI)`
- inherits: `UMaterialExpression`
- L49 _private member_ `float MappingScale;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerCoords)` — Uniform scale to apply to the mapping.
- L53 _private member_ `float MappingRotation;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerCoords)` — Rotation to apply to the mapping.
- L57 _private member_ `float MappingPanU;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerCoords)` — Offset to apply to the mapping along U.
- L61 _private member_ `float MappingPanV;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerCoords)` — Offset to apply to the mapping along V.
- L65 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L66 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`

### `Source/Runtime/Landscape/Classes/Materials/MaterialExpressionLandscapeLayerSample.h` (Public)


#### class `UMaterialExpressionLandscapeLayerSample`  
`class UMaterialExpressionLandscapeLayerSample : public UMaterialExpression`  
_L16-47_
- reflection: `UCLASS(collapsecategories, hidecategories=Object, MinimalAPI)`
- inherits: `UMaterialExpression`
- L21 _private member_ `FName ParameterName;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerWeight)`
- L24 _private member_ `float PreviewWeight;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerWeight)`
- L30 _public function_ `virtual bool CanRenameNode() const override`
- L31 _public prototype_ `virtual FString GetEditableName() const override;`
- L32 _public prototype_ `virtual void SetEditableName(const FString& NewName) override;`
- L33 _public prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L34 _public prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L35 _public prototype_ `virtual bool MatchesSearchQuery(const TCHAR* SearchQuery) override;`
- L41 _public prototype_ `virtual void GetLandscapeLayerNames(TArray<FName>& OutLayers) const override;` — Gets the landscape layer names
- L43 _public prototype_ `virtual UObject* GetReferencedTexture() const override;`
- L44 _public prototype_ `virtual ReferencedTextureArray GetReferencedTextures() const override;`
- L45 _public function_ `virtual bool CanReferenceTexture() const override`

### `Source/Runtime/Landscape/Classes/Materials/MaterialExpressionLandscapeLayerSwitch.h` (Public)


#### class `UMaterialExpressionLandscapeLayerSwitch`  
`class UMaterialExpressionLandscapeLayerSwitch : public UMaterialExpression`  
_L18-71_
- reflection: `UCLASS(collapsecategories, hidecategories=Object, MinimalAPI)`
- inherits: `UMaterialExpression`
- L23 _private member_ `FExpressionInput LayerUsed;` — `UPROPERTY()`
- L26 _private member_ `FExpressionInput LayerNotUsed;` — `UPROPERTY()`
- L29 _private member_ `FName ParameterName;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerSwitch)`
- L32 _private member_ `uint32 PreviewUsed:1;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerSwitch)`
- L37 _public prototype_ `virtual void Serialize(FStructuredArchive::FRecord Record) override;`
- L42 _public prototype_ `virtual bool IsResultMaterialAttributes(int32 OutputIndex) override;`
- L43 _public prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L44 _public function_ `virtual bool CanRenameNode() const override`
- L45 _public prototype_ `virtual FString GetEditableName() const override;`
- L46 _public prototype_ `virtual void SetEditableName(const FString& NewName) override;`
- L47 _public prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L48 _public prototype_ `virtual bool MatchesSearchQuery(const TCHAR* SearchQuery) override;`
- L50 _public prototype_ `virtual UObject* GetReferencedTexture() const override;`
- L51 _public prototype_ `virtual ReferencedTextureArray GetReferencedTextures() const override;`
- L52 _public function_ `virtual bool CanReferenceTexture() const override`
- L54 _public function_ `virtual EMaterialValueType GetInputValueType(int32 InputIndex) override`
- L55 _public function_ `virtual EMaterialValueType GetOutputValueType(int32 InputIndex) override`
- L60 _public prototype_ `virtual void GetLandscapeLayerNames(TArray<FName>& OutLayers) const override;` — Gets the landscape layer names
- L69 _public prototype_ `virtual void PostLoad() override;` — Do any object-specific cleanup required immediately after loading an object, and immediately after any undo/redo.

### `Source/Runtime/Landscape/Classes/Materials/MaterialExpressionLandscapeLayerWeight.h` (Public)


#### class `UMaterialExpressionLandscapeLayerWeight`  
`class UMaterialExpressionLandscapeLayerWeight : public UMaterialExpression`  
_L18-70_
- reflection: `UCLASS(collapsecategories, hidecategories=Object, MinimalAPI)`
- inherits: `UMaterialExpression`
- L23 _private member_ `FExpressionInput Base;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Defaults to 'ConstBase' if not specified"))`
- L26 _private member_ `FExpressionInput Layer;` — `UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Ignored if not specified"))`
- L29 _private member_ `FName ParameterName;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerWeight)`
- L32 _private member_ `float PreviewWeight;` — `UPROPERTY(EditAnywhere, Category=MaterialExpressionLandscapeLayerWeight)`
- L36 _private member_ `FVector ConstBase;` — `UPROPERTY(EditAnywhere, Category = MaterialExpressionLandscapeLayerWeight, meta = (OverridingInputProperty = "Base"))` — only used if Base is not hooked up
- L42 _public prototype_ `virtual bool IsResultMaterialAttributes(int32 OutputIndex) override;`
- L43 _public prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L44 _public function_ `virtual bool CanRenameNode() const override`
- L45 _public prototype_ `virtual FString GetEditableName() const override;`
- L46 _public prototype_ `virtual void SetEditableName(const FString& NewName) override;`
- L47 _public prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L48 _public prototype_ `virtual bool MatchesSearchQuery(const TCHAR* SearchQuery) override;`
- L50 _public prototype_ `virtual UObject* GetReferencedTexture() const override;`
- L51 _public prototype_ `virtual ReferencedTextureArray GetReferencedTextures() const override;`
- L52 _public function_ `virtual bool CanReferenceTexture() const override`
- L54 _public function_ `virtual EMaterialValueType GetInputValueType(int32 InputIndex) override`
- L59 _public prototype_ `virtual void GetLandscapeLayerNames(TArray<FName>& OutLayers) const override;` — Gets the landscape layer names
- L68 _public prototype_ `virtual void PostLoad() override;` — Do any object-specific cleanup required immediately after loading an object, and immediately after any undo/redo.

### `Source/Runtime/Landscape/Classes/Materials/MaterialExpressionLandscapePhysicalMaterialOutput.h` (Public)


#### struct `FPhysicalMaterialInput`  
`struct FPhysicalMaterialInput`  
_L12-25_
- reflection: `USTRUCT()`
- desc: Structure linking a material expression input with a physical material. For use by UMaterialExpressionLandscapePhysicalMaterialOutput.
- L17 _public member_ `TObjectPtr<class UPhysicalMaterial> PhysicalMaterial;` — `UPROPERTY(EditAnywhere, Category = PhysicalMaterial)`
- L20 _public member_ `FExpressionInput Input;` — `UPROPERTY(meta = (RequiredInput = "true"))`
- L22 _public function_ `FPhysicalMaterialInput() : PhysicalMaterial(nullptr)`

#### class `UMaterialExpressionLandscapePhysicalMaterialOutput`  
`class UMaterialExpressionLandscapePhysicalMaterialOutput : public UMaterialExpressionCustomOutput`  
_L33-65_
- reflection: `UCLASS(collapsecategories, hidecategories=Object, MinimalAPI)`
- inherits: `UMaterialExpressionCustomOutput`
- desc: Custom output node to write out physical material weights. This can be used to generate the dominant physical material for each point on a landscape. Note that the use of a material output node to generate this information is optional and when a node of this type is not present we fall back on a CPU path which analyzes landscape layer data.
- L38 _private member_ `static constexpr int32 MaxPhysicalMaterials = 16;` — Maximum number of supported grass types on a given landscape material. Whenever adjusting this, make sure to update LandscapeGrassWeight.usf accordingly:
- L42 _private member_ `TArray< FPhysicalMaterialInput > Inputs;` — `UPROPERTY(EditAnywhere, Category = PhysicalMaterial)` — Array of physical material inputs.
- L46 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L50 _private prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L51 _private prototype_ `virtual TArrayView<FExpressionInput*> GetInputsView() override;`
- L52 _private prototype_ `virtual FExpressionInput* GetInput(int32 InputIndex) override;`
- L53 _private prototype_ `virtual FName GetInputName(int32 InputIndex) const override;`
- L54 _private function_ `virtual EMaterialValueType GetInputValueType(int32 InputIndex) override`
- L55 _private prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L61 _private function_ `virtual int32 GetNumOutputs() const override`
- L62 _private function_ `virtual int32 GetMaxOutputs() const`
- L63 _private function_ `virtual FString GetFunctionName() const override`

### `Source/Runtime/Landscape/Classes/Materials/MaterialExpressionLandscapeVisibilityMask.h` (Public)


#### class `UMaterialExpressionLandscapeVisibilityMask`  
`class UMaterialExpressionLandscapeVisibilityMask : public UMaterialExpression`  
_L16-39_
- reflection: `UCLASS(collapseCategories, hideCategories=Object, MinimalAPI)`
- inherits: `UMaterialExpression`
- L22 _public member_ `static FName ParameterName;`
- L26 _public prototype_ `virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;`
- L27 _public prototype_ `virtual void GetCaption(TArray<FString>& OutCaptions) const override;`
- L33 _public prototype_ `virtual void GetLandscapeLayerNames(TArray<FName>& OutLayers) const override;` — Gets the landscape layer names
- L35 _public prototype_ `virtual UObject* GetReferencedTexture() const override;`
- L36 _public prototype_ `virtual ReferencedTextureArray GetReferencedTextures() const override;`
- L37 _public function_ `virtual bool CanReferenceTexture() const override`

### `Source/Runtime/Landscape/Internal/LandscapeGrassWeightExporter.h` (Internal)


#### enum `UE::Landscape::Grass::EGrassWeightExporterFlags`  
`enum class EGrassWeightExporterFlags`  
_L29-37_
- L31 _public enumerator_ `None = 0`
- L32 _public enumerator_ `NeedsGrassmap = (1 << 0)`
- L33 _public enumerator_ `NeedsHeightmap = (1 << 1)`
- L34 _public enumerator_ `RenderImmediately = (1 << 2)`
- L35 _public enumerator_ `ReadbackToCPU = (1 << 3)`
- L36 _public enumerator_ `Default = NeedsGrassmap | NeedsHeightmap | RenderImmediately | ReadbackToCPU`

#### class `FLandscapeGrassWeightExporter_RenderThread_FixLayout`  
`class FLandscapeGrassWeightExporter_RenderThread_FixLayout`  
_L45-49_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L48 _public prototype_ `virtual ~FLandscapeGrassWeightExporter_RenderThread_FixLayout() = default;`

#### class `FLandscapeGrassWeightExporter_RenderThread`  
`class FLandscapeGrassWeightExporter_RenderThread : public FLandscapeGrassWeightExporter_RenderThread_FixLayout`  
_L52-172_
- inherits: `FLandscapeGrassWeightExporter_RenderThread_FixLayout`
- desc: data also accessible by render thread
- L59 _private prototype_ `FLandscapeGrassWeightExporter_RenderThread(int32 InComponentSizeVerts, int32 InSubsectionSizeQuads, int32 InNumSubsections, TConstArrayView<int32> InHeightMips, UE::Landscape::Grass::EGrassWeightExporterFlags InFlags);`
- L63 _public prototype_ `virtual ~FLandscapeGrassWeightExporter_RenderThread();`
- L65 _public function_ `const FIntPoint& GetTargetSize() const`
- L67 _public function_ `int32 GetTileSize() const`
- L75 _public prototype_ `void RenderLandscapeComponentToTexture_RenderThread(FRDGBuilder& GraphBuilder, FRDGTextureRef OutputTexture);` — Renders the components to the given texture.
- L91 _public prototype_ `TValueOrError<FIntRect , EHeightmapTextureInfoError> GetTextureInfoForHeight(const FIntPoint& InComponentKey, int32 InMipIndex = INDEX_NONE);` — Return the location of the height data for the requested component / mip in the output texture @param InComponentKey Key of the component being requested @param InMipIndex Requested mip index. If < 0, will return mip 0. Otherwise, the mip needs to have been requested in HeightMips @return If the component / mip data is found, FIntRect contains the pixels containing the requested height data in the generated texture (channels R and G). Returns an error otherwise.
- L107 _public prototype_ `TValueOrError<TPair<FIntRect , uint8 >, EGrassmapTextureInfoError> GetTextureInfoForGrass(const FIntPoint& InComponentKey, const FName& InGrassName);` — Return the location of the grass data for the requested component in the output texture @param InComponentKey Key of the component being requested @param InGrassName Name of the grass map being requested @return If the component / grass data is found, a FIntRect that contains the pixels containing the requested grass data in the generated texture, along with the channel index. Returns an error otherwise.
- L111 _private prototype_ `void RenderLandscapeComponentToTexture_RenderThread(FRHICommandListImmediate& RHICmdList, FLandscapeAsyncTextureReadback* AsyncReadbackPtr);` — Creates a texture and renders the component to it, and then and triggers a readback of the texture.
- L156 _private member_ `int32 ComponentSizeVerts = 0;`
- L157 _private member_ `int32 SubsectionSizeQuads = 0;`
- L158 _private member_ `int32 NumSubsections = 0;`
- L159 _private member_ `FSceneInterface* SceneInterface = nullptr;`
- L160 _private member_ `TArray<FComponentInfo, TInlineAllocator<1>> ComponentInfos;`
- L161 _private member_ `FIntPoint TargetSize = FIntPoint(ForceInit);`
- L162 _private member_ `TArray<int32> HeightMips;`
- L163 _private member_ `float PassOffsetX = 0.0f;`
- L164 _private member_ `FVector ViewOrigin = FVector(ForceInit);`
- L165 _private member_ `UE::Landscape::Grass::EGrassWeightExporterFlags Flags = UE::Landscape::Grass::EGrassWeightExporterFlags::None;`
- L168 _private member_ `FLandscapeAsyncTextureReadback* GameThreadAsyncReadbackPtr = nullptr;` — game thread synchronous, do not access directly from render thread
- L170 _private member_ `FMatrix ViewRotationMatrix = FMatrix::Identity;`
- L171 _private member_ `FMatrix ProjectionMatrix = FMatrix::Identity;`

#### enum `FLandscapeGrassWeightExporter_RenderThread::EHeightmapTextureInfoError`  
`enum class EHeightmapTextureInfoError`  
_L77-82_
- L79 _public enumerator_ `InvalidComponentKey`
- L80 _public enumerator_ `InvalidFlags`
- L81 _public enumerator_ `InvalidMipIndex`

#### enum `FLandscapeGrassWeightExporter_RenderThread::EGrassmapTextureInfoError`  
`enum class EGrassmapTextureInfoError`  
_L93-98_
- L95 _public enumerator_ `InvalidComponentKey`
- L96 _public enumerator_ `InvalidFlags`
- L97 _public enumerator_ `InvalidGrassName`

#### struct `FLandscapeGrassWeightExporter_RenderThread::FComponentInfo`  
`struct FComponentInfo`  
_L114-154_
- L116 _public prototype_ `FComponentInfo(ULandscapeComponent* InComponent, UE::Landscape::Grass::EGrassWeightExporterFlags InFlags, TConstArrayView<FName> InRequestedGrassNames, TConstArrayView<int32> InRequestedHeightMips);`
- L119 _public function_ `int32 GetNumPasses() const`
- L124 _public function_ `bool HasMipHeightData() const`
- L146 _public member_ `FIntPoint ComponentKey = FIntPoint(MAX_int32, MAX_int32);` — Identifier for this component (use its key because it's a render-thread object so we don't want to access TObjectPtr there)
- L147 _public member_ `TMap<FName, FPassChannelIndex> PerGrassNamePassChannelIndices;`
- L148 _public member_ `TArray<FIntVector4> PerPassPerChannelGrassWeightIndices;`
- L149 _public member_ `FVector2D ViewOffset = FVector2D::ZeroVector;`
- L150 _public member_ `int32 PixelOffsetX = 0;`
- L151 _public member_ `FLandscapeComponentSceneProxy* SceneProxy = nullptr;`
- L152 _public member_ `int32 FirstHeightMipsPassIndex = MAX_int32;`
- L153 _public member_ `UE::Landscape::Grass::EGrassWeightExporterFlags Flags = UE::Landscape::Grass::EGrassWeightExporterFlags::None;`

#### struct `FLandscapeGrassWeightExporter_RenderThread::FComponentInfo::FPassChannelIndex`  
`struct FPassChannelIndex`  
_L129-143_
- L131 _public member_ `int32 PassIndex = INDEX_NONE;`
- L132 _public member_ `int32 ChannelIndex = INDEX_NONE;`
- L134 _public function_ `bool operator == (const FPassChannelIndex& InOther) const`
- L139 _public function_ `bool IsValidChannelIndex() const`

#### class `FLandscapeGrassWeightExporter`  
`class FLandscapeGrassWeightExporter : public FLandscapeGrassWeightExporter_RenderThread`  
_L177-224_
- inherits: `FLandscapeGrassWeightExporter_RenderThread`
- L183 _public prototype_ `FLandscapeGrassWeightExporter(ALandscapeProxy* InLandscapeProxy, TArrayView<ULandscapeComponent* const> InLandscapeComponents, bool bInNeedsGrassmap = true, bool bInNeedsHeightmap = true, const TArray<int32>& InHeightMips = {}, bool bInRenderImmediately = true, bool bInReadbackToCPU = true);` — `UE_DEPRECATED(5.8, "Use the new constructor with explicit flags and explicit grass names")`
- L192 _public prototype_ `FLandscapeGrassWeightExporter(ALandscape* InLandscape, TArrayView<ULandscapeComponent* const> InRequestedComponents, UE::Landscape::Grass::EGrassWeightExporterFlags InFlags, TConstArrayView<FName> InRequestedGrassNames = {}, TConstArrayView<int32> InRequestedHeightMips = {});` — @param InLandscape - Parent landscape. All requested component must share the same parent landscape @param InRequestedComponents - List of components for which to export weight (/height) maps @param InFlags - Flags for specializing what to export and how to read back the results @param InRequestedGrassNames - (Optional) List of grass map names requested for readback. If empty, all grass maps are exported @param InRequestedHeightMips - (Optional) List of mip levels requested for reading back heightmaps
- L199 _public prototype_ `bool CheckAndUpdateAsyncReadback(bool& bOutRenderCommandsQueued, const bool bInForceFinish = false);` — If using the async readback path, check its status and update if needed. Return true when the AsyncReadbackResults are available. You must call this periodically, or the async readback may not complete. bInForceFinish will force the RenderThread to wait until GPU completes the readback, ensuring the readback is completed after the render thread executes the command. NOTE: you may still see false returned, this just means the render thread hasn't executed the command yet.
- L202 _public prototype_ `bool IsAsyncReadbackComplete();` — return true if the async readback is complete.  (Does not update the readback state)
- L207 _public prototype_ `TMap<ULandscapeComponent*, TUniquePtr<FLandscapeComponentGrassData>, TInlineSetAllocator<1>> FetchResults(bool bFreeAsyncReadback);` — Fetches the results from the GPU texture and translates them into FLandscapeComponentGrassDatas. If using async readback, requires AsyncReadback to be complete before calling this. bFreeAsyncReadback if true will call FreeAsyncReadback() to free the readback resource (otherwise you must do it manually)
- L210 _private prototype_ `void FreeAsyncReadback();`
- L213 _private prototype_ `static void ApplyResults(TMap<ULandscapeComponent*, TUniquePtr<FLandscapeComponentGrassData>, TInlineSetAllocator<1>>& Results);` — Applies the results using pre-fetched data.
- L217 _private prototype_ `void ApplyResults();` — Fetches the results and applies them to the landscape components If using async readback, requires AsyncReadback to be complete before calling this.
- L219 _private prototype_ `void CancelAndSelfDestruct();`
- L222 _private member_ `TObjectPtr<ALandscape> Landscape;`
- L223 _private member_ `TArray<TObjectPtr<ULandscapeGrassType>> GrassTypes;`

#### Free symbols / members of external scopes

- L17 _typedef_ `using FRDGTextureRef = FRDGTexture*;`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Landscape` (scope `UE`)
- L22 _prototype_ `bool CanRenderGrassMap(ULandscapeComponent* Component);` (scope `UE::Landscape`) — `UE_DEPRECATED(5.8, "Use ULandscapeComponent::CanRenderGrassMap instead")`
- L24 _prototype_ `bool IsRuntimeGrassMapGenerationSupported();` (scope `UE::Landscape`) — `UE_DEPRECATED(5.8, "Renamed to SupportsRuntimeGrassMapGeneration (LandscapeUtils.h)")`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Landscape` (scope `UE`)
- L27 _namespace_ `namespace Grass` (scope `UE::Landscape`)
- L38 _prototype_ `ENUM_CLASS_FLAGS(EGrassWeightExporterFlags);` (scope `UE::Landscape::Grass`)

### `Source/Runtime/Landscape/Private/LandscapeAsyncTextureReadback.h` (Private)


#### class `FLandscapeAsyncTextureReadback`  
`class FLandscapeAsyncTextureReadback`  
_L12-90_
- desc: Class that performs an async GPU texture readback for landscape purposes. Only supports BGRA8 texture format, and returns the results as an array of FColors.
- L16 _private member_ `std::atomic_int PendingRenderThreadCommands = 0;` — game thread / render thread shared state
- L17 _private member_ `std::atomic_bool bCancel = false;` — set by game thread to signal cancel readback: we don't need to produce valid results
- L20 _private member_ `std::atomic_bool bStartedOnRenderThread = false;` — render thread state
- L21 _private member_ `std::atomic_bool bFinishedOnRenderThread = false;` — render thread finish command has made the data available to game thread
- L23 _private member_ `TUniquePtr<FRHIGPUTextureReadback> AsyncReadback;` — render thread managed async readback structure
- L26 _private member_ `int32 TextureWidth = 0;` — results - readable by game thread when bFinishedOnRenderThread
- L27 _private member_ `int32 TextureHeight = 0;`
- L28 _private member_ `TArray<FColor> ReadbackResults;`
- L32 _public function_ `FLandscapeAsyncTextureReadback()` — construct on the game thread
- L35 _public function_ `~FLandscapeAsyncTextureReadback()` — destruct on the render thread.  From game thread, call QueueDeletion() instead
- L41 _public prototype_ `void StartReadback_RenderThread(FRDGBuilder& GraphBuilder, FRDGTextureRef RDGTexture);` — use this to start an async readback operation from the render thread (on a render graph texture)
- L45 _public prototype_ `void CheckAndUpdate_RenderThread(const bool bInForceFinish);` — checks if the operation is ready to finish, and if it is, calls FinishReadback_RenderThread() to complete the readback. bInForceFinish will force the readback to finish by stalling the render thread until it is ready
- L49 _public prototype_ `void FinishReadback_RenderThread();` — use this to finish an async readback operation from the render thread Calling this when !IsComplete() will cause a stall until the GPU has completed the readback
- L57 _public prototype_ `bool CheckAndUpdate(bool& bOutRenderCommandQueued, const bool bInForceFinish);` — Non-blocking call from the game thread to check readback status and start the finish command if needed. Returns true when the AsyncReadbackResults are available to the game thread, at which point you can call TakeResults() to access them. bOutRenderCommandQueued is set to true if any render command was queued in this call, othwerwise unchanged. You must call this function occasionally or the readback will never complete, as the finish command is required. bInForceFinish will force the finish process to be queued on the render thread (potentially stalling render thread, but forcing it to finish the readback) bInForceFinish DOES NOT generally make the results immediately available, but it will ensure they are available after the render thread executes the command.
- L60 _public prototype_ `void CancelAndSelfDestruct();` — Call from game thread to terminate any readback in flight and queue deletion of this (FLandscapeAsyncTextureReadback) on the render thread
- L63 _public function_ `bool IsComplete()` — Returns true when async readback results are available.  Call TakeResults() to retrieve them.
- L70 _public function_ `TArray<FColor> TakeResults(FIntPoint* OutSize)` — Retrieve the async readback results.  Requires readback to be complete. This function returns its internal memory buffer, relinquishing control over it, so this function can only be called once.
- L80 _public function_ `FString ToString()`
- L89 _public prototype_ `void QueueDeletionFromGameThread();` — once complete, call this to queue deletion of the readback object on the render thread (this must be deleted on the render thread to avoid other render-thread queued commands from accessing a deallocated pointer)

### `Source/Runtime/Landscape/Private/LandscapeCulling.h` (Private)


#### struct `UE::Landscape::Culling::FArguments`  
`struct FArguments`  
_L30-36_
- L32 _public member_ `FRHIBuffer* IndirectArgsBuffer;`
- L33 _public member_ `FRHIBuffer* TileDataVertexBuffer;`
- L34 _public member_ `uint32 IndirectArgsOffset;`
- L35 _public member_ `uint32 TileDataOffset;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ERHIFeatureLevel`
- L26 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Landscape` (scope `UE`)
- L28 _namespace_ `namespace Culling` (scope `UE::Landscape`)
- L38 _prototype_ `bool UseCulling(EShaderPlatform ShaderPlatform);` (scope `UE::Landscape::Culling`)
- L40 _prototype_ `FVertexFactoryType* GetTileVertexFactoryType();` (scope `UE::Landscape::Culling`)
- L42 _prototype_ `void SetupMeshBatch(const FLandscapeSharedBuffers& SharedBuffers, FMeshBatch& MeshBatch);` (scope `UE::Landscape::Culling`)
- L43 _prototype_ `void RegisterLandscape(FRHICommandListBase& RHICmdList, FLandscapeSharedBuffers& SharedBuffers, ERHIFeatureLevel::Type FeatureLevel, uint32 LandscapeKey, int32 SubsectionSizeVerts, int32 NumSubsections);` (scope `UE::Landscape::Culling`)
- L44 _prototype_ `void UnregisterLandscape(uint32 LandscapeKey);` (scope `UE::Landscape::Culling`)
- L46 _prototype_ `void PreRenderViewFamily(FSceneViewFamily& InViewFamily);` (scope `UE::Landscape::Culling`)
- L47 _prototype_ `void InitMainViews(FRDGBuilder& GraphBuilder, TArrayView<const FSceneView*> Views);` (scope `UE::Landscape::Culling`)
- L48 _prototype_ `void InitShadowViews(FRDGBuilder& GraphBuilder, TArrayView<const FSceneView*> ShadowDepthViews, TArrayView<FViewMatrices> ShadowViewMatrices);` (scope `UE::Landscape::Culling`)
- L49 _prototype_ `bool GetViewArguments(const FSceneView& View, uint32 LandscapeKey, FIntPoint SectionBase, int32 LODIndex, FArguments& Args);` (scope `UE::Landscape::Culling`)

### `Source/Runtime/Landscape/Private/LandscapeEditLayerRendererPrivate.h` (Private)


#### class `ULandscapeDefaultEditLayerRenderer`  
`class ULandscapeDefaultEditLayerRenderer : public UObject #if CPP && WITH_EDITOR , public ILandscapeEditLayerRenderer #endif`  
_L20-39_
- reflection: `UCLASS()`
- inherits: `UObject,ILandscapeEditLayerRenderer`
- desc: Edit layer renderer added at the bottom of the stack to provide the default value for every requested target layer (heightmaps and weightmaps) It could have been handled with a simple clear as the first operation when performing the merge, but doing it through a renderer turns out to be an elegant way to resolve the situation where the first actual edit layer's render item declares dependencies between each component and others (e.g. say you have only a ULandscapeHeightmapNormalsEditLayerRenderer in the renderer stack, which requires each component's immediate neighbors). In such a situation, the component dependencies would be skipped because dependencies are between a renderer and its previous one in the stack and since in the case described above (a single renderer in the stack), there's no previous renderer, then the dependencies would simply not be registered, and the render batches would end up being incorrect as a result.
- L30 _public prototype_ `virtual void GetRendererStateInfo(const UE::Landscape::EditLayers::FMergeContext* InMergeContext, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutSupportedTargetTypeState, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutEnabledTargetTypeState, TArray<UE::Landscape::EditLayers::FTargetLayerGroup>& OutTargetLayerGroups) const override;`
- L33 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRenderItem> GetRenderItems(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L34 _public prototype_ `virtual FString GetEditLayerRendererDebugName() const override;`
- L35 _public function_ `virtual UE::Landscape::EditLayers::ERenderFlags GetRenderFlags(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override`
- L36 _public prototype_ `virtual bool RenderLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override;`

#### class `ULandscapeHeightmapNormalsEditLayerRenderer`  
`class ULandscapeHeightmapNormalsEditLayerRenderer : public UObject #if CPP && WITH_EDITOR , public ILandscapeEditLayerRenderer #endif`  
_L47-66_
- reflection: `UCLASS()`
- inherits: `UObject,ILandscapeEditLayerRenderer`
- desc: Edit layer renderer added at the top of the stack to generate the normals, right before resolving the textures. For now, the rendered components require (up to) their 8 immediate neighbors to generate adequate normals on the border so the renderer inserts that strong dependency, so that the components that are needed in the batch are guaranteed to have their neighbors present in the same batch :
- L57 _public prototype_ `virtual void GetRendererStateInfo(const UE::Landscape::EditLayers::FMergeContext* InMergeContext, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutSupportedTargetTypeState, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutEnabledTargetTypeState, TArray<UE::Landscape::EditLayers::FTargetLayerGroup>& OutTargetLayerGroups) const override;`
- L60 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRenderItem> GetRenderItems(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L61 _public prototype_ `virtual FString GetEditLayerRendererDebugName() const override;`
- L62 _public function_ `virtual UE::Landscape::EditLayers::ERenderFlags GetRenderFlags(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override`
- L63 _public prototype_ `virtual bool RenderLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override;`

#### class `ULandscapeWeightmapWeightBlendedLayersRenderer`  
`class ULandscapeWeightmapWeightBlendedLayersRenderer : public UObject #if CPP && WITH_EDITOR , public ILandscapeEditLayerRenderer #endif`  
_L72-93_
- reflection: `UCLASS()`
- inherits: `UObject,ILandscapeEditLayerRenderer`
- desc: Edit layer renderer inserted at the end of the edit layers stack merge to normalize the weights of the rendered weightmaps
- L82 _public prototype_ `virtual void GetRendererStateInfo(const UE::Landscape::EditLayers::FMergeContext* InMergeContext, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutSupportedTargetTypeState, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutEnabledTargetTypeState, TArray<UE::Landscape::EditLayers::FTargetLayerGroup>& OutTargetLayerGroups) const override;`
- L85 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRenderItem> GetRenderItems(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L86 _public prototype_ `virtual FString GetEditLayerRendererDebugName() const override;`
- L87 _public function_ `virtual UE::Landscape::EditLayers::ERenderFlags GetRenderFlags(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override`
- L88 _public prototype_ `virtual bool RenderLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override;`
- L91 _public prototype_ `TBitArray<> GatherWeightBlendedWeightmapLayerBitIndices(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const;`

### `Source/Runtime/Landscape/Private/LandscapeEditReadback.h` (Private)


#### class `FLandscapeEditLayerReadback`  
`class FLandscapeEditLayerReadback`  
_L16-79_
- desc: Read back queue for a landscape edit layer texture. This handles reading landscape edit data back from the GPU to the game thread. Multiple read backs can be queued in a single object and any completed results can be retrieved. Tick() must be called regularly to update the internal read back tasks. When results are available GetCompletedResultNum() will be greater than zero. After getting latest results with GetResult()/GetResultContext() you should call ReleaseCompletedResults() to prevent leaks.
- L19 _public prototype_ `FLandscapeEditLayerReadback();`
- L20 _public prototype_ `~FLandscapeEditLayerReadback();`
- L23 _public prototype_ `bool SetHash(uint64 InHash);` — Update the stored hash value. Return true if this changes the value.
- L25 _public function_ `uint64 GetHash() const` — Get the stored hash value.
- L27 _public typedef_ `using FPerChannelLayerNames = TStaticArray<FName, 4>;`
- L40 _public typedef_ `using FReadbackContext = TArray<FComponentReadbackContext>;` — Full context for processing read back results.
- L43 _public prototype_ `void Enqueue(UTexture2D const* InSourceTexture, FReadbackContext&& InReadbackContext);` — Queue a new texture to read back. The GPU copy will be queued to the render thread inside this function.
- L46 _public prototype_ `void Tick();` — Tick the read back tasks.
- L48 _public prototype_ `void Flush();` — Flush all read back tasks to completion. This may stall waiting for the render thread.
- L51 _public prototype_ `int32 GetCompletedResultNum() const;` — Returns a value greater than 0 if there are completed read back tasks for which we can retrieve results.
- L54 _public prototype_ `TArray< TArray<FColor> > const& GetResult(int32 InResultIndex) const;` — Get the result for the completed task index. Returned reference will be valid until we next call ReleaseCompletedResults().
- L56 _public prototype_ `FReadbackContext const& GetResultContext(int32 InResultIndex) const;` — Get the result context for the completed task index. Returned reference will be valid until we next call ReleaseCompletedResults().
- L59 _public prototype_ `void ReleaseCompletedResults(int32 InResultNum);` — Release results. Pass in a value which is no more than the value returned by GetCompletedResultNum().
- L61 _public function_ `bool HasActiveTasks() const`
- L67 _public prototype_ `static bool HasAnyGlobalWork();` — Returns true if there are any queued tasks that haven't been released for any readback object.
- L70 _public prototype_ `static void GarbageCollectTasks();` — Optional call to allow garbage collection of any task resources and check for leaks. Call once per frame.
- L74 _public prototype_ `static void FlushAllReadbackTasks();` — Brute-force flush of all pending readback tasks. Use this when you want to make sure all readbacks are performed. In case of multiple readbacks, this is much more efficient than individually flushing each task.
- L77 _private member_ `uint64 Hash = 0;`
- L78 _private member_ `TArray<int32> TaskHandles;`

#### struct `FLandscapeEditLayerReadback::FComponentReadbackContext`  
`struct FComponentReadbackContext`  
_L30-38_
- desc: Per component context required for processing read back results.
- L33 _public member_ `FIntPoint ComponentKey;` — Component identifier key.
- L35 _public member_ `int32 UpdateModes = 0;` — Component ELandscapeLayerUpdateMode flags.
- L37 _public member_ `FPerChannelLayerNames PerChannelLayerNames;` — For weightmaps only : configuration of the channels for this component and texture when the readback was performed (useful in case the channel configuration changed before we could perform the readback)

### `Source/Runtime/Landscape/Private/LandscapeGrassMapsBuilder.h` (Private)


#### class `FAsyncFetchTask`  
`class FAsyncFetchTask : public FNonAbandonableTask`  
_L20-38_
- inherits: `FNonAbandonableTask`
- L24 _public member_ `TNonNullPtr< FLandscapeGrassWeightExporter> ActiveRender;` — non-owned pointer. The lifetime is managed externally and must guarantee this pointer is valid while the task is in flight
- L25 _public member_ `TMap<ULandscapeComponent*, TUniquePtr<FLandscapeComponentGrassData>, TInlineSetAllocator<1>> Results;`
- L27 _public function_ `FAsyncFetchTask(FLandscapeGrassWeightExporter* ActiveRender) : ActiveRender(ActiveRender)`
- L32 _public prototype_ `void DoWork();`
- L34 _public function_ `FORCEINLINE TStatId GetStatId() const`

#### class `FLandscapeGrassMapsBuilder`  
`class FLandscapeGrassMapsBuilder`  
_L43-301_
- desc: Helper class used to Build or monitor outdated Grass maps of a world
- L46 _public prototype_ `FLandscapeGrassMapsBuilder(UWorld* InWorld, FLandscapeTextureStreamingManager& InTextureStreamingManager);`
- L47 _public prototype_ `~FLandscapeGrassMapsBuilder();`
- L51 _public prototype_ `void Build(UE::Landscape::EBuildFlags InBuildFlags);` — Synchronously build all grass maps on all proxies in the world
- L54 _public prototype_ `int32 GetOutdatedGrassMapCount(bool bInForceUpdate = true) const;` — Return the number of landscape components in the world that have grass map data that is not up to date (NOT including components missing grass map data altogether)
- L58 _public prototype_ `int32 CountOutdatedGrassMaps(const TArray<TObjectPtr<ULandscapeComponent>>& LandscapeComponents) const;` — count components that have valid data but whose generation hash does not match
- L61 _public prototype_ `void RegisterComponent(ULandscapeComponent* Component);` — called when components are registered to the world
- L63 _public prototype_ `void UnregisterComponent(const ULandscapeComponent* Component);` — called when components are unregistered from the world.
- L66 _public function_ `int32 GetTotalGrassMapsWaitingToRender() const` — get the number of grass maps that are still waiting to render, as of the last AmortizedUpdateGrassMaps()
- L72 _public prototype_ `void AmortizedUpdateGrassMaps(const TArray<FVector>& Cameras, bool bPrioritizeCreation, bool bAllowStartGrassMapGeneration, bool bAnyLandscapeActorHasGrassEnabled);` — Amortized Update of Grass Maps near the specified cameras. if Cameras is empty, it considers all distances to be zero for update purposes: - it won't evict anything for distance - it will not start tracking (building grass maps) for any components
- L76 _public prototype_ `bool BuildGrassMapsNowForComponents(TArrayView<TObjectPtr<ULandscapeComponent>> LandscapeComponents, FScopedSlowTask* SlowTask, bool bMarkDirty);` — synchronous build of grassmaps for a specific set of components returns true if it successfully makes all LandscapeComponents have up to date Grass Maps.
- L81 _public prototype_ `void DebugRenderComponents(TArrayView<TObjectPtr<ULandscapeComponent>> LandscapeComponents);` — Force stream textures and issue draw calls for the specified components -- mainly for capturing the rendering behavior and debugging issues (this will evict existing populated grass maps on those components)
- L87 _private prototype_ `bool CanCurrentlyRender() const;` — false if the world can not currently render the grass (but this may change later, for example if preview modes are modified)
- L95 _private prototype_ `bool UpdateTrackedComponents(const TArray<FVector>& Cameras, int32 LocalMaxRendering, int32 MaxExpensiveUpdateChecksToPerform, bool bCancelAndEvictAllImmediately, bool bEvictWhenBeyondEvictionRange, int32 DeltaTicks);` — Update all of the non-pending components.  Returns true if any components changed states. If passed an empty Cameras array, distances are calculated as zero (i.e. it won't evict for distance) MaxExpensiveUpdateChecksToPerform controls how many expensive component updates are performed (pass ComponentStates.Num() to process all) bCancelAndEvictAllImmediately will move all tracked component states to the pending state and block until any in-flight processing is cancelled and cleaned up bEvictWhenBeyondEvictionRange will evict any populated components that are beyond the eviction range distance (used to reclaim memory when using runtime generation) DeltaTicks specifies how many ticks to advance the tick counter on each tracked component.  In general 1 tick, though in some cases where we are iterating within a single frame, and don't need to trigger delayed-tick events (i.e. D3D11 readback), we can pass 0.
- L99 _private prototype_ `void StartPrioritizedGrassMapGeneration(const TArray<FVector>& Cameras, int32 MaxComponentsToStart, bool bOnlyWhenCloserThanEvictionRange);` — Start the grass map generation process on pending components in priority order (based on distance from the given Camera set) -- Cameras must not be empty.
- L224 _private member_ `UWorld* World = nullptr;`
- L227 _private member_ `int32 PendingCount = 0;` — counts of how many components are currently in each stage
- L228 _private member_ `int32 NotReadyCount = 0;`
- L229 _private member_ `int32 StreamingCount = 0;`
- L230 _private member_ `int32 RenderingCount = 0;`
- L231 _private member_ `int32 AsyncFetchCount = 0;`
- L232 _private member_ `int32 PopulatedCount = 0;`
- L235 _private member_ `int32 TotalComponentsWaitingCount = 0;` — number of components that need to render but are waiting (as of the last call to StartTrackingComponents())
- L238 _private member_ `bool bRenderCommandsQueuedByLastUpdate = false;` — true if any render thread commands were queued by the last call to UpdateTrackedComponents()
- L240 _private member_ `TAllocatorFixedSizeFreeList<sizeof(FComponentState), 32> StatePoolAllocator;`
- L243 _private member_ `TMap<ULandscapeComponent*, FComponentState*> ComponentStates;` — store the grass map state of each registered (or recently unregistered) component
- L246 _private member_ `TArray<FPendingComponent> PendingComponentsHeap;` — Pending components, in a min heap by distance to streaming cameras
- L247 _private member_ `int32 FirstNewPendingComponent = TNumericLimits<int32>::Max();`
- L248 _private member_ `int32 PendingUpdateAmortizationCounter = 0;`
- L249 _private member_ `float LastMustHaveDistanceScale = 0.0f;` — used to detect spawn distance scales changing
- L252 _private member_ `FAmortizedUpdate AmortizedUpdate;` — state to amortize the update of components
- L255 _private member_ `FLandscapeTextureStreamingManager& TextureStreamingManager;` — system to manage texture streaming requests
- L258 _private member_ `UE::Geometry::TPointHashGrid3<FVector, double> PreviousCameraHashGrid;` — hash grid storing previously used camera locations (to determine when cameras have jumped)
- L263 _private prototype_ `bool CancelAndEvict(FComponentState& State, bool bCancelImmediately);` — tries to cancel any in flight operations and transition back to the Pending state returns true when the state has been successfully transitioned back to Pending if bCancelImmediately is true, it will ensure the component reaches Pending state before returning (possibly blocking on async or gpu tasks)
- L266 _private prototype_ `bool StartGrassMapGeneration(FComponentState& State, bool bForceCompileShaders, bool bTryFastPaths = true);` — try to kick off the grass map generation pipeline -- returns true if it started the amortized update path, false otherwise.
- L269 _private prototype_ `bool TryFastpathsFromPending(FComponentState& State, bool bRecalculateHashes);` — try to apply fast path transitions to a pending component -- returns true if a fastpath was taken, and the component is no longer pending.
- L272 _private prototype_ `void KickOffRenderAndReadback(FComponentState& State);` — once textures are streamed, this kicks off the grass data render, and async GPU readback
- L275 _private prototype_ `void LaunchAsyncFetchTask(FComponentState& State);` — once the GPU readback is complete, this starts processing the data to generate a GrassData structure
- L277 _private prototype_ `void PopulateGrassDataFromAsyncFetchTask(FComponentState& State);`
- L280 _private prototype_ `void PopulateGrassDataFromReadback(FComponentState& State);` — once the GPU readback is complete, this populates the grass data on the component (and cancels texture stream requests)
- L281 _private prototype_ `void RemoveTextureStreamingRequests(FComponentState& State);`
- L284 _private prototype_ `void StreamingToNotReady(FComponentState& State);` — state transition helpers
- L285 _private prototype_ `void PendingToNotReady(FComponentState& State);`
- L286 _private prototype_ `void PendingToPopulatedFastPathAlreadyHasData(FComponentState& State);`
- L287 _private prototype_ `void PendingToPopulatedFastPathNoGrass(FComponentState& State);`
- L288 _private prototype_ `void PendingToStreaming(FComponentState& State);`
- L291 _private prototype_ `void AddToPendingComponentHeap(FComponentState* State);` — pending component heap add/remove
- L292 _private prototype_ `void RemoveFromPendingComponentHeap(FComponentState* State);`
- L294 _private prototype_ `void CompleteAllAsyncTasksNow();`
- L298 _private member_ `mutable int32 OutdatedGrassMapCount = 0;` — cached count of how many grass maps are outdated, and the last time we calculated that value
- L299 _private member_ `mutable double GrassMapsLastCheckTime = 0.0;`

#### enum `FLandscapeGrassMapsBuilder::EComponentStage`  
`enum class EComponentStage : uint8`  
_L101-109_
- L103 _public enumerator_ `Pending` — initial state; the component is waiting to start the generation process.
- L104 _public enumerator_ `NotReady` — tried to start generation process, but either no grass types exist or the material is not ready. wait for that to change.
- L105 _public enumerator_ `TextureStreaming` — texture streaming was requested.  wait for the mips to be available
- L106 _public enumerator_ `Rendering` — GPU render commands were sent -- waiting for async readback to complete
- L107 _public enumerator_ `AsyncFetch` — Waiting for the async fetch task to complete
- L108 _public enumerator_ `GrassMapsPopulated` — grass maps are built and are ready to create instances

#### struct `FLandscapeGrassMapsBuilder::FComponentState`  
`struct FComponentState`  
_L111-146_
- L116 _public member_ `ULandscapeComponent* Component = nullptr;` — this pointer is valid as long as the Component is registered (the FComponentState itself may continue to exist after unregistration, until all resources are cleaned up)
- L118 _public member_ `EComponentStage Stage = EComponentStage::Pending;`
- L120 _public member_ `bool bInPendingHeap = false;`
- L123 _public member_ `int32 TickCount = 0;` — counts the number of ticks this component has remained in the current stage
- L127 _public member_ `uint32 GrassMapGenerationHash = 0;` — the hashes of dependencies when this component's grass map was built, for tracking automatic invalidation
- L128 _public member_ `uint32 GrassInstanceGenerationHash = 0;`
- L132 _public member_ `TArray<TWeakObjectPtr<UTexture>> TexturesToStream;` — list of textures to stream prior to rendering this component (valid only in TextureSreaming and Rendering stages)
- L135 _public member_ `TUniquePtr<FLandscapeGrassWeightExporter> ActiveRender;` — the active render (valid only in Rendering stage)
- L138 _public member_ `TUniquePtr<FAsyncTask<FAsyncFetchTask>> AsyncFetchTask;` — when in AsyncFetch stage, this is async task that we are waiting for
- L140 _public prototype_ `FComponentState(ULandscapeComponent* Component);`
- L142 _public prototype_ `bool AreTexturesStreamedIn();`
- L143 _public prototype_ `bool IsBeyondEvictionRange(const TArray<FVector>& Cameras) const;`
- L145 _public prototype_ `bool IsComponentValid() const;` — Validate that the component is valid, as well as its landscape info and main landscape actor

#### struct `FLandscapeGrassMapsBuilder::FPendingComponent`  
`struct FPendingComponent`  
_L149-165_
- desc: components in the Pending state are also tracked in a priority heap, using this structure
- L151 _public function_ `FPendingComponent(FComponentState* InComponentState) : State(InComponentState)`
- L156 _public function_ `bool operator<(const FPendingComponent& Other) const` — comparison operator used for Heap functions -- smaller keys have priority over larger keys
- L161 _public prototype_ `void UpdatePriorityDistance(const TArray<FVector>& Cameras, float MustHaveDistanceScale);`
- L163 _public member_ `FComponentState* State = nullptr;`
- L164 _public member_ `double PriorityKey = TNumericLimits<double>::Lowest();`

#### struct `FLandscapeGrassMapsBuilder::FAmortizedUpdate`  
`struct FAmortizedUpdate`  
_L168-222_
- desc: structure to do an amortized update of a set of update elements in a (conceptual) array
- L171 _public member_ `int32 FirstIndex = 0;` — the first index to update this tick (inclusive)
- L174 _public member_ `int32 LastIndex = 0;` — the last index to update this tick (exclusive)
- L178 _public function_ `void StartUpdateTick(int32 UpdateElementCount, int32 MaxUpdatesThisFrame)` — Call at the beginning of the update tick to set up how many updates you want to run this tick UpdateElementCount is the total number of update elements (to wrap when we hit the end of the possibility space)
- L200 _public function_ `bool ShouldUpdate(int32 UpdateElementIndex)` — return true if the given element should update
- L210 _public function_ `void HandleDeletion(int32 DeletedUpdateElementIndex)` — call if an update element is deleted from the array, to update the valid ranges

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Landscape` (scope `UE`)

### `Source/Runtime/Landscape/Private/LandscapeGroup.h` (Private)


#### struct `FLandscapeGroup`  
`struct FLandscapeGroup`  
_L21-100_
- L26 _public member_ `FRWLock RWLock;` — read-write lock that protect access to XYToEdgeFixupMap, and registered ULandscapeHeightmapTextureEdgeFixup's Snapshots, EdgeModifiedFlags and GPUEdgeHashes
- L28 _public member_ `uint32 LandscapeGroupKey = 0;`
- L32 _public member_ `int32 ComponentResolution = -1;` — Resolution, Origin and Size, defines the group coordinate system (the first component registered gets to be the origin)
- L33 _public member_ `FVector GroupCoordOrigin = FVector::ZeroVector;` — world space position of the center of the origin component (render coord 0,0)
- L34 _public member_ `FVector GroupCoordXVector = FVector::ZeroVector;` — world space vector in the direction of component local X
- L35 _public member_ `FVector GroupCoordYVector = FVector::ZeroVector;` — world space vector in the direction of component local Y
- L36 _public member_ `FVector LandscapeGridScale = FVector::ZeroVector;` — scale used to calculate normals, value set at the same time as above
- L39 _public member_ `TMap<FIntPoint, TObjectPtr<ULandscapeHeightmapTextureEdgeFixup>> XYToEdgeFixupMap;` — map of fixups (key is group coordinate)
- L43 _public member_ `static TMap<TObjectPtr<UTexture2D>, TObjectPtr<ULandscapeComponent>> HeightmapTextureToActiveComponent;` — global map of heightmap textures to the landscape active component (this is used to detect and handle shared heightmaps)
- L47 _public member_ `TSet<TObjectPtr<ULandscapeHeightmapTextureEdgeFixup>> AllRegisteredFixups;` — set of fixups that are registered with this group (some of which may not be mapped) this is only used to double check correct behavior
- L50 _public member_ `TSet<TObjectPtr<ULandscapeHeightmapTextureEdgeFixup>> HeightmapsMoved;` — set of fixups that were moved and may need to modify their mapped position (or if all are moved, we may need to reset the map grid)
- L54 _public member_ `TSet<TObjectPtr<ULandscapeHeightmapTextureEdgeFixup>> HeightmapsNeedingEdgeSnapshotCapture;` — fixups that need to capture new edge snapshots
- L58 _public member_ `TSet<TObjectPtr<ULandscapeHeightmapTextureEdgeFixup>> HeightmapsNeedingEdgeTexturePatching;` — fixups that may need to GPU edge patch their heightmap textures
- L61 _public member_ `FSetElementId AmortizeIndex;` — amortization state for amortized slow checks
- L63 _public function_ `FLandscapeGroup(uint32 InLandscapeGroupKey) : LandscapeGroupKey(InLandscapeGroupKey)`
- L68 _public prototype_ `~FLandscapeGroup();`
- L70 _public prototype_ `void RegisterComponent(ULandscapeComponent* Component);`
- L71 _public prototype_ `void UnregisterComponent(ULandscapeComponent* Component);`
- L72 _public prototype_ `void OnTransformUpdated(ULandscapeComponent* Component);`
- L74 _public prototype_ `static void RegisterAllComponentsOnStreamingProxy(ALandscapeStreamingProxy* StreamingProxy);`
- L75 _public prototype_ `static void UnregisterAllComponentsOnStreamingProxy(ALandscapeStreamingProxy* StreamingProxy);`
- L76 _public prototype_ `static void AddReferencedObjects(FLandscapeGroup* InThis, FReferenceCollector& Collector);`
- L78 _public function_ `ULandscapeHeightmapTextureEdgeFixup* GetEdgeFixupAtCoord(FIntPoint Coord)`
- L88 _public function_ `ULandscapeHeightmapTextureEdgeFixup* GetNeighborEdgeFixup(FIntPoint Coord, UE::Landscape::ENeighborIndex NeighborIndex)`
- L94 _public prototype_ `void TickEdgeFixup(ULandscapeSubsystem* LandscapeSubsystem, bool bForcePatchAll);`
- L97 _private prototype_ `void DisableAndUnmap(ULandscapeHeightmapTextureEdgeFixup* Fixup);`
- L98 _private prototype_ `FIntPoint Map(ULandscapeHeightmapTextureEdgeFixup* Fixup, ULandscapeComponent* Component);`
- L99 _private prototype_ `void Unmap(ULandscapeHeightmapTextureEdgeFixup* Fixup, const bool bRemoveFromLists = true);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Landscape` (scope `UE`)
- L16 _prototype_ `bool ShouldInstallEdgeFixup();` (scope `UE::Landscape`)
- L17 _prototype_ `bool ShouldPatchStreamingMipEdges();` (scope `UE::Landscape`)
- L18 _prototype_ `bool ShouldPatchAllLandscapeComponentEdges(bool bResetForNext = false);` (scope `UE::Landscape`)

### `Source/Runtime/Landscape/Private/LandscapePrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLandscape, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLandscapeBP, Display, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGrass, Log, All);`
- L13 _macro_ `#define GRASS_DEBUG_LOG(...) UE_LOG(LogGrass, Verbose, __VA_ARGS__)`
- L18 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Dynamic Draw Time"), STAT_LandscapeDynamicDrawTime, STATGR` — Landscape stats
- L19 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Render SetMesh Draw Time VS"), STAT_LandscapeVFDrawTime`
- L20 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Render SetMesh Draw Time PS"), STAT_LandscapeVFDrawTime`
- L22 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Regenerate Layers DrawCalls"), STAT_LandscapeLayersRegenerateDrawCal`
- L23 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Processed Triangles"), STAT_LandscapeTriangles, STAT`
- L24 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("Render Passes"), STAT_LandscapeComponentRenderPasses, STATGROUP_`
- L25 _delegate_ `DECLARE_DWORD_COUNTER_STAT_EXTERN(TEXT("DrawCalls"), STAT_LandscapeDrawCalls, STATGROUP_Land`

### `Source/Runtime/Landscape/Private/LandscapeSplineRaster.h` (Private)


#### struct `LandscapeSplineRaster::FPointifyFalloffs`  
`struct FPointifyFalloffs`  
_L16-44_
- L18 _public function_ `FPointifyFalloffs(float StartFalloff, float EndFalloff) : StartLeftSide(StartFalloff) , EndLeftSide(EndFalloff) , StartRightSide(StartFalloff) , EndRightSide(EndFalloff) , StartLeftSideLayer(StartFalloff) , EndLeftSideLayer(EndFalloff) , StartRightSideLayer(StartFalloff) , EndRightSideLayer(EndFalloff)`
- L30 _public function_ `FPointifyFalloffs() : FPointifyFalloffs(0.0f, 0.0f)`
- L36 _public member_ `float StartLeftSide;`
- L37 _public member_ `float EndLeftSide;`
- L38 _public member_ `float StartRightSide;`
- L39 _public member_ `float EndRightSide;`
- L40 _public member_ `float StartLeftSideLayer;`
- L41 _public member_ `float EndLeftSideLayer;`
- L42 _public member_ `float StartRightSideLayer;`
- L43 _public member_ `float EndRightSideLayer;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace LandscapeSplineRaster`
- L14 _prototype_ `bool FixSelfIntersection(TArray<FLandscapeSplineInterpPoint>& Points, FVector FLandscapeSplineInterpPoint::* Side);` (scope `LandscapeSplineRaster`)
- L46 _prototype_ `void Pointify(const FInterpCurveVector& SplineInfo, TArray<FLandscapeSplineInterpPoint>& OutPoints, int32 NumSubdivisions, float StartFalloffFraction, float EndFalloffFraction, const float StartWidth, const float EndWidth, const float StartLayerWidth, const float EndLayerWidth, const FPointifyFalloffs& Falloffs, const float StartRollDegrees, const float EndRollDegrees);` (scope `LandscapeSplineRaster`)
- L53 _prototype_ `void RasterizeSegmentPoints(ULandscapeInfo* LandscapeInfo, TArray<FLandscapeSplineInterpPoint> Points, const FTransform& SplineToWorld, bool bRaiseTerrain, bool bLowerTerrain, ULandscapeLayerInfoObject* LayerInfo);` (scope `LandscapeSplineRaster`)

### `Source/Runtime/Landscape/Private/LandscapeTextureStreamingManager.h` (Private)


#### class `FLandscapeTextureStreamingManagerUndoDetector`  
`class FLandscapeTextureStreamingManagerUndoDetector : FSelfRegisteringEditorUndoClient`  
_L11-26_
- inherits: `FSelfRegisteringEditorUndoClient`
- L14 _public member_ `bool bUndoRedoPerformed = false;`
- L17 _private function_ `virtual void PostUndo(bool bSuccess) override`
- L22 _private function_ `virtual void PostRedo(bool bSuccess) override`

#### class `FLandscapeTextureStreamingManager`  
`class FLandscapeTextureStreamingManager`  
_L32-92_
- L40 _public prototype_ `bool RequestTextureFullyStreamedIn(UTexture* Texture, bool bWaitForStreaming);` — Put in a request to have all streamable mips of a texture streamed in. bWaitForStreaming true will cause it to block until the texture streaming operation completes. bWaitForStreaming false will asynchronously stream in the textures, and you can check for completion with IsTextureFullyStreamedIn(). The texture will* remain streamed in until you call UnrequestTextureFullyStreamedIn() Returns true if the texture is currently fully streamed in.
- L45 _public prototype_ `void UnrequestTextureFullyStreamedIn(UTexture* Texture);` — Remove a request to have all streamable mips of a texture streamed in. The texture may still remain streamed in if someone else has a request, or if the texture manager doesn't see any need to evict it to reclaim texture memory.
- L50 _public prototype_ `bool RequestTextureFullyStreamedInForever(UTexture* Texture, bool bWaitForStreaming);` — Request that this texture be fully streamed in for as long as the texture is loaded. No backsies. bWaitForStreaming will also block until the texture is fully streamed in. Returns true if the texture is fully streamed.
- L58 _public prototype_ `bool WaitForTextureStreaming();` — Synchronously waits for all textures to complete their requested streaming. Returns true if successful. This necessary if you are requesting streaming and waiting for the textures to be streamed within a local loop. (normally they don't complete streaming until a certain point in the update tick)
- L61 _public prototype_ `void CleanupPostGarbageCollect();` — Call this post garbage collect to clean up any old entries in tracked TextureStates for textures that have been unloaded without first being Unrequested, and make sure the streaming flags weren't cleared
- L64 _public prototype_ `void CheckRequestedTextures();` — Check that all requested textures are still requested.
- L66 _public prototype_ `static bool IsTextureFullyStreamedIn(UTexture* Texture);`
- L68 _public prototype_ `FLandscapeTextureStreamingManager();`
- L69 _public prototype_ `~FLandscapeTextureStreamingManager();`
- L83 _private member_ `TMap<TWeakObjectPtr<UTexture>, FTextureState, FDefaultSetAllocator, TWeakObjectPtrMapKeyFuncs<TWeakObjectPtr<UTexture>, FTextureState>> TextureStates;`
- L85 _private member_ `static TArray<FLandscapeTextureStreamingManager*> AllStreamingManagers;`
- L86 _private prototype_ `static bool AnyStreamingManagerWantsTextureStreamedIn(TWeakObjectPtr<UTexture> TexturePtr);`
- L89 _private member_ `FLandscapeTextureStreamingManagerUndoDetector UndoDetector;`

#### struct `FLandscapeTextureStreamingManager::FTextureState`  
`struct FTextureState`  
_L72-81_
- L74 _public member_ `int32 RequestCount = 0;`
- L75 _public member_ `bool bForever = false;`
- L77 _public function_ `bool WantsTextureStreamedIn() const`

### `Source/Runtime/Landscape/Private/LandscapeUtilsPrivate.h` (Private)


#### class `UE::Landscape::Private::T2DIndexer`  
`template <typename ValueType, typename KeyFuncs> class T2DIndexer`  
_L38-307_
- desc: Helper class to transform a list of values into a 2D array. This is a replacement for a TMap<FIntPoint, ValueType>, where FIntPoint is a 2D key and ValueType, the type of object to store. It uses bit arrays to note the presence of an object and the 2D key to index it. The advantage is that the key can trivially be turned into linear index (and vice-versa), derived from the bounds of all registered keys. It is meant to be used as a temporary helper, which is why there are currently no Add/Remove functions (all objects are registered in the constructor) but this could be done eventually, and even replace ULandscapeInfo's XYToComponentMap entirely
- L41 _public function_ `T2DIndexer(TConstArrayView<ValueType> InValues)`
- L73 _public prototype_ `virtual ~T2DIndexer() = default;`
- L74 _public prototype_ `T2DIndexer(const T2DIndexer& Other) = default;`
- L75 _public prototype_ `T2DIndexer(T2DIndexer&& Other) = default;`
- L76 _public prototype_ `T2DIndexer& operator=(const T2DIndexer& Other) = default;`
- L77 _public prototype_ `T2DIndexer& operator=(T2DIndexer&& Other) = default;`
- L79 _public function_ `bool IsValidKey(const FIntPoint& InKey) const`
- L84 _public function_ `bool IsValidValueIndex(int32 InIndex) const`
- L89 _public function_ `ValueType& GetValueForKey(const FIntPoint& InKey) const`
- L94 _public function_ `ValueType& GetValueForKeySafe(const FIntPoint& InKey) const`
- L99 _public function_ `ValueType& GetValueForKeyChecked(const FIntPoint& InKey) const`
- L105 _public function_ `int32 GetValueIndexForKey(const FIntPoint& InKey) const`
- L111 _public function_ `int32 GetValueIndexForKeySafe(const FIntPoint& InKey) const`
- L116 _public function_ `int32 GetValueIndexForKeyChecked(const FIntPoint& InKey) const`
- L122 _public function_ `FIntPoint GetValueKeyForIndex(int32 InIndex) const`
- L128 _public function_ `FIntPoint GetValueKeyForIndexSafe(int32 InIndex) const`
- L133 _public function_ `FIntPoint GetValueKeyForIndexChecked(int32 InIndex) const`
- L139 _public function_ `int32 GetValueIndex(const ValueType& InValue) const`
- L144 _public function_ `int32 GetValueIndexSafe(const ValueType& InValue) const`
- L149 _public function_ `int32 GetValueIndexChecked(const ValueType& InValue) const`
- L154 _public function_ `bool IsValidValue(const FIntPoint& InKey) const`
- L159 _public function_ `bool IsValidValueSafe(const FIntPoint& InKey) const`
- L164 _public function_ `bool IsValidValueChecked(const FIntPoint& InKey) const`
- L170 _public function_ `bool HasValidValueInBounds(const FIntRect& InBounds, bool bInInclusiveBounds)`
- L199 _public function_ `TBitArray<> GetValidValueBitIndicesInBounds(const FIntRect& InBounds, bool bInInclusiveBounds)`
- L228 _public function_ `TArray<ValueType> GetValidValuesForBitIndices(const TBitArray<>& InBitIndices)`
- L243 _public function_ `FIntRect GetValidValuesBoundsForBitIndices(const TBitArray<>& InBitIndices, bool bInInclusiveBounds)`
- L289 _public function_ `TArray<ValueType> GetValidValues()`
- L300 _public function_ `const TArray<ValueType>& GetAllValues() const`
- L301 _public function_ `const TBitArray<>& GetValidValueBitIndices() const`
- L304 _private member_ `FIntRect KeyExclusiveBounds;`
- L305 _private member_ `TArray<ValueType> AllValues;`
- L306 _private member_ `TBitArray<> ValidValueBitIndices;`

#### struct `UE::Landscape::Private::FLandscapeComponent2DIndexerKeyFuncs`  
`struct FLandscapeComponent2DIndexerKeyFuncs`  
_L309-312_
- L311 _public prototype_ `static FIntPoint GetKey(ULandscapeComponent* InComponent);`

#### struct `UE::Landscape::Private::FBlitBuffer2DDesc`  
`struct FBlitBuffer2DDesc`  
_L318-323_
- L320 _public member_ `int32 BufferSize = 0;` — Buffer size in elements.
- L321 _public member_ `int32 Stride = 0;` — Buffer stride in elements.  i.e. the distance between the start of each row.
- L322 _public member_ `FIntRect Rect;` — The 2D region represented by this buffer.  Rect.Area() should be <= BufferSize.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Landscape` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Landscape`)
- L17 _prototype_ `int32 ComputeMaxDeltasOffsetForMip(int32 InMipIndex, int32 InNumRelevantMips);` (scope `UE::Landscape::Private`)
- L18 _prototype_ `int32 ComputeMaxDeltasCountForMip(int32 InMipIndex, int32 InNumRelevantMips);` (scope `UE::Landscape::Private`)
- L19 _prototype_ `int32 ComputeMipToMipMaxDeltasIndex(int32 InSourceMipIndex, int32 InDestinationMipIndex, int32 InNumRelevantMips);` (scope `UE::Landscape::Private`)
- L20 _prototype_ `int32 ComputeMipToMipMaxDeltasCount(int32 InNumRelevantMips);` (scope `UE::Landscape::Private`)
- L24 _prototype_ `bool UseWeightmapTextureArray(EShaderPlatform InPlatform);` (scope `UE::Landscape::Private`) — Returns true if InPlatform is a mobile platform and the Landscape.MobileWeightTextureArray CVar set
- L27 _prototype_ `bool IsMobileWeightmapTextureArrayEnabled();` (scope `UE::Landscape::Private`) — Check if Landscape.MobileWeightTextureArray CVar set and we should attempt to use texture arrays for weight maps on mobile platforms
- L29 _prototype_ `void CreateLandscapeComponentLayerDataDuplicate(const FLandscapeLayerComponentData& InSourceComponentData, FLandscapeLayerComponentData& OutDestComponentData);` (scope `UE::Landscape::Private`)
- L314 _typedef_ `using FLandscapeComponent2DIndexer = T2DIndexer<ULandscapeComponent*, FLandscapeComponent2DIndexerKeyFuncs>;` (scope `UE::Landscape::Private`)
- L315 _prototype_ `FLandscapeComponent2DIndexer CreateLandscapeComponent2DIndexer(const ULandscapeInfo* InInfo);` (scope `UE::Landscape::Private`)
- L336 _prototype_ `int32 BlitHeightChannelsToUint16(uint16* DestBuffer, const FBlitBuffer2DDesc& Dest, uint32* SrcBuffer, const FBlitBuffer2DDesc& Src, FIntRect ClipRect);` (scope `UE::Landscape::Private`) — Copy height values from the R+G channels of the source buffer into a plain uint16 dest buffer.  The source and destination buffers represent sub-regions of a shared 2D coordinate system expressed in the Rect parameters.  ClipRect is the desired area of that shared coordinate space to limit the operation to.  Copies only values in the the intersection of Src.Rect, Dest.Rect, and ClipRect. All FIntRect params are treated as half-open.  .Min is included.  .Max is excluded. @param DestBuffer destination buffer @param Dest description of the destination buffer @param SrcBuffer source buffer @param Src description of the source buffer @param ClipRect The operation will be limited to this region, in the same shared coordinate space of the rects from the buffer descriptions. @return number of elements copied.
- L350 _prototype_ `int32 BlitWeightChannelsToUint8(uint8* DestBuffer, const FBlitBuffer2DDesc& Dest, uint32* SrcBuffer, const FBlitBuffer2DDesc& Src, FIntRect ClipRect);` (scope `UE::Landscape::Private`) — Copy 16-bit weight values from the R+G channels of the source buffer, scaled down into a plain uint8 dest buffer.  The source and destination buffers represent sub-regions of a shared 2D coordinate system expressed in the Rect parameters.  ClipRect is the desired area of that shared coordinate space to limit the operation to.  Copies only values in the the intersection of Src.Rect, Dest.Rect, and ClipRect. All FIntRect params are treated as half-open.  .Min is included.  .Max is excluded. @param DestBuffer destination buffer @param Dest description of the destination buffer @param SrcBuffer source buffer @param Src description of the source buffer @param ClipRect The operation will be limited to this region, in the same shared coordinate space of the rects from the buffer descriptions. @return number of elements copied.
- L352 _prototype_ `void SubmitGPUCommands(bool bBlockUntilRTComplete, bool bBlockRTUntilGPUComplete);` (scope `UE::Landscape::Private`)
- L359 _namespace_ `namespace UE`
- L359 _namespace_ `namespace Landscape` (scope `UE`)
- L359 _namespace_ `namespace Grass` (scope `UE::Landscape`)
- L359 _namespace_ `namespace Private` (scope `UE::Landscape::Grass`)
- L362 _prototype_ `uint32 ComputeNamedGrassTypesHash(const TMap<FName, TObjectPtr<ULandscapeGrassType>>& InNamedGrassTypes);` (scope `UE::Landscape::Grass::Private`)

### `Source/Runtime/Landscape/Private/LandscapeVersion.h` (Private)


#### enum `FLandscapeCustomVersion::Type`  
`enum Type`  
_L11-40_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L16 _public enumerator_ `NewSplineCrossLevelMeshSerialization` — Changed to TMap properties instead of manual serialization and fixed landscape spline control point cross-level mesh components not being serialized
- L18 _public enumerator_ `GrassMaterialWPO` — Support material world-position-offset in the heightmap used for grass placement
- L20 _public enumerator_ `CollisionMaterialWPO` — Support material world-position-offset in landscape simple collision
- L22 _public enumerator_ `LightmassMaterialWPO` — Support material world-position-offset in landscape lighting mesh
- L24 _public enumerator_ `GrassMaterialInstanceFix` — Fix for landscape grass not updating when using a material instance as the landscape material and changing parameters
- L26 _public enumerator_ `SplineForeignDataLazyObjectPtrFix` — Fix for spline Foreign data that used TMap<TLazyObjectPtr, ...> to now use TArray<...> to prevent key creation every time we do a search thus putting the package dirty
- L28 _public enumerator_ `MigrateOldPropertiesToNewRenderingProperties` — Migration of deprecated property from old landscape rendering to new landscape Rendering
- L30 _public enumerator_ `AddingBodyInstanceToSplinesElements` — Migration of old EnabledCollision for spline elements to the full body instance exposed
- L32 _public enumerator_ `AddSplineLayerFalloff` — Spline Layer Falloff
- L34 _public enumerator_ `AddSplineLayerWidth` — Spline Layer Width
- L36 _public enumerator_ `NewLandscapeContinuousLOD` — New LOD distribution and tessellation calculations are introduced, needs parameter conversion
- L38 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L39 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace FLandscapeCustomVersion`
- L43 _variable_ `const static FGuid GUID = FGuid(0x23AFE18E, 0x4CE14E58, 0x8D61C252, 0xB953BEB7);` (scope `FLandscapeCustomVersion`) — The GUID for this custom version

### `Source/Runtime/Landscape/Public/GlobalMergeLegacySupportUtil.h` (Public)


#### class `ULandscapeBrushRenderCallAdapter_GlobalMergeLegacySupport`  
`class UE_DEPRECATED(5.7, "Global merge has been deprecated so this is no longer used. T`  
_L16-16_

#### class `ILandscapeBrushRenderCallAdapter_GlobalMergeLegacySupport`  
`class UE_DEPRECATED(5.7, "Global merge has been deprecated so this is no longer used. T`  
_L17-17_
- reflection: `UE_DEPRECATED(5.7, "Global merge has been deprecated so this is no longer used. There's no good way of deprecating UInterfaces ATM, hence this forward-declaration")`

#### class `ULandscapeBrushRenderCallAdapter_GlobalMergeLegacySupport_DEPRECATED`  
`class ULandscapeBrushRenderCallAdapter_GlobalMergeLegacySupport_DEPRECATED : public UInterface`  
_L21-24_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UObject for the UInterface

#### class `ILandscapeBrushRenderCallAdapter_GlobalMergeLegacySupport_DEPRECATED`  
`class ILandscapeBrushRenderCallAdapter_GlobalMergeLegacySupport_DEPRECATED`  
_L34-68_
- L45 _public function_ `UTextureRenderTarget2D* RenderAsBlueprintBrush(const FLandscapeBrushParameters& InParameters, const FTransform& LandscapeTransform)` — In global merge mode, this function is called in the same places that FLandscapeLayerBrush::RenderLayer(BrushParameters) is called. This function calls the virtual InitializeAsBlueprintBrush and RenderLayerAsBlueprintBrush functions, which are equivalent to a blueprint brush actor's Initialize_Native and RenderLayer_Native.
- L48 _public function_ `virtual bool AffectsHeightmapAsBlueprintBrush() const` — Called in the same places as the equivalent methods on FLandscapeLayerBrush.
- L49 _public function_ `virtual bool AffectsWeightmapLayerAsBlueprintBrush(const FName& InLayerName) const`
- L50 _public function_ `virtual bool AffectsVisibilityLayerAsBlueprintBrush() const`
- L55 _protected function_ `virtual void InitializeAsBlueprintBrush(const FTransform& InLandscapeTransform, const FIntPoint& InLandscapeSize, const FIntPoint& InLandscapeRenderTargetSize)` — Overridable, equivalent to Initialize_Native on a blueprint brush actor
- L60 _protected prototype_ `virtual UTextureRenderTarget2D* RenderLayerAsBlueprintBrush(const FLandscapeBrushParameters& InParameters) PURE_VIRTUAL(ILandscapeBrushRenderCallAdapter_GlobalMergeLegacySupport_DEPRECATED::InitializeAsBlueprintBrush, return nullptr; );` — Overridable, equivalent to RenderLayer_Native on a blueprint brush actor.
- L64 _protected member_ `FTransform CurrentRenderAreaWorldTransform;` — Used in RenderAsBlueprintBrush to cache things the same way that blueprint brushes do
- L65 _protected member_ `FIntPoint CurrentRenderAreaSize = FIntPoint(ForceInitToZero);`
- L66 _protected member_ `FIntPoint CurrentRenderTargetSize = FIntPoint(ForceInitToZero);`

### `Source/Runtime/Landscape/Public/LandscapeBlueprintBrushBase.h` (Public)


#### struct `FLandscapeBrushParameters`  
`struct FLandscapeBrushParameters`  
_L16-37_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public prototype_ `FLandscapeBrushParameters() = default;`
- L21 _public prototype_ `FLandscapeBrushParameters(bool bInIsHeightmapMerge, const FTransform& InRenderAreaWorldTransform, const FIntPoint& InRenderAreaSize, UTextureRenderTarget2D* InCombinedResult, const FName& InWeightmapLayerName = FName());`
- L24 _public member_ `FTransform RenderAreaWorldTransform;` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)`
- L27 _public member_ `FIntPoint RenderAreaSize = FIntPoint(MAX_int32, MAX_int32);` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)`
- L30 _public member_ `TObjectPtr<UTextureRenderTarget2D> CombinedResult;` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)`
- L33 _public member_ `ELandscapeToolTargetType LayerType = ELandscapeToolTargetType::Invalid;` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)`
- L36 _public member_ `FName WeightmapLayerName;` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)`

#### class `ALandscapeBlueprintBrushBase`  
`class ALandscapeBlueprintBrushBase : public AActor #if CPP && WITH_EDITOR`  
_L41-162_
- reflection: `UCLASS(Abstract, NotPlaceable, NotBlueprintable, MinimalAPI)`
- inherits: `AActor,ILandscapeEditLayerRenderer,UE::Landscape::EditLayers::IEditLayerRendererProvider`
- L51 _protected member_ `bool UpdateOnPropertyChange;` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)`
- L54 _protected member_ `bool AffectHeightmap;` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite, Setter = "SetCanAffectHeightmap")`
- L57 _protected member_ `bool AffectWeightmap;` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite, Setter = "SetCanAffectWeightmap")`
- L60 _protected member_ `bool AffectVisibilityLayer;` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite, Setter="SetCanAffectVisibilityLayer")`
- L63 _protected member_ `TArray<FName> AffectedWeightmapLayers;` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite)`
- L70 _protected member_ `bool bUsePowerOfTwoRenderTarget = true;` — `UPROPERTY(Category = "Settings", EditAnywhere, BlueprintReadWrite, Setter="SetCanAffectVisibilityLayer")` — It is possible to define whether this BP brush works exclusively with power-of-2 render targets. This used to be mandatory so for full backwards-compatibility, this is still the case by default but it can be turned off.
- L74 _protected member_ `TObjectPtr<class ALandscape> OwningLandscape;` — `UPROPERTY(Transient)`
- L77 _protected member_ `bool bIsVisible;` — `UPROPERTY(Transient)`
- L79 _protected member_ `uint32 LastRequestLayersContentUpdateFrameNumber;`
- L81 _protected member_ `FTransform CurrentRenderAreaWorldTransform;`
- L82 _protected member_ `FIntPoint CurrentRenderAreaSize = FIntPoint(ForceInitToZero);`
- L83 _protected member_ `FIntPoint CurrentRenderTargetSize = FIntPoint(ForceInitToZero);`
- L88 _public prototype_ `UTextureRenderTarget2D* Render(bool InIsHeightmap, UTextureRenderTarget2D* InCombinedResult, const FName& InWeightmapLayerName);` — `UFUNCTION(BlueprintNativeEvent, meta = (DeprecatedFunction, DeprecationMessage = "Please use RenderLayer instead."))`
- L91 _public prototype_ `UTextureRenderTarget2D* RenderLayer(const FLandscapeBrushParameters& InParameters);` — `UFUNCTION(BlueprintNativeEvent)`
- L92 _public prototype_ `virtual UTextureRenderTarget2D* RenderLayer_Native(const FLandscapeBrushParameters& InParameters);`
- L95 _public prototype_ `void Initialize(const FTransform& InLandscapeTransform, const FIntPoint& InLandscapeSize, const FIntPoint& InLandscapeRenderTargetSize);` — `UFUNCTION(BlueprintNativeEvent)`
- L96 _public function_ `virtual void Initialize_Native(const FTransform& InLandscapeTransform, const FIntPoint& InLandscapeSize, const FIntPoint& InLandscapeRenderTargetSize)`
- L99 _public prototype_ `void RequestLandscapeUpdate(bool bInUserTriggered = false);` — `UFUNCTION(BlueprintCallable, Category = "Landscape")`
- L102 _public prototype_ `void GetBlueprintRenderDependencies(TArray<UObject*>& OutStreamableAssets);` — `UFUNCTION(BlueprintImplementableEvent, CallInEditor)`
- L104 _public prototype_ `void SetCanAffectHeightmap(bool bInCanAffectHeightmap);`
- L105 _public prototype_ `void SetCanAffectWeightmap(bool bInCanAffectWeightmap);`
- L106 _public prototype_ `void SetCanAffectVisibilityLayer(bool bInCanAffectVisibilityLayer);`
- L107 _public prototype_ `void SetUsePowerOfTwoRenderTarget(bool bInUsePowerOfTwoRenderTarget);`
- L111 _public prototype_ `virtual void GetRendererStateInfo(const UE::Landscape::EditLayers::FMergeContext* InMergeContext, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutSupportedTargetTypeState, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutEnabledTargetTypeState, TArray<UE::Landscape::EditLayers::FTargetLayerGroup>& OutTargetLayerGroups) const override;`
- L114 _public function_ `virtual UE::Landscape::EditLayers::ERenderFlags GetRenderFlags(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override`
- L115 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRenderItem> GetRenderItems(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L116 _public prototype_ `virtual bool RenderLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) override;`
- L117 _public prototype_ `virtual FString GetEditLayerRendererDebugName() const override;`
- L121 _public prototype_ `TArray<UE::Landscape::EditLayers::FEditLayerRendererState> GetEditLayerRendererStates(const UE::Landscape::EditLayers::FMergeContext* InMergeContext);`
- L124 _public prototype_ `UTextureRenderTarget2D* Execute(const FLandscapeBrushParameters& InParameters);`
- L126 _public prototype_ `virtual void CheckForErrors() override;`
- L128 _public prototype_ `virtual void GetRenderDependencies(TSet<UObject*>& OutDependencies);`
- L130 _public prototype_ `virtual void SetOwningLandscape(class ALandscape* InOwningLandscape);`
- L131 _public prototype_ `class ALandscape* GetOwningLandscape() const;`
- L136 _public function_ `bool CanAffectHeightmap() const` — CanAffect... methods indicate the brush has the _capacity_ to affect this or that aspect of the landscape. Note: it doesn't mean the brush currently affects it : the Affects... methods are used for that.
- L137 _public function_ `bool CanAffectWeightmap() const`
- L138 _public function_ `bool CanAffectVisibilityLayer() const`
- L139 _public prototype_ `virtual bool CanAffectWeightmapLayer(const FName& InLayerName) const;`
- L140 _public prototype_ `virtual bool AffectsHeightmap() const;`
- L141 _public prototype_ `virtual bool AffectsWeightmap() const;`
- L142 _public prototype_ `virtual bool AffectsWeightmapLayer(const FName& InLayerName) const;`
- L143 _public prototype_ `virtual bool AffectsVisibilityLayer() const;`
- L144 _public function_ `virtual bool SupportsBlueprintBrushTool() const`
- L146 _public function_ `bool IsVisible() const`
- L147 _public prototype_ `bool IsLayerUpdatePending() const;`
- L149 _public prototype_ `void SetIsVisible(bool bInIsVisible);`
- L151 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L152 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L153 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L154 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L155 _public prototype_ `virtual void PostEditUndo() override;`
- L156 _public prototype_ `virtual void Destroyed() override;`
- L158 _public prototype_ `virtual void PushDeferredLayersContentUpdate();`
- L160 _public function_ `virtual bool CanChangeIsSpatiallyLoadedFlag() const override`

### `Source/Runtime/Landscape/Public/LandscapeConfigHelper.h` (Public)


#### enum `ELandscapeResizeMode`  
`enum class ELandscapeResizeMode : uint8`  
_L11-16_
- reflection: `UENUM()`
- L13 _public enumerator_ `Resample = 0`
- L14 _public enumerator_ `Clip = 1`
- L15 _public enumerator_ `Expand = 2`

#### struct `FLandscapeConfig`  
`struct FLandscapeConfig`  
_L28-49_
- L30 _public function_ `FLandscapeConfig(int32 InComponentNumSubSections, int32 InSubsectionSizeQuads, int32 InGridSizeInComponents) : ComponentNumSubsections(InComponentNumSubSections) , SubsectionSizeQuads(InSubsectionSizeQuads) , GridSizeInComponents(InGridSizeInComponents)`
- L37 _public prototype_ `FLandscapeConfig(ULandscapeInfo* InLandscapeInfo);`
- L39 _public function_ `int32 GetComponentSizeQuads() const`
- L40 _public function_ `int32 GetComponentSizeVerts() const`
- L41 _public function_ `int32 GetGridSizeQuads() const`
- L43 _public member_ `int32 ComponentNumSubsections;`
- L44 _public member_ `int32 SubsectionSizeQuads;`
- L45 _public member_ `int32 GridSizeInComponents;`
- L47 _public member_ `static int32 NumSectionValues[2];`
- L48 _public member_ `static int32 SubsectionSizeQuadsValues[6];`

#### struct `FLandscapeConfigChange`  
`struct FLandscapeConfigChange : public FLandscapeConfig`  
_L51-64_
- inherits: `FLandscapeConfig`
- L53 _public function_ `FLandscapeConfigChange(int32 InComponentNumSubSections, int32 InSubsectionSizeQuads, int32 InGridSize, ELandscapeResizeMode InResizeMode, bool bInZeroBased) : FLandscapeConfig(InComponentNumSubSections, InSubsectionSizeQuads, InGridSize) , ResizeMode(InResizeMode) , bZeroBased(bInZeroBased)`
- L60 _public prototype_ `bool Validate() const;`
- L62 _public member_ `ELandscapeResizeMode ResizeMode;`
- L63 _public member_ `bool bZeroBased;`

#### class `FLandscapeConfigHelper`  
`class FLandscapeConfigHelper`  
_L66-202_
- L69 _public prototype_ `static ALandscapeProxy* FindOrAddLandscapeStreamingProxy(ULandscapeInfo* InLandscapeInfo, const FIntPoint& InSectionBase);`
- L70 _public prototype_ `static ULandscapeInfo* ChangeConfiguration(ULandscapeInfo* InLandscapeInfo, const FLandscapeConfigChange& InNewConfig, TSet<AActor*>& OutActorsToDelete, TSet<AActor*>& OutModifiedActors);`
- L71 _public prototype_ `static bool ChangeGridSize(ULandscapeInfo* InLandscapeInfo, uint32 InNewGridSizeInComponents, TSet<AActor*>& OutActorsToDelete);`
- L72 _public prototype_ `static bool PartitionLandscape(UWorld* InWorld, ULandscapeInfo* InLandscapeInfo, uint32 InGridSizeInComponents);`
- L75 _private prototype_ `static ALandscapeProxy* FindOrAddLandscapeStreamingProxy(UActorPartitionSubsystem* ActorPartitionSubsystem, ULandscapeInfo* LandscapeInfo, const UActorPartitionSubsystem::FCellCoord& CellCoord);`
- L76 _private prototype_ `static void CopyRegionToComponent(ULandscapeInfo* LandscapeInfo, const FIntRect& Region, bool bResample, ULandscapeComponent* Component);`
- L77 _private prototype_ `static void ExtractLandscapeData(ULandscapeInfo* LandscapeInfo, const FIntRect& Region, const FGuid& LayerGuid, TArray<uint16>& OutHeightData, TArray<FLandscapeImportLayerInfo>& OutImportMaterialLayerInfos);`
- L78 _private prototype_ `static void MoveSplinesToLandscape(ULandscapeInfo* InLandscapeInfo, ALandscapeProxy* InLandscape, float InScaleFactor);`
- L79 _private prototype_ `static void MoveFoliageToLandscape(ULandscapeInfo* InLandscapeInfo, ULandscapeInfo* InNewLandscapeInfo);`
- L83 _public function_ `template<typename T> static void CopyData(const TArray<T>& InData, TArray<T>& OutData, const FIntRect& InSrcRegion, const FIntRect& InDestRegion, bool bInResample)`
- L96 _public function_ `template<typename T> static void ExpandData(const TArray<T>& InData, TArray<T>& OutData, const FIntRect& InSrcRegion, const FIntRect& InDestRegion, bool bOffset)`
- L143 _public function_ `template<typename T> static void CopySubregion(const TArrayView<T>& InData, TArray<T>& OutData, const FIntRect& InSrcRegion, uint32 InSrcDataPitch)`
- L169 _public function_ `template<typename T> static void ResampleData(const TArray<T>& InData, TArray<T>& OutData, const FIntRect& InSrcRegion, const FIntRect& InDestRegion)`

### `Source/Runtime/Landscape/Public/LandscapeDataAccess.h` (Public)


#### struct `FLandscapeDataInterface`  
`struct FLandscapeDataInterface`  
_L89-150_
- desc: FLandscapeDataInterface
- L106 _public function_ `FLandscapeDataInterface()` — Constructor @param bInAutoDestroy - shall we automatically clean up when the last
- L109 _public function_ `void* LockMip(UTexture2D* Texture, int32 MipLevel)`
- L133 _public function_ `void UnlockMip(UTexture2D* Texture, int32 MipLevel)`
- L149 _private member_ `TMap<UTexture2D*, TArray<FLockedMipDataInfo> > LockedMipInfoMap;`

#### struct `FLandscapeDataInterface::FLockedMipDataInfo`  
`struct FLockedMipDataInfo`  
_L93-101_
- L95 _public function_ `FLockedMipDataInfo() : LockCount(0)`
- L99 _public member_ `TArray64<uint8> MipData;`
- L100 _public member_ `int32 LockCount;`

#### struct `FLandscapeComponentDataInterfaceBase`  
`struct FLandscapeComponentDataInterfaceBase`  
_L153-283_
- L155 _public function_ `FLandscapeComponentDataInterfaceBase()`
- L156 _public prototype_ `FLandscapeComponentDataInterfaceBase(ULandscapeComponent* InComponent, int32 InMipLevel, bool InWorkOnEditingLayer = true);`
- L159 _public function_ `void VertexIndexToXY(int32 VertexIndex, int32& OutX, int32& OutY) const` — Accessors
- L166 _public function_ `void QuadIndexToXY(int32 QuadIndex, int32& OutX, int32& OutY) const` — Accessors
- L172 _public function_ `int32 VertexXYToIndex(int32 VertX, int32 VertY) const`
- L177 _public function_ `void ComponentXYToSubsectionXY(int32 CompX, int32 CompY, int32& SubNumX, int32& SubNumY, int32& SubX, int32& SubY ) const`
- L201 _public function_ `void VertexXYToTexelXY(int32 VertX, int32 VertY, int32& OutX, int32& OutY) const`
- L210 _public function_ `int32 VertexIndexToTexel(int32 VertexIndex) const`
- L219 _public function_ `int32 TexelXYToIndex(int32 TexelX, int32 TexelY) const`
- L224 _public function_ `uint16 GetHeight(int32 LocalX, int32 LocalY, const TArray<FColor>& HeightAndNormals) const`
- L230 _public function_ `float GetScaleFactor() const`
- L235 _public function_ `FVector GetLocalVertex(int32 LocalX, int32 LocalY, const TArray<FColor>& HeightAndNormals) const`
- L242 _public function_ `float GetLocalHeight(int32 LocalX, int32 LocalY, const TArray<FColor>& HeightAndNormals) const`
- L247 _public function_ `const FColor* GetHeightData(int32 LocalX, int32 LocalY, const TArray<FColor>& HeightAndNormals) const`
- L259 _public function_ `void GetLocalTangentVectors(int32 LocalX, int32 LocalY, FVector& LocalTangentX, FVector& LocalTangentY, FVector& LocalTangentZ, const TArray<FColor>& HeightAndNormals) const`
- L268 _public function_ `int32 GetComponentSizeVerts() const`
- L272 _public member_ `int32 HeightmapStride = 0;` — offset of this component's data into heightmap texture
- L273 _public member_ `int32 HeightmapComponentOffsetX = 0;`
- L274 _public member_ `int32 HeightmapComponentOffsetY = 0;`
- L275 _public member_ `int32 HeightmapSubsectionOffset = 0;`
- L276 _public member_ `const int32 MipLevel = 0;`
- L279 _protected member_ `int32 ComponentSizeQuads = 0;`
- L280 _protected member_ `int32 ComponentSizeVerts = 0;`
- L281 _protected member_ `int32 SubsectionSizeVerts = 0;`
- L282 _protected member_ `int32 ComponentNumSubsections = 0;`

#### struct `FLandscapeComponentDataInterface`  
`struct FLandscapeComponentDataInterface : public FLandscapeComponentDataInterfaceBase`  
_L288-413_
- inherits: `FLandscapeComponentDataInterfaceBase`
- desc: FLandscapeComponentDataInterface
- L293 _public prototype_ `FLandscapeComponentDataInterface(ULandscapeComponent* InComponent, int32 InMipLevel = 0, bool InWorkOnEditingLayer = true);` — tors
- L294 _public prototype_ `~FLandscapeComponentDataInterface();`
- L296 _public function_ `FColor* GetRawHeightData() const`
- L301 _public function_ `void SetRawHeightData(FColor* NewHeightData)`
- L306 _public prototype_ `int32 GetHeightmapSizeX(int32 MipIndex) const;`
- L307 _public prototype_ `int32 GetHeightmapSizeY(int32 MipIndex) const;`
- L310 _public prototype_ `void GetHeightmapTextureData(TArray<FColor>& OutData, bool bOkToFail = false);` — Return the raw heightmap data exactly same size for Heightmap texture which belong to only this component
- L312 _public prototype_ `bool GetWeightmapTextureData(ULandscapeLayerInfoObject* InLayerInfo, TArray<uint8>& OutData, bool bInUseEditingWeightmap = false, bool bInRemoveSubsectionDuplicates = false);`
- L314 _public function_ `FColor* GetHeightData(int32 LocalX, int32 LocalY) const`
- L330 _public prototype_ `FColor* GetXYOffsetData(int32 LocalX, int32 LocalY) const;` — `UE_DEPRECATED(5.7, "RetopologizeTool/XYOffset deprecated with the removal of non-edit layer landscapes")`
- L332 _public function_ `uint16 GetHeight( int32 LocalX, int32 LocalY ) const`
- L338 _public function_ `uint16 GetHeight( int32 VertexIndex ) const`
- L345 _public function_ `float GetLocalHeight(int32 LocalX, int32 LocalY) const`
- L350 _public function_ `float GetLocalHeight(int32 VertexIndex) const`
- L355 _public prototype_ `FVector GetLocalVertex(int32 LocalX, int32 LocalY) const;`
- L357 _public function_ `void GetLocalTangentVectors( int32 LocalX, int32 LocalY, FVector& LocalTangentX, FVector& LocalTangentY, FVector& LocalTangentZ ) const`
- L367 _public function_ `FVector GetLocalVertex( int32 VertexIndex ) const`
- L374 _public function_ `void GetLocalTangentVectors( int32 VertexIndex, FVector& LocalTangentX, FVector& LocalTangentY, FVector& LocalTangentZ ) const`
- L381 _public prototype_ `FVector GetWorldVertex(int32 LocalX, int32 LocalY) const;`
- L383 _public prototype_ `void GetWorldTangentVectors(int32 LocalX, int32 LocalY, FVector& WorldTangentX, FVector& WorldTangentY, FVector& WorldTangentZ) const;`
- L385 _public prototype_ `void GetWorldPositionTangents(int32 LocalX, int32 LocalY, FVector& WorldPos, FVector& WorldTangentX, FVector& WorldTangentY, FVector& WorldTangentZ) const;`
- L387 _public function_ `FVector GetWorldVertex( int32 VertexIndex ) const`
- L394 _public function_ `void GetWorldTangentVectors( int32 VertexIndex, FVector& WorldTangentX, FVector& WorldTangentY, FVector& WorldTangentZ ) const`
- L401 _public function_ `void GetWorldPositionTangents( int32 VertexIndex, FVector& WorldPos, FVector& WorldTangentX, FVector& WorldTangentY, FVector& WorldTangentZ ) const`
- L409 _private member_ `FLandscapeDataInterface DataInterface;`
- L410 _private member_ `ULandscapeComponent* Component = nullptr;`
- L411 _private member_ `bool bWorkOnEditingLayer = false;`
- L412 _private member_ `FColor* HeightMipData = nullptr;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LANDSCAPE_VALIDATE_DATA_ACCESS 1`
- L13 _macro_ `#define LANDSCAPE_ZSCALE (1.0f/128.0f)`
- L14 _macro_ `#define LANDSCAPE_INV_ZSCALE 128.0f`
- L16 _macro_ `#define LANDSCAPE_XYOFFSET_SCALE UE_DEPRECATED_MACRO(5.7, "RetopologizeTool/XYOffset deprecated with the removal of non-edit layer landscapes") (1.0f/256.f)`
- L17 _macro_ `#define LANDSCAPE_INV_XYOFFSET_SCALE UE_DEPRECATED_MACRO(5.7, "RetopologizeTool/XYOffset deprecated with the removal of non-edit layer landscapes") 256.f`
- L19 _macro_ `#define LANDSCAPE_VISIBILITY_THRESHOLD (2.0f/3.0f)`
- L24 _namespace_ `namespace LandscapeDataAccess`
- L26 _variable_ `inline constexpr int32 MaxValue = 65535;` (scope `LandscapeDataAccess`)
- L27 _variable_ `inline constexpr float MidValue = 32768.f;` (scope `LandscapeDataAccess`)
- L28 _variable_ `inline constexpr float MidNormalValue = 127.5f;` (scope `LandscapeDataAccess`)
- L30 _function_ `FORCEINLINE float GetLocalHeight(uint16 Height)` (scope `LandscapeDataAccess`)
- L35 _function_ `FORCEINLINE uint16 GetTexHeight(float Height)` (scope `LandscapeDataAccess`)
- L40 _function_ `FORCEINLINE FColor PackHeight(uint16 Height)` (scope `LandscapeDataAccess`)
- L48 _function_ `FORCEINLINE float UnpackHeight(const FColor& InHeightmapSample)` (scope `LandscapeDataAccess`)
- L54 _function_ `FORCEINLINE FColor PackNormal(const FVector& InNormal)` (scope `LandscapeDataAccess`)
- L64 _function_ `FORCEINLINE FVector UnpackNormal(const FColor& InHeightmapSample)` (scope `LandscapeDataAccess`)
- L73 _function_ `FORCEINLINE FColor GetDefaultPackedHeightColor()` (scope `LandscapeDataAccess`)
- L417 _function_ `template<typename T> void FillCornerValues(uint8& CornerSet, T* CornerValues)` — Helper functions

### `Source/Runtime/Landscape/Public/LandscapeEdit.h` (Public)


#### class `ILandscapeEdModeInterface`  
`class ILandscapeEdModeInterface`  
_L37-46_
- desc: Landscape EdMode Interface (used by ALandscape in Editor mode to access EdMode properties)
- L40 _public prototype_ `virtual void PostUpdateLayerContent() PURE_VIRTUAL(ILandscapeEdModeInterface::PostUpdateLayerContent(), return;);`
- L41 _public prototype_ `virtual ELandscapeToolTargetType GetLandscapeToolTargetType() const PURE_VIRTUAL(ILandscapeEdModeInterface::GetLandscapeToolTargetType(), return ELandscapeToolTargetType::Invalid;);`
- L42 _public prototype_ `virtual const ULandscapeEditLayerBase* GetLandscapeSelectedLayer() const PURE_VIRTUAL(ILandscapeEdModeInterface::GetLandscapeSelectedLayer(), return nullptr;);`
- L43 _public prototype_ `virtual ULandscapeLayerInfoObject* GetSelectedLandscapeLayerInfo() const PURE_VIRTUAL(ILandscapeEdModeInterface::GetSelectedLandscapeLayerInfo(), return nullptr;);`
- L45 _public prototype_ `virtual void OnCanHaveLayersContentChanged() PURE_VIRTUAL(ILandscapeEdModeInterface::OnCanHaveLayersContentChanged(), return;);` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")`

#### struct `FLandscapeTextureDataInfo`  
`struct FLandscapeTextureDataInfo`  
_L48-84_
- L57 _public prototype_ `FLandscapeTextureDataInfo(UTexture2D* InTexture, bool bShouldDirtyPackage, ELandscapeTextureUsage TextureUsage = ELandscapeTextureUsage::Unknown, ELandscapeTextureType TextureType = ELandscapeTextureType::Unknown);`
- L58 _public prototype_ `virtual ~FLandscapeTextureDataInfo();`
- L61 _public prototype_ `bool UpdateTextureData();` — returns true if we need to block on the render thread before unlocking the mip data
- L63 _public function_ `int32 NumMips()`
- L65 _public prototype_ `void AddMipUpdateRegion(int32 InMipIndex, int32 InX1, int32 InY1, int32 InX2, int32 InY2);`
- L67 _public prototype_ `void* GetMipData(int32 InMipIndex);`
- L69 _public function_ `int32 GetMipSizeX(int32 InMipIndex) const`
- L74 _public function_ `int32 GetMipSizeY(int32 InMipIndex) const`
- L80 _private member_ `UTexture2D* Texture = nullptr;`
- L81 _private member_ `TArray<FMipInfo> MipInfo;`
- L82 _private member_ `ELandscapeTextureUsage TextureUsage = ELandscapeTextureUsage::Unknown;`
- L83 _private member_ `ELandscapeTextureType TextureType = ELandscapeTextureType::Unknown;`

#### struct `FLandscapeTextureDataInfo::FMipInfo`  
`struct FMipInfo`  
_L50-55_
- L52 _public member_ `void* MipData = nullptr;`
- L53 _public member_ `TArray<FUpdateTextureRegion2D> MipUpdateRegions;`
- L54 _public member_ `bool bFull = false;`

#### struct `FLandscapeTextureDataInterface`  
`struct FLandscapeTextureDataInterface`  
_L86-123_
- L88 _public prototype_ `FLandscapeTextureDataInterface(bool bInUploadTextureChangesToGPU = true);`
- L89 _public prototype_ `virtual ~FLandscapeTextureDataInterface();`
- L91 _public function_ `void SetShouldDirtyPackage(bool bValue)`
- L92 _public function_ `bool GetShouldDirtyPackage() const`
- L95 _public prototype_ `FLandscapeTextureDataInfo* GetTextureDataInfo(UTexture2D* Texture);` — Texture data access
- L98 _public prototype_ `void Flush();` — Flush texture updates
- L101 _public prototype_ `void CopyTextureChannel(UTexture2D* Dest, int32 DestChannel, UTexture2D* Src, int32 SrcChannel);` — Texture bulk operations for weightmap reallocation
- L102 _public prototype_ `void ZeroTextureChannel(UTexture2D* Dest, int32 DestChannel);`
- L103 _public prototype_ `void CopyTextureFromHeightmap(UTexture2D* Dest, ULandscapeComponent* Comp, int32 MipIndex);`
- L104 _public prototype_ `void CopyTextureFromHeightmap(UTexture2D* Dest, int32 DestChannel, ULandscapeComponent* Comp, int32 SrcChannel);`
- L105 _public prototype_ `void CopyTextureFromWeightmap(UTexture2D* Dest, int32 DestChannel, ULandscapeComponent* Comp, ULandscapeLayerInfoObject* LayerInfo);`
- L106 _public prototype_ `void CopyTextureFromWeightmap(UTexture2D* Dest, int32 DestChannel, ULandscapeComponent* Comp, ULandscapeLayerInfoObject* LayerInfo, int32 MipIndex);`
- L109 _public prototype_ `template<typename TData> void SetTextureValueTempl(UTexture2D* Dest, TData Value);`
- L110 _public prototype_ `void ZeroTexture(UTexture2D* Dest);`
- L111 _public prototype_ `void SetTextureValue(UTexture2D* Dest, FColor Value);`
- L114 _public prototype_ `template<typename TData> bool EqualTextureValueTempl(UTexture2D* Src, TData Value);`
- L115 _public prototype_ `bool EqualTextureValue(UTexture2D* Src, FColor Value);`
- L118 _private prototype_ `void CopyTextureFromWeightmap(FLandscapeTextureDataInfo* DestDataInfo, int32 DestChannel, ULandscapeComponent* Comp, ULandscapeLayerInfoObject* LayerInfo, int32 MipIndex);`
- L120 _private member_ `TMap<UTexture2D*, FLandscapeTextureDataInfo*> TextureDataMap;`
- L121 _private member_ `bool bUploadTextureChangesToGPU;`
- L122 _private member_ `bool bShouldDirtyPackage;`

#### struct `FLandscapeEditDataInterface`  
`struct FLandscapeEditDataInterface : public FLandscapeTextureDataInterface`  
_L125-303_
- inherits: `FLandscapeTextureDataInterface`
- L128 _public prototype_ `FLandscapeEditDataInterface(ULandscapeInfo* InLandscape, bool bInUploadTextureChangesToGPU = true);` — this constructor will build an interface that works in the current edit layer (uses the ALandscape PrivateEditingLayer state)
- L131 _public prototype_ `FLandscapeEditDataInterface(ULandscapeInfo* InLandscape, const FGuid& InEditLayerGUID, bool bInUploadTextureChangesToGPU = true);` — this constructor will build an interface that works in the specified edit layer : InEditLayerGUID
- L134 _public prototype_ `void SetEditLayer(const FGuid& InEditLayerGUID);` — switch the layer this interface works in
- L137 _public prototype_ `FGuid GetEditLayer() const;` — returns the current layer this interface is working in
- L140 _public prototype_ `bool GetComponentsInRegion(int32 X1, int32 Y1, int32 X2, int32 Y2, TSet<ULandscapeComponent*>* OutComponents = NULL);` — Misc
- L145 _public prototype_ `void SetHeightData(int32 X1, int32 Y1, int32 X2, int32 Y2, const uint16* InData, int32 InStride, bool InCalcNormals, const uint16* InNormalData = nullptr, const uint16* InHeightAlphaBlendData = nullptr, const uint8* InHeightRaiseLowerData = nullptr, bool InCreateComponents = false, UTexture2D* InHeightmap = nullptr, UTexture2D* InXYOffsetmapTexture = nullptr, bool InUpdateBounds = true, bool InUpdateCollision = true, bool InGenerateMips = true);` — Heightmap access
- L149 _public prototype_ `FORCEINLINE uint16 GetHeightMapData(const ULandscapeComponent* Component, int32 TexU, int32 TexV, FColor* TextureData = NULL);` — Helper accessor
- L151 _public prototype_ `FORCEINLINE uint16 GetHeightMapAlphaBlendData(const ULandscapeComponent* Component, int32 TexU, int32 TexV, FColor* TextureData = NULL);` — Helper accessor
- L153 _public prototype_ `FORCEINLINE uint8 GetHeightMapFlagsData(const ULandscapeComponent* Component, int32 TexU, int32 TexV, FColor* TextureData = NULL);` — Helper accessor
- L156 _public prototype_ `template<typename TStoreData> void GetHeightDataTempl(int32& X1, int32& Y1, int32& X2, int32& Y2, TStoreData& StoreData);` — Generic
- L158 _public prototype_ `template<typename TStoreData> void GetHeightAlphaBlendDataTempl(int32& X1, int32& Y1, int32& X2, int32& Y2, TStoreData& StoreData);`
- L160 _public prototype_ `template<typename TStoreData> void GetHeightFlagsDataTempl(int32& X1, int32& Y1, int32& X2, int32& Y2, TStoreData& StoreData);`
- L163 _public prototype_ `template<typename TStoreData> void GetHeightDataTemplFast(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TStoreData& StoreData, UTexture2D* InHeightmap = nullptr, TStoreData* NormalData = NULL);` — Without data interpolation, able to get normal data
- L165 _public prototype_ `void GetHeightData(int32& X1, int32& Y1, int32& X2, int32& Y2, uint16* Data, int32 Stride);` — Implementation for fixed array
- L166 _public prototype_ `void GetHeightDataFast(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, uint16* Data, int32 Stride, uint16* NormalData = NULL, UTexture2D* InHeightmap = nullptr);`
- L167 _public prototype_ `void GetHeightAlphaBlendData(int32& X1, int32& Y1, int32& X2, int32& Y2, uint16* Data, int32 Stride);`
- L168 _public prototype_ `void GetHeightFlagsData(int32& X1, int32& Y1, int32& X2, int32& Y2, uint8* Data, int32 Stride);`
- L170 _public prototype_ `void GetHeightData(int32& X1, int32& Y1, int32& X2, int32& Y2, TMap<FIntPoint, uint16>& SparseData);` — Implementation for sparse array
- L171 _public prototype_ `void GetHeightDataFast(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TMap<FIntPoint, uint16>& SparseData, TMap<FIntPoint, uint16>* NormalData = NULL, UTexture2D* InHeightmap = nullptr);`
- L174 _public prototype_ `void RecalculateNormals();` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")`
- L180 _public prototype_ `FORCEINLINE uint8 GetWeightMapData(const ULandscapeComponent* Component, ULandscapeLayerInfoObject* LayerInfo, int32 TexU, int32 TexV, uint8 Offset = 0, UTexture2D* Texture = NULL, uint8* TextureData = NULL);` — Weightmap access Helper accessor
- L182 _public prototype_ `template<typename TStoreData> void GetWeightDataTempl(ULandscapeLayerInfoObject* LayerInfo, int32& X1, int32& Y1, int32& X2, int32& Y2, TStoreData& StoreData);`
- L185 _public prototype_ `template<typename TStoreData> void GetWeightDataTemplFast(ULandscapeLayerInfoObject* LayerInfo, const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TStoreData& StoreData);` — Without data interpolation
- L187 _public prototype_ `void GetWeightData(ULandscapeLayerInfoObject* LayerInfo, int32& X1, int32& Y1, int32& X2, int32& Y2, uint8* Data, int32 Stride);` — Implementation for fixed array
- L189 _public prototype_ `void GetWeightDataFast(ULandscapeLayerInfoObject* LayerInfo, const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, uint8* Data, int32 Stride);` — void GetWeightData(FName LayerName, int32& X1, int32& Y1, int32& X2, int32& Y2, TArray<uint8>* Data, int32 Stride);
- L190 _public prototype_ `void GetWeightDataFast(ULandscapeLayerInfoObject* LayerInfo, const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TArray<uint8>* Data, int32 Stride);`
- L192 _public prototype_ `void GetWeightData(ULandscapeLayerInfoObject* LayerInfo, int32& X1, int32& Y1, int32& X2, int32& Y2, TMap<FIntPoint, uint8>& SparseData);` — Implementation for sparse array
- L194 _public prototype_ `void GetWeightDataFast(ULandscapeLayerInfoObject* LayerInfo, const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TMap<FIntPoint, uint8>& SparseData);` — void GetWeightData(FName LayerName, int32& X1, int32& Y1, int32& X2, int32& Y2, TMap<uint64, TArray<uint8>>& SparseData);
- L195 _public prototype_ `void GetWeightDataFast(ULandscapeLayerInfoObject* LayerInfo, const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TMap<FIntPoint, TArray<uint8>>& SparseData);`
- L197 _public prototype_ `void SetAlphaData(ULandscapeLayerInfoObject* LayerInfo, const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, const uint8* Data, int32 Stride, ELandscapeLayerPaintingRestriction PaintingRestriction = ELandscapeLayerPaintingRestriction::None);` — Updates weightmap for LayerInfo
- L199 _public prototype_ `void SetAlphaData(ULandscapeLayerInfoObject* LayerInfo, const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, const uint8* Data, int32 Stride, ELandscapeLayerPaintingRestriction PaintingRestriction, bool bWeightAdjust, bool bTotalWeightAdjust);` — `UE_DEPRECATED(5.7, "Support for bWeightAdjust and bTotalWeightAdjust have been removed, this function shall be used anymore")`
- L201 _public prototype_ `void SetAlphaData(const TSet<ULandscapeLayerInfoObject*>& DirtyLayerInfos, const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, const uint8* Data, int32 Stride, ELandscapeLayerPaintingRestriction PaintingRestriction = ELandscapeLayerPaintingRestriction::None);` — Updates weightmaps for all layers. Data points to packed data for all layers in the landscape info
- L203 _public prototype_ `void DeleteLayer(ULandscapeLayerInfoObject* LayerInfo);` — Delete a layer and re-normalize other layers
- L205 _public prototype_ `void FillLayer(ULandscapeLayerInfoObject* LayerInfo);` — Fill a layer and re-normalize other layers
- L207 _public prototype_ `void FillEmptyLayers(ULandscapeLayerInfoObject* LayerInfo);` — Fill all empty layers and re-normalize layers
- L210 _public prototype_ `void ReplaceLayer(ULandscapeLayerInfoObject* FromLayerInfo, ULandscapeLayerInfoObject* ToLayerInfo);` — Replace/merge a layer (across all edit layers and the main runtime layer)
- L213 _public prototype_ `template<typename TStoreData> void GetEditToolTextureData(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TStoreData& StoreData, TFunctionRef<UTexture2D*(ULandscapeComponent*)> GetComponentTexture);`
- L214 _public prototype_ `void SetEditToolTextureData(int32 X1, int32 Y1, int32 X2, int32 Y2, const uint8* Data, int32 Stride, TFunctionRef<UTexture2D*&(ULandscapeComponent*)> GetComponentTexture, TextureGroup InTextureGroup = TEXTUREGROUP_Terrain_Weightmap);`
- L218 _public prototype_ `template<typename TStoreData> void GetSelectDataTempl(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TStoreData& StoreData);` — Without data interpolation, Select Data
- L219 _public prototype_ `void GetSelectData(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, uint8* Data, int32 Stride);`
- L220 _public prototype_ `void GetSelectData(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TMap<FIntPoint, uint8>& SparseData);`
- L221 _public prototype_ `void SetSelectData(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, const uint8* Data, int32 Stride);`
- L224 _public prototype_ `template<typename TStoreData> void GetLayerContributionDataTempl(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TStoreData& StoreData);`
- L225 _public prototype_ `void GetLayerContributionData(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, uint8* Data, int32 Stride);`
- L226 _public prototype_ `void GetLayerContributionData(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TMap<FIntPoint, uint8>& SparseData);`
- L227 _public prototype_ `void SetLayerContributionData(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, const uint8* Data, int32 Stride);`
- L230 _public prototype_ `template<typename TStoreData> void GetDirtyDataTempl(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TStoreData& StoreData);`
- L231 _public prototype_ `void GetDirtyData(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, uint8* Data, int32 Stride);`
- L232 _public prototype_ `void GetDirtyData(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TMap<FIntPoint, uint8>& SparseData);`
- L233 _public prototype_ `void SetDirtyData(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, const uint8* Data, int32 Stride);`
- L236 _public prototype_ `void SetXYOffsetData(int32 X1, int32 Y1, int32 X2, int32 Y2, const FVector2D* Data, int32 Stride);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")`
- L238 _public prototype_ `void SetXYOffsetData(int32 X1, int32 Y1, int32 X2, int32 Y2, const FVector* Data, int32 Stride);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")`
- L241 _public prototype_ `FORCEINLINE FVector2D GetXYOffsetmapData(const ULandscapeComponent* Component, int32 TexU, int32 TexV, FColor* TextureData = NULL);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")` — Helper accessor
- L244 _public prototype_ `void GetXYOffsetData(int32& X1, int32& Y1, int32& X2, int32& Y2, FVector2D* Data, int32 Stride);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")`
- L246 _public prototype_ `void GetXYOffsetData(int32& X1, int32& Y1, int32& X2, int32& Y2, TMap<FIntPoint, FVector2D>& SparseData);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")`
- L248 _public prototype_ `void GetXYOffsetData(int32& X1, int32& Y1, int32& X2, int32& Y2, FVector* Data, int32 Stride);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")`
- L250 _public prototype_ `void GetXYOffsetData(int32& X1, int32& Y1, int32& X2, int32& Y2, TMap<FIntPoint, FVector>& SparseData);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")`
- L254 _public prototype_ `void GetXYOffsetDataFast(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, FVector2D* Data, int32 Stride);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")` — Without data interpolation, able to get normal data
- L256 _public prototype_ `void GetXYOffsetDataFast(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TMap<FIntPoint, FVector2D>& SparseData);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")`
- L258 _public prototype_ `void GetXYOffsetDataFast(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, FVector* Data, int32 Stride);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")`
- L260 _public prototype_ `void GetXYOffsetDataFast(const int32 X1, const int32 Y1, const int32 X2, const int32 Y2, TMap<FIntPoint, FVector>& SparseData);` — `UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes")`
- L263 _public prototype_ `template<typename T> static void ShrinkData(TArray<T>& Data, int32 OldMinX, int32 OldMinY, int32 OldMaxX, int32 OldMaxY, int32 NewMinX, int32 NewMinY, int32 NewMaxX, int32 NewMaxY);`
- L265 _public prototype_ `const ALandscape* GetTargetLandscape() const;`
- L268 _public prototype_ `bool CanHaveLandscapeLayersContent() const;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")`
- L270 _public prototype_ `bool HasLandscapeLayersContent() const;` — `UE_DEPRECATED(5.7, "Non-edit layer landscapes are deprecated, all landscapes use the edit layer system now.")`
- L273 _private member_ `int32 ComponentSizeQuads;`
- L274 _private member_ `int32 SubsectionSizeQuads;`
- L275 _private member_ `int32 ComponentNumSubsections;`
- L276 _private member_ `FVector DrawScale;`
- L278 _private member_ `ULandscapeInfo* LandscapeInfo;`
- L281 _private member_ `bool bUseSharedLandscapeEditLayer;` — if true, we use the LandscapeActor->PrivateEditingLayer, otherwise we use the LocalEditLayerGUID specified below
- L282 _private member_ `FGuid LocalEditLayerGUID;`
- L284 _private prototype_ `void FillLayer(ULandscapeLayerInfoObject* LayerInfo, bool bEmptyLayersOnly);`
- L288 _private prototype_ `template<typename TData, typename TStoreData, typename FType> void CalcMissingValues(const int32 X1, const int32 X2, const int32 Y1, const int32 Y2, const int32 ComponentIndexX1, const int32 ComponentIndexX2, const int32 ComponentIndexY1, const int32 ComponentIndexY2, const int32 ComponentSizeX, const int32 ComponentSizeY, TData* CornerValues, TArray<bool>& NoBorderY1, TArray<bool>& NoBorderY2, TArray<bool>& ComponentDataExist, TStoreData& StoreData);` — Only for Missing Data interpolation... only internal usage
- L295 _private prototype_ `template<typename TStoreData, typename TGetHeightMapDataFunction> void GetHeightDataInternal(int32& ValidX1, int32& ValidY1, int32& ValidX2, int32& ValidY2, TStoreData& StoreData, TGetHeightMapDataFunction GetHeightMapDataFunction);` — Generic Height Data access
- L297 _private prototype_ `FORCEINLINE const FColor& GetHeightMapColor(const ULandscapeComponent* Component, int32 TexU, int32 TexV, FColor* TextureData);`
- L300 _private prototype_ `inline bool IsLayerAllowed(const ULandscapeLayerInfoObject* LayerInfo, int32 ComponentIndexX, int32 SubIndexX, int32 SubX, int32 ComponentIndexY, int32 SubIndexY, int32 SubY);` — test if layer is allowed for a given texel
- L331 _function_ `template<typename T> void FLandscapeEditDataInterface::ShrinkData(TArray<T>& Data, int32 OldMinX, int32 OldMinY, int32 OldMaxX, int32 OldMaxY, int32 NewMinX, int32 NewMinY, int32 NewMaxX, int32 NewMaxY)`

#### struct `FLandscapeDoNotDirtyScope`  
`struct FLandscapeDoNotDirtyScope`  
_L305-328_
- L307 _public function_ `FLandscapeDoNotDirtyScope(FLandscapeEditDataInterface& InEditInterface, bool bInScopeEnabled = true) : EditInterface(InEditInterface), bScopeEnabled(bInScopeEnabled)`
- L317 _public function_ `~FLandscapeDoNotDirtyScope()`
- L325 _public member_ `FLandscapeEditDataInterface& EditInterface;`
- L326 _public member_ `bool bPreviousValue;`
- L327 _public member_ `bool bScopeEnabled;`

#### struct `FHeightmapAccessor`  
`template<bool bInUseInterp> struct FHeightmapAccessor`  
_L361-496_
- desc: FHeightmapAccessor
- L364 _public function_ `FHeightmapAccessor(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo = nullptr) : LandscapeInfo(InLandscapeInfo) , LandscapeEdit(InLandscapeInfo)`
- L372 _public prototype_ `FHeightmapAccessor(FHeightmapAccessor&& InOther) = default;`
- L373 _public prototype_ `FHeightmapAccessor& operator = (FHeightmapAccessor&& InOther) = default;`
- L374 _public prototype_ `FHeightmapAccessor(const FHeightmapAccessor& InOther) = delete;`
- L375 _public prototype_ `FHeightmapAccessor& operator = (const FHeightmapAccessor& InOther) = delete;`
- L377 _public function_ `void SetEditLayer(const FGuid& InEditLayerGUID)`
- L382 _public function_ `FGuid GetEditLayer() const`
- L388 _public function_ `void GetData(int32& X1, int32& Y1, int32& X2, int32& Y2, TMap<FIntPoint, uint16>& Data)` — accessors
- L393 _public function_ `void GetData(int32& X1, int32& Y1, int32& X2, int32& Y2, uint16* Data)`
- L398 _public function_ `void GetDataFast(int32 X1, int32 Y1, int32 X2, int32 Y2, TMap<FIntPoint, uint16>& Data)`
- L403 _public function_ `void GetDataFast(int32 X1, int32 Y1, int32 X2, int32 Y2, uint16* Data)`
- L411 _public function_ `static bool GetSelectiveLayerData(ALandscape* Landscape, FIntRect EvalRect, TBitArray<> ActiveEditLayers, TArrayView<uint16> OutData)` — Render the heightmap with overrides on edit layer visibility.  Does not modify persistent landscape data like FLandscapeEditDataInterface does. This function exists mainly as a template customization point to handle uint16 for heights and uint8 for weights. EvalRect is half-open.
- L421 _public function_ `void SetData(int32 X1, int32 Y1, int32 X2, int32 Y2, const uint16* Data, ELandscapeLayerPaintingRestriction PaintingRestriction = ELandscapeLayerPaintingRestriction::None)`
- L481 _public function_ `void Flush()`
- L486 _public function_ `virtual ~FHeightmapAccessor()`
- L493 _private member_ `ULandscapeInfo* LandscapeInfo;`
- L494 _private member_ `FLandscapeEditDataInterface LandscapeEdit;`
- L495 _private member_ `TSet<ULandscapeComponent*> ChangedComponents;`

#### enum `FHeightmapAccessor::(anonymous)`  
`enum`  
_L363-363_

#### struct `TAlphamapAccessor`  
`template<bool bInUseInterp> struct TAlphamapAccessor`  
_L502-581_
- desc: TAlphamapAccessor
- L505 _public function_ `TAlphamapAccessor(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo) : LandscapeInfo(InLandscapeInfo) , LandscapeEdit(InLandscapeInfo) , LayerInfo(InLayerInfo)`
- L513 _public prototype_ `TAlphamapAccessor(TAlphamapAccessor&& InOther) = default;`
- L514 _public prototype_ `TAlphamapAccessor& operator = (TAlphamapAccessor&& InOther) = default;`
- L515 _public prototype_ `TAlphamapAccessor(const TAlphamapAccessor& InOther) = delete;`
- L516 _public prototype_ `TAlphamapAccessor& operator = (const TAlphamapAccessor& InOther) = delete;`
- L518 _public function_ `void GetData(int32& X1, int32& Y1, int32& X2, int32& Y2, TMap<FIntPoint, uint8>& Data)`
- L523 _public function_ `void GetData(int32& X1, int32& Y1, int32& X2, int32& Y2, uint8* Data)`
- L528 _public function_ `void GetDataFast(int32 X1, int32 Y1, int32 X2, int32 Y2, TMap<FIntPoint, uint8>& Data)`
- L533 _public function_ `void GetDataFast(int32 X1, int32 Y1, int32 X2, int32 Y2, uint8* Data)`
- L538 _public function_ `static bool GetSelectiveLayerData(ALandscape* Landscape, FIntRect EvalRect, TBitArray<> ActiveEditLayers, TArrayView<uint8> OutData)`
- L544 _public function_ `void SetData(int32 X1, int32 Y1, int32 X2, int32 Y2, const uint8* Data, ELandscapeLayerPaintingRestriction PaintingRestriction)`
- L560 _public function_ `void Flush()`
- L565 _public function_ `void SetEditLayer(const FGuid& InEditLayerGUID)`
- L570 _public function_ `FGuid GetEditLayer() const`
- L576 _private member_ `ULandscapeInfo* LandscapeInfo;`
- L577 _private member_ `FLandscapeEditDataInterface LandscapeEdit;`
- L578 _private member_ `TSet<ULandscapeComponent*> ModifiedComponents;`
- L579 _private member_ `ULandscapeLayerInfoObject* LayerInfo;`
- L580 _private member_ `bool bPerformLegacyWeightBalancing;`

#### enum `TAlphamapAccessor::(anonymous)`  
`enum`  
_L504-504_

#### struct `FAlphamapAccessor`  
`template<bool bInUseInterp, bool bInUseTotalNormalize> struct UE_DEPRECATED(5.7, "Use TAlphamapAccessor instead") FAlphamapAccessor : public TAlphamapAccessor<bInUseInterp>`  
_L584-586_
- inherits: `TAlphamapAccessor<bInUseInterp>`

#### Free symbols / members of external scopes

- L363 _enumerator_ `enum { bUseInterp = bInUseInterp }; FHeightmapAccessor(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo = nullptr) : LandscapeInfo(InLandscapeInfo)` (scope `FHeightmapAccessor::__anonf7fcefb80103`)
- L504 _enumerator_ `enum { bUseInterp = bInUseInterp }; TAlphamapAccessor(ULandscapeInfo* InLandscapeInfo, ULandscapeLayerInfoObject* InLayerInfo) : LandscapeInfo(InLandscapeInfo)` (scope `TAlphamapAccessor::__anonf7fcefb80203`)

### `Source/Runtime/Landscape/Public/LandscapeEditLayerMergeContext.h` (Public)


#### class `UE::Landscape::EditLayers::FMergeContext`  
`class FMergeContext`  
_L32-242_
- desc: Global info about the landscape being merged that can be used throughout the merge.
- L37 _public typedef_ `using FTargetLayerGroupsPerBlendingMethod = TStaticArray<TArray<FTargetLayerGroup>, static_cast<uint8>(ELandscapeTargetLayerBlendMethod::Count)>;`
- L39 _public prototype_ `FMergeContext(ALandscape* InLandscape, bool bInIsHeightmapMerge, bool bInSkipProceduralRenderers);`
- L40 _public prototype_ `virtual ~FMergeContext() = default;`
- L41 _public prototype_ `FMergeContext(const FMergeContext& Other) = default;`
- L42 _public prototype_ `FMergeContext(FMergeContext&& Other) = default;`
- L43 _public prototype_ `FMergeContext& operator=(const FMergeContext& Other) = default;`
- L44 _public prototype_ `FMergeContext& operator=(FMergeContext&& Other) = default;`
- L46 _public function_ `inline ALandscape* GetLandscape() const`
- L48 _public function_ `inline ULandscapeInfo* GetLandscapeInfo() const`
- L53 _public function_ `inline const TArray<FName>& GetAllTargetLayerNames() const` — @return all target layer names declared in this context, including ones that are potentially invalid (i.e. no layer info associated)
- L58 _public prototype_ `TArray<FName> GetValidTargetLayerNames() const;` — @return all target layer names that have a valid layer info object. Will return the height layer in the case of a heightmap merge, even though there's no layer info for those :
- L63 _public function_ `inline const TArray<ULandscapeLayerInfoObject*>& GetAllWeightmapLayerInfos() const` — @return all layer info objects declared in this context (can contain null entries for invalid layers or in the case of a heightmap merge)
- L68 _public function_ `inline bool IsHeightmapMerge() const` — @return true if this merge context is used for a heightmap merge, false otherwise (visibility / weightmap)
- L73 _public function_ `inline bool ShouldSkipProceduralRenderers() const` — @return true if this merge context is used for a heightmap merge, false otherwise (visibility / weightmap)
- L78 _public prototype_ `int32 IsValidTargetLayerName(const FName& InName) const;` — @return true if the target layer name is registered to this merge context and has an associated layer info object
- L83 _public prototype_ `int32 IsValidTargetLayerNameChecked(const FName& InName) const;` — @return true if the target layer name has an associated layer info object. Asserts if the layer name isn't known to the merge context
- L89 _public prototype_ `int32 IsTargetLayerIndexValid(int32 InIndex) const;` — @return true if the target layer index is valid in the list of declared target layers on the merge context. Important note : it doesn't mean that it's associated with a valid layer info object, use IsValidTargetLayerName for this!
- L94 _public prototype_ `int32 GetTargetLayerIndexForName(const FName& InName) const;` — @return the index of this target layer name in this context, INDEX_NONE if not found
- L99 _public prototype_ `int32 GetTargetLayerIndexForNameChecked(const FName& InName) const;` — @return the index of this target layer name in this context. Asserts if the layer name isn't known to the merge context
- L104 _public prototype_ `FName GetTargetLayerNameForIndex(int32 InIndex) const;` — @return the target layer name corresponding to the index in this context, NAME_None if not found
- L109 _public prototype_ `FName GetTargetLayerNameForIndexChecked(int32 InIndex) const;` — @return the target layer name corresponding to the index in this context, NAME_None if not found. Asserts if the layer index isn't known to the merge context
- L114 _public prototype_ `int32 GetTargetLayerIndexForLayerInfo(ULandscapeLayerInfoObject* InLayerInfo) const;` — @return the index of this landscape layer info in this context, INDEX_NONE if not found
- L119 _public prototype_ `int32 GetTargetLayerIndexForLayerInfoChecked(ULandscapeLayerInfoObject* InLayerInfo) const;` — @return the index of this landscape layer info in this context. Asserts if the layer info isn't known to the merge context
- L124 _public prototype_ `ULandscapeLayerInfoObject* GetTargetLayerInfoForName(const FName& InName) const;` — @return the landscape layer object corresponding to the target layer name in this context, nullptr if not found
- L129 _public prototype_ `ULandscapeLayerInfoObject* GetTargetLayerInfoForNameChecked(const FName& InName) const;` — @return the landscape layer object corresponding to the target layer name in this context. Asserts if the layer name isn't known to the merge context
- L134 _public prototype_ `ULandscapeLayerInfoObject* GetTargetLayerInfoForIndex(int32 InIndex) const;` — @return the landscape layer object corresponding to the index in this context, nullptr if not found. Asserts if the layer index isn't known to the merge context
- L139 _public prototype_ `TBitArray<> ConvertTargetLayerNamesToBitIndices(TConstArrayView<FName> InTargetLayerNames) const;` — @return a TBitArray<> where, for each layer from InTargetLayerNames that is found in this context, the corresponding bit is set
- L144 _public prototype_ `TBitArray<> ConvertTargetLayerNamesToBitIndicesChecked(TConstArrayView<FName> InTargetLayerNames) const;` — @return a TBitArray<> where, for each layer from InTargetLayerNames that is found in this context, the corresponding bit is set. Asserts if one of the layer names isn't known to the merge context
- L149 _public prototype_ `TArray<FName> ConvertTargetLayerBitIndicesToNames(const TBitArray<>& InTargetLayerBitIndices) const;` — @return a list of target layer names for each set bit in InTargetLayerBitIndices. Asserts if InTargetLayerBitIndices isn't the same size as AllTargetLayerNames
- L154 _public prototype_ `TArray<ULandscapeLayerInfoObject*> ConvertTargetLayerBitIndicesToLayerInfos(const TBitArray<>& InTargetLayerBitIndices) const;` — @return a list of landscape layer info objects for each set bit in InTargetLayerBitIndices. Asserts if InTargetLayerBitIndices isn't the same size as AllTargetLayerNames
- L164 _public prototype_ `void ForEachTargetLayer(const TBitArray<>& InTargetLayerBitIndices, TFunctionRef<bool(int32 , const FName& , ULandscapeLayerInfoObject* )> Fn) const;` — Runs the given function for each all valid target layer in the bit indices in parameters, with the possibility of early exit Most easily used with a lambda as follows: ForEachTargetLayer([](int32 InTargetLayerIndex, FName InTargetLayerName) -> bool { return continueLoop ? true : false; });
- L167 _public prototype_ `void ForEachValidTargetLayer(TFunctionRef<bool(int32 , const FName& , ULandscapeLayerInfoObject* )> Fn) const;` — Same as ForEachTargetLayer but skips over invalid target layers
- L172 _public function_ `inline int32 GetVisibilityTargetLayerIndex() const` — @return the index corresponding to the visibility target layer in AllTargetLayerNames, INDEX_NONE if it's not in the list of layers
- L177 _public function_ `inline const TBitArray<>& GetVisibilityTargetLayerMask() const` — @return a bit mask the size of AllTargetLayerNames, where all bits are set to zero except the one corresponding to the visibility target layer
- L180 _public function_ `inline const TBitArray<>& GetNegatedVisibilityTargetLayerMask() const` — Same as GetVisibilityTargetLayerMask() but negated
- L185 _public function_ `inline const TBitArray<>& GetValidTargetLayerBitIndices() const` — @return a bit mask for all target layers from AllTargetLayerNames that have a valid landscape layer info object
- L190 _public prototype_ `TBitArray<> BuildTargetLayerBitIndices(bool bInBitValue) const;` — @return a bit mask the size of AllTargetLayerNames, where all bits are set to bBitValue
- L192 _public function_ `const FTargetLayerGroupsPerBlendingMethod& GetTargetLayerGroupsPerBlendingMethod() const`
- L198 _public prototype_ `TArray<FTargetLayerGroup> BuildGenericBlendTargetLayerGroups(const TBitArray<>& InTargetLayerBitIndices) const;` — Return the target layer groups for the renderers performing the generic blend. This concerns only the blend methods that are applied per renderer @param InTargetLayerBitIndices bit mask of the target layers that are concerned by this blend
- L201 _private prototype_ `void FinalizeTargetLayerGroupsPerBlendingMethod();`
- L202 _private prototype_ `TArray<FTargetLayerGroup> GatherTargetLayerGroupsForBlendMethod(ELandscapeTargetLayerBlendMethod InBlendMethod) const;`
- L209 _protected member_ `bool bIsHeightmapMerge = false;` — Type of merge being requested
- L212 _protected member_ `bool bSkipProceduralRenderers = false;` — Allows to skip all non-default (i.e. persistent edit layer) layer renderers for this merge. Mostly there for backwards compatibility and debugging purposes.
- L215 _protected member_ `ALandscape* Landscape = nullptr;` — Landscape being merged
- L218 _protected member_ `ULandscapeInfo* LandscapeInfo = nullptr;` — Landscape info associated with the landscape being merged
- L223 _protected member_ `TArray<FName> AllTargetLayerNames;` — List of all target layer names that can possibly be rendered on this landscape (even invalid ones). The index of the target layer in that list is important : it allows to use a TBitArray instead of a TSet to designate a list of target layers all throughout the merge, which greatly accelerates all the intersection tests being made. If merging heightmaps, it contains a single name (that is only meaningful for debug display).
- L226 _protected member_ `TBitArray<> VisibilityTargetLayerMask;` — Bit mask that corresponds to only the visibility layer
- L229 _protected member_ `TBitArray<> NegatedVisibilityTargetLayerMask;` — Bit mask that corresponds to all target layers except the visibility layer
- L232 _protected member_ `TArray<ULandscapeLayerInfoObject*> AllWeightmapLayerInfos;` — Per-target layer info. Same size as AllTargetLayerNames (only meaningful when rendering weightmaps)
- L235 _protected member_ `TBitArray<> ValidTargetLayerBitIndices;` — List of valid target layers. If a target layer name is present here, it's because it has a valid landscape layer info object. Each bit in that bit array corresponds to an entry in AllTargetLayerNames
- L238 _protected member_ `FTargetLayerGroupsPerBlendingMethod TargetLayerGroupsPerBlendingMethod;` — Contains the list of target layer groups for each weight-blending method as defined by the landscape layer info objects
- L241 _protected member_ `int32 VisibilityTargetLayerIndex = INDEX_NONE;` — Index of the visibility layer in AllTargetLayerNames (always valid for weightmap merges)

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Landscape` (scope `UE`)
- L17 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Landscape` (scope `UE`)
- L24 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)

### `Source/Runtime/Landscape/Public/LandscapeEditLayerMergeRenderBlackboardItem.h` (Public)


#### struct `FLandscapeEditLayerMergeRenderBlackboardItem`  
`struct FLandscapeEditLayerMergeRenderBlackboardItem`  
_L17-22_
- reflection: `USTRUCT(meta = (Abstract))`
- desc: Base class for various blackboard items that can be attached to FMergeRenderContext in order to transfer temporary information between renderers. It's a USTRUCT only to benefit from the RTTI services provided by TInstancedStruct
- L21 _public prototype_ `virtual ~FLandscapeEditLayerMergeRenderBlackboardItem() = default;`

### `Source/Runtime/Landscape/Public/LandscapeEditLayerMergeRenderContext.h` (Public)


#### struct `UE::Landscape::EditLayers::FMergeRenderParams`  
`struct FMergeRenderParams`  
_L52-67_
- desc: Params struct passed to the merge function. It contains everything needed for requesting a given set of target layers (for weightmaps) on a given number of components and for a certain configuration of edit layers Note that this is what is requested by the caller, but in practice, there might be more renderers (e.g. some might get added e.g. legacy weight-blending, some removed because they turn out to be disabled...) and more weightmaps being rendered (e.g. a requested weightmap might depend on another one that has not been requested), or less (e.g. a requested weightmap is actually invalid) :
- L54 _public prototype_ `FMergeRenderParams(TArray<ULandscapeComponent*> InComponentsToMerge, const TArrayView<FEditLayerRendererState>& InEditLayerRendererStates, const TSet<FName>& InWeightmapLayerNames = {}, bool bInRequestAllLayers = false);`
- L57 _public member_ `TArray<ULandscapeComponent*> ComponentsToMerge;` — List of components that need merging
- L60 _public member_ `TArray<FEditLayerRendererState> EditLayerRendererStates;` — Requested states for every edit layer renderer participating to the merge
- L63 _public member_ `TSet<FName> WeightmapLayerNames;` — List of weightmap layers being requested.
- L66 _public member_ `bool bRequestAllLayers = false;` — Ignore the computed list of requested layers and instead request all valid layers

#### struct `UE::Landscape::EditLayers::FMergeRenderStep`  
`struct FMergeRenderStep`  
_L75-129_
- desc: Defines an individual render step of the batch merge
- L94 _public function_ `FMergeRenderStep(EType InType) : Type(InType)`
- L99 _public function_ `FMergeRenderStep(EType InType, const TBitArray<>& InTargetLayerGroupBitIndices, const TArrayView<ULandscapeComponent*>& InComponentsToRender) : Type(InType) , TargetLayerGroupBitIndices(InTargetLayerGroupBitIndices) , ComponentsToRender(InComponentsToRender)`
- L105 _public function_ `FMergeRenderStep(EType InType, ERenderFlags InRenderFlags, const FEditLayerRendererState& InRendererState, const TBitArray<>& InTargetLayerGroupBitIndices, const TArrayView<ULandscapeComponent*>& InComponentsToRender) : Type(InType) , RenderFlags(InRenderFlags) , RendererState(InRendererState) , TargetLayerGroupBitIndices(InTargetLayerGroupBitIndices) , ComponentsToRender(InComponentsToRender)`
- L114 _public member_ `EType Type = EType::Invalid;` — Type of operation for this step
- L117 _public member_ `ERenderFlags RenderFlags = ERenderFlags::None;` — The render flags corresponding to this state
- L121 _public member_ `FEditLayerRendererState RendererState = FEditLayerRendererState::GetDummyRendererState();` — Renderer state to be used this step. This includes the renderer as well as its precise step (e.g. which weightmap are supported? which are enabled?)
- L125 _public member_ `TBitArray<> TargetLayerGroupBitIndices;` — List of target layers being involved in this step. Each bit in that bit array corresponds to an entry in FMergeContext's AllTargetLayerNames
- L128 _public member_ `TArray<ULandscapeComponent*> ComponentsToRender;` — List of components involved in this step

#### enum `UE::Landscape::EditLayers::FMergeRenderStep::EType`  
`enum class EType`  
_L78-92_
- desc: Describes what kind of operation this render step executes. Despite some of the names in there, those steps all run on the game thread but the _RenderThread ones will defer operations to the render thread.
- L80 _public enumerator_ `Invalid`
- L82 _public enumerator_ `BeginRenderCommandRecorder` — Initiates a render command recorder that will batch one or several RenderLayer_Recorded operations, runs on the game thread
- L83 _public enumerator_ `EndRenderCommandRecorder` — Ends the render command recorder initiated by the last BeginRenderCommandRecorder, runs on the game thread but this is where the render command executing the recorded operations from (several) RenderLayer_Recorded step(s) will be pushed (on the render thread, this is where the FRDBuilder is created 
- L85 _public enumerator_ `BeginRenderLayerGroup` — Initiates a series of RenderLayer steps for renderers that can be rendered one after another without an intermediate BlendLayer. Triggers a call to BeginRenderLayerGroup() on the first renderer in the group
- L86 _public enumerator_ `EndRenderLayerGroup` — Ends a series of RenderLayer steps for renderers that can be rendered one after another without an intermediate BlendLayer. Triggers a call to EndRenderLayerGroup() on the last renderer in the group
- L88 _public enumerator_ `RenderLayer` — Performs the rendering of a target layer group on an edit layer on a given world region (i.e. in a batch), runs on the game thread. Use the command recorder to perform the render operations. In RenderMode_Recorded, these will be delayed until EndRenderCommandRecorder
- L89 _public enumerator_ `BlendLayer` — Performs the rendering of a target layer group on an edit layer on a given world region (i.e. in a batch), runs on the game thread. Use the command recorder to perform the render operations. In RenderMode_Recorded, these will be delayed until EndRenderCommandRecorder
- L91 _public enumerator_ `SignalBatchMergeGroupDone` — Final step when rendering a target layer group on a given world region (i.e. in a batch) : runs on the game thread and allows to retrieve the result of the merge and do something with it (e.g. resolve the final textures)

#### struct `UE::Landscape::EditLayers::FMergeRenderBatch`  
`struct FMergeRenderBatch`  
_L138-211_
- desc: Defines an individual render batch when merging the landscape. A batch corresponds to a target layer group on a world's region, i.e. a set of weightmaps (or the heightmap) to render on a portion of the world. Each batch is composed of a series of render steps.
- L140 _public prototype_ `bool operator < (const FMergeRenderBatch& InOther) const;`
- L142 _public member_ `ALandscape* Landscape = nullptr;`
- L145 _public member_ `FIntRect LandscapeExtent;` — Entire section of the the landscape currently loaded (in landscape vertex coordinates, inclusive bounds)
- L148 _public member_ `FIntRect SectionRect;` — Section of the landscape being covered by this batch (in landscape vertex coordinates, inclusive bounds)
- L152 _public member_ `FIntPoint Resolution = FIntPoint(ForceInitToZero);` — TODO [jonathan.bard] : rename EffectiveResolution and make private maybe?
- L154 _public member_ `FIntPoint MinComponentKey = FIntPoint(MAX_int32, MAX_int32);`
- L155 _public member_ `FIntPoint MaxComponentKey = FIntPoint(MIN_int32, MIN_int32);`
- L158 _public member_ `TArray<FMergeRenderStep> RenderSteps;` — Sequential list of rendering operations that need to be performed to fully render this batch
- L161 _public member_ `TSet<ULandscapeComponent*> ComponentsToRender;` — List of all components involved in this batch
- L164 _public member_ `TBitArray<> TargetLayerBitIndices;` — List of all target layers being rendered in this batch (i.e. bitwise OR of all of the render steps' TargetLayerGroupBitIndices). Each bit in that bit array corresponds to an entry in FMergeRenderContext's AllTargetLayerNames
- L168 _public member_ `TMap<ULandscapeComponent*, TBitArray<>> ComponentToTargetLayerBitIndices;` — List of components involved in this batch and the target layers they're writing to (redundant with ComponentsToRender but we keep the latter for convenience) (each bit corresponds to a target layer name in FMergeContext's AllTargetLayerNames)
- L171 _public member_ `TArray<TSet<ULandscapeComponent*>> TargetLayersToComponents;` — Reverse lookup of ComponentToTargetLayerBitIndices : one entry per element in ComponentToTargetLayerBitIndices, each entry containing all of the components involved in this merge for this target layer
- L174 _public prototype_ `FIntPoint GetRenderTargetResolution(bool bInWithDuplicateBorders) const;`
- L185 _public prototype_ `int32 ComputeSubsectionRects(ULandscapeComponent* InComponent, TArray<FIntRect, TInlineAllocator<4>>& OutSubsectionRects, TArray<FIntRect, TInlineAllocator<4>>& OutSubsectionRectsWithDuplicateBorders) const;` — Find the area in the render batch render target corresponding to each of the subsections of this component @param InComponent Which component to compute the subsection rects for @param OutSubsectionRects List of (up to 4) subsection rects when *not* taking into account duplicate borders (inclusive bounds) @param OutSubsectionRectsWithDuplicateBorders List of (up to 4) subsection rects when taking into account duplicate borders (inclusive bounds) @param bInWithDuplicateBorders indicates whether the rect coordinates should include the duplicated column/row at the end of the subsection or not @return number of subsections
- L194 _public prototype_ `FIntRect ComputeSectionRect(ULandscapeComponent* InComponent, bool bInWithDuplicateBorders) const;` — Find the area in the render batch render target corresponding to this component @param InComponent Which component to compute the section rect for @param bInWithDuplicateBorders indicates whether the rect coordinates should include the duplicated columns/rows at the end of each subsection or not @Return the section rect (inclusive bounds)
- L200 _public prototype_ `TArray<FIntRect> ComputeAllComponentSectionRects(bool bInWithDuplicateBorders) const;` — Returns all subregions of the render batch representing valid data. @param bInWithDuplicateBorders indicates whether the rect coordinates should include the duplicated columns/rows at the end of each subsection or not
- L207 _public prototype_ `void ComputeAllSubsectionRects(TArray<FIntRect>& OutSubsectionRects, TArray<FIntRect>& OutSubsectionRectsWithDuplicateBorders) const;` — Compute the rects corresponding to the sub-sections that need to be read from and written to when expanding the render target (inclusive bounds) @param OutSubsectionRects List of all subsection rects when *not* taking into account duplicate borders (inclusive bounds) @param OutSubsectionRectsWithDuplicateBorders List of all subsection rects when taking into account duplicate borders (inclusive bounds)
- L210 _public prototype_ `uint32 ComputeComponentLinearIndex(const FIntPoint& InComponentKey) const;` — Compute the component's linear index within that batch starting from the upper-left corner. This ensures a deterministic order within batch

#### struct `UE::Landscape::EditLayers::FComponentMergeRenderInfo`  
`struct FComponentMergeRenderInfo`  
_L219-231_
- desc: Utility struct for attaching some information that pertains to a given landscape component in the context of a batch render
- L222 _public member_ `ULandscapeComponent* Component = nullptr;` — Component to render
- L225 _public member_ `FIntRect ComponentRegionInRenderArea;` — Texture region that corresponds to this component in the render area's render target
- L228 _public member_ `FIntPoint ComponentKeyInRenderArea = FIntPoint(ForceInitToZero);` — Index of the component in the render area's render target
- L230 _public prototype_ `bool operator < (const FComponentMergeRenderInfo& InOther) const;`

#### struct `UE::Landscape::EditLayers::FRenderParams`  
`struct FRenderParams`  
_L237-274_
- desc: Struct passed to ILandscapeEditLayerRenderer's render functions. This would normally be an inner struct of ILandscapeEditLayerRenderer but this prevents forward-declaration so we leave in the UE::Landscape::EditLayers namespace instead.
- L239 _public prototype_ `FRenderParams(FMergeRenderContext* InMergeRenderContext, const TArrayView<FName>& InTargetLayerGroupLayerNames, const TArrayView<ULandscapeLayerInfoObject*>& InTargetLayerGroupLayerInfos, const FEditLayerRendererState& InRendererState, const TArrayView<FComponentMergeRenderInfo>& InSortedComponentMergeRenderInfos, const FTransform& InRenderAreaWorldTransform, const FIntRect& InRenderAreaSectionRect, int32 InNumSuccessfulRenderLayerStepsUntilBlendLayerStep);`
- L249 _public member_ `FMergeRenderContext* MergeRenderContext = nullptr;` — Merge context
- L252 _public member_ `TArray<FName> TargetLayerGroupLayerNames;` — List of target layers being involved in this step
- L255 _public member_ `TArray<ULandscapeLayerInfoObject*> TargetLayerGroupLayerInfos;` — List of target layer info objects being involved in this step (same size as TargetLayerGroupLayerNames)
- L260 _public member_ `FEditLayerRendererState RendererState;` — Full state for the renderer involved in this step. This allows to retrieve the exact state of this renderer (e.g. enabled weightmaps, which can be different than the target layer group, in that target layers A, B and C might belong to the same group but this renderer actually only has A enabled). This is therefore the renderer's responsibility to check that a given target layer from the target layer group is effectively enabled.
- L263 _public member_ `TArray<FComponentMergeRenderInfo> SortedComponentMergeRenderInfos;` — List of components (with additional info) to render
- L267 _public member_ `FTransform RenderAreaWorldTransform;` — World transform that corresponds to the origin (bottom left corner) of the render area. The scale corresponds to the size of each quad in the landscape.
- L270 _public member_ `FIntRect RenderAreaSectionRect;` — SectionRect (i.e. landscape vertex coordinates, in landscape space) that corresponds to this render area
- L273 _public member_ `int32 NumSuccessfulRenderLayerStepsUntilBlendLayerStep = 0;` — When separate blend is enabled, tracks how many RenderLayer calls have succeeded yet (valid until the BlendLayer step occurs)

#### class `UE::Landscape::EditLayers::FMergeRenderContext`  
`class FMergeRenderContext : public FMergeContext`  
_L282-484_
- inherits: `FMergeContext`
- desc: Utility class that contains everything necessary to perform the batched merge : scratch render targets, list of batches, etc.
- L287 _public prototype_ `FMergeRenderContext(const FMergeContext& InMergeContext);`
- L288 _public prototype_ `virtual ~FMergeRenderContext();`
- L289 _public prototype_ `FMergeRenderContext(const FMergeRenderContext& Other) = default;`
- L290 _public prototype_ `FMergeRenderContext(FMergeRenderContext&& Other) = default;`
- L291 _public prototype_ `FMergeRenderContext& operator=(const FMergeRenderContext& Other) = default;`
- L292 _public prototype_ `FMergeRenderContext& operator=(FMergeRenderContext&& Other) = default;`
- L294 _public prototype_ `bool IsValid() const;`
- L305 _public prototype_ `void CycleBlendRenderTargets(UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder);` — Cycle between the 3 render targets used for blending: Write becomes Read -> Read becomes ReadPrevious -> ReadPrevious becomes Write The new Write RT will be transitioned to state == InDesiredWriteAccess (if != ERHIAccess::None) The new Read RT will be transitioned to state ERHIAccess::SRVMask The new ReadPrevious RT will stay in state ERHIAccess::SRVMask @param RDGBuilderRecorder recorder to append operations to a single FRDGBuilder, if the the recorder in "recording" mode. In "immediate" mode, a render command will be enqueued immediately
- L307 _public prototype_ `ULandscapeScratchRenderTarget* GetBlendRenderTargetWrite() const;`
- L308 _public prototype_ `ULandscapeScratchRenderTarget* GetBlendRenderTargetRead() const;`
- L309 _public prototype_ `ULandscapeScratchRenderTarget* GetBlendRenderTargetReadPrevious() const;`
- L310 _public prototype_ `ULandscapeScratchRenderTarget* GetComponentIdRenderTarget() const;`
- L336 _public prototype_ `void Render(TFunction<void(const FOnRenderBatchTargetGroupDoneParams& , UE::Landscape::FRDGBuilderRecorder& )> OnRenderBatchTargetGroupDone);`
- L338 _public member_ `static constexpr uint8 ComponentLinearIdBitCount = 32;`
- L339 _public member_ `static constexpr uint32 MaxComponentsPerBatch = static_cast<uint32>(1u << (ComponentLinearIdBitCount - 1));`
- L341 _public function_ `inline FIntPoint GetMaxNeededResolution() const`
- L342 _public function_ `inline const TArray<FMergeRenderBatch>& GetRenderBatches() const`
- L343 _public prototype_ `const FMergeRenderBatch* GetCurrentRenderBatch() const;`
- L344 _public prototype_ `const int32 GetCurrentRenderBatchIdx() const;`
- L346 _public prototype_ `FTransform ComputeVisualLogTransform(const FTransform& InTransform) const;`
- L347 _public prototype_ `void IncrementVisualLogOffset();`
- L348 _public prototype_ `void ResetVisualLogOffset();`
- L351 _public prototype_ `static int32 GetVisualLogAlpha();`
- L352 _public prototype_ `bool IsVisualLogEnabled() const;`
- L360 _public prototype_ `void RenderComponentIds(UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder);` — Render the component ids in this merge for this batch @param RDGBuilderRecorder recorder to append operations to a single FRDGBuilder, if the the recorder in "recording" mode. In "immediate" mode, a render command will be enqueued immediately
- L367 _public prototype_ `void RenderExpandedRenderTarget(UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder);` — Duplicates the vertex data from the (sub-)sections of the batch, assuming GetBlendRenderTargetRead() is the RT that is read from and GetBlendRenderTargetWrite() the one that is written to @param RDGBuilderRecorder recorder to append operations to a single FRDGBuilder, if the the recorder in "recording" mode. In "immediate" mode, a render command will be enqueued immediately
- L376 _public prototype_ `void GenericBlendLayer(const FBlendParams& InBlendParams, FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder);` — Performs a generic blend assuming GetBlendRenderTargetWrite() is the RT that contains the layer to blend and GetBlendRenderTargetRead() the one that contains the result of the merge up until this layer. It will cycle the RTs such as after this call, GetBlendRenderTargetWrite() will contain the merge result @param InBlendParams defines how heightmaps/weightmaps should be blended. In the case of weightmaps, there must be as may entries in WeightmapBlendParams as there are layers in the target layers group @param RDGBuilderRecorder recorder to append operations to a single FRDGBuilder, if the the recorder in "recording" mode. In "immediate" mode, a render command will be enqueued immediately
- L378 _public function_ `const TBitArray<>& GetFinalTargetLayerBitIndices() const`
- L387 _public prototype_ `template <typename T, typename = std::enable_if_t<std::is_base_of_v<FLandscapeEditLayerMergeRenderBlackboardItem, std::decay_t<T>>>> bool HasBlackboardItem() const;` — @return true if there is at least one blackboard item of type T in the context's list
- L395 _public prototype_ `template <typename T, typename... TArgs, typename = std::enable_if_t<std::is_base_of_v<FLandscapeEditLayerMergeRenderBlackboardItem, std::decay_t<T>>>> T& AddBlackboardItem(TArgs&&... InArgs);` — Create a new blackboard item of type T and adds it to the context's list @return the newly-created blackboard item
- L401 _public prototype_ `template <typename T, typename = std::enable_if_t<std::is_base_of_v<FLandscapeEditLayerMergeRenderBlackboardItem, std::decay_t<T>>>> T* TryGetBlackboardItem();` — @return the first blackboard item of type T from the context's list or nullptr if there isn't one
- L407 _public prototype_ `template <typename T, typename = std::enable_if_t<std::is_base_of_v<FLandscapeEditLayerMergeRenderBlackboardItem, std::decay_t<T>>>> T& GetBlackboardItem();` — @return the first blackboard item of type T from the context's list. Asserts if there isn't one
- L413 _public prototype_ `template <typename T, typename... TArgs, typename = std::enable_if_t<std::is_base_of_v<FLandscapeEditLayerMergeRenderBlackboardItem, std::decay_t<T>>>> T& GetOrCreateBlackboardItem(TArgs&&... InArgs);` — @return the first blackboard item of type T from the context's list or create a new one if there isn't one
- L419 _public prototype_ `template <typename T, typename = std::enable_if_t<std::is_base_of_v<FLandscapeEditLayerMergeRenderBlackboardItem, std::decay_t<T>>>> TArray<T*> GetBlackboardItems();` — @return all blackboard items of type T from the context's list
- L424 _public function_ `const TArray<TInstancedStruct<FLandscapeEditLayerMergeRenderBlackboardItem>>& GetAllBlackboardItems() const` — @return all blackboard items currently stored in the context
- L428 _private prototype_ `void AllocateResources();` — Allocate all needed render targets for this merge
- L430 _private prototype_ `void FreeResources();` — Free all render targets used in this merge
- L432 _private prototype_ `void AllocateBatchResources(const FMergeRenderBatch& InRenderBatch);` — Allocate all needed render targets for this batch
- L434 _private prototype_ `void FreeBatchResources(const FMergeRenderBatch& InRenderBatch);` — Free all render targets used in this batch
- L439 _private member_ `static constexpr int32 NumBlendRenderTargets = 3;` — Blending is pretty much what we only do during the merge. It requires 3 render targets : 1 that we write to and therefore use as RTV (Write) and 2 that we read from and therefore use as SRV (one that contains the layer to merge, the other the accumulated result so far) : Previous(SRV) + Current(SRV) --> Write(RTV)
- L442 _private member_ `TStaticArray<ULandscapeScratchRenderTarget*, NumBlendRenderTargets> BlendRenderTargets;` — Render targets that are used throughout the blending operations (they could be texture arrays in the case of multiple weightmaps)
- L443 _private member_ `int32 CurrentBlendRenderTargetWriteIndex = -1;`
- L447 _private member_ `TBitArray<> FinalTargetLayerBitIndices;` — Final list of target layer names being involved in this merge context. If a target layer name is present here, it's because it's a valid target layer and it needs to be rendered because it has been requested or one of the target layers that have been requested needs it to be present (e.g. weight-blending). Each bit in that bit array corresponds to an entry in AllTargetLayerNames
- L452 _private member_ `ULandscapeScratchRenderTarget* ComponentIdRenderTarget = nullptr;` — Render targets storing the id (uint32, stored as a RTF_R32f) of the component within the batch that each pixel belongs to. It can be used as a stencil-like buffer, which can be useful when sampling neighbors, to know whether the data there corresponds to a valid neighbor, but also to resolve ambiguities when rendering overlapping quads (because the borders then belong to 2 components but this render target has the authority as to which one of those a given pixel "belongs to")
- L455 _private member_ `FIntPoint MaxNeededResolution = FIntPoint(ForceInit);` — Maximum resolution needed by a given batch in this context (means we won't ever need more than this size of a render target during the whole merge)
- L458 _private member_ `int32 MaxNeededNumSlices = 0;` — Maximum number of slices needed by a given batch / target layer group in this context (means we won't ever need more than this number of slices in a given render target texture array during the whole merge)
- L461 _private member_ `FIntPoint MaxNumComponents = FIntPoint(ForceInit);` — Maximum number of components needed by a given batch in this context (means we won't ever render more than this amount of components during the whole merge)
- L465 _private member_ `TArray<FMergeRenderBatch> RenderBatches;` — Successive batches of components being processed by this context. Each batch should be self-contained so that we won't ever need to keep more than one in memory (VRAM) in order to compute the info we need (heightmap/weightmaps), i.e. nothing should ever depend on 2 different batches.
- L468 _private member_ `int32 CurrentRenderBatchIndex = INDEX_NONE;` — Current batch being rendered
- L471 _private member_ `FVector CurrentVisualLogOffset = FVector(ForceInitToZero);` — Offset for visual debugging
- L474 _private member_ `double MaxLocalHeight = DBL_MIN;` — Maximum height of all components to render in local space.
- L477 _private member_ `TMap<ULandscapeComponent*, TBitArray<>> ComponentToTargetLayerBitIndices;` — List of components involved in this merge and the target layers they're writing to (each bit corresponds to the target layer name in AllTargetLayerNames)
- L480 _private member_ `TArray<TSet<ULandscapeComponent*>> TargetLayersToComponents;` — Reverse lookup of ComponentToTargetLayerBitIndices : one entry per element in ComponentToTargetLayerBitIndices, each entry containing all of the components involved in this merge for this target layer
- L483 _private member_ `TArray<TInstancedStruct<FLandscapeEditLayerMergeRenderBlackboardItem>> BlackboardItems;` — Generic data struct to store some data to pass around throughout the context's lifetime. Basically, this is a mini-RTTI system that e.g. allows to store/pass around specific data between renderers in a generic way

#### struct `UE::Landscape::EditLayers::FMergeRenderContext::FOnRenderBatchTargetGroupDoneParams`  
`struct FOnRenderBatchTargetGroupDoneParams`  
_L312-335_
- L314 _public function_ `FOnRenderBatchTargetGroupDoneParams(FMergeRenderContext* InMergeRenderContext, const TArrayView<FName>& InTargetLayerGroupLayerNames, const TArrayView<ULandscapeLayerInfoObject*>& InTargetLayerGroupLayerInfos, const TArrayView<FComponentMergeRenderInfo>& InSortedComponentMergeRenderInfos) : MergeRenderContext(InMergeRenderContext) , TargetLayerGroupLayerNames(InTargetLayerGroupLayerNames) , TargetLayerGroupLayerInfos(InTargetLayerGroupLayerInfos) , SortedComponentMergeRenderInfos(InSortedComponentMergeRenderInfos)`
- L325 _public member_ `FMergeRenderContext* MergeRenderContext = nullptr;` — Render context : this is still active in this step and can be used for doing additional renders in the blend render targets, etc.
- L328 _public member_ `TArray<FName> TargetLayerGroupLayerNames;` — List of target layers being involved in this step
- L331 _public member_ `TArray<ULandscapeLayerInfoObject*> TargetLayerGroupLayerInfos;` — List of target layer info objects being involved in this step (same size as TargetLayerGroupLayerNames)
- L334 _public member_ `const TArray<FComponentMergeRenderInfo> SortedComponentMergeRenderInfos;` — Additional info about the components that have been processed in this batch render

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Landscape` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Landscape` (scope `UE`)
- L32 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace Landscape` (scope `UE`)
- L40 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)

### `Source/Runtime/Landscape/Public/LandscapeEditLayerMergeRenderContext.inl` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Landscape` (scope `UE`)
- L9 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)
- L15 _function_ `template <typename T, typename> bool UE::Landscape::EditLayers::FMergeRenderContext::HasBlackboardItem() const` (scope `UE::Landscape::EditLayers::UE::Landscape::EditLayers::FMergeRenderContext`)
- L28 _function_ `template <typename T, typename... TArgs, typename> T& UE::Landscape::EditLayers::FMergeRenderContext::AddBlackboardItem(TArgs&&... InArgs)` (scope `UE::Landscape::EditLayers::UE::Landscape::EditLayers::FMergeRenderContext`)
- L35 _function_ `template <typename T, typename> T* UE::Landscape::EditLayers::FMergeRenderContext::TryGetBlackboardItem()` (scope `UE::Landscape::EditLayers::UE::Landscape::EditLayers::FMergeRenderContext`)
- L48 _function_ `template <typename T, typename> T& UE::Landscape::EditLayers::FMergeRenderContext::GetBlackboardItem()` (scope `UE::Landscape::EditLayers::UE::Landscape::EditLayers::FMergeRenderContext`)
- L65 _function_ `template <typename T, typename... TArgs, typename> T& UE::Landscape::EditLayers::FMergeRenderContext::GetOrCreateBlackboardItem(TArgs&&... InArgs)` (scope `UE::Landscape::EditLayers::UE::Landscape::EditLayers::FMergeRenderContext`)
- L77 _function_ `template <typename T, typename> TArray<T*> UE::Landscape::EditLayers::FMergeRenderContext::GetBlackboardItems()` (scope `UE::Landscape::EditLayers::UE::Landscape::EditLayers::FMergeRenderContext`)

### `Source/Runtime/Landscape/Public/LandscapeEditLayerRenderer.h` (Public)


#### struct `UE::Landscape::EditLayers::FOOBox2D`  
`struct FOOBox2D`  
_L49-61_
- desc: TODO [jonathan.bard] : use FOrientedBox2d instead?
- L51 _public prototype_ `FOOBox2D() = default;`
- L52 _public function_ `FOOBox2D(const FTransform& InTransform, const FVector2D& InExtents) : Transform(InTransform) , Extents(InExtents)`
- L57 _public member_ `FTransform Transform;`
- L58 _public member_ `FVector2D Extents = FVector2D(ForceInit);`
- L60 _public prototype_ `FBox BuildAABB() const;`

#### class `UE::Landscape::EditLayers::FInputWorldArea`  
`class FInputWorldArea`  
_L69-115_
- desc: Describes the input area needed for a given edit layer renderer's render item: this allows to infer the dependency between each component being rendered and the components it depends on
- L80 _public function_ `static FInputWorldArea CreateInfinite()`
- L81 _public function_ `static FInputWorldArea CreateLocalComponent(const FIntRect& InLocalArea = FIntRect())`
- L82 _public function_ `static FInputWorldArea CreateSpecificComponent(const FIntPoint& InComponentKey, const FIntRect& InLocalArea = FIntRect())`
- L83 _public function_ `static FInputWorldArea CreateOOBox(const FOOBox2D& InOOBox)`
- L85 _public function_ `EType GetType() const`
- L87 _public prototype_ `FIntRect GetLocalComponentKeys(const FIntPoint& InComponentKey) const;` — In the EType::LocalComponent case, returns the component's coordinates and the local area around it (inclusive bounds)
- L89 _public prototype_ `FIntRect GetSpecificComponentKeys() const;` — In the EType::SpecificComponent case, returns the component's coordinates and the local area around it (inclusive bounds)
- L91 _public function_ `const FOOBox2D& GetOOBox() const` — In the EType::OOBox case, returns the OOBox
- L92 _public function_ `const FOOBox2D* TryGetOOBox() const`
- L94 _public prototype_ `FBox ComputeWorldAreaAABB(const FTransform& InLandscapeTransform, const FBox& InLandscapeLocalBounds, const FTransform& InComponentTransform, const FBox& InComponentLocalBounds) const;`
- L95 _public prototype_ `FOOBox2D ComputeWorldAreaOOBB(const FTransform& InLandscapeTransform, const FBox& InLandscapeLocalBounds, const FTransform& InComponentTransform, const FBox& InComponentLocalBounds) const;`
- L98 _private function_ `FInputWorldArea(EType InType, const FIntPoint& InComponentKey = FIntPoint(ForceInit), const FIntRect& InLocalArea = FIntRect(), const FOOBox2D& InOOBox2D = FOOBox2D()) : Type(InType) , SpecificComponentKey(InComponentKey) , LocalArea(InLocalArea) , OOBox2D(InOOBox2D)`
- L106 _private member_ `EType Type = EType::LocalComponent;`
- L108 _private member_ `FIntPoint SpecificComponentKey = FIntPoint(ForceInit);` — Coordinates of the component (see ULandscapeComponent::GetComponentKey()) in the EType::SpecificComponent case
- L111 _private member_ `FIntRect LocalArea;` — Area around the component that is needed in the EType::LocalComponent / EType::SpecificComponent case (in component coordinates (see ULandscapeComponent::GetComponentKey()), e.g. use (-1, -1, 1, 1) for the component and its immediate neighbors all around)
- L114 _private member_ `FOOBox2D OOBox2D;` — World space object-oriented box in the EType::OOBBox case

#### enum `UE::Landscape::EditLayers::FInputWorldArea::EType`  
`enum class EType`  
_L72-78_
- L74 _public enumerator_ `LocalComponent` — Designates any landscape component (i.e. the input area corresponds to the component being requested), with an optional number of neighboring components around it
- L75 _public enumerator_ `SpecificComponent` — Designates a specific landscape component (based on its component key), with an optional number of neighboring components around it
- L76 _public enumerator_ `OOBox` — Designates a fixed world area (an object-oriented box)
- L77 _public enumerator_ `Infinite` — Designates the entire loaded landscape area

#### class `UE::Landscape::EditLayers::FOutputWorldArea`  
`class FOutputWorldArea`  
_L124-161_
- desc: Describes the output area needed where a given edit layer renderer's render item writes: this allows to define the components of landscape that need to be processed and allows to divide the work into batches
- L134 _public function_ `static FOutputWorldArea CreateLocalComponent()`
- L135 _public function_ `static FOutputWorldArea CreateSpecificComponent(const FIntPoint& InComponentKey)`
- L136 _public function_ `static FOutputWorldArea CreateOOBox(const FOOBox2D& InOOBox)`
- L138 _public function_ `EType GetType() const`
- L140 _public function_ `const FIntPoint& GetSpecificComponentKey() const` — In the EType::SpecificComponent case, returns the component's coordinates
- L142 _public function_ `const FOOBox2D& GetOOBox() const` — In the EType::OOBox case, returns the OOBox
- L143 _public function_ `const FOOBox2D* TryGetOOBox() const`
- L145 _public prototype_ `FBox ComputeWorldAreaAABB(const FTransform& InComponentTransform, const FBox& InComponentLocalBounds) const;`
- L146 _public prototype_ `FOOBox2D ComputeWorldAreaOOBB(const FTransform& InComponentTransform, const FBox& InComponentLocalBounds) const;`
- L149 _private function_ `FOutputWorldArea(EType InType, const FIntPoint& InComponentKey = FIntPoint(ForceInit), const FOOBox2D& InOOBox = FOOBox2D()) : Type(InType) , SpecificComponentKey(InComponentKey) , OOBox2D(InOOBox)`
- L156 _private member_ `EType Type = EType::LocalComponent;`
- L158 _private member_ `FIntPoint SpecificComponentKey = FIntPoint(ForceInit);` — Coordinates of the component (see ULandscapeComponent::GetComponentKey()) in the EType::SpecificComponent case
- L160 _private member_ `FOOBox2D OOBox2D;` — World space Object-oriented box in the EType::OOBBox case

#### enum `UE::Landscape::EditLayers::FOutputWorldArea::EType`  
`enum class EType`  
_L127-132_
- L129 _public enumerator_ `LocalComponent` — Designates any landscape component (i.e. the input area corresponds to the component being requested)
- L130 _public enumerator_ `SpecificComponent` — Designates a specific landscape component (based on its component key)
- L131 _public enumerator_ `OOBox` — Designates a fixed world area (an Object-oriented box)

#### class `UE::Landscape::EditLayers::FEditLayerRenderItem`  
`class FEditLayerRenderItem`  
_L171-215_
- desc: Each edit layer render item represents the capabilities of what a given edit layer can render in terms of landscape data : a renderer can provide one or many render items, which contain the "locality" (what area do I affect?) as well as the "capability" (what target tool type do I affect? what weightmap(s)?) information related to what this layer item can do. See ILandscapeEditLayerRenderer::GetRenderItems
- L174 _public prototype_ `FEditLayerRenderItem() = delete;`
- L175 _public function_ `FEditLayerRenderItem(const FEditLayerTargetTypeState& InTargetTypeState, const FInputWorldArea& InInputWorldArea, const FOutputWorldArea& InOutputWorldArea, bool bInModifyExistingWeightmapsOnly) : TargetTypeState(InTargetTypeState) , InputWorldArea(InInputWorldArea) , OutputWorldArea(InOutputWorldArea) , bModifyExistingWeightmapsOnly(bInModifyExistingWeightmapsOnly)`
- L182 _public function_ `const FEditLayerTargetTypeState& GetTargetTypeState() const`
- L184 _public function_ `const FInputWorldArea& GetInputWorldArea() const`
- L185 _public function_ `void SetInputWorldArea(const FInputWorldArea& InInputWorldArea)`
- L187 _public function_ `const FOutputWorldArea& GetOutputWorldArea() const`
- L188 _public function_ `void SetOutputWorldArea(const FOutputWorldArea& InOutputWorldArea)`
- L190 _public function_ `bool GetModifyExistingWeightmapsOnly() const`
- L195 _private member_ `FEditLayerTargetTypeState TargetTypeState;` — Target types / weightmaps that this render item writes to
- L203 _private member_ `FInputWorldArea InputWorldArea;` — Area that this render item needs in order to render properly. - If Infinite, it is assumed the render item needs the entire loaded landscape to render properly (i.e. it's dependent on all loaded landscape components) - If Local, it requires a particular component and optionally its immediate neighbors - If OOBox, then only the landscape components covered by this area will be considered as inputs
- L211 _private member_ `FOutputWorldArea OutputWorldArea;` — Area that this render item writes to. - If Infinite, the render item writes everywhere (use only if necessary, as it will - If Local, it requires a particular component and optionally its immediate neighbors - If OOBox, then only the landscape components covered by this area will be considered as inputs
- L214 _private member_ `bool bModifyExistingWeightmapsOnly = false;` — Indicates whether this render item actually outputs weightmaps (if false) or only modifies existing ones underneath (i.e. blending-only)

#### class `UE::Landscape::EditLayers::IEditLayerRendererProvider`  
`class IEditLayerRendererProvider`  
_L223-234_
- desc: Interface to implement to be able to provide an ordered list of renderers to the landscape.
- L226 _public prototype_ `virtual ~IEditLayerRendererProvider() = default;`
- L233 _public prototype_ `virtual TArray<FEditLayerRendererState> GetEditLayerRendererStates(const FMergeContext* InMergeContext) PURE_VIRTUAL(IEditLayerRendererProvider::GetEditLayerRendererStates, return {}; );` — @param InMergeContext context containing all sorts of information related to this merge operation @return a list of renderer states (i.e. a ILandscapeEditLayerRenderer and its current state) to be processed in that order by the merge operation

#### class `ULandscapeEditLayerRenderer`  
`class ULandscapeEditLayerRenderer : public UInterface`  
_L247-252_
- reflection: `UINTERFACE()`
- inherits: `UInterface`
- desc: UInterface for a landscape edit layer renderer

#### class `ILandscapeEditLayerRenderer`  
`class ILandscapeEditLayerRenderer`  
_L259-375_
- desc: Interface that needs to be implemented for anything that can render heightmap/weightmap/visibility when merging landscape edit layers. Ideally it would have been defined in the UE::Landscape::EditLayers namespace but UHT prevents us from doing so. The renderers are provided to the landscape by a IEditLayerRendererProvider.
- L285 _public prototype_ `virtual void GetRendererStateInfo(const UE::Landscape::EditLayers::FMergeContext* InMergeContext, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutSupportedTargetTypeState, UE::Landscape::EditLayers::FEditLayerTargetTypeState& OutEnabledTargetTypeState, TArray<UE::Landscape::EditLayers::FTargetLayerGroup>& OutTargetLayerGroups) const PURE_VIRTUAL(ILandscapeEditLayerRenderer::GetRendererStateInfo, );` — GetRendererStateInfo retrieves the current state of this renderer (what it can and does render, as well as how to group target layers together), and part of this will then be mutable for the duration of the merge. The idea is that FEditLayerRendererState's SupportedTargetTypeState tells the capabilities of this renderer, while EnabledTargetTypeState tells what it currently does render. A target type must be both supported and enabled in order to have this renderer affect it and the "enabled" state can be changed at will by the user (e.g. to temporarily disable a given edit layer just for the duration of the merge) : see FEditLayerRendererState @param InMergeContext context containing all sorts of information related to this merge operation @param OutSupportedTargetTypeState List of all target types / weightmaps that this renderer supports (e.g. if, say ELandscapeToolTargetType::Weightmap, is not included, the renderer will *not* be used at all when rendering any kind of weightmap) @param OutEnabledTargetTypeMask List of all target types / weightmaps that this renderer is currently enabled for (i.e. default state of this renderer wrt this target type). A target type must be both supported and enabled in order to have this renderer affect it. The "enabled" state can be changed at will by the user (e.g. to temporarily disable a given edit layer) : see FEditLayerRendererState @param OutTargetLayerGroups List of groups of target layers that this renderer requires to be rendered to
- L293 _public prototype_ `virtual FString GetEditLayerRendererDebugName() const PURE_VIRTUAL(ILandscapeEditLayerRenderer::GetEditLayerRendererDebugName, return TEXT(""); );` — @return the a debug name for this renderer
- L303 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRenderItem> GetRenderItems(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const PURE_VIRTUAL(ILandscapeEditLayerRenderer::GetRenderItems, return { }; );` — GetRenderItems retrieves information about the areas this renderer renders to and specifically what respective input area they require to render properly @param InMergeContext context containing all sorts of information related to this merge operation @return list of all render items that affect this renderer
- L311 _public prototype_ `virtual UE::Landscape::EditLayers::ERenderFlags GetRenderFlags(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const PURE_VIRTUAL(ILandscapeEditLayerRenderer::GetRenderFlags, return UE::Landscape::EditLayers::ERenderFlags::None; );` — @param InMergeContext context containing all sorts of information related to this merge operation @return details about how this renderer's render method is implemented
- L334 _public prototype_ `virtual bool RenderLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder) PURE_VIRTUAL(ILandscapeEditLayerRenderer::RenderLayer, return false; );` — RenderLayer is where the renderer has a chance to render its content and eventually blend it with the merged result of all preceding layers (if ERenderFlags::BlendMode_SeparateBlend is not returned) It operates on a limited set of components (depending on the size of the render batches) and on a set of target layers (e.g. multiple weightmaps). It guarantees access to the merged result from preceding layers of each target layer. @param RenderParams contains parameters necessary for this render (affected components, merge context, etc.) @param RDGBuilderRecorder recorder to append operations to a single FRDGBuilder, if the the recorder in "recording" mode. In "immediate" mode, a render command will be enqueued immediately. The recorder can be in 2 states, depending on the result from GetRenderFlags - ERenderFlags::RenderMode_Immediate : the recorder is in immediate mode renderer can enqueue render commands just like any other game thread-based renderer - ERenderFlags::RenderMode_Recorded : the function runs on the game thread but is *not* meant to enqueue render commands directly. Instead, it registers consecutive "render commands" via "RDG/render command" accumulated on a FRDGBuilderRecorder. This allows to coalesce several render commands onto the same FRDGBuilder (which is critical for performance) while still allowing to interleave game thread-based renders (flushing the command recorder, enqueuing the game thread-based render, and starting recording on the same (or a new) 
- L346 _public function_ `virtual void BlendLayer(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder)` — BlendLayer is where the renderer has a chance to blend its content with the merged result of all preceding layers It operates on a limited set of components (depending on the size of the render batches) and on a set of target layers (e.g. multiple weightmaps). It guarantees access to the merged result from preceding layers of each target layer. @param RenderParams contains parameters necessary for this render (affected components, merge context, etc.) @param RDGBuilderRecorder (see RenderLayer)
- L356 _public function_ `virtual bool CanGroupRenderLayerWith(TScriptInterface<ILandscapeEditLayerRenderer> InOtherRenderer) const` — Return whether this renderer's RenderLayer operation can be grouped with one of the previous renderers in the render layer group. Only called if ERenderFlags::RenderLayerGroup_SupportsGrouping is returned by GetRenderFlags() on both renderers @param InOtherRenderer the other renderer we're trying to group this renderer's RenderLayer operation with @return true if both RenderLayer can be done in the same render layer group
- L364 _public function_ `virtual void BeginRenderLayerGroup(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder)` — Called before the first call to RenderLayer, on the first renderer of a render layer group : Only called if ERenderFlags::RenderLayerGroup_SupportsGrouping is returned by GetRenderFlags() @param RenderParams contains parameters necessary for this render (affected components, merge context, etc.)
- L372 _public function_ `virtual void EndRenderLayerGroup(UE::Landscape::EditLayers::FRenderParams& RenderParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder)` — Called after the last call to RenderLayer, on the last renderer of a render layer group. Only called if ERenderFlags::RenderLayerGroup_SupportsGrouping is returned by GetRenderFlags() @param RenderParams contains parameters necessary for this render (affected components, merge context, etc.)

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Landscape` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace Landscape` (scope `UE`)
- L29 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace Landscape` (scope `UE`)
- L40 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)

### `Source/Runtime/Landscape/Public/LandscapeEditLayerRendererState.h` (Public)


#### class `UE::Landscape::EditLayers::FEditLayerRendererState`  
`class FEditLayerRendererState`  
_L32-165_
- desc: FEditLayerRendererState describes the entire state of an edit layer renderer : what it is capable of doing (SupportedTargetTypeState, immutable) and what it is currently doing (EnabledTargetTypeState, mutable) These states are provided by IEditLayerRendererProvider in order to describe both what the renderer can do and what it currently does by default. e.g. a disabled edit layer supports rendering heightmaps but its enabled state for the heightmap target type is false. This way, the user can selectively enable it at merge time without altering the entire landscape's state (i.e. just for the purpose of a specific merge render) A target type must be both supported and enabled on a given edit layer renderer in order for this renderer to render anything. It also describes the target layer groups this renderer needs when rendering its weightmap (i.e. which weightmap needs to be rendered with which weightmaps : e.g. for weight blending)
- L36 _private prototype_ `FEditLayerRendererState() = default;` — Private constructor : either use the constructors taking a merge context in parameter or use GetDummyRendererState()
- L39 _public prototype_ `static const FEditLayerRendererState& GetDummyRendererState();`
- L41 _public prototype_ `explicit FEditLayerRendererState(const FMergeContext* InMergeContext);`
- L42 _public prototype_ `explicit FEditLayerRendererState(const FMergeContext* InMergeContext, TScriptInterface<ILandscapeEditLayerRenderer> InRenderer);`
- L45 _public function_ `TScriptInterface<ILandscapeEditLayerRenderer> GetRenderer() const` — Returns the edit layer renderer which this state relates to
- L48 _public function_ `const FEditLayerTargetTypeState& GetSupportedTargetTypeState() const` — Returns a mask of all target types / weightmaps supported by this renderer
- L51 _public function_ `const FEditLayerTargetTypeState& GetEnabledTargetTypeState() const` — Returns a mask of all target types / weightmaps enabled on this renderer
- L54 _public function_ `FEditLayerTargetTypeState GetActiveTargetTypeState() const` — Returns a mask of all target types / weightmaps supported and enabled on this renderer
- L57 _public prototype_ `void EnableTargetType(ELandscapeToolTargetType InTargetType);` — Mutates the EnabledTargetTypeState by adding the target type in parameter to the mask of active target types
- L60 _public prototype_ `void EnableTargetTypeMask(ELandscapeToolTargetTypeFlags InTargetTypeMask);` — Mutates the EnabledTargetTypeState by adding the target type mask in parameter to the mask of active target types
- L63 _public prototype_ `void DisableTargetType(ELandscapeToolTargetType InTargetType);` — Mutates the EnabledTargetTypeState by removing the target type in parameter from the mask of active target types
- L66 _public prototype_ `void DisableTargetTypeMask(ELandscapeToolTargetTypeFlags InTargetTypeMask);` — Mutates the EnabledTargetTypeState by removing the target type mask in parameter from the mask of active target types
- L71 _public prototype_ `void EnableWeightmap(ELandscapeToolTargetType InTargetType, const FName& InWeightmapLayerName);` — Mutates the EnabledTargetTypeState by adding the weightmap in parameter to the list of enabled weightmaps, if it is known to the merge context
- L76 _public prototype_ `void EnableWeightmapChecked(ELandscapeToolTargetType InTargetType, const FName& InWeightmapLayerName);` — Mutates the EnabledTargetTypeState by adding the weightmap in parameter to the list of enabled weightmaps. Asserts if the layer name isn't known to the merge context
- L81 _public prototype_ `void EnableWeightmap(ELandscapeToolTargetType InTargetType, int32 InWeightmapLayerIndex);` — Mutates the EnabledTargetTypeState by adding the weightmap in parameter to the list of enabled weightmaps. Asserts if the layer index isn't known to the merge context
- L86 _public prototype_ `void DisableWeightmap(const FName& InWeightmapLayerName);` — Mutates the EnabledTargetTypeState by removing the weightmap in parameter from the list of enabled weightmaps, if it is known to the merge context
- L91 _public prototype_ `void DisableWeightmapChecked(const FName& InWeightmapLayerName);` — Mutates the EnabledTargetTypeState by removing the weightmap in parameter from the list of enabled weightmaps. Asserts if the layer index isn't known to the merge context
- L96 _public prototype_ `void DisableWeightmap(int32 InWeightmapLayerIndex);` — Mutates the EnabledTargetTypeState by removing the weightmap in parameter from the list of enabled weightmaps. Asserts if the layer index isn't known to the merge context
- L100 _public prototype_ `ELandscapeToolTargetTypeFlags GetActiveTargetTypeMask() const;`
- L107 _public prototype_ `bool IsTargetActive(ELandscapeToolTargetType InTargetType, const FName& InWeightmapLayerName = NAME_None) const;` — Indicates whether a given target type and weightmap layer name is currently supported and enabled by this renderer. @param InTargetType the requested target type (heightmap/weightmap/visibility) @param InWeightmapLayerName (optional) is the requested weightmap, only relevant for the ELandscapeToolTargetType::Weightmap case
- L114 _public prototype_ `bool IsTargetActiveChecked(ELandscapeToolTargetType InTargetType, const FName& InWeightmapLayerName = NAME_None) const;` — Indicates whether a given target type and weightmap layer name is currently supported and enabled by this renderer. Asserts if the layer name isn't known to the merge context (except if NAME_None) @param InTargetType the requested target type (heightmap/weightmap/visibility) @param InWeightmapLayerName (optional) is the requested weightmap, only relevant for the ELandscapeToolTargetType::Weightmap case
- L121 _public prototype_ `bool IsTargetActive(ELandscapeToolTargetType InTargetType, int32 InWeightmapLayerIndex = INDEX_NONE) const;` — Indicates whether a given target type and weightmap layer name is currently supported and enabled by this renderer. Asserts if the layer index isn't known to the merge context (except if INDEX_NONE) @param InTargetType the requested target type (heightmap/weightmap/visibility) @param InWeightmapLayerIndex (optional) is the requested weightmap's index in the merge index, only relevant for the ELandscapeToolTargetType::Weightmap case
- L126 _public prototype_ `TArray<FName> GetActiveTargetWeightmaps() const;` — Returns a list of all weightmaps supported and enabled by this renderer (only relevant for ELandscapeToolTargetType::Weightmap (and ELandscapeToolTargetType::Visibility))
- L131 _public prototype_ `TBitArray<> GetActiveTargetWeightmapBitIndices() const;` — Returns a list of all weightmaps supported and enabled by this renderer (only relevant for ELandscapeToolTargetType::Weightmap (and ELandscapeToolTargetType::Visibility))
- L135 _public function_ `TArray<FTargetLayerGroup> GetTargetLayerGroups() const` — Returns the target layer groups associated with this renderer. A target layer group is a set of target layers (weightmaps) that depend on one another in order to produce the output target layers. This allows to implement "horizontal blending", where weightmaps can be blended with one another at each step of the landscape edit layers merge algorithm
- L138 _private prototype_ `void UpdateActiveTargetTypeState();`
- L142 _private member_ `const FMergeContext* MergeContext = nullptr;` — Global context being used for this merge : contains generic information about the landscape, its available layer names, etc.
- L145 _private member_ `TScriptInterface<ILandscapeEditLayerRenderer> Renderer;` — Renderer associated with this state
- L148 _private member_ `FString DebugName;` — For debug purposes : this is the same as Renderer->GetEditLayerRendererDebugName() but having a member makes it easier to debug in the watch window
- L152 _private member_ `FEditLayerTargetTypeState SupportedTargetTypeState = FEditLayerTargetTypeState::GetDummyTargetTypeState();` — Struct that contains the supported target types and the which weightmap are supported by this renderer. Immutable.
- L155 _private member_ `FEditLayerTargetTypeState EnabledTargetTypeState = FEditLayerTargetTypeState::GetDummyTargetTypeState();` — Struct that contains the enabled target types and the which weightmap are currently enabled by this renderer. Can be set by the user using EnableTargetType.
- L158 _private member_ `FEditLayerTargetTypeState ActiveTargetTypeState = FEditLayerTargetTypeState::GetDummyTargetTypeState();` — Intersection of SupportedTargetTypeState and EnabledTargetTypeState (defines what is both supported and enabled on this renderer)
- L164 _private member_ `TArray<FTargetLayerGroup> TargetLayerGroups;` — List of groups of target layers that this renderer requires to be rendered together. All target layers listed in SupportedTargetTypeState must belong to 1 (and 1 only) target layer group. Each target layer group is a bit array for which each bit corresponds to an entry in FMergeContext's AllTargetLayerNames

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Landscape` (scope `UE`)
- L18 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)

### `Source/Runtime/Landscape/Public/LandscapeEditLayerTargetLayerGroup.h` (Public)


#### class `UE::Landscape::EditLayers::FTargetLayerGroup`  
`class FTargetLayerGroup`  
_L18-47_
- desc: FTargetLayerGroup describes a group of target layers that need to be rendered together, typically for weight-blending reasons
- L21 _public function_ `inline FTargetLayerGroup(const FName& InName, const TBitArray<>& InWeightmapTargetLayerBitIndices) : Name(InName) , WeightmapTargetLayerBitIndices(InWeightmapTargetLayerBitIndices)`
- L26 _public function_ `inline FName GetName() const`
- L31 _public function_ `inline const TBitArray<>& GetWeightmapTargetLayerBitIndices() const`
- L40 _private member_ `FName Name;` — Identifier for this group of target layers
- L46 _private member_ `TBitArray<> WeightmapTargetLayerBitIndices;` — List of weightmaps that belong to this group Each bit in that bit array corresponds to an entry in FMergeContext's AllTargetLayerNames

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Landscape` (scope `UE`)
- L10 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)

### `Source/Runtime/Landscape/Public/LandscapeEditLayerTargetTypeState.h` (Public)


#### class `UE::Landscape::EditLayers::FEditLayerTargetTypeState`  
`class FEditLayerTargetTypeState`  
_L34-176_
- desc: FEditLayerTargetTypeState fully describes the state of an edit layer renderer wrt its target types. It's named after the enum "ELandscapeToolTargetType" in order to tell whether the renderer's heightmaps and/or visibility and/or weightmaps are enabled (and if so, which weightmap is enabled exactly) It is meant to be provided by the edit layer renderer's GetRendererStateInfo implementation.
- L41 _private prototype_ `FEditLayerTargetTypeState() = default;` — Private constructor : either use the constructors taking a merge context in parameter or use GetDummyTargetTypeState()
- L44 _public prototype_ `static const FEditLayerTargetTypeState& GetDummyTargetTypeState();`
- L51 _public prototype_ `FEditLayerTargetTypeState(const FMergeContext* InMergeContext);` — Constructs an empty FEditLayerTargetTypeState (all target types turned off, no active weightmaps) @param InMergeContext context containing all sorts of information related to this merge operation
- L59 _public prototype_ `FEditLayerTargetTypeState(const FMergeContext* InMergeContext, ELandscapeToolTargetTypeFlags InTargetTypeMask);` — Initializes a FEditLayerTargetTypeState with the target types passed in parameter @param InMergeContext context containing all sorts of information related to this merge operation @param InTargetTypeMask target type mask supported by this target type state (no active weightmaps)
- L69 _public prototype_ `FEditLayerTargetTypeState(const FMergeContext* InMergeContext, ELandscapeToolTargetTypeFlags InTargetTypeMask, const TArrayView<const FName>& InSupportedWeightmaps, bool bInChecked);` — Initializes a FEditLayerTargetTypeState with the target types and the weightmaps passed in parameter (by name) @param InMergeContext context containing all sorts of information related to this merge operation @param InTargetTypeMask target type mask supported by this target type state @param InSupportedWeightmaps names of weightmaps supported by this target type state @param bInChecked, if true, will validate that every weightmap requested is part of the merge context (if false, only the known weightmaps will be marked as supported)
- L79 _public prototype_ `FEditLayerTargetTypeState(const FMergeContext* InMergeContext, ELandscapeToolTargetTypeFlags InTargetTypeMask, const TBitArray<>& InSupportedWeightmapLayerIndices);` — Initializes a FEditLayerTargetTypeState with the target types and (optionally) the weightmaps passed in parameter (by bit index) @param InMergeContext context containing all sorts of information related to this merge operation @param InTargetTypeMask target type mask supported by this target type state @param InSupportedWeightmaps bit indices of the weightmaps supported by this target type state (corresponds to the FMergeContext's AllTargetLayerNames) Asserts if one of the layer indices isn't valid for the merge context (except when InSupportedWeightmapLayerIndices is == TBitArray<>)
- L86 _public prototype_ `bool IsActive(ELandscapeToolTargetType InTargetType, const FName& InWeightmapLayerName = NAME_None) const;` — Indicates whether a given target type is currently active in this state @param InTargetType the requested target type (heightmap/weightmap/visibility) @param InWeightmapLayerName (optional) is the requested weightmap, only relevant for the ELandscapeToolTargetType::Weightmap case
- L93 _public prototype_ `bool IsActiveChecked(ELandscapeToolTargetType InTargetType, const FName& InWeightmapLayerName = NAME_None) const;` — Indicates whether a given target type is currently active in this state @param InTargetType the requested target type (heightmap/weightmap/visibility) @param InWeightmapLayerName (optional) is the requested weightmap, only relevant for the ELandscapeToolTargetType::Weightmap case. Asserts if the layer name isn't valid for the merge context (except for NAME_None)
- L100 _public prototype_ `bool IsActive(ELandscapeToolTargetType InTargetType, int32 InWeightmapLayerIndex = INDEX_NONE) const;` — Indicates whether a given target type is currently active in this state @param InTargetType is the requested target type (heightmap/weightmap/visibility) @param int32 (optional) is the requested weightmap index (in FMergeContex), only relevant for the ELandscapeToolTargetType::Weightmap case. Asserts if the layer index isn't valid for the merge context (except for INDEX_NONE)
- L107 _public prototype_ `TArray<FName> GetActiveWeightmaps() const;` — Returns the currently active weightmaps : - If Weightmap is amongst the target types it will return all the weightmaps - Additionally, if Visibility is amongst the target types, it will also return the visibility weightmap - If neither Weightmap nor Visibility is amongst the target types, it will return an empty array
- L114 _public prototype_ `TBitArray<> GetActiveWeightmapBitIndices() const;` — Returns the currently active weightmaps : - If Weightmap is amongst the target types it will return all the weightmaps - Additionally, if Visibility is amongst the target types, it will also return the visibility weightmap - If neither Weightmap nor Visibility is amongst the target types, it will return an empty array
- L117 _public function_ `ELandscapeToolTargetTypeFlags GetTargetTypeMask() const` — Returns the target type mask (i.e. same as ELandscapeToolTargetType, but as bit flags)
- L120 _public prototype_ `void SetTargetTypeMask(ELandscapeToolTargetTypeFlags InTargetTypeMask);` — Sets the target type mask (i.e. same as ELandscapeToolTargetType, but as bit flags)
- L123 _public prototype_ `void AddTargetType(ELandscapeToolTargetType InTargetType);` — Adds the target type in parameter to the mask of active target types
- L126 _public prototype_ `void AddTargetTypeMask(ELandscapeToolTargetTypeFlags InTargetTypeMask);` — Appends the target type mask in parameter to the mask of active target types
- L129 _public prototype_ `void RemoveTargetType(ELandscapeToolTargetType InTargetType);` — Removes a single target type from the mask of active target types
- L132 _public prototype_ `void RemoveTargetTypeMask(ELandscapeToolTargetTypeFlags InTargetTypeMask);` — Removes the target type mask in parameter from the mask of active target types
- L135 _public prototype_ `void AddWeightmap(const FName& InWeightmapLayerName);` — Adds a weightmap to the list of active weightmaps (make sure ELandscapeToolTargetType::Weightmap is amongst the supported target types)
- L138 _public prototype_ `void AddWeightmapChecked(const FName& InWeightmapLayerName);` — Adds a weightmap to the list of active weightmaps (make sure ELandscapeToolTargetType::Weightmap is amongst the supported target types). Asserts if the layer name isn't known to the merge context.
- L141 _public prototype_ `void AddWeightmap(int32 InWeightmapLayerIndex);` — Adds a weightmap to the list of active weightmaps (make sure ELandscapeToolTargetType::Weightmap is amongst the supported target types). Asserts if the layer index isn't valid for the merge context
- L144 _public prototype_ `void RemoveWeightmap(const FName& InWeightmapLayerName);` — Removes a weightmap from the list of active weightmaps
- L147 _public prototype_ `void RemoveWeightmapChecked(const FName& InWeightmapLayerName);` — Removes a weightmap from the list of active weightmaps. Asserts if the layer name isn't known to the merge context.
- L150 _public prototype_ `void RemoveWeightmap(int32 InWeightmapLayerIndex);` — Removes a weightmap from the list of active weightmaps. Asserts if the layer index isn't valid for the merge context.
- L158 _public prototype_ `FEditLayerTargetTypeState Intersect(const FEditLayerTargetTypeState& InOther) const;` — Returns the "intersection" (AND operation) between the target type state and the one in parameter. e.g. if state S0 is: - (---------|Visibility|Weightmap) with active weightmaps (A|B|C|-), and state S1 is: - (Heightmap|----------|Weightmap) with active weightmaps (-|-|C|D), then state S0.Intersect(S1) is: - (---------|----------|Weightmap) with active weightmaps (-|-|C|-)
- L160 _public prototype_ `bool operator == (const FEditLayerTargetTypeState& InOther) const;`
- L162 _public prototype_ `FString ToString() const;`
- L166 _private member_ `const FMergeContext* MergeContext = nullptr;` — Global context being used for this merge : contains generic information about the landscape, its available layer names, etc.
- L169 _private member_ `ELandscapeToolTargetTypeFlags TargetTypeMask = ELandscapeToolTargetTypeFlags::None;` — Bitmask of the target types that are supported
- L175 _private member_ `TBitArray<> WeightmapTargetLayerBitIndices;` — List of weightmaps that are supported for the ELandscapeToolTargetType::Weightmap/ELandscapeToolTargetType::Visibility type. Each bit in that bit array corresponds to an entry in FMergeContext's AllTargetLayerNames

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Landscape` (scope `UE`)
- L14 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Landscape` (scope `UE`)
- L24 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)

### `Source/Runtime/Landscape/Public/LandscapeEditLayerTypes.h` (Public)


#### enum `UE::Landscape::EditLayers::EHeightmapBlendMode`  
`enum class EHeightmapBlendMode : uint32`  
_L15-22_
- desc: Must match EHeightmapBlendMode in LandscapeEditLayersHeightmaps.usf
- L17 _public enumerator_ `Additive = 0`
- L18 _public enumerator_ `LegacyAlphaBlend` — In legacy alpha blend, the layer stores the height with premultiplied alpha (legacy landscape splines)
- L19 _public enumerator_ `AlphaBlend`
- L21 _public enumerator_ `Num`

#### enum `UE::Landscape::EditLayers::EHeightmapAlphaFlags`  
`enum class EHeightmapAlphaFlags : uint8`  
_L28-35_
- desc: Must match EHeightmapAlphaFlags in LandscapeCommon.ush
- L30 _public enumerator_ `None = 0` — aka Additive
- L31 _public enumerator_ `Additive = 0` — The height is considered to be an offset (positive or negative)
- L32 _public enumerator_ `Min = (1 << 0)` — Only lower the existing landscape values
- L33 _public enumerator_ `Max = (1 << 1)` — Only raise the existing landscape values
- L34 _public enumerator_ `AlphaBlend = (Min | Max)` — Raise or lower the existing landscape values

#### enum `UE::Landscape::EditLayers::EWeightmapBlendMode`  
`enum class EWeightmapBlendMode : uint32`  
_L42-51_
- desc: Must match EWeightmapBlendMode in LandscapeEditLayersWeightmaps.usf
- L44 _public enumerator_ `None = 0` — aka Additive
- L45 _public enumerator_ `Additive = 0`
- L46 _public enumerator_ `Subtractive`
- L47 _public enumerator_ `Passthrough`
- L48 _public enumerator_ `AlphaBlend`
- L50 _public enumerator_ `Num`

#### enum `UE::Landscape::EditLayers::EWeightmapAlphaFlags`  
`enum class EWeightmapAlphaFlags : uint8`  
_L57-64_
- desc: Must match EWeightmapAlphaFlags in LandscapeCommon.ush
- L59 _public enumerator_ `None = 0` — aka Additive
- L60 _public enumerator_ `Additive = 0` — The weight is considered to be an offset (positive)
- L61 _public enumerator_ `Min = (1 << 0)` — Only retain the min between the weight and the existing landscape weight value
- L62 _public enumerator_ `Max = (1 << 1)` — Only retain the max between the weight and the existing landscape weight value
- L63 _public enumerator_ `AlphaBlend = (Min | Max)` — Full alpha blending of the weight against the existing landscape weight value

#### enum `UE::Landscape::EditLayers::EWeightmapTargetLayerFlags`  
`enum class EWeightmapTargetLayerFlags : uint32`  
_L71-79_
- desc: Must match EWeightmapTargetLayerFlags in LandscapeEditLayersWeightmaps.usf
- L73 _public enumerator_ `IsVisibilityLayer = (1 << 0)` — This target layer is the visibility layer
- L74 _public enumerator_ `IsWeightBlended = (1 << 1)` — Blend the target layer's value with all the other target layers weights
- L75 _public enumerator_ `Skip = (1 << 2)` — This layer should be skipped from blending because it has not been rendered in this batch
- L76 _public enumerator_ `IsPremultipliedAlphaWeightBlended = (1 << 3)` — Blend the target layer's weight with other target layers' weights of the same target layer blend group, using the premultiplied alpha blend formula
- L78 _public enumerator_ `None = 0`

#### struct `UE::Landscape::EditLayers::FFinalWeightBlendingTargetLayerInfo`  
`struct FFinalWeightBlendingTargetLayerInfo`  
_L86-89_
- desc: Must match FFinalWeightBlendingTargetLayerInfo in LandscapeEditLayersWeightmaps.usf
- L88 _public member_ `EWeightmapTargetLayerFlags Flags = EWeightmapTargetLayerFlags::None;` — Additional info about this target layer

#### struct `UE::Landscape::EditLayers::FMergeEditLayerTargetLayerInfo`  
`struct FMergeEditLayerTargetLayerInfo`  
_L95-99_
- desc: Must match FMergeEditLayerTargetLayerInfo in LandscapeEditLayersWeightmaps.usf
- L97 _public member_ `EWeightmapTargetLayerFlags Flags = EWeightmapTargetLayerFlags::None;` — Additional info about this target layer
- L98 _public member_ `int32 BlendGroupIndex = INDEX_NONE;` — Defines the target layer blend group that this target layer belongs to in this blend operation. -1 if not applicable

#### struct `UE::Landscape::EditLayers::FHeightmapBlendParams`  
`struct FHeightmapBlendParams`  
_L105-114_
- desc: Defines how heightmaps should be blended (see GenericBlendLayer)
- L107 _public prototype_ `FHeightmapBlendParams() = default;`
- L108 _public function_ `FHeightmapBlendParams(EHeightmapBlendMode InBlendMode) : BlendMode(InBlendMode)`
- L112 _public member_ `EHeightmapBlendMode BlendMode = EHeightmapBlendMode::Additive;`
- L113 _public member_ `float Alpha = 1.0f;`

#### struct `UE::Landscape::EditLayers::FWeightmapBlendParams`  
`struct FWeightmapBlendParams`  
_L120-141_
- desc: Defines how weightmaps should be blended (see GenericBlendLayer)
- L122 _public prototype_ `FWeightmapBlendParams() = default;`
- L123 _public function_ `FWeightmapBlendParams(EWeightmapBlendMode InBlendMode) : BlendMode(InBlendMode)`
- L127 _public function_ `static const FWeightmapBlendParams& GetDefaultPassthroughBlendParams()`
- L133 _public function_ `static const FWeightmapBlendParams& GetDefaultAdditiveBlendParams()`
- L139 _public member_ `EWeightmapBlendMode BlendMode = EWeightmapBlendMode::Passthrough;`
- L140 _public member_ `float Alpha = 1.0f;`

#### struct `UE::Landscape::EditLayers::FBlendParams`  
`struct FBlendParams`  
_L148-152_
- desc: Defines heightmaps+weightmaps blending params (see GenericBlendLayer) There should be as many blend params as there are target layers to be blended in the blend operation, the others are simply passthrough
- L150 _public member_ `FHeightmapBlendParams HeightmapBlendParams;`
- L151 _public member_ `TMap<FName, FWeightmapBlendParams> WeightmapBlendParams;`

#### enum `UE::Landscape::EditLayers::ERenderFlags`  
`enum class ERenderFlags : uint8`  
_L160-174_
- desc: Flags that allow a given ILandscapeEditLayerRenderer to customize the way it renders/blends
- L162 _public enumerator_ `None = 0`
- L165 _public enumerator_ `RenderMode_Recorded = (1 << 0)` — Render mode flags
- L166 _public enumerator_ `RenderMode_Immediate = (1 << 1)` — This renderer enqueues its render commands immediately either via the FRDGBuilderRecorder in "immediate" mode or just enqueuing render commands the usual way. Exclusive with RenderMode_Recorded
- L167 _public enumerator_ `RenderMode_Mask = RenderMode_Recorded | RenderMode_Immediate`
- L170 _public enumerator_ `BlendMode_SeparateBlend = (1 << 2)` — Blend mode flags
- L173 _public enumerator_ `RenderLayerGroup_SupportsGrouping = (1 << 3)` — Render layer group flags

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Landscape` (scope `UE`)
- L9 _namespace_ `namespace EditLayers` (scope `UE::Landscape`)
- L36 _prototype_ `ENUM_CLASS_FLAGS(EHeightmapAlphaFlags);` (scope `UE::Landscape::EditLayers`)
- L65 _prototype_ `ENUM_CLASS_FLAGS(EWeightmapAlphaFlags);` (scope `UE::Landscape::EditLayers`)
- L80 _prototype_ `ENUM_CLASS_FLAGS(EWeightmapTargetLayerFlags);` (scope `UE::Landscape::EditLayers`)
- L175 _prototype_ `ENUM_CLASS_FLAGS(ERenderFlags);` (scope `UE::Landscape::EditLayers`)

### `Source/Runtime/Landscape/Public/LandscapeEditResourcesSubsystem.h` (Public)


#### struct `UE::Landscape::FScratchRenderTargetParams`  
`struct FScratchRenderTargetParams`  
_L28-61_
- L30 _public prototype_ `FScratchRenderTargetParams() = default;`
- L31 _public function_ `explicit FScratchRenderTargetParams(const FString& InDebugName, bool bInExactDimensions, bool bInUseUAV, bool bInTargetArraySlicesIndependently, const FIntPoint& InResolution, int32 InNumSlices, ETextureRenderTargetFormat InFormat, const FLinearColor& InClearColor, ERHIAccess InInitialState) : DebugName(InDebugName) , bExactDimensions(bInExactDimensions) , bUseUAV(bInUseUAV) , bTargetArraySlicesIndependently(bInTargetArraySlicesIndependently) , Resolution(InResolution) , NumSlices(InNumSlices) , Format(InFormat) , ClearColor(InClearColor) , InitialState(InInitialState)`
- L44 _public member_ `FString DebugName;` — Allows to specify a friendly name for this render target (for the duration that the scratch render target is in use : a new name will be used the next time it's recycled)
- L46 _public member_ `bool bExactDimensions = false;` — Use this to make sure the returned render target has the exact dimension as was requested (if false, a larger RT might be recycled)
- L48 _public member_ `bool bUseUAV = false;` — Requires the render target to have the ETextureCreateFlags::UAV flag
- L50 _public member_ `bool bTargetArraySlicesIndependently = false;` — Requires the render target to have the ETextureCreateFlags::TargetArraySlicesIndependently flag
- L52 _public member_ `FIntPoint Resolution = FIntPoint(ForceInit);` — Requested (minimal) resolution for this render target
- L54 _public member_ `int32 NumSlices = 0;` — Number of slices requested for this render target. 0 means the render target will be a UTextureRenderTarget2D, > 0 means it will be a UTextureRenderTarget2DArray
- L56 _public member_ `ETextureRenderTargetFormat Format = ETextureRenderTargetFormat::RTF_RGBA8;` — Format of the requested render target
- L58 _public member_ `FLinearColor ClearColor = FLinearColor(ForceInitToZero);` — Default clear color of the requested render target
- L60 _public member_ `ERHIAccess InitialState = ERHIAccess::None;` — (optional) State the render target should be in when it's being requested

#### struct `UE::Landscape::FScratchRenderTargetScope`  
`struct FScratchRenderTargetScope : public FNoncopyable`  
_L63-71_
- inherits: `FNoncopyable`
- L65 _public prototype_ `FScratchRenderTargetScope() = delete;`
- L66 _public prototype_ `FScratchRenderTargetScope(const FScratchRenderTargetParams& InParams);`
- L67 _public prototype_ `~FScratchRenderTargetScope();`
- L69 _public member_ `ULandscapeEditResourcesSubsystem* EditResourcesSubsystem = nullptr;`
- L70 _public member_ `ULandscapeScratchRenderTarget* RenderTarget = nullptr;`

#### class `ULandscapeScratchRenderTarget`  
`class ULandscapeScratchRenderTarget : public UObject`  
_L82-239_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: ULandscapeScratchRenderTarget holds a UTextureRenderTarget2D. It can be used in the landscape tools as transient memory by requesting/releasing an instance via ULandscapeEditResourcesSubsystem It contains information about the current state (ERHIAccess) of the resource in order to automate/minimize state transitions. In order to minimize memory consumption, the internal render target can be larger than what was requested. It's therefore important to take that into account when setting up draw calls on this render target and use GetEffectiveResolution() instead of the RT's resolution
- L90 _public prototype_ `ULandscapeScratchRenderTarget();`
- L93 _public prototype_ `const FString& GetDebugName() const;` — @return a debug name while this render target is in use. This helps track things down, since the underlying resource can be recycled
- L95 _public function_ `UTextureRenderTarget* GetRenderTarget() const` — @return Getter for the internal UTextureRenderTarget
- L97 _public prototype_ `UTextureRenderTarget2D* GetRenderTarget2D() const;` — @return Getter for the internal UTextureRenderTarget2D (only when CurrentRenderTargetParams.NumSlices == 0, asserts if CurrentRenderTargetParams.NumSlices > 0)
- L99 _public prototype_ `UTextureRenderTarget2D* TryGetRenderTarget2D() const;` — @return the internal UTextureRenderTarget2D (only when CurrentRenderTargetParams.NumSlices == 0, returns nullptr if CurrentRenderTargetParams.NumSlices > 0)
- L101 _public prototype_ `UTextureRenderTarget2DArray* GetRenderTarget2DArray() const;` — @return the internal UTextureRenderTarget2DArray (only when CurrentRenderTargetParams.NumSlices > 0, asserts if CurrentRenderTargetParams.NumSlices == 0)
- L103 _public prototype_ `UTextureRenderTarget2DArray* TryGetRenderTarget2DArray() const;` — @return the internal UTextureRenderTarget2DArray (only when CurrentRenderTargetParams.NumSlices > 0, returns nullptr if CurrentRenderTargetParams.NumSlices == 0)
- L105 _public prototype_ `FIntPoint GetResolution() const;` — @return the internal render target's true resolution (can be different than the effective resolution if CurrentRenderTargetParams.bExactDimensions is false)
- L107 _public prototype_ `FIntPoint GetEffectiveResolution() const;` — @return the internal render target's effective resolution (can be different than the actual resolution if CurrentRenderTargetParams.bExactDimensions is false) while this render target is in use
- L109 _public prototype_ `int32 GetNumSlices() const;` — @return the internal render target's number of slices (can be different than the actual number of slices if CurrentRenderTargetParams.bExactDimensions is false)
- L111 _public prototype_ `int32 GetEffectiveNumSlices() const;` — @return the internal render target's effective number of slices (can be different than the actual number of slices if CurrentRenderTargetParams.bExactDimensions is false) while this render target is in use
- L112 _public function_ `bool IsTexture2D() const`
- L113 _public function_ `bool IsTexture2DArray() const`
- L114 _public prototype_ `ETextureRenderTargetFormat GetFormat() const;`
- L115 _public prototype_ `FLinearColor GetClearColor() const;`
- L116 _public function_ `ERHIAccess GetCurrentState() const`
- L117 _public function_ `const UE::Landscape::FScratchRenderTargetParams& GetCurrentRenderTargetParams()`
- L188 _public prototype_ `void CopyFrom(const FCopyFromTextureParams& InCopyParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder);` — Copies the content of the texture in parameter to the scratch texture (assuming the input texture is in CopySrc state already). Transitions the scratch texture's RHIAccess @param InCopyParams parameters for the texture to copy from @param RDGBuilderRecorder when the recorder is in "recording" mode, the copy's render command enqueuing will be delayed to the render thread, after a FRDGBuilder has been created but the scratch render target's current state will still be mutated to reflect the state change on the game thread. In "immediate" mode, a render command will be enqueued immediately
- L196 _public prototype_ `void CopyFrom(const FCopyFromScratchRenderTargetParams& InCopyParams, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder);` — Copies the content of the scratch texture in parameter to the scratch texture. Transitions both scratch textures' RHIAccess @param InCopyParams parameters for the scratch texture to copy from @param RDGBuilderRecorder when the recorder is in "recording" mode, the copy's render command enqueuing will be delayed to the render thread, after a FRDGBuilder has been created but the scratch render targets' current state will still be mutated to reflect the state changes on the game thread. In "immediate" mode, a render command will be enqueued immediately
- L204 _public prototype_ `void TransitionTo(ERHIAccess InStateAfter, UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder);` — Perform a transition of the scratch texture's RHIAccess @param InStateAfter desired RHIAccess of the scratch render target @param RDGBuilderRecorder  when the recorder is in "recording" mode, the transition's render command enqueuing will not be executed (we assume the FRDGBuilder will take care of it) but the scratch render target's current state will still be mutated to reflect the state change on the game thread. In "immediate" mode, a render command will be enqueued immediately
- L211 _public prototype_ `void Clear(UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder);` — Perform a clear of the scratch texture @param RDGBuilderRecorder  when the recorder is in "recording" mode, the clear's render command enqueuing will be delayed to the render thread, after a FRDGBuilder has been created but the scratch render target's current state will still be mutated to reflect the state change on the game thread. In "immediate" mode, a render command will be enqueued immediately
- L214 _public prototype_ `bool IsCompatibleWith(const UE::Landscape::FScratchRenderTargetParams& InParams) const;` — @return true if this scratch texture is compatible (and can therefore be used) with the requested render target params
- L217 _public function_ `bool IsInUse() const` — @return true if the scratch texture is currently in use (it has been requested but not released)
- L220 _private prototype_ `void OnRequested(const UE::Landscape::FScratchRenderTargetParams& InParams);`
- L221 _private prototype_ `void OnReleased();`
- L225 _private member_ `TObjectPtr<UTextureRenderTarget> RenderTarget;` — `UPROPERTY(NonTransactional)`
- L232 _private member_ `ETextureRenderTargetFormat RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8;` — Format of the render target. Technically, we could infer it from RenderTarget->Format but since it's stored as a EPixelFormat, end there's no easy conversion from EPixelFormat to ETextureRenderTargetFormat, we store a copy here instead:
- L236 _private member_ `bool bIsInUse = false;` — Current state of the scratch render target :
- L237 _private member_ `UE::Landscape::FScratchRenderTargetParams CurrentRenderTargetParams;`
- L238 _private member_ `ERHIAccess CurrentState = ERHIAccess::None;`

#### class `ULandscapeScratchRenderTarget::FTransitionInfo`  
`class FTransitionInfo`  
_L119-135_
- L122 _public prototype_ `FTransitionInfo() = default;`
- L123 _public function_ `FTransitionInfo(FTextureResource* InResource, ERHIAccess InStateBefore, ERHIAccess InStateAfter) : Resource(InResource) , StateBefore(InStateBefore) , StateAfter(InStateAfter)`
- L129 _public prototype_ `FRHITransitionInfo ToRHITransitionInfo() const;`
- L132 _private member_ `FTextureResource* Resource = nullptr;`
- L133 _private member_ `ERHIAccess StateBefore = ERHIAccess::None;`
- L134 _private member_ `ERHIAccess StateAfter = ERHIAccess::None;`

#### class `ULandscapeScratchRenderTarget::FTransitionBatcherScope`  
`class FTransitionBatcherScope : public FNoncopyable`  
_L137-148_
- inherits: `FNoncopyable`
- L140 _public prototype_ `FTransitionBatcherScope(UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder);`
- L141 _public prototype_ `~FTransitionBatcherScope();`
- L143 _public prototype_ `void TransitionTo(ULandscapeScratchRenderTarget* InScratchRenderTarget, ERHIAccess InStateAfter);`
- L146 _private member_ `UE::Landscape::FRDGBuilderRecorder& RDGBuilderRecorder;`
- L147 _private member_ `TArray<FTransitionInfo> PendingTransitions;`

#### struct `ULandscapeScratchRenderTarget::FCopyFromParams`  
`struct FCopyFromParams`  
_L150-159_
- L152 _public member_ `FIntPoint CopySize = FIntPoint(0, 0);`
- L153 _public member_ `FIntPoint SourcePosition = FIntPoint(0, 0);`
- L154 _public member_ `FIntPoint DestPosition = FIntPoint(0, 0);`
- L155 _public member_ `uint8 SourceMip = 0;`
- L156 _public member_ `uint8 DestMip = 0;`
- L157 _public member_ `uint32 SourceSliceIndex = 0;`
- L158 _public member_ `uint32 DestSliceIndex = 0;`

#### struct `ULandscapeScratchRenderTarget::FCopyFromTextureParams`  
`struct FCopyFromTextureParams : public FCopyFromParams`  
_L161-168_
- inherits: `FCopyFromParams`
- L163 _public function_ `explicit FCopyFromTextureParams(UTexture* InSourceTexture) : SourceTexture(InSourceTexture)`
- L167 _public member_ `UTexture* SourceTexture = nullptr;`

#### struct `ULandscapeScratchRenderTarget::FCopyFromScratchRenderTargetParams`  
`struct FCopyFromScratchRenderTargetParams : public FCopyFromParams`  
_L170-180_
- inherits: `FCopyFromParams`
- L172 _public function_ `explicit FCopyFromScratchRenderTargetParams(ULandscapeScratchRenderTarget* InSourceScratchRenderTarget) : SourceScratchRenderTarget(InSourceScratchRenderTarget)`
- L179 _public member_ `ULandscapeScratchRenderTarget* SourceScratchRenderTarget = nullptr;`

#### class `ULandscapeEditResourcesSubsystem`  
`class ULandscapeEditResourcesSubsystem : public UEngineSubsystem`  
_L243-307_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: ULandscapeEditResourcesSubsystem provides services to manage/pool render resources used by the landscape tools, across landscape actors, in order to minimize memory consumption
- L248 _public prototype_ `ULandscapeEditResourcesSubsystem();`
- L251 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — UEngineSubsystem implementation
- L252 _public prototype_ `virtual void Deinitialize() override;`
- L258 _public prototype_ `ULandscapeScratchRenderTarget* RequestScratchRenderTarget(const UE::Landscape::FScratchRenderTargetParams& InParams);` — Returns an existing (recycled) or new ULandscapeScratchRenderTarget @param InParams the requested attributes of the render target (see FScratchRenderTargetParams comments)
- L264 _public prototype_ `void ReleaseScratchRenderTarget(ULandscapeScratchRenderTarget* InScratchRenderTarget);` — Releases a previously requested ULandscapeScratchRenderTarget and returns it to the pool @param InScratchRenderTarget scratch render target to release
- L267 _public function_ `UMaterialInterface* GetLayerDebugColorMaterial() const`
- L268 _public function_ `UMaterialInterface* GetSelectionColorMaterial() const`
- L269 _public function_ `UMaterialInterface* GetSelectionRegionMaterial() const`
- L270 _public function_ `UMaterialInterface* GetMaskRegionMaterial() const`
- L271 _public function_ `UMaterialInterface* GetColorMaskRegionMaterial() const`
- L272 _public function_ `UTexture2D* GetLandscapeBlackTexture() const`
- L273 _public function_ `UMaterialInterface* GetLandscapeLayerUsageMaterial() const`
- L274 _public function_ `UMaterialInterface* GetLandscapeDirtyMaterial() const`
- L279 _private member_ `TArray<TObjectPtr<ULandscapeScratchRenderTarget>> ScratchRenderTargets;` — `UPROPERTY(Transient, NonTransactional)`
- L283 _private member_ `TObjectPtr<UMaterialInterface> LayerDebugColorMaterial;` — `UPROPERTY(Transient, NonTransactional)`
- L286 _private member_ `TObjectPtr<UMaterialInterface> SelectionColorMaterial;` — `UPROPERTY(Transient, NonTransactional)`
- L289 _private member_ `TObjectPtr<UMaterialInterface> SelectionRegionMaterial;` — `UPROPERTY(Transient, NonTransactional)`
- L292 _private member_ `TObjectPtr<UMaterialInterface> MaskRegionMaterial;` — `UPROPERTY(Transient, NonTransactional)`
- L295 _private member_ `TObjectPtr<UMaterialInterface> ColorMaskRegionMaterial;` — `UPROPERTY(Transient, NonTransactional)`
- L298 _private member_ `TObjectPtr<UTexture2D> LandscapeBlackTexture;` — `UPROPERTY(Transient, NonTransactional)`
- L301 _private member_ `TObjectPtr<UMaterialInterface> LandscapeLayerUsageMaterial;` — `UPROPERTY(Transient, NonTransactional)`
- L304 _private member_ `TObjectPtr<UMaterialInterface> LandscapeDirtyMaterial;` — `UPROPERTY(Transient, NonTransactional)`

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Landscape` (scope `UE`)

### `Source/Runtime/Landscape/Public/LandscapeEditTypes.h` (Public)


#### enum `ELandscapeToolTargetType`  
`enum class ELandscapeToolTargetType : uint8`  
_L11-18_
- reflection: `UENUM()`
- L13 _public enumerator_ `Heightmap = 0`
- L14 _public enumerator_ `Weightmap = 1`
- L15 _public enumerator_ `Visibility = 2`
- L16 _public enumerator_ `Invalid = 3 UMETA(Hidden)` — only valid for LandscapeEdMode->CurrentToolTarget.TargetType
- L17 _public enumerator_ `Count = Invalid UMETA(Hidden)` — Only the elements above Invalid actually count as proper target types

#### enum `ELandscapeToolTargetTypeFlags`  
`enum class ELandscapeToolTargetTypeFlags : uint8`  
_L21-28_
- L23 _public enumerator_ `None = 0`
- L24 _public enumerator_ `Heightmap = (1 << static_cast<uint8>(ELandscapeToolTargetType::Heightmap))`
- L25 _public enumerator_ `Weightmap = (1 << static_cast<uint8>(ELandscapeToolTargetType::Weightmap))`
- L26 _public enumerator_ `Visibility = (1 << static_cast<uint8>(ELandscapeToolTargetType::Visibility))`
- L27 _public enumerator_ `All = Heightmap | Weightmap | Visibility`

#### enum `ELandscapeTargetLayerBlendMethod`  
`enum class ELandscapeTargetLayerBlendMethod : uint8`  
_L32-38_
- reflection: `UENUM()`
- L34 _public enumerator_ `None = 0 UMETA(DisplayName = "No Weight Blending", Tooltip = "The target layer's weight is unaffected by other target layers.")`
- L35 _public enumerator_ `FinalWeightBlending UMETA(DisplayName = "Weight Blending (Legacy)", Tooltip = "The target layer's weight is adjusted against the weights of the other (legacy) weight-blended target layers such that their sum is 0. Doesn't work well when combined with edit layers, as this (horizontal) blend is only applied at the end of the edit layers (vertical) blending.")`
- L36 _public enumerator_ `PremultipliedAlphaBlending UMETA(DisplayName = "Advanced Weight Blending", Tooltip = "The target layer's weight is adjusted against the weights of the other advanced weight-blended target layers such that their sum is 0. Takes into account edit layers : the blending is applied at each edit layer, such that the target layer's weight will always be weight-blended but will also retain its relative weight against other edit layers underneath.")`
- L37 _public enumerator_ `Count UMETA(Hidden)` — Only the elements above actually count as proper target types

#### enum `UE::Landscape::EOutdatedDataFlags`  
`enum class EOutdatedDataFlags : uint8`  
_L43-59_
- L45 _public enumerator_ `None = 0`
- L48 _public enumerator_ `GrassMaps = (1 << 0)` — Actual flags :
- L49 _public enumerator_ `PhysicalMaterials = (1 << 1)`
- L50 _public enumerator_ `NaniteMeshes = (1 << 2)`
- L51 _public enumerator_ `PackageModified = (1 << 3)`
- L54 _public enumerator_ `LastPlusOne` — Not real flags, only useful to loop through the actual flags :
- L55 _public enumerator_ `Last = LastPlusOne - 1`
- L58 _public enumerator_ `All = (GrassMaps | PhysicalMaterials | NaniteMeshes | PackageModified)` — Combined flags :

#### enum `UE::Landscape::EBuildFlags`  
`enum class EBuildFlags : uint8`  
_L69-75_
- L71 _public enumerator_ `None = 0`
- L73 _public enumerator_ `WriteFinalLog = (1 << 0)` — Log a message at the end of the build operation
- L74 _public enumerator_ `ForceRebuild = (1 << 1)` — Forces a rebuild even if not needed

#### Free symbols / members of external scopes

- L19 _prototype_ `ENUM_RANGE_BY_COUNT(ELandscapeToolTargetType, ELandscapeToolTargetType::Count);`
- L29 _prototype_ `ENUM_CLASS_FLAGS(ELandscapeToolTargetTypeFlags);`
- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace Landscape` (scope `UE`)
- L60 _prototype_ `ENUM_CLASS_FLAGS(EOutdatedDataFlags);` (scope `UE::Landscape`)
- L62 _function_ `inline uint32 GetOutdatedDataFlagIndex(EOutdatedDataFlags InFlag)` (scope `UE::Landscape`)

### `Source/Runtime/Landscape/Public/LandscapeEditorServices.h` (Public)


#### class `ILandscapeEditorServices`  
`class ILandscapeEditorServices`  
_L7-28_
- L10 _public prototype_ `virtual ~ILandscapeEditorServices() = default;`
- L21 _public prototype_ `virtual int32 GetOrCreateEditLayer(FName InEditLayerName, ALandscape* InTargetLandscape, const TSubclassOf<ULandscapeEditLayerBase>& InEditLayerClass = TSubclassOf<ULandscapeEditLayerBase>()) = 0;` — Attempts to find an edit layer named InEditLayerName in InTargetLandscape. Creates the layer if it does not exist. @param InEditLayerName The name of the layer to search for and possibly create @param InTargetLandscape The landscape which should have a layer called InEditLayerName @param InEditLayerClass The class of the edit layer to create. If none specified, a standard edit layer (ULandscapeEditLayer) will be created @return The index at which the edit layer named InEditLayerName exists
- L24 _public prototype_ `virtual void RefreshDetailPanel() = 0;` — Requires the landscape editor mode, if active, to refresh its detail panel
- L27 _public prototype_ `virtual void RegenerateLayerThumbnails() = 0;` — Requires the landscape editor mode, if active, to invalidate all of its thumbnails

### `Source/Runtime/Landscape/Public/LandscapeHLODBuilder.h` (Public)


#### class `ULandscapeHLODBuilder`  
`class ULandscapeHLODBuilder : public UHLODBuilder`  
_L11-24_
- reflection: `UCLASS(HideDropdown, MinimalAPI)`
- inherits: `UHLODBuilder`
- L17 _public prototype_ `virtual bool ComputeHLODHash(FHLODHashBuilder& HashBuilder, const UActorComponent* InSourceComponent) const override;`
- L22 _public prototype_ `virtual TArray<UActorComponent*> Build(const FHLODBuildContext& InHLODBuildContext, const TArray<UActorComponent*>& InSourceComponents) const override;` — Components created with this method need to be properly outered & assigned to your target actor.

### `Source/Runtime/Landscape/Public/LandscapeLight.h` (Public)


#### class `FLandscapeStaticLightingTextureMapping`  
`class FLandscapeStaticLightingTextureMapping : public FStaticLightingTextureMapping`  
_L22-51_
- inherits: `FStaticLightingTextureMapping`
- desc: A texture mapping for landscapes
- L26 _public prototype_ `FLandscapeStaticLightingTextureMapping(ULandscapeComponent* InPrimitive,FStaticLightingMesh* InMesh,int32 InLightMapWidth,int32 InLightMapHeight,bool bPerformFullQualityRebuild);` — Initialization constructor.
- L29 _public prototype_ `virtual void Apply(FQuantizedLightmapData* QuantizedData, const TMap<ULightComponent*,FShadowMapData2D*>& ShadowMapData, const FStaticLightingBuildContext* LightingContext);` — FStaticLightingTextureMapping interface
- L36 _public prototype_ `virtual void ExportMapping(FLightmassExporter* Exporter);` — Export static lighting mapping instance data to an exporter @param Exporter - export interface to process static lighting data
- L37 _public prototype_ `virtual void Serialize(FArchive& Ar);`
- L41 _public prototype_ `FLandscapeStaticLightingTextureMapping(const FArchive& Ar);`
- L43 _public function_ `virtual FString GetDescription() const`
- L50 _private member_ `ULandscapeComponent* LandscapeComponent;` — The primitive this mapping represents.

#### class `FLandscapeStaticLightingGlobalVolumeMapping`  
`class FLandscapeStaticLightingGlobalVolumeMapping : public FLandscapeStaticLightingTextureMapping`  
_L53-84_
- inherits: `FLandscapeStaticLightingTextureMapping`
- L56 _public prototype_ `FLandscapeStaticLightingGlobalVolumeMapping(ULandscapeComponent* InPrimitive,FStaticLightingMesh* InMesh,int32 InLightMapWidth,int32 InLightMapHeight,bool bPerformFullQualityRebuild);`
- L58 _public function_ `virtual void Apply(struct FQuantizedLightmapData* QuantizedData, const TMap<ULightComponent*,class FShadowMapData2D*>& ShadowMapData, const FStaticLightingBuildContext* LightingContext) override`
- L65 _public function_ `virtual bool DebugThisMapping() const override`
- L74 _public prototype_ `virtual void ExportMapping(class FLightmassExporter* Exporter) override;` — Export static lighting mapping instance data to an exporter @param Exporter - export interface to process static lighting data
- L78 _public function_ `virtual bool IsValidMapping() const override` — Whether or not this mapping should be processed or imported
- L80 _public function_ `virtual FString GetDescription() const override`

#### class `FLandscapeStaticLightingMesh`  
`class FLandscapeStaticLightingMesh : public FStaticLightingMesh`  
_L88-141_
- inherits: `FStaticLightingMesh`
- desc: Represents the triangles of a Landscape component to the static lighting system.
- L92 _public prototype_ `FLandscapeStaticLightingMesh(ULandscapeComponent* InComponent, const TArray<ULightComponent*>& InRelevantLights, int32 InExpandQuadsX, int32 InExpandQuadsY, float LightMapRatio, int32 InLOD);` — tors
- L93 _public prototype_ `virtual ~FLandscapeStaticLightingMesh();`
- L96 _public prototype_ `virtual void GetTriangle(int32 TriangleIndex,FStaticLightingVertex& OutV0,FStaticLightingVertex& OutV1,FStaticLightingVertex& OutV2) const;` — FStaticLightingMesh interface
- L97 _public prototype_ `virtual void GetTriangleIndices(int32 TriangleIndex,int32& OutI0,int32& OutI1,int32& OutI2) const;`
- L98 _public prototype_ `virtual FLightRayIntersection IntersectLightRay(const FVector& Start,const FVector& End,bool bFindNearestIntersection) const;`
- L100 _public function_ `virtual bool IsInstancedMesh() const override`
- L107 _public prototype_ `virtual void ExportMeshInstance(FLightmassExporter* Exporter) const;` — Export static lighting mesh instance data to an exporter @param Exporter - export interface to process static lighting data
- L111 _protected prototype_ `void GetHeightmapData(int32 InLOD, int32 GeometryLOD);`
- L114 _protected prototype_ `void GetStaticLightingVertex(int32 VertexIndex, FStaticLightingVertex& OutVertex) const;` — Fills in the static lighting vertex data for the Landscape vertex.
- L116 _protected member_ `ULandscapeComponent* LandscapeComponent;`
- L119 _protected member_ `FTransform LocalToWorld;` — FLandscapeStaticLightingMeshData
- L120 _protected member_ `int32 ComponentSizeQuads;`
- L121 _protected member_ `float LightMapRatio;`
- L122 _protected member_ `int32 ExpandQuadsX;`
- L123 _protected member_ `int32 ExpandQuadsY;`
- L125 _protected member_ `TArray<FColor> HeightData;`
- L127 _protected member_ `int32 NumVertices;` — Cache
- L128 _protected member_ `int32 NumQuads;`
- L129 _protected member_ `float UVFactor;`
- L130 _protected member_ `bool bReverseWinding;`
- L137 _public member_ `static TMap<FIntPoint, FColor> LandscapeUpscaleHeightDataCache;` — Cache data for Landscape upscaling data
- L139 _public member_ `static TMap<FIntPoint, FColor> LandscapeUpscaleXYOffsetDataCache;` — `UE_DEPRECATED(5.7, "RetopologizeTool/XYOffset deprecated with the removal of non-edit layer landscapes")`

#### Free symbols / members of external scopes

- L144 _namespace_ `namespace (anonymous)`
- L152 _function_ `static float GetTerrainExpandPatchCount(float LightMapRes, int32& X, int32& Y, int32 ComponentSize, int32 LightmapSize, int32& DesiredSize, uint32 LightingLOD)` (scope `__anon1df2b84a0111`) — LightmapRes: Multiplier of lightmap size relative to landscape size X: (Output) PatchExpandCountX (at Lighting LOD) Y: (Output) PatchExpandCountY (at Lighting LOD) ComponentSize: Component size in patches (at LOD 0) LigtmapSize: Size desired for lightmap (texels) DesiredSize: (Output) Recommended lightmap size (texels) return: LightMapRatio

### `Source/Runtime/Landscape/Public/LandscapeModule.h` (Public)


#### class `ILandscapeModule`  
`class ILandscapeModule : public IModuleInterface`  
_L22-35_
- inherits: `IModuleInterface`
- desc: Landscape module interface
- L25 _public prototype_ `virtual TSharedPtr<FLandscapeSceneViewExtension, ESPMode::ThreadSafe> GetLandscapeSceneViewExtension() const = 0;`
- L27 _public prototype_ `virtual void SetLandscapeEditorServices(ILandscapeEditorServices* InLandscapeEditorServices) PURE_VIRTUAL(ILandscapeModule::SetLandscapeEditorServices, );`
- L28 _public prototype_ `virtual ILandscapeEditorServices* GetLandscapeEditorServices() const PURE_VIRTUAL(ILandscapeModule::GetLandscapeEditorServices, return nullptr; );`
- L29 _public prototype_ `virtual void SetCreateLandscapeComponentSceneProxyDelegate(const UE::Landscape::FCreateLandscapeComponentSceneProxyDelegate& InDelegate) PURE_VIRTUAL(ILandscapeModule::SetCreateLandscapeComponentSceneProxyDelegate, );`
- L30 _public prototype_ `virtual const UE::Landscape::FCreateLandscapeComponentSceneProxyDelegate& GetCreateLandscapeComponentSceneProxyDelegate() const PURE_VIRTUAL(ILandscapeModule::GetCreateLandscapeComponentSceneProxyDelegate, static UE::Landscape::FCreateLandscapeComponentSceneProxyDelegate Dummy; return Dummy; );`
- L32 _public prototype_ `virtual void SetSetupLandscapePSOPrecacheVertexFactoryDataListDelegate(const UE::Landscape::FSetupLandscapePSOPrecacheVertexFactoryDataListDelegate& InDelegate) PURE_VIRTUAL(ILandscapeModule::SetSetupLandscapePSOPrecacheVertexFactoryDataListDelegate, );`
- L33 _public prototype_ `virtual const UE::Landscape::FSetupLandscapePSOPrecacheVertexFactoryDataListDelegate& GetSetupLandscapePSOPrecacheVertexFactoryDataListDelegate() const PURE_VIRTUAL(ILandscapeModule::GetSetupLandscapePSOPrecacheVertexFactoryDataListDelegate, static UE::Landscape::FSetupLandscapePSOPrecacheVertexFactoryDataListDelegate Dummy; return Dummy; );`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Landscape` (scope `UE`)
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FPrimitiveSceneProxy*, FCreateLandscapeComponentSceneProxyDelegate, ULandscapeComponent* );`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FPrimitiveSceneProxy*, FCreateLandscapeComponentSceneProxyDelegate, ULandscapeComponent* );` (scope `UE::Landscape`)
- L16 _delegate_ `DECLARE_DELEGATE_TwoParams(FSetupLandscapePSOPrecacheVertexFactoryDataListDelegate, ULandscapeComponent* , FPSOPrecacheVertexFactoryDataList& );`
- L16 _prototype_ `DECLARE_DELEGATE_TwoParams(FSetupLandscapePSOPrecacheVertexFactoryDataListDelegate, ULandscapeComponent* , FPSOPrecacheVertexFactoryDataList& );` (scope `UE::Landscape`)

### `Source/Runtime/Landscape/Public/LandscapeNotification.h` (Public)


#### enum `ELandscapeNotificationType`  
`enum class ELandscapeNotificationType`  
_L11-16_
- desc: The various types of landscape notifications, ordered by priority (a single notification is displayed at a time).
- L13 _public enumerator_ `ShadingModelInvalid = 0`
- L14 _public enumerator_ `LandscapeTextureResourcesNotReady`
- L15 _public enumerator_ `LandscapeEditLayerResourcesNotReady`

#### struct `FLandscapeNotification`  
`struct FLandscapeNotification`  
_L18-63_
- L20 _public typedef_ `using FConditionCallback = TFunction<bool(void)>;`
- L21 _public typedef_ `using FUpdateTextCallback = TFunction<void(FText&)>;`
- L31 _public function_ `FLandscapeNotification(const TWeakObjectPtr<ALandscape>& InLandscape, ELandscapeNotificationType InNotificationType, FConditionCallback InConditionCallback = FConditionCallback([]() { return true; }), FUpdateTextCallback InUpdateTextCallback = [](FText& InText) {});` — Constructs a notification which is expected to have a longer lifetime and behave in a dynamic way. @param InLandscape - The landscape actor associated with this notification. @param InNotificationType - The type of notification which determines its display priority. @param InConditionCallback - Lambda used to conditionally determine whether this notification should be displayed per tick. @param InUpdateTextCallback - Lambda used to construct notification text when the text can change (e.g. displaying the value of a variable).
- L31 _public prototype_ `FLandscapeNotification(const TWeakObjectPtr<ALandscape>& InLandscape, ELandscapeNotificationType InNotificationType, FConditionCallback InConditionCallback = FConditionCallback([]() { return true; }), FUpdateTextCallback InUpdateTextCallback = [](FText& InText) {});` — Constructs a notification which is expected to have a longer lifetime and behave in a dynamic way. @param InLandscape - The landscape actor associated with this notification. @param InNotificationType - The type of notification which determines its display priority. @param InConditionCallback - Lambda used to conditionally determine whether this notification should be displayed per tick. @param InUpdateTextCallback - Lambda used to construct notification text when the text can change (e.g. displaying the value of a variable).
- L32 _public prototype_ `~FLandscapeNotification() = default;`
- L34 _public prototype_ `bool operator == (const FLandscapeNotification& Other) const;`
- L35 _public prototype_ `bool operator < (const FLandscapeNotification& Other) const;`
- L37 _public function_ `TWeakObjectPtr<ALandscape> GetLandscape() const`
- L38 _public function_ `ELandscapeNotificationType GetNotificationType() const`
- L41 _public prototype_ `bool ShouldShowNotification() const;` — Public wrappers for the callback functions.
- L42 _public prototype_ `void SetNotificationText();`
- L45 _private prototype_ `FLandscapeNotification() = delete;`
- L49 _public member_ `FText NotificationText;` — The text to be displayed.Can either be set by user directly or by setting SetTextCallback at notification construction.
- L52 _public member_ `double NotificationStartTime = -1.0;` — Determines when a notification should be displayed, ignored if less than 0.
- L55 _private member_ `TWeakObjectPtr<ALandscape> Landscape;`
- L56 _private member_ `ELandscapeNotificationType NotificationType;`
- L59 _private member_ `FConditionCallback ConditionCallback;` — Determines whether or not a notification should be shown. Defaults to return true.
- L62 _private member_ `FUpdateTextCallback UpdateTextCallback;` — Sets the notification text per frame by manipulating InText&. Defaults to do nothing, allowing direct manipulation of NotificationText.

#### class `FLandscapeNotificationManager`  
`class FLandscapeNotificationManager`  
_L68-86_
- desc: FLandscapeNotificationManager : centralizes landscape-related user notifications so that the user doesn't get flooded by toasts when multiple messages from possibly multiple landscapes are tossed around
- L71 _public prototype_ `~FLandscapeNotificationManager();`
- L73 _public prototype_ `void Tick();`
- L75 _public prototype_ `void RegisterNotification(const TWeakPtr<FLandscapeNotification>& InNotification);`
- L76 _public prototype_ `void UnregisterNotification(const TWeakPtr<FLandscapeNotification>& InNotification);`
- L79 _private prototype_ `void ShowNotificationItem(const FText& InText);`
- L80 _private prototype_ `void HideNotificationItem();`
- L83 _private member_ `TArray<TWeakPtr<FLandscapeNotification>> LandscapeNotifications;`
- L84 _private member_ `TWeakPtr<FLandscapeNotification> ActiveNotification;`
- L85 _private member_ `TWeakPtr<SNotificationItem> NotificationItem;`

### `Source/Runtime/Landscape/Public/LandscapeRender.h` (Public)


#### enum `ELandscapeViewMode::Type`  
`enum Type: int32`  
_L54-67_
- L56 _public enumerator_ `Invalid = -1`
- L58 _public enumerator_ `Normal = 0` — Color only
- L59 _public enumerator_ `EditLayer`
- L61 _public enumerator_ `DebugLayer` — Layer debug only
- L62 _public enumerator_ `LayerDensity`
- L63 _public enumerator_ `LayerUsage`
- L64 _public enumerator_ `LOD`
- L65 _public enumerator_ `WireframeOnTop`
- L66 _public enumerator_ `LayerContribution`

#### enum `ELandscapeEditRenderMode::Type`  
`enum Type`  
_L74-85_
- L76 _public enumerator_ `None = 0x0`
- L77 _public enumerator_ `Gizmo = 0x1`
- L78 _public enumerator_ `SelectRegion = 0x2`
- L79 _public enumerator_ `SelectComponent = 0x4`
- L80 _public enumerator_ `Select = SelectRegion | SelectComponent`
- L81 _public enumerator_ `Mask = 0x8`
- L82 _public enumerator_ `InvertedMask = 0x10` — Should not be overlapped with other bits
- L83 _public enumerator_ `BitMaskForMask = Mask | InvertedMask`

#### struct `FLandscapeBatchElementParams`  
`struct FLandscapeBatchElementParams`  
_L146-156_
- desc: Data needed for the landscape vertex factory to set the render state for an individual batch element
- L149 _public member_ `FRHIUniformBuffer* LandscapeVertexFactoryMVFUniformBuffer;`
- L151 _public member_ `const TUniformBuffer<FLandscapeUniformShaderParameters>* LandscapeUniformShaderParametersResource;`
- L152 _public member_ `const TArray<TUniformBuffer<FLandscapeFixedGridUniformShaderParameters>>* FixedGridUniformShaderParameters;`
- L153 _public member_ `FUniformBufferRHIRef LandscapeSectionLODUniformParameters;`
- L154 _public member_ `const FLandscapeComponentSceneProxy* SceneProxy;`
- L155 _public member_ `int32 CurrentLOD;`

#### class `FLandscapeElementParamArray`  
`class FLandscapeElementParamArray : public FOneFrameResource`  
_L158-162_
- inherits: `FOneFrameResource`
- L161 _public member_ `TArray<FLandscapeBatchElementParams, SceneRenderingAllocator> ElementParams;`

#### class `FLandscapeVertexFactoryVertexShaderParameters`  
`class FLandscapeVertexFactoryVertexShaderParameters : public FVertexFactoryShaderParameters`  
_L164-187_
- inherits: `FVertexFactoryShaderParameters`
- L172 _public function_ `void Bind(const FShaderParameterMap& ParameterMap)` — Bind shader constants by name @param	ParameterMap - mapping of named shader constants to indices
- L176 _public prototype_ `void GetElementShaderBindings( const class FSceneInterface* Scene, const FSceneView* InView, const class FMeshMaterialShader* Shader, const EVertexInputStreamType InputStreamType, ERHIFeatureLevel::Type FeatureLevel, const FVertexFactory* VertexFactory, const FMeshBatchElement& BatchElement, class FMeshDrawSingleShaderBindings& ShaderBindings, FVertexInputStreamArray& VertexStreams ) const;`

#### class `FLandscapeVertexFactoryPixelShaderParameters`  
`class FLandscapeVertexFactoryPixelShaderParameters : public FVertexFactoryShaderParameters`  
_L190-208_
- inherits: `FVertexFactoryShaderParameters`
- desc: Pixel shader parameters for use with FLandscapeVertexFactory
- L194 _public prototype_ `void GetElementShaderBindings( const class FSceneInterface* Scene, const FSceneView* InView, const class FMeshMaterialShader* Shader, const EVertexInputStreamType InputStreamType, ERHIFeatureLevel::Type FeatureLevel, const FVertexFactory* VertexFactory, const FMeshBatchElement& BatchElement, class FMeshDrawSingleShaderBindings& ShaderBindings, FVertexInputStreamArray& VertexStreams ) const;`

#### class `FLandscapeVertexFactory`  
`class FLandscapeVertexFactory : public FVertexFactory`  
_L211-267_
- inherits: `FVertexFactory`
- desc: vertex factory for VTF-heightmap terrain
- L217 _public prototype_ `FLandscapeVertexFactory(ERHIFeatureLevel::Type InFeatureLevel);`
- L219 _public function_ `virtual ~FLandscapeVertexFactory()`
- L234 _public prototype_ `static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);` — Should we cache the material's shadertype on this platform with this vertex factory?
- L239 _public prototype_ `static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);` — Can be overridden by FVertexFactory subclasses to modify their compile environment just before compilation occurs.
- L244 _public prototype_ `static void GetPSOPrecacheVertexFetchElements(EVertexInputStreamType VertexInputStreamType, FVertexDeclarationElementList& Elements);` — Get vertex elements used when during PSO precaching materials using this vertex factory type
- L250 _public prototype_ `void Copy(const FLandscapeVertexFactory& Other);` — Copy the data from another vertex factory @param Other - factory to copy from
- L253 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — FRenderResource interface.
- L254 _public function_ `virtual void ReleaseResource() override final`
- L259 _public function_ `void SetData(const FDataType& InData)` — An implementation of the interface used by TSynchronizedResource to update the resource with new data from the game thread.
- L266 _public member_ `FDataType Data;` — stream component data bound to this vertex factory

#### struct `FLandscapeVertexFactory::FDataType`  
`struct FDataType`  
_L225-229_
- L228 _public member_ `FVertexStreamComponent PositionComponent;` — The stream to read the vertex position from.

#### class `FLandscapeXYOffsetVertexFactory`  
`class UE_DEPRECATED(5.7, "XYOffset deprecated with the removal of non-edit layer landscapes") FLandscapeXYOffsetVertexFactory : public FLandscapeVertexFactory`  
_L271-280_
- inherits: `FLandscapeVertexFactory`
- desc: vertex factory for VTF-heightmap terrain
- L276 _public function_ `FLandscapeXYOffsetVertexFactory(ERHIFeatureLevel::Type InFeatureLevel) : FLandscapeVertexFactory(InFeatureLevel)`

#### class `FLandscapeFixedGridVertexFactory`  
`class FLandscapeFixedGridVertexFactory : public FLandscapeVertexFactory`  
_L284-295_
- inherits: `FLandscapeVertexFactory`
- desc: Vertex factory for fixed grid runtime virtual texture lod
- L289 _public function_ `FLandscapeFixedGridVertexFactory(ERHIFeatureLevel::Type InFeatureLevel) : FLandscapeVertexFactory(InFeatureLevel)`
- L294 _public prototype_ `static void ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment);`

#### struct `FLandscapeVertex`  
`struct FLandscapeVertex`  
_L298-304_
- L300 _public member_ `uint8 VertexX;`
- L301 _public member_ `uint8 VertexY;`
- L302 _public member_ `uint8 SubX;`
- L303 _public member_ `uint8 SubY;`

#### class `FLandscapeVertexBuffer`  
`class FLandscapeVertexBuffer final : public FVertexBuffer`  
_L309-338_
- inherits: `FVertexBuffer`
- desc: FLandscapeVertexBuffer
- L311 _private member_ `ERHIFeatureLevel::Type FeatureLevel;`
- L312 _private member_ `int32 NumVertices;`
- L313 _private member_ `int32 SubsectionSizeVerts;`
- L314 _private member_ `int32 NumSubsections;`
- L318 _public function_ `FLandscapeVertexBuffer(FRHICommandListBase& RHICmdList, ERHIFeatureLevel::Type InFeatureLevel, int32 InNumVertices, int32 InSubsectionSizeVerts, int32 InNumSubsections, const FName& InOwnerName) : FeatureLevel(InFeatureLevel) , NumVertices(InNumVertices) , SubsectionSizeVerts(InSubsectionSizeVerts) , NumSubsections(InNumSubsections)` — Constructor.
- L329 _public function_ `virtual ~FLandscapeVertexBuffer()` — Destructor.
- L337 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Initialize the RHI for this rendering resource

#### class `FLandscapeSharedBuffers`  
`class FLandscapeSharedBuffers : public FRefCountedObject`  
_L343-394_
- inherits: `FRefCountedObject`
- desc: FLandscapeSharedBuffers
- L354 _public member_ `int32 NumVertices;`
- L355 _public member_ `int32 SharedBuffersKey;`
- L356 _public member_ `int32 NumIndexBuffers;`
- L357 _public member_ `int32 SubsectionSizeVerts;`
- L358 _public member_ `int32 NumSubsections;`
- L359 _public member_ `int32 NumRayTracingSections;`
- L361 _public member_ `FLandscapeVertexFactory* VertexFactory;`
- L362 _public member_ `FLandscapeVertexFactory* FixedGridVertexFactory;`
- L363 _public member_ `FLandscapeVertexBuffer* VertexBuffer;`
- L365 _public member_ `TArray<TUniformBuffer<FLandscapeFixedGridUniformShaderParameters>> LandscapeFixedGridUniformShaderParameters;`
- L367 _public member_ `FRenderResource* TileMesh;`
- L368 _public member_ `FLandscapeVertexFactory* TileVertexFactory;`
- L369 _public member_ `FVertexBuffer* TileDataBuffer;`
- L372 _public member_ `FIndexBuffer** IndexBuffers;` — array per mip level, storing FIndexBuffer pointers
- L375 _public member_ `FLandscapeIndexRanges* IndexRanges;` — array per mip level, storing index buffer ranges per subssection, and for the entire component
- L377 _public member_ `bool bUse32BitIndices;`
- L378 _public member_ `FIndexBuffer* GrassIndexBuffer;`
- L379 _public member_ `TArray<int32, TInlineAllocator<8>> GrassIndexMipOffsets;`
- L382 _public member_ `TArray<FIndexBuffer*> ZeroOffsetIndexBuffers;`
- L385 _public prototype_ `FLandscapeSharedBuffers(FRHICommandListBase& RHICmdList, int32 SharedBuffersKey, int32 SubsectionSizeQuads, int32 NumSubsections, int32 NumRayTracingSections, ERHIFeatureLevel::Type FeatureLevel, const FName& OwnerName = NAME_None);`
- L388 _public prototype_ `template <typename INDEX_TYPE> void CreateIndexBuffers(FRHICommandListBase& RHICmdList, const FName& OwnerName);`
- L391 _public prototype_ `template <typename INDEX_TYPE> void CreateGrassIndexBuffer(FRHICommandListBase& RHICmdList, const FName& InOwnerName);`
- L393 _public prototype_ `virtual ~FLandscapeSharedBuffers();`

#### struct `FLandscapeSharedBuffers::FLandscapeIndexRanges`  
`struct FLandscapeIndexRanges`  
_L346-352_
- L348 _public member_ `int32 MinIndex[LANDSCAPE_MAX_SUBSECTION_NUM][LANDSCAPE_MAX_SUBSECTION_NUM];`
- L349 _public member_ `int32 MaxIndex[LANDSCAPE_MAX_SUBSECTION_NUM][LANDSCAPE_MAX_SUBSECTION_NUM];`
- L350 _public member_ `int32 MinIndexFull;`
- L351 _public member_ `int32 MaxIndexFull;`

#### class `FLandscapeSectionInfo`  
`class FLandscapeSectionInfo : public TIntrusiveLinkedList<FLandscapeSectionInfo>`  
_L400-443_
- inherits: `TIntrusiveLinkedList<FLandscapeSectionInfo>`
- L403 _public prototype_ `FLandscapeSectionInfo(const UWorld* InWorld, const FGuid& InLandscapeGuid, const FIntPoint& InComponentBase, uint32 LODGroupKey, uint32 InLandscapeKey);`
- L404 _public prototype_ `virtual ~FLandscapeSectionInfo() = default;`
- L406 _public prototype_ `virtual float ComputeLODForView(const FSceneView& InView) const = 0;`
- L407 _public prototype_ `virtual float ComputeLODBias() const = 0;`
- L408 _public function_ `virtual int32 GetSectionPriority() const`
- L409 _public prototype_ `virtual const FPrimitiveSceneInfo* GetPrimitiveSceneInfo() const = 0;`
- L412 _public function_ `virtual double ComputeSectionResolution() const` — Computes the worldspace units per vertex of the landscape section.
- L414 _public prototype_ `virtual void GetSectionBoundsAndLocalToWorld(FBoxSphereBounds& LocalBounds, FMatrix& LocalToWorld) const = 0;`
- L415 _public prototype_ `virtual void GetSectionCenterAndVectors(FVector& OutSectionCenterWorldSpace, FVector& OutSectionXVectorWorldSpace, FVector& OutSectionYVectorWorldSpace) const = 0;`
- L418 _public function_ `virtual int32 GetComponentResolution() const` — return the resolution of a component, in vertices (-1 for any sections that are not grid based, i.e. mesh sections)
- L421 _public prototype_ `virtual void OnRenderCoordsChanged(FRHICommandListBase& RHICmdList) = 0;` — Used to notify derived classes when render coords are calculated
- L423 _public function_ `virtual bool ShouldInvalidateShadows(const FSceneView& InView, float InLODValue, float InLastShadowInvalidationLODValue) const`
- L426 _public prototype_ `virtual void RayTracingNotifyViewDeleted(uint32 ViewKey) = 0;`
- L431 _public member_ `uint32 LandscapeKey = 0;` — A hash of the world and (LandscapeGUID or LOD Group Key)
- L433 _public member_ `uint32 LODGroupKey = 0;` — LOD Group Key (0 if no group)
- L435 _public member_ `FIntPoint RenderCoord = FIntPoint(INT32_MIN, INT32_MIN);` — Coordinate in the RenderSystem
- L437 _public member_ `FIntPoint ComponentBase = FIntPoint(ForceInit);` — Component base coordinate (relative to the ALandscape actor)
- L439 _public member_ `FSceneInterface* Scene = nullptr;` — Scene that this landscape section belongs to
- L441 _public member_ `bool bResourcesCreated = false;`
- L442 _public member_ `bool bRegistered = false;`

#### struct `FLandscapeRenderSystem`  
`struct FLandscapeRenderSystem`  
_L448-573_
- desc: FLandscapeRenderSystem
- L450 _public typedef_ `typedef uint32 FViewKey;`
- L465 _public prototype_ `static float ComputeLODFromScreenSize(const LODSettingsComponent& InLODSettings, float InScreenSizeSquared);`
- L467 _public member_ `static TBitArray<> LandscapeIndexAllocator;`
- L469 _public member_ `int32 LandscapeIndex;`
- L471 _public member_ `FIntPoint Min;`
- L472 _public member_ `FIntPoint Size;`
- L474 _public member_ `TResourceArray<float> SectionLODBiases;`
- L475 _public member_ `TArray<FLandscapeSectionInfo*> SectionInfos;`
- L477 _public member_ `int32 ReferenceCount;` — Number of sections with resources created
- L479 _public member_ `int32 RegisteredCount;` — Number of sections registered
- L481 _public member_ `FBufferRHIRef SectionLODBiasBuffer;`
- L482 _public member_ `FShaderResourceViewRHIRef SectionLODBiasSRV;`
- L484 _public member_ `FUniformBufferRHIRef SectionLODUniformBuffer;`
- L489 _public member_ `TMap<const FSceneView*, TResourceArray<float>> PerViewCachedSectionLODValues;` — For a given view, we use those 2 maps to store, for each FLandscapeSectionInfo in SectionInfos, the current LOD Values so that it can be passed down to the renderer These are only really valid for a given render since the list of sections can change in the next frame. The first map is for views that don't have a persistent view state
- L490 _public member_ `TMap<uint32, TResourceArray<float>> PerViewStateCachedSectionLODValues;` — Key = view state key corresponding to the view to render, Value = linear list of LOD values for each FLandscapeSectionInfo
- L495 _public typedef_ `using SectionKeyToLODValueMap = TMap<FIntPoint, float>;` — This map allows to track, for each FLandscapeSectionInfo that triggered a shadow invalidation, the LOD value that was used when the invalidation occurred Key = SectionInfo's RenderCoord (we cannot use a linear index like the TMaps above because these might change as new sections get added/removed dynamically and this needs to be tracked across frames) Value = LOD value of the section when the last shadow invalidation occurred
- L496 _public member_ `TMap<uint32, SectionKeyToLODValueMap> PerViewStateLastShadowInvalidationSectionLODValues;` — Key = view state key corresponding to the view to render, Value = see above
- L499 _public member_ `TMap<UE::Renderer::Private::IShadowInvalidatingInstances*, TArray<const FPrimitiveSceneInfo*>> ShadowInvalidationRequests;` — List of shadow invalidations to perform this frame (because IShadowInvalidatingInstances is not parallel-render thread-safe, we have to store them temporarily and issue them on the render thread later on) :
- L502 _public member_ `int8 ForcedLODOverride;` — Forced LOD level which overrides the ForcedLOD level of all the sections under this LandscapeRenderSystem.
- L505 _public member_ `int32 ComponentResolution = -1;` — Resolution, Origin and Size, for use in LOD Groups to verify that all landscapes are of matching resolutions, orientation and scale
- L506 _public member_ `FVector ComponentOrigin = FVector::ZeroVector;` — world space position of the center of the origin component (render coord 0,0)
- L507 _public member_ `FVector ComponentXVector = FVector::ZeroVector;` — world space vector in the direction of component local X
- L508 _public member_ `FVector ComponentYVector = FVector::ZeroVector;` — world space vector in the direction of component local Y
- L511 _public member_ `int32 SectionsRemovedSinceLastCompact;` — Counter used to reduce how often we call compact on the map when removing sections
- L513 _public member_ `uint32 LandscapeKey = 0;`
- L514 _public member_ `FSceneInterface* Scene = nullptr;`
- L516 _public prototype_ `FLandscapeRenderSystem(uint32 InLandscapeKey, FSceneInterface* InScene);`
- L517 _public prototype_ `~FLandscapeRenderSystem();`
- L519 _public prototype_ `static void CreateResources(FRHICommandListBase& RHICmdList, FLandscapeSectionInfo* SectionInfo);`
- L520 _public prototype_ `static void DestroyResources(FLandscapeSectionInfo* SectionInfo);`
- L522 _public prototype_ `static void RegisterSection(FLandscapeSectionInfo* SectionInfo);`
- L523 _public prototype_ `static void UnregisterSection(FLandscapeSectionInfo* SectionInfo);`
- L525 _public function_ `bool IsValidCoord(FIntPoint InRenderCoord) const`
- L531 _public function_ `int32 GetSectionLinearIndex(FIntPoint InRenderCoord) const`
- L538 _public prototype_ `void ResizeAndMoveTo(FIntPoint NewMin, FIntPoint NewMax);`
- L539 _public prototype_ `void ResizeToInclude(const FIntPoint& NewCoord);`
- L540 _public prototype_ `void CompactMap();`
- L541 _public prototype_ `bool AnySectionsInRangeInclusive(FIntPoint RangeMin, FIntPoint RangeMax);`
- L543 _public function_ `void SetSectionInfo(FIntPoint InRenderCoord, FLandscapeSectionInfo* InSectionInfo)`
- L551 _public function_ `FLandscapeSectionInfo* GetSectionInfo(FIntPoint InRenderCoord)`
- L560 _public prototype_ `float GetSectionLODValue(const FSceneView& InView, FIntPoint InRenderCoord) const;`
- L561 _public prototype_ `const TResourceArray<float>& GetCachedSectionLODValues(const FSceneView& InView) const;`
- L563 _public prototype_ `float GetSectionLODBias(FIntPoint InRenderCoord) const;`
- L565 _public prototype_ `const TResourceArray<float>& ComputeSectionsLODForView(const FSceneView& InView, UE::Renderer::Private::IShadowInvalidatingInstances* InShadowInvalidatingInstances);`
- L566 _public prototype_ `void PerformShadowInvalidations(UE::Renderer::Private::IShadowInvalidatingInstances& InShadowInvalidatingInstances);`
- L567 _public prototype_ `void FetchHeightmapLODBiases();`
- L568 _public prototype_ `void UpdateBuffers(FRHICommandListBase& RHICmdList);`
- L571 _private prototype_ `void CreateResources_Internal(FRHICommandListBase& RHICmdList, FLandscapeSectionInfo* InSectionInfo);`
- L572 _private prototype_ `void DestroyResources_Internal(FLandscapeSectionInfo* InSectionInfo);`

#### struct `FLandscapeRenderSystem::LODSettingsComponent`  
`struct LODSettingsComponent`  
_L452-463_
- L454 _public member_ `float LOD0ScreenSizeSquared;`
- L455 _public member_ `float LOD1ScreenSizeSquared;`
- L456 _public member_ `float LODOnePlusDistributionScalarSquared;`
- L457 _public member_ `float LastLODScreenSizeSquared;`
- L458 _public member_ `float VirtualShadowMapInvalidationLimitLOD;`
- L459 _public member_ `int8 LastLODIndex;`
- L460 _public member_ `int8 ForcedLOD;`
- L461 _public member_ `int8 DrawCollisionPawnLOD;`
- L462 _public member_ `int8 DrawCollisionVisibilityLOD;`

#### class `FLandscapeLODOverridesCustomRenderPassUserData`  
`class FLandscapeLODOverridesCustomRenderPassUserData : public ICustomRenderPassUserData`  
_L578-592_
- inherits: `ICustomRenderPassUserData`
- desc: FLandscapeLODOverridesCustomRenderPassUserData
- L581 _public prototype_ `IMPLEMENT_CUSTOM_RENDER_PASS_USER_DATA(FLandscapeLODOverridesCustomRenderPassUserData);`
- L583 _public function_ `FLandscapeLODOverridesCustomRenderPassUserData(const TMap<uint32, int32>& InLandscapeLODOverrides) : LandscapeLODOverrides(InLandscapeLODOverrides)`
- L588 _public function_ `const TMap<uint32, int32>& GetLandscapeLODOverrides() const`
- L591 _private member_ `TMap<uint32, int32> LandscapeLODOverrides;`

#### class `FLandscapeSceneViewExtension`  
`class FLandscapeSceneViewExtension : public FSceneViewExtensionBase`  
_L597-636_
- inherits: `FSceneViewExtensionBase`
- desc: FLandscapeSceneViewExtension
- L600 _public prototype_ `FLandscapeSceneViewExtension(const FAutoRegister& AutoReg);`
- L601 _public prototype_ `virtual ~FLandscapeSceneViewExtension();`
- L603 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L605 _public prototype_ `virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;`
- L606 _public prototype_ `virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;`
- L607 _public prototype_ `virtual void PreInitViews_RenderThread(FRDGBuilder& GraphBuilder) override;`
- L609 _public prototype_ `static const TMap<uint32, FLandscapeRenderSystem*>& GetLandscapeRenderSystems();`
- L610 _public prototype_ `static TArray<FLandscapeRenderSystem*> GetLandscapeRenderSystems(const class FSceneInterface* InScene);`
- L611 _public prototype_ `static FLandscapeRenderSystem* GetLandscapeRenderSystem(const class FSceneInterface* InScene, uint32 InLandscapeKey);`
- L612 _public function_ `int32 GetNumViewsWithShowCollision() const`
- L615 _private prototype_ `void EndFrame_GameThread();`
- L616 _private prototype_ `void EndFrame_RenderThread();`
- L632 _private member_ `TArray<FLandscapeViewData> LandscapeViews;`
- L633 _private member_ `UE::Tasks::FTask LandscapeSetupTask;`
- L634 _private member_ `int32 NumViewsWithShowCollision = 0;` — Last frame number of views with collision enabled.
- L635 _private member_ `int32 NumViewsWithShowCollisionAcc = 0;` — Accumulate the number of views with collision

#### struct `FLandscapeSceneViewExtension::FLandscapeViewData`  
`struct FLandscapeViewData`  
_L620-630_
- L622 _public prototype_ `FLandscapeViewData() = default;`
- L623 _public prototype_ `FLandscapeViewData(FSceneView& InView);`
- L625 _public member_ `FSceneView* View = nullptr;`
- L627 _public member_ `UE::Renderer::Private::IShadowInvalidatingInstances* ShadowInvalidatingInstances = nullptr;` — Optional interface to use if the view needs to invalidate the shadow cache :
- L628 _public member_ `TResourceArray<uint32> LandscapeIndirection;`
- L629 _public member_ `TResourceArray<float> LandscapeLODData;`

#### struct `FLandscapeDebugOptions`  
`struct FLandscapeDebugOptions`  
_L641-654_
- desc: FLandscapeDebugOptions
- L643 _public prototype_ `FLandscapeDebugOptions();`
- L645 _public member_ `bool bShowPatches;`
- L646 _public member_ `bool bDisableStatic;`
- L649 _private member_ `FAutoConsoleCommand PatchesConsoleCommand;`
- L650 _private member_ `FAutoConsoleCommand StaticConsoleCommand;`
- L652 _private prototype_ `void Patches();`
- L653 _private prototype_ `void Static();`

#### class `FLandscapeMeshProxySceneProxy`  
`class FLandscapeMeshProxySceneProxy final : public FStaticMeshSceneProxy`  
_L661-678_
- inherits: `FStaticMeshSceneProxy`
- desc: FLandscapeMeshProxySceneProxy
- L664 _public prototype_ `SIZE_T GetTypeHash() const override;`
- L666 _public prototype_ `FLandscapeMeshProxySceneProxy(UStaticMeshComponent* InComponent, const FGuid& InLandscapeGuid, const TArray<FIntPoint>& InProxySectionsBases, const TArray<FVector>& InProxySectionsCentersLocalSpace, const FVector& InComponentXVector, const FVector& InComponentYVector, const FTransform& LocalToWorld, int32 ComponentResolution, int8 InProxyLOD, uint32 InLODGroupKey, uint32 LandscapeKey);`
- L667 _public prototype_ `virtual void CreateRenderThreadResources(FRHICommandListBase& RHICmdList) override;`
- L668 _public prototype_ `virtual void DestroyRenderThreadResources() override;`
- L671 _protected prototype_ `virtual void OnForceHiddenChanged() override;`
- L674 _private prototype_ `void RegisterSections();`
- L675 _private prototype_ `void UnregisterSections();`
- L677 _private member_ `TArray<TUniquePtr<FLandscapeSectionInfo>> ProxySectionsInfos;`

#### class `FLandscapeComponentSceneProxy`  
`class FLandscapeComponentSceneProxy : public FPrimitiveSceneProxy, public FLandscapeSectionInfo`  
_L683-936_
- inherits: `FPrimitiveSceneProxy,FLandscapeSectionInfo`
- desc: FLandscapeComponentSceneProxy
- L687 _private prototype_ `SIZE_T GetTypeHash() const override;`
- L726 _public member_ `static const int8 MAX_SUBSECTION_COUNT = 2*2;`
- L729 _public member_ `TPimplPtr<FLandscapeRayTracingImpl> RayTracingImpl;`
- L737 _public member_ `static TMap<uint32, FLandscapeSharedBuffers*> SharedBuffersMap;` — Reference counted vertex and index buffer shared among all landscape scene proxies of the same component size Key is the component size and number of subsections. Also being reused by GPULightmass currently to save mem
- L741 _protected member_ `int8 MaxLOD;` — Maximum LOD level, user override possible
- L742 _protected member_ `int8 NumWeightmapLayerAllocations;`
- L743 _protected member_ `uint8 StaticLightingLOD;`
- L744 _protected member_ `uint8 VirtualTexturePerPixelHeight;`
- L745 _protected member_ `float WeightmapSubsectionOffset;`
- L747 _protected member_ `TArray<float> LODScreenRatioSquared;` — Table of valid screen size -> LOD index
- L749 _protected member_ `int32 FirstLOD;` — First LOD we have batch elements for
- L751 _protected member_ `int32 LastLOD;` — Last LOD we have batch elements for
- L752 _protected member_ `int32 FirstVirtualTextureLOD;`
- L753 _protected member_ `int32 LastVirtualTextureLOD;`
- L755 _protected member_ `float ComponentMaxExtend;` — The max extend value in any axis
- L757 _protected member_ `float InvLODBlendRange;` — 1.0 / LODBlendRange
- L759 _protected member_ `FLandscapeRenderSystem::LODSettingsComponent LODSettings;`
- L765 _protected member_ `int32 NumSubsections;` — Number of subsections within the component in each dimension, this can be 1 or 2. Subsections exist to improve the speed at which LOD transitions can take place over distance.
- L767 _protected member_ `int32 SubsectionSizeQuads;` — Number of unique heights in the subsection.
- L769 _protected member_ `int32 SubsectionSizeVerts;` — Number of heightmap heights in the subsection. This includes the duplicate row at the end.
- L771 _protected member_ `int32 ComponentSizeQuads;` — Size of the component in unique heights.
- L776 _protected member_ `int32 ComponentSizeVerts;` — ComponentSizeQuads + 1. Note: in the case of multiple subsections, this is not very useful, as there will be an internal duplicate row of heights in addition to the row at the end.
- L778 _protected member_ `int32 NumRayTracingSections;` — Number of ray tracing sections in a landscape section for better culling and optimized BLAS builds
- L780 _protected member_ `float StaticLightingResolution;`
- L782 _protected member_ `FIntPoint SectionBase;` — Address of the component within the parent Landscape in unique height texels.
- L784 _protected member_ `FMatrix LocalToWorldNoScaling;`
- L787 _protected member_ `TArray<FLandscapeBatchElementParams> StaticBatchParamArray;` — Storage for static draw list batch params
- L789 _protected member_ `bool bNaniteActive;`
- L790 _protected member_ `bool bUsesLandscapeCulling;`
- L793 _protected member_ `FMeshBatch GrassMeshBatch;` — Precomputed grass rendering MeshBatch and per-LOD params
- L794 _protected member_ `TArray<FLandscapeBatchElementParams> GrassBatchParams;`
- L796 _protected member_ `FVector4f WeightmapScaleBias;`
- L797 _protected member_ `TArray<UTexture2D*> WeightmapTextures;`
- L799 _protected member_ `UTexture2D* VisibilityWeightmapTexture;`
- L800 _protected member_ `int32 VisibilityWeightmapChannel;`
- L803 _protected member_ `TArray<FLinearColor> LayerColors;`
- L804 _protected member_ `static ULandscapeEditResourcesSubsystem* LandscapeEditResourcesSubsystem;`
- L807 _protected member_ `UTexture2D* HeightmapTexture;` — Heightmap in RG and Normalmap in BA
- L808 _protected member_ `FVector4f HeightmapScaleBias;`
- L809 _protected member_ `float HeightmapSubsectionOffsetU;`
- L810 _protected member_ `float HeightmapSubsectionOffsetV;`
- L812 _protected member_ `uint32 SharedBuffersKey;`
- L813 _protected member_ `FLandscapeSharedBuffers* SharedBuffers;`
- L814 _protected member_ `FLandscapeVertexFactory* VertexFactory;`
- L815 _protected member_ `FLandscapeVertexFactory* FixedGridVertexFactory;`
- L818 _protected member_ `TArray<FMaterialRenderProxy*> AvailableMaterials;` — All available materials, including LOD Material, Tessellation generated materials
- L821 _protected member_ `TUniquePtr<FLandscapeLCI> ComponentLightInfo;` — FLightCacheInterface
- L824 _protected member_ `TArray<int8> LODIndexToMaterialIndex;` — Mapping between LOD and Material Index
- L827 _protected member_ `TArray<int8> MaterialIndexToStaticMeshBatchLOD;` — Mapping between Material Index to Static Mesh Batch
- L830 _protected member_ `TArray<FMaterialRelevance> MaterialRelevances;` — Material Relevance for each material in AvailableMaterials
- L833 _protected member_ `int32 NumRelevantMips = 0;` — Number of mips that are actually usable (that have more than 1 vertex)
- L838 _protected member_ `TArray<double> WorldSpaceMipToMipMaxDeltas;` — Maximum deltas between vertices and their counterparts from other mips (see additional details in ULandscapeComponent) Stored in world space to avoid useless runtime computation :
- L841 _protected member_ `float VirtualShadowMapConstantDepthBias;` — Constant bias to handle the worst artifacts of the continuous LOD morphing when rendering to VSM.
- L844 _protected member_ `float VirtualShadowMapInvalidationHeightErrorThreshold;` — Height threshold to invalidate VSM pages when using non-Nanite landscape.
- L847 _protected member_ `FLandscapeEditToolRenderData EditToolRenderData;`
- L852 _protected member_ `int32 CollisionMipLevel;`
- L853 _protected member_ `int32 SimpleCollisionMipLevel;`
- L855 _protected member_ `FCollisionResponseContainer CollisionResponse;`
- L860 _protected member_ `int32 LightMapResolution;` — LightMap resolution used for VMI_LightmapDensity
- L863 _protected member_ `TUniformBuffer<FLandscapeUniformShaderParameters> LandscapeUniformShaderParameters;`
- L866 _protected member_ `FMatrix WorldToLocal;` — Cached versions of these
- L869 _protected member_ `FName DebugName;`
- L873 _protected prototype_ `virtual ~FLandscapeComponentSceneProxy();`
- L875 _protected prototype_ `bool GetMeshElementForFixedGrid(int32 InLodIndex, FMaterialRenderProxy* InMaterialInterface, FMeshBatch& OutMeshBatch, TArray<FLandscapeBatchElementParams>& OutStaticBatchParamArray) const;`
- L876 _protected prototype_ `template<class ArrayType> bool GetStaticMeshElement(int32 LODIndex, bool bForToolMesh, FMeshBatch& MeshBatch, ArrayType& OutStaticBatchParamArray) const;`
- L878 _protected prototype_ `virtual void OnForceHiddenChanged() override;`
- L882 _public prototype_ `FLandscapeComponentSceneProxy(ULandscapeComponent* InComponent);` — constructor
- L885 _public prototype_ `virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI) override;` — FPrimitiveSceneProxy interface.
- L886 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;`
- L887 _public prototype_ `virtual void ApplyViewDependentMeshArguments(const FSceneView& View, FMeshBatch& ViewDependentMeshBatch) const override;`
- L888 _public function_ `virtual uint32 GetMemoryFootprint() const override`
- L889 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L890 _public prototype_ `virtual bool CanBeOccluded() const override;`
- L891 _public prototype_ `virtual void GetLightRelevance(const FLightSceneProxy* LightSceneProxy, bool& bDynamic, bool& bRelevant, bool& bLightMapped, bool& bShadowMapped) const override;`
- L892 _public prototype_ `virtual void OnTransformChanged(FRHICommandListBase& RHICmdList) override;`
- L893 _public prototype_ `virtual void CreateRenderThreadResources(FRHICommandListBase& RHICmdList) override;`
- L894 _public prototype_ `virtual void DestroyRenderThreadResources() override;`
- L902 _public function_ `const FMeshBatch& GetGrassMeshBatch() const`
- L905 _public prototype_ `virtual bool HeightfieldHasPendingStreaming() const override;` — FLandcapeSceneProxy
- L907 _public prototype_ `virtual void GetHeightfieldRepresentation(UTexture2D*& OutHeightmapTexture, UTexture2D*& OutVisibilityTexture, FHeightfieldComponentDescription& OutDescription) const override;`
- L909 _public prototype_ `virtual void GetLCIs(FLCIArray& LCIs) override;`
- L912 _public function_ `virtual int32 GetLightMapResolution() const override`
- L916 _public prototype_ `virtual void GetDynamicRayTracingInstances(FRayTracingInstanceCollector& Collector) override final;`
- L917 _public function_ `virtual bool HasRayTracingRepresentation() const override`
- L918 _public function_ `virtual bool IsRayTracingRelevant() const override`
- L922 _public prototype_ `virtual float ComputeLODForView(const FSceneView& InView) const override;` — FLandscapeSectionInfo interface
- L923 _public prototype_ `virtual float ComputeLODBias() const override;`
- L924 _public prototype_ `virtual void OnRenderCoordsChanged(FRHICommandListBase& RHICmdList) override;`
- L925 _public prototype_ `virtual int32 GetComponentResolution() const override;`
- L926 _public prototype_ `virtual double ComputeSectionResolution() const override;`
- L927 _public prototype_ `virtual void GetSectionBoundsAndLocalToWorld(FBoxSphereBounds& LocalBounds, FMatrix& LocalToWorld) const override;`
- L928 _public prototype_ `virtual void GetSectionCenterAndVectors(FVector& OutSectionCenterWorldSpace, FVector& OutSectionXVectorWorldSpace, FVector& OutSectionYVectorWorldSpace) const override;`
- L929 _public prototype_ `virtual const FPrimitiveSceneInfo* GetPrimitiveSceneInfo() const override;`
- L930 _public prototype_ `virtual bool ShouldInvalidateShadows(const FSceneView& InView, float InLODValue, float InLastShadowInvalidationLODValue) const override;`
- L933 _public prototype_ `virtual void RayTracingNotifyViewDeleted(uint32 ViewKey) override;`

#### class `FLandscapeComponentSceneProxy::FLandscapeLCI`  
`class FLandscapeLCI final : public FLightCacheInterface`  
_L688-723_
- inherits: `FLightCacheInterface`
- L692 _public function_ `FLandscapeLCI(const ULandscapeComponent* InComponent, ERHIFeatureLevel::Type FeatureLevel, bool bVFRequiresPrimitiveUniformBuffer) : FLightCacheInterface()` — Initialization constructor.
- L719 _public prototype_ `virtual FLightInteraction GetInteraction(const FLightSceneProxy* LightSceneProxy) const override;` — FLightCacheInterface
- L722 _private member_ `TArray<FGuid> IrrelevantLights;`

#### class `FLandscapeDebugMaterialRenderProxy`  
`class FLandscapeDebugMaterialRenderProxy : public FMaterialRenderProxy`  
_L938-1016_
- inherits: `FMaterialRenderProxy`
- L941 _public member_ `const FMaterialRenderProxy* const Parent;`
- L942 _public member_ `const UTexture2D* RedTexture;`
- L943 _public member_ `const UTexture2D* GreenTexture;`
- L944 _public member_ `const UTexture2D* BlueTexture;`
- L945 _public member_ `const FLinearColor R;`
- L946 _public member_ `const FLinearColor G;`
- L947 _public member_ `const FLinearColor B;`
- L950 _public function_ `FLandscapeDebugMaterialRenderProxy(const FMaterialRenderProxy* InParent, const UTexture2D* TexR, const UTexture2D* TexG, const UTexture2D* TexB, const FLinearColor& InR, const FLinearColor& InG, const FLinearColor& InB) : FMaterialRenderProxy(InParent->GetMaterialName()), Parent(InParent), RedTexture(TexR), GreenTexture(TexG), BlueTexture(TexB), R(InR), G(InG), B(InB)` — Initialization constructor.
- L963 _public function_ `virtual const FMaterial* GetMaterialNoFallback(ERHIFeatureLevel::Type InFeatureLevel) const override` — FMaterialRenderProxy interface.
- L968 _public function_ `virtual const FMaterialRenderProxy* GetFallback(ERHIFeatureLevel::Type InFeatureLevel) const override`
- L973 _public function_ `virtual bool GetParameterValue(EMaterialParameterType Type, const FHashedMaterialParameterInfo& ParameterInfo, FMaterialParameterValue& OutValue, const FMaterialRenderContext& Context) const`

#### class `FLandscapeSelectMaterialRenderProxy`  
`class FLandscapeSelectMaterialRenderProxy : public FMaterialRenderProxy`  
_L1018-1064_
- inherits: `FMaterialRenderProxy`
- L1021 _public member_ `const FMaterialRenderProxy* const Parent;`
- L1022 _public member_ `const UTexture2D* SelectTexture;`
- L1025 _public function_ `FLandscapeSelectMaterialRenderProxy(const FMaterialRenderProxy* InParent, const UTexture2D* InTexture) : FMaterialRenderProxy(InParent->GetMaterialName()), Parent(InParent), SelectTexture(InTexture)` — Initialization constructor.
- L1032 _public function_ `virtual const FMaterial* GetMaterialNoFallback(ERHIFeatureLevel::Type InFeatureLevel) const override` — FMaterialRenderProxy interface.
- L1036 _public function_ `virtual const FMaterialRenderProxy* GetFallback(ERHIFeatureLevel::Type InFeatureLevel) const override`
- L1041 _public function_ `virtual bool GetParameterValue(EMaterialParameterType Type, const FHashedMaterialParameterInfo& ParameterInfo, FMaterialParameterValue& OutValue, const FMaterialRenderContext& Context) const`

#### class `FLandscapeMaskMaterialRenderProxy`  
`class FLandscapeMaskMaterialRenderProxy : public FMaterialRenderProxy`  
_L1066-1114_
- inherits: `FMaterialRenderProxy`
- L1069 _public member_ `const FMaterialRenderProxy* const Parent;`
- L1070 _public member_ `const UTexture2D* SelectTexture;`
- L1071 _public member_ `const bool bInverted;`
- L1074 _public function_ `FLandscapeMaskMaterialRenderProxy(const FMaterialRenderProxy* InParent, const UTexture2D* InTexture, const bool InbInverted) : FMaterialRenderProxy(InParent->GetMaterialName()), Parent(InParent), SelectTexture(InTexture), bInverted(InbInverted)` — Initialization constructor.
- L1082 _public function_ `virtual const FMaterial* GetMaterialNoFallback(ERHIFeatureLevel::Type InFeatureLevel) const override` — FMaterialRenderProxy interface.
- L1086 _public function_ `virtual const FMaterialRenderProxy* GetFallback(ERHIFeatureLevel::Type InFeatureLevel) const override`
- L1091 _public function_ `virtual bool GetParameterValue(EMaterialParameterType Type, const FHashedMaterialParameterInfo& ParameterInfo, FMaterialParameterValue& OutValue, const FMaterialRenderContext& Context) const`

#### class `FLandscapeLayerUsageRenderProxy`  
`class FLandscapeLayerUsageRenderProxy : public FMaterialRenderProxy`  
_L1116-1199_
- inherits: `FMaterialRenderProxy`
- L1118 _private member_ `const FMaterialRenderProxy* const Parent;`
- L1120 _private member_ `int32 ComponentSizeVerts;`
- L1121 _private member_ `TArray<FLinearColor> LayerColors;`
- L1122 _private member_ `float Rotation;`
- L1124 _public function_ `FLandscapeLayerUsageRenderProxy(const FMaterialRenderProxy* InParent, int32 InComponentSizeVerts, const TArray<FLinearColor>& InLayerColors, float InRotation) : FMaterialRenderProxy(InParent->GetMaterialName()) , Parent(InParent) , ComponentSizeVerts(InComponentSizeVerts) , LayerColors(InLayerColors) , Rotation(InRotation)`
- L1133 _public function_ `virtual const FMaterial* GetMaterialNoFallback(ERHIFeatureLevel::Type InFeatureLevel) const override` — FMaterialRenderProxy interface.
- L1137 _public function_ `virtual const FMaterialRenderProxy* GetFallback(ERHIFeatureLevel::Type InFeatureLevel) const override`
- L1142 _public function_ `virtual bool GetParameterValue(EMaterialParameterType Type, const FHashedMaterialParameterInfo& ParameterInfo, FMaterialParameterValue& OutValue, const FMaterialRenderContext& Context) const`

#### Free symbols / members of external scopes

- L35 _macro_ `#define LANDSCAPE_LOD_LEVELS 8`
- L36 _macro_ `#define LANDSCAPE_MAX_SUBSECTION_NUM 2`
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace Renderer` (scope `UE`)
- L45 _namespace_ `namespace Private` (scope `UE::Renderer`)
- L52 _namespace_ `namespace ELandscapeViewMode`
- L70 _externvar_ `extern int32 GLandscapeViewMode;`
- L72 _namespace_ `namespace ELandscapeEditRenderMode`
- L88 _externvar_ `extern bool GLandscapeEditModeActive;`
- L89 _externvar_ `extern int32 GLandscapeEditRenderMode;`
- L92 _namespace_ `namespace UE`
- L92 _namespace_ `namespace Landscape` (scope `UE`)
- L94 _prototype_ `bool NeedsFixedGridVertexFactory(EShaderPlatform InShaderPlatform);` (scope `UE::Landscape`)
- L95 _prototype_ `bool ShouldBuildGrassMapRenderingResources();` (scope `UE::Landscape`)
- L96 _prototype_ `bool UseLandscapeVertexMask();` (scope `UE::Landscape`)
- L97 _prototype_ `EPSOPrecacheProxyCreationStrategy GetLandscapePSOPrecacheProxyCreationStrategy();` (scope `UE::Landscape`)
- L132 _typedef_ `typedef TUniformBufferRef<FLandscapeVertexFactoryMVFParameters> FLandscapeVertexFactoryMVFUniformBufferRef;`
- L656 _externvar_ `extern FLandscapeDebugOptions GLandscapeDebugOptions;`

### `Source/Runtime/Landscape/Public/LandscapeSettings.h` (Public)


#### enum `ELandscapeDirtyingMode`  
`enum class ELandscapeDirtyingMode : uint8`  
_L15-31_
- reflection: `UENUM()`
- L20 _public enumerator_ `Auto` — Auto : Landscapes that are marked as needing to be resaved will appear in the Choose files to save dialog. Changes are saved whenever the Landscape requires it.
- L25 _public enumerator_ `InLandscapeModeOnly` — In Landscape Mode Only : Landscapes that are marked as needing to be resaved will not appear in the Choose files to save dialog. This is a manual saving mode that puts the responsibility on the user to avoid file contention with other team members. The viewport will display an error message indicating that landscape actors are not up-to-date and need to be resaved. This is done using Build > Save Modified Landscapes (or Build > Build Landscape).
- L30 _public enumerator_ `InLandscapeModeAndUserTriggeredChanges` — In Landscape Mode And User Triggered Changes : Landscapes that are marked as needing to be resaved will not appear in the Choose files to save dialog. However, any user-triggered changes (direct or indirect) will require the Landscape to be resaved. This mode is recommended for team collaboration as it provides the best features of the other two modes while ensuring that modified landscape actors are still saved and properly submitted to source control.

#### enum `EFoliageLandscapeSnappingMode`  
`enum class EFoliageLandscapeSnappingMode : uint8`  
_L34-42_
- reflection: `UENUM()`
- L37 _public enumerator_ `DontSnap` — Foliage will not ever be snapped to the landscape
- L39 _public enumerator_ `SnapUnderBrushOnly` — Foliage will only be snapped on areas where the landscape sculpt brush tool was used. This doesn't include procedural changes (e.g. water brush) or global updates (e.g. deactivating a layer)
- L41 _public enumerator_ `SnapEverywhere` — Foliage will be snapped onto the entire landscape upon update. This includes procedural changes (e.g. water brush) or global updates (e.g. deactivating a layer)

#### class `ULandscapeSettings`  
`class ULandscapeSettings : public UDeveloperSettings`  
_L46-171_
- reflection: `UCLASS(config = Engine, defaultconfig, meta = (DisplayName = "Landscape"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L52 _public function_ `bool IsLandscapeResolutionRestricted() const` — Returns true if landscape resolution should be constrained.
- L55 _public function_ `bool AreBlueprintToolsAllowed() const` — Returns true if blueprint landscape tools usage is allowed
- L58 _public function_ `int32 GetTotalResolutionLimit() const` — Returns the current landscape resolution limit.
- L60 _public function_ `bool InRestrictiveMode() const`
- L61 _public function_ `void SetRestrictiveMode(bool bEnabled)`
- L63 _public function_ `int32 GetSideResolutionLimit() const`
- L65 _public function_ `float GetBrushSizeUIMax() const`
- L66 _public function_ `float GetBrushSizeClampMax() const`
- L68 _public function_ `int32 GetHLODMaxTextureSize() const`
- L70 _public function_ `float GetSplineIconWorldZOffset() const`
- L71 _public function_ `float GetSplineIconScale() const`
- L74 _public function_ `TSoftObjectPtr<UMaterialInterface> GetDefaultLandscapeMaterial() const` — Returns the default landscape material that should be used when creating a new landscape.
- L77 _public function_ `TSoftObjectPtr<ULandscapeLayerInfoObject> GetDefaultLayerInfoObject() const` — Returns the default landscape layer info object that will be assigned to unset layers when creating a new landscape.
- L79 _public function_ `bool GetShouldUpdateEditLayersDuringInteractiveChanges() const`
- L81 _public function_ `EFoliageLandscapeSnappingMode GetFoliageLandscapeSnappingMode() const`
- L83 _public function_ `bool ShouldDisplayTargetLayerThumbnails() const`
- L85 _public function_ `bool ShouldDisableTemporalAntiAliasingInLandscapeMode() const`
- L87 _public function_ `ELandscapeTargetLayerBlendMethod GetTargetLayerDefaultBlendMethod() const`
- L91 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L92 _public prototype_ `virtual void PreEditUndo() override;`
- L93 _public prototype_ `virtual void PostEditUndo() override;`
- L98 _public member_ `int32 MaxNumberOfLayers = 8;` — `UPROPERTY(config, EditAnywhere, Category = "Edit Layers", meta=(UIMin = "1", UIMax = "32", ClampMin = "1", ClampMax = "32", ToolTip = "This option controls the maximum editing layers that can be added to a Landscape"))`
- L102 _public member_ `bool bShowDialogForAutomaticLayerCreation = true;` — `UPROPERTY(EditAnywhere, config, Category = "Edit Layers", meta = (ToolTip = "When true, automatic edit layer creation pops up a dialog where the new layer can be reordered relative to other layers."))`
- L105 _public member_ `int32 MaxComponents = 256;` — `UPROPERTY(config, EditAnywhere, Category = "Configuration", meta=(ToolTip = "Maximum Dimension of Landscape in Components"))`
- L108 _public member_ `uint32 MaxImageImportCacheSizeMegaBytes = 256;` — `UPROPERTY(config, EditAnywhere, Category = "Configuration", meta = (UIMin = "1", UIMax = "1024", ClampMin = "1", ClampMax = "1024", ToolTip = "Maximum Size of Import Image Cache in MB"))`
- L111 _public member_ `float PaintStrengthGamma = 2.2f;` — `UPROPERTY(config, EditAnywhere, Category = "Configuration", meta = (UIMin = "0.0", UIMax = "10.0", ClampMin = "0.0", ClampMax = "10.0", ToolTip = "Exponent for the Paint Tool Strength"))`
- L114 _public member_ `bool bDisablePaintingStartupSlowdown = true;` — `UPROPERTY(config, EditAnywhere, Category = "Configuration", meta = (ToolTip = "Disable Painting Startup Slowdown"))`
- L118 _public member_ `ELandscapeDirtyingMode LandscapeDirtyingMode = ELandscapeDirtyingMode::InLandscapeModeAndUserTriggeredChanges;` — `UPROPERTY(Config, Category = "Configuration", EditAnywhere)` — Defines when the engine requires the landscape actors to be resaved
- L122 _protected member_ `int32 SideResolutionLimit = 2048;` — `UPROPERTY(config)`
- L125 _protected member_ `TSoftObjectPtr<UMaterialInterface> DefaultLandscapeMaterial;` — `UPROPERTY(EditAnywhere, config, Category = "Materials", meta = (ToolTip = "Default Landscape Material will be prefilled when creating a new landscape."))`
- L128 _protected member_ `TSoftObjectPtr<ULandscapeLayerInfoObject> DefaultLayerInfoObject;` — `UPROPERTY(EditAnywhere, config, Category = "Target Layers", meta = (ToolTip = "Default Layer Info Object"))`
- L131 _protected member_ `float BrushSizeUIMax = 8192;` — `UPROPERTY(EditAnywhere, config, Category = "Configuration", meta = (ToolTip = "Maximum size that can be set via the slider for the landscape sculpt/paint brushes"))`
- L134 _protected member_ `float BrushSizeClampMax = 65536;` — `UPROPERTY(EditAnywhere, config, Category = "Configuration", meta = (ToolTip = "Maximum size that can be set manually for the landscape sculpt/paint brushes"))`
- L137 _protected member_ `int32 HLODMaxTextureSize = 1024;` — `UPROPERTY(EditAnywhere, config, Category = "HLOD", meta = (DisplayName = "HLOD Max Texture Size", ClampMin = "64", ClampMax = "8192", ToolTip = "Maximum size of the textures generated for landscape HLODs"))`
- L141 _protected member_ `bool bShouldUpdateEditLayersDuringInteractiveChanges = false;` — `UPROPERTY(EditAnywhere, config, Category = "Edit Layers")` — For landscape layers-affecting changes, allows the landscape to be updated when performing an interactive change (e.g. when changing an edit layer's alpha). Set to false if the performance when editing gets too bad (the landscape will be properly updated when the dragging operation is done).
- L144 _protected member_ `EFoliageLandscapeSnappingMode FoliageLandscapeSnappingMode = EFoliageLandscapeSnappingMode::DontSnap;` — `UPROPERTY(EditAnywhere, config, Category = "Edit Layers")`
- L147 _protected member_ `bool bRestrictiveMode = false;` — `UPROPERTY(transient)`
- L151 _protected member_ `float SplineIconWorldZOffset = 100.0f;` — `UPROPERTY(EditAnywhere, config, Category = "Spline", meta = (ClampMin = "0", UIMax = "4096"))` — Offset in Z for the landscape spline point icon in world-space.
- L155 _protected member_ `float SplineIconScale = 125.0f;` — Size of the landscape spline control point icon in the viewport.
- L159 _protected member_ `bool bDisplayTargetLayerThumbnails = true;` — `UPROPERTY(EditAnywhere, config, Category = "Target Layers", meta = (ToolTip = "When true, each target layer will have a representative thumbnail in landscape mode. However, the thumbnail system can be slow. Plus, certain landscape materials (e.g. using RVT) are not able to properly render thumbnails. Thus, setting this to false will skip needlessly rendering landscape layer thumbnails, which can improve the editing experience"))`
- L163 _protected member_ `bool bDisableTemporalAntiAliasingInLandscapeMode = true;` — `UPROPERTY(EditAnywhere, config, Category = "Configuration", meta = (ToolTip = "When true, temporal anti-aliasing will be inactive while in landscape mode. This avoids the ghosting effect on the landscape brush but can lead to aliasing or shimmering on other parts of the image."))`
- L167 _protected member_ `ELandscapeTargetLayerBlendMethod TargetLayerDefaultBlendMethod = ELandscapeTargetLayerBlendMethod::None;` — `UPROPERTY(Config, Category = "Target Layers", EditAnywhere)` — Target layer blend method to use for newly created Landscape Layer Info assets. Changing this setting will not affect existing Landscape Layer Info assets. This is only used when DefaultLayerInfoObject isn't set.
- L170 _private member_ `TOptional<bool> DisplayTargetLayerThumbnailsBeforeUndo;`

### `Source/Runtime/Landscape/Public/LandscapeSplineProxies.h` (Public)


#### struct `HLandscapeSplineProxy`  
`struct HLandscapeSplineProxy : public HActor`  
_L14-20_
- inherits: `HActor`
- L16 _public prototype_ `DECLARE_HIT_PROXY( );`
- L18 _public prototype_ `HLandscapeSplineProxy(ULandscapeSplinesComponent* SplineComponent, EHitProxyPriority InPriority = HPP_Wireframe);`
- L19 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() override;`

#### struct `HLandscapeSplineProxy_Segment`  
`struct HLandscapeSplineProxy_Segment : public HLandscapeSplineProxy`  
_L22-30_
- inherits: `HLandscapeSplineProxy`
- L24 _public prototype_ `DECLARE_HIT_PROXY( );`
- L26 _public member_ `TObjectPtr<ULandscapeSplineSegment> SplineSegment;`
- L28 _public prototype_ `HLandscapeSplineProxy_Segment(ULandscapeSplineSegment* InSplineSegment);`
- L29 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`

#### struct `HLandscapeSplineProxy_ControlPoint`  
`struct HLandscapeSplineProxy_ControlPoint : public HLandscapeSplineProxy`  
_L32-40_
- inherits: `HLandscapeSplineProxy`
- L34 _public prototype_ `DECLARE_HIT_PROXY( );`
- L36 _public member_ `TObjectPtr<ULandscapeSplineControlPoint> ControlPoint;`
- L38 _public prototype_ `HLandscapeSplineProxy_ControlPoint(ULandscapeSplineControlPoint* InControlPoint);`
- L39 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`

#### struct `HLandscapeSplineProxy_Tangent`  
`struct HLandscapeSplineProxy_Tangent : public HLandscapeSplineProxy`  
_L42-54_
- inherits: `HLandscapeSplineProxy`
- L44 _public prototype_ `DECLARE_HIT_PROXY( );`
- L46 _public member_ `TObjectPtr<ULandscapeSplineSegment> SplineSegment;`
- L47 _public member_ `uint32 End:1;`
- L49 _public prototype_ `HLandscapeSplineProxy_Tangent(ULandscapeSplineSegment* InSplineSegment, bool InEnd);`
- L50 _public prototype_ `virtual void Serialize(FArchive& Ar);`
- L52 _public prototype_ `virtual EMouseCursor::Type GetMouseCursor() override;`
- L53 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`

### `Source/Runtime/Landscape/Public/LandscapeSubsystem.h` (Public)


#### struct `FOnHeightmapStreamedContext`  
`struct FOnHeightmapStreamedContext`  
_L53-81_
- L56 _private member_ `const ALandscape* Landscape = nullptr;`
- L57 _private member_ `const FBox2D& UpdateRegion;`
- L58 _private member_ `const TSet<class ULandscapeComponent*>& LandscapeComponentsInvolved;`
- L61 _public function_ `const ALandscape* GetLandscape() const`
- L66 _public function_ `const FBox2D& GetUpdateRegion() const`
- L71 _public function_ `const TSet<class ULandscapeComponent*>& GetLandscapeComponentsInvolved() const`
- L76 _public function_ `FOnHeightmapStreamedContext(const ALandscape* InLandscape, const FBox2D& InUpdateRegion, const TSet<class ULandscapeComponent*>& InLandscapeComponentsInvolved) : Landscape(InLandscape) , UpdateRegion(InUpdateRegion) , LandscapeComponentsInvolved(InLandscapeComponentsInvolved)`

#### class `ULandscapeSubsystem`  
`class ULandscapeSubsystem : public UTickableWorldSubsystem`  
_L87-307_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTickableWorldSubsystem`
- L92 _public prototype_ `ULandscapeSubsystem();`
- L93 _public prototype_ `virtual ~ULandscapeSubsystem();`
- L95 _public prototype_ `void RegisterActor(ALandscapeProxy* Proxy);`
- L96 _public prototype_ `void UnregisterActor(ALandscapeProxy* Proxy);`
- L99 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L100 _public function_ `virtual bool IsTickableInEditor() const override`
- L101 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L102 _public prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;`
- L103 _public prototype_ `virtual TStatId GetStatId() const override;`
- L106 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L109 _public function_ `void PrioritizeGrassCreation(bool bPrioritizeGrassCreation)` — setting this to true causes grass instance generation to go wider (multiplies the limits by GGrassCreationPrioritizedMultipler)
- L110 _public function_ `bool IsGrassCreationPrioritized() const`
- L111 _public function_ `FLandscapeGrassMapsBuilder* GetGrassMapBuilder()`
- L112 _public function_ `FLandscapeTextureStreamingManager* GetTextureStreamingManager()`
- L120 _public prototype_ `void RegenerateGrass(bool bInFlushGrass, bool bInForceSync, TOptional<TArrayView<FVector>> InOptionalCameraLocations = TOptional<TArrayView<FVector>>());` — Can be called at runtime : (optionally) flushes grass on all landscape components and updates them @param bInFlushGrass : flushes all grass from landscape components prior to updating them @param bInForceSync : synchronously updates grass on all landscape components @param InOptionalCameraLocations : (optional) camera locations that should be used when updating the grass. If not specified, the usual (streaming manager-based) view locations will be used
- L123 _public prototype_ `void RemoveGrassInstances(const TSet<ULandscapeComponent*>* ComponentsToRemoveGrassInstances = nullptr);` — Remove all grass instances from the specified components.  If passed null, removes all grass instances from all proxies.
- L126 _public prototype_ `void RegisterComponent(ULandscapeComponent* Component);` — called when components are registered to the world
- L127 _public prototype_ `void UnregisterComponent(ULandscapeComponent* Component);`
- L129 _public prototype_ `void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld);`
- L132 _public function_ `bool AnyViewShowCollisions() const` — Returns true if any view has view collisions enabled.
- L136 _public prototype_ `void BuildAll(UE::Landscape::EBuildFlags InBuildFlags);`
- L139 _public prototype_ `void BuildGrassMaps(UE::Landscape::EBuildFlags InBuildFlags);` — Synchronously build grass maps for all components
- L141 _public prototype_ `void BuildPhysicalMaterial(UE::Landscape::EBuildFlags InBuildFlags);`
- L148 _public prototype_ `void BuildNanite(UE::Landscape::EBuildFlags InBuildFlags, TArrayView<ALandscapeProxy*> InProxiesToBuild = TArrayView<ALandscapeProxy*>());` — Updates the Nanite mesh on all landscape actors whose mesh is not up to date. @param InProxiesToBuild - If specified, only the Nanite meshes of the specified landscape actors (recursively for all streaming proxies, in the case of a 1 ALandscape / N ALandscapeStreamingProxy setup) will be built @param InBuildFlags - Various flags for driving the build
- L150 _public prototype_ `TArray<TTuple<ALandscapeProxy*, UE::Landscape::EOutdatedDataFlags>> GetOutdatedProxyDetails(UE::Landscape::EOutdatedDataFlags InMatchingOutdatedDataFlags, bool bInMustMatchAllFlags) const;`
- L152 _public prototype_ `bool IsGridBased() const;`
- L153 _public prototype_ `void ChangeGridSize(ULandscapeInfo* LandscapeInfo, uint32 NewGridSizeInComponents);`
- L154 _public prototype_ `ALandscapeProxy* FindOrAddLandscapeProxy(ULandscapeInfo* LandscapeInfo, const FIntPoint& SectionBase);`
- L156 _public prototype_ `bool GetActionableMessage(FActionableMessage& OutActionableMessage);`
- L157 _public prototype_ `void MarkModifiedLandscapesAsDirty(UE::Landscape::EBuildFlags InBuildFlags);`
- L159 _public prototype_ `void SaveModifiedLandscapes(UE::Landscape::EBuildFlags InBuildFlags);` — Dirties and saves the landscapes in the editor world that have been automatically modified and are in need of being saved (see LandscapeDirtyingMode)
- L161 _public prototype_ `bool HasModifiedLandscapes() const;` — Returns true if there are some landscapes in the editor world that have been automatically modified and are in need of being saved (see LandscapeDirtyingMode)
- L162 _public prototype_ `bool GetDirtyOnlyInMode() const;`
- L164 _public function_ `FLandscapeNotificationManager* GetNotificationManager()`
- L169 _public function_ `FOnHeightmapStreamedDelegate::RegistrationType& OnHeightmapStreamed()`
- L174 _public function_ `FOnLandscapeProxyComponentDataChanged::RegistrationType& OnLandscapeProxyComponentDataChanged() const`
- L179 _public function_ `FOnLandscapeProxyMaterialChanged::RegistrationType& OnLandscapeProxyMaterialChanged() const`
- L184 _public prototype_ `FDateTime GetAppCurrentDateTime();`
- L186 _public prototype_ `TSharedRef<UE::Landscape::Nanite::FAsyncBuildData> CreateTrackedNaniteBuildState(ALandscapeProxy* LandscapeProxy, int32 InLODToExport, const TArray<ULandscapeComponent*>& InComponentsToExport);`
- L195 _public prototype_ `void AddNaniteFinalizeBuildEvent(FGraphEventRef InNaniteFinalizeBuildEvent);`
- L198 _public prototype_ `bool FinishAllNaniteBuildsInFlightNow(EFinishAllNaniteBuildsInFlightFlags FinishFlags);` — returns true if all nanite builds were completed (false if cancelled, or failed to complete)
- L201 _public prototype_ `bool IsMultithreadedNaniteBuildEnabled();` — Returns true if we should build nanite meshes in parallel asynchronously.
- L204 _public prototype_ `bool IsLiveNaniteRebuildEnabled();` — Returns true if the user has requested Nanite Meshes to be generated on landscape edit. If we return false then the nanite build will happen either on map save or explicit build
- L206 _public prototype_ `bool AreNaniteBuildsInProgress() const;`
- L207 _public prototype_ `void IncNaniteBuild();`
- L208 _public prototype_ `void DecNaniteBuild();`
- L211 _public prototype_ `void WaitLaunchNaniteBuild();` — Wait unit we're able to continue a landscape export task (Max concurrent nanite mesh builds is defined by  landscape.Nanite.MaxSimultaneousMultithreadBuilds and landscape.Nanite.MultithreadBuild CVars)
- L226 _public prototype_ `FDelegateAccess GetDelegateAccess() const;`
- L230 _public prototype_ `void TickEdgeFixup();` — runs per-tick edge fixup on ALL landscape groups in the subsystem
- L232 _public prototype_ `FLandscapeGroup* GetLandscapeGroupForProxy(TObjectPtr<ALandscapeProxy> Proxy);`
- L233 _public prototype_ `FLandscapeGroup* GetLandscapeGroupForComponent(ULandscapeComponent* Component);`
- L235 _public prototype_ `void ForEachLandscapeInfo(TFunctionRef<bool(ULandscapeInfo*)> ForEachLandscapeInfoFunc) const;`
- L240 _private prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L241 _private prototype_ `virtual void Deinitialize() override;`
- L244 _private function_ `void OnNaniteWorldSettingsChanged(AWorldSettings* WorldSettings)`
- L245 _private prototype_ `void OnNaniteEnabledChanged(IConsoleVariable*);`
- L247 _private prototype_ `void HandlePostGarbageCollect();`
- L249 _private prototype_ `TSet<UPackage*> GetDirtyLandscapeProxyPackages() const;`
- L252 _private prototype_ `void OnProxyMoved(USceneComponent*, EUpdateTransformFlags, ETeleportType);` — When proxies move, we may need to update their position in the landscape group
- L255 _private prototype_ `void TickNaniteFinalizeBuildEvents();`
- L260 _private member_ `TMap<uint32, FLandscapeGroup*> Groups;` — LODGroupKey --> Landscape Group
- L264 _private member_ `TSet<TObjectPtr<ALandscapeStreamingProxy>> StreamingProxiesNeedingReregister;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — list of streaming proxies that need to re-register with their group because they moved, or changed their LODGroupKey
- L266 _private member_ `bool bIsGrassCreationPrioritized = false;`
- L269 _private member_ `TArray<TObjectPtr<ALandscape>> LandscapeActors;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)`
- L274 _private member_ `TArray<TObjectPtr<ALandscapeProxy>> Proxies;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — UPROPERTY ensures these objects are not deleted before being unregistered (technically not necessary, as actors should always unregister prior to deletion)
- L276 _private member_ `FDelegateHandle OnNaniteWorldSettingsChangedHandle;`
- L278 _private member_ `FLandscapeTextureStreamingManager* TextureStreamingManager = nullptr;`
- L279 _private member_ `FLandscapeGrassMapsBuilder* GrassMapsBuilder = nullptr;`
- L281 _private member_ `int32 LastVisualTickFrameNumber = -1;`
- L284 _private member_ `mutable FOnHeightmapStreamedDelegate OnHeightmapStreamedDelegate;`
- L285 _private member_ `mutable FOnLandscapeProxyComponentDataChanged OnLandscapeProxyComponentDataChangedDelegate;`
- L286 _private member_ `mutable FOnLandscapeProxyMaterialChanged OnLandscapeProxyMaterialChangedDelegate;`
- L288 _private member_ `class FLandscapePhysicalMaterialBuilder* PhysicalMaterialBuilder = nullptr;`
- L289 _private member_ `FLandscapeNotificationManager* NotificationManager = nullptr;`
- L290 _private member_ `FDateTime AppCurrentDateTime;` — Represents FDateTime::Now(), at the beginning of the frame (useful to get a human-readable date/time that is fixed during the frame)
- L293 _private member_ `TArray<FGraphEventRef> NaniteFinalizeBuildEvents;` — A list of graph events that track the status of
- L294 _private member_ `TArray<TSharedRef<UE::Landscape::Nanite::FAsyncBuildData>> NaniteMeshBuildStates;`
- L295 _private member_ `float NumNaniteMeshUpdatesAvailable = 0.0f;`
- L297 _private member_ `std::atomic<int32> NaniteBuildsInFlight;`
- L298 _private member_ `std::atomic<int32> NaniteStaticMeshesInFlight;`
- L303 _private member_ `bool bAnyViewShowCollisions = false;`
- L306 _private member_ `FDelegateHandle OnScalabilityChangedHandle;`

#### enum `ULandscapeSubsystem::EFinishAllNaniteBuildsInFlightFlags`  
`enum class EFinishAllNaniteBuildsInFlightFlags`  
_L188-193_
- L190 _public enumerator_ `Default = 0x00`
- L191 _public enumerator_ `DisplaySlowTaskDialog = 0x01`
- L192 _public enumerator_ `AllowCancel = 0x02`

#### class `ULandscapeSubsystem::FDelegateAccess`  
`class FDelegateAccess`  
_L214-225_
- desc: Helper class reserved for friends that are allowed to fire the subsystem's inner callbacks
- L220 _private prototype_ `FDelegateAccess(FOnHeightmapStreamedDelegate& InOnHeightmapStreamed, FOnLandscapeProxyComponentDataChanged& InOnLandscapeProxyComponentDataChanged, FOnLandscapeProxyMaterialChanged& InOnLandscapeProxyMaterialChanged);`
- L222 _private member_ `FOnHeightmapStreamedDelegate& OnHeightmapStreamedDelegate;`
- L223 _private member_ `FOnLandscapeProxyComponentDataChanged& OnLandscapeProxyComponentDataChangedDelegate;`
- L224 _private member_ `FOnLandscapeProxyMaterialChanged& OnLandscapeProxyMaterialChangedDelegate;`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Landscape` (scope `UE`)
- L35 _prototype_ `bool HasModifiedLandscapes();` (scope `UE::Landscape`) — Returns true if there are some landscapes in the editor world that have been automatically modified and are in need of being saved (see LandscapeDirtyingMode)
- L38 _prototype_ `void SaveModifiedLandscapes(EBuildFlags InBuildFlags);` (scope `UE::Landscape`) — Dirties and saves the landscapes in the editor world that have been automatically modified and are in need of being saved (see LandscapeDirtyingMode)
- L39 _prototype_ `void MarkModifiedLandscapesAsDirty(EBuildFlags InBuildFlags);` (scope `UE::Landscape`)
- L40 _prototype_ `void BuildGrassMaps(EBuildFlags InBuildFlags);` (scope `UE::Landscape`)
- L41 _prototype_ `void BuildPhysicalMaterial(EBuildFlags InBuildFlags);` (scope `UE::Landscape`)
- L42 _prototype_ `void BuildNanite(EBuildFlags InBuildFlags);` (scope `UE::Landscape`)
- L43 _prototype_ `void BuildAll(EBuildFlags InBuildFlags);` (scope `UE::Landscape`)
- L46 _namespace_ `namespace Nanite` (scope `UE::Landscape`)
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHeightmapStreamedDelegate, const FOnHeightmapStreamedContext& context);`
- L83 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnHeightmapStreamedDelegate, const FOnHeightmapStreamedContext& context);`

### `Source/Runtime/Landscape/Public/LandscapeUtils.h` (Public)


#### class `UE::Landscape::FRDGBuilderRecorder`  
`class FRDGBuilderRecorder final`  
_L108-230_
- desc: This struct is usually meant to be allocated on the game thread (where there's no FRDGBuilder, which is Render Thread-only) and allows to queue successive operations (lambdas) onto a single render command, sharing the same FRDGBuilder. This allows to sequence a list of RDG passes from the game thread and makes it possible to interleave render thread operations (in a single render command) with game thread-initiated render commands. Here's an extensive use case : FRDGBuilderRecorder Recorder; // Start recording commands to a single graph builder : Recorder.StartRecording(); Recorder.EnqueueRDGCommand([](FRDGBuilder* GraphBuilder) { GraphBuilder->AddPass(); }); // Append a Pass_A ENQUEUE_RENDER_COMMAND(...)  // Push Render_Command_A (immediately) Recorder.EnqueueRDGCommand([](FRDGBuilder* GraphBuilder) { GraphBuilder->AddPass(); }, { { SomeTexture, ERHIAccess::RTV } }); // Append a Pass_B and inform of the final state of a given texture to prevent the RDG from auto-transitioning to SRVMask at the end Recorder.EnqueueRenderCommand([](FRHICommandListImmediate& InRHICmdList) mutable { [...]; }); // Append a Render_Command_B to the graph builder Recorder.EnqueueRDGCommand([](FRDGBuilder* GraphBuilder) { GraphBuilder->AddPass(); }, { { }SomeTexture, ERHIAccess::CopySrc } }); // Append a Pass_C and inform of the final state of a given texture to prevent the RDG from auto-transitioning to SRVMask at the end // Stop recording and issue a render command with all that's been recorded so 
- L111 _public typedef_ `using FRDGRecorderRDGCommand = TFunction<void(FRDGBuilder& )>;`
- L112 _public typedef_ `using FRDGRecorderRenderCommand = TFunction<void(FRHICommandListImmediate& )>;`
- L119 _public prototype_ `FRDGBuilderRecorder() = default;`
- L120 _public prototype_ `~FRDGBuilderRecorder();`
- L128 _public function_ `inline EState GetState() const`
- L129 _public function_ `inline bool IsRecording() const`
- L134 _public prototype_ `void StartRecording();` — Starts recording commands
- L139 _public prototype_ `void StopRecording();` — Stops recording commands. A call to Flush is needed to ensure any pending command is flushed to the render thread (use StopRecordingAndFlush to do both)
- L145 _public prototype_ `void StopRecordingAndFlush(FRDGEventName&& EventName);` — Stops recording commands and flushes them to the render thread. Expects the recorder to be in Recording mode and changes it to Immediate mode. @param EventName RDG event name to use on the render command's FRDGBuilder
- L151 _public prototype_ `void Flush(FRDGEventName&& EventName);` — Flushes any pending command to the render thread @param EventName RDG event name to use on the render command's FRDGBuilder
- L159 _public prototype_ `void EnqueueRDGCommand(FRDGRecorderRDGCommand InRDGCommand, TConstArrayView<FRDGExternalTextureAccessFinal> InRDGExternalTextureAccessFinalList = {});` — Records a FRDGRecorderRDGCommand to execute when registering passes to the single FRDGBuilder when in Recording mode or pushes it immediately to the render thread when in Immediate mode @param InRDGCommand Lambda to execute on the render thread @param InRDGTextureAccessFinalList (optional) : list of external texture with the RHIAccess they should have when executing the FRDGBuilder. This is to prevent the RDG from auto-transitioning to SRVMask at the end
- L166 _public prototype_ `void EnqueueRenderCommand(FRDGRecorderRenderCommand InRenderCommand);` — Records a FRDGRecorderRenderCommand to execute when registering passes to the single FRDGBuilder when in Recording mode or pushes it immediately to the render thread when in Immediate mode @param InRenderCommand Lambda to execute on the render thread
- L171 _public prototype_ `bool IsEmpty() const;` — @return true if there's no command currently recorded
- L177 _public prototype_ `void Clear();` — Cancels all recorder operations. This must be used if the FRDGEventRenderRecorder is "cancelled" (i.e. its sequence of operations is not flushed to a render command). Otherwise, there will be an assert in ~FRDGBuilderRecorder().
- L180 _private member_ `EState State = EState::Immediate;`
- L183 _private member_ `TArray<FRDGRecorderRDGCommand> RDGCommands;` — List of callbacks to call on the render thread after the render command was initiated
- L186 _private member_ `TMap<FTextureResource*, ERHIAccess> RDGExternalTextureAccessFinal;` — Map of textures and the RHI access they should have when leaving the FRDGBuilder :

#### struct `UE::Landscape::FRDGBuilderRecorder::FRDGExternalTextureAccessFinal`  
`struct FRDGExternalTextureAccessFinal`  
_L113-117_
- L115 _public member_ `FTextureResource* TextureResource = nullptr;`
- L116 _public member_ `ERHIAccess Access = ERHIAccess::None;`

#### enum `UE::Landscape::FRDGBuilderRecorder::EState`  
`enum class EState`  
_L122-126_
- L124 _public enumerator_ `Immediate` — In immediate mode, any command that is enqueued will be pushed to the render thread immediately (effectively acting like a ENQUEUE_RENDER_COMMAND)
- L125 _public enumerator_ `Recording` — In recording mode, any command that is enqueued will be deferred to the render thread (effectively acting like a ENQUEUE_RENDER_COMMAND)

#### class `UE::Landscape::FRDGBuilderRecorder::FScopedBreadcrumbEvent`  
`class FScopedBreadcrumbEvent final`  
_L194-228_
- desc: Scope object meant to insert a RDG event in the RDG operations, as if it was inserted on the render thread on a FRDGBuilder. Use RDG_RENDER_COMMAND_RECORDER_BREADCRUMB_EVENT to create one.
- L198 _public function_ `template <size_t N> FScopedBreadcrumbEvent(FRDGBuilderRecorder& InRecorder, TCHAR const(&StaticName)[N], FRDGEventName&& EventName) : Recorder(&InRecorder) , RDGEvent(MakeShared<TOptional<TRDGEventScopeGuard<FRDGScope_RHI>>>())`
- L216 _public function_ `~FScopedBreadcrumbEvent()`
- L226 _private member_ `FRDGBuilderRecorder* Recorder = nullptr;`
- L227 _private member_ `TSharedPtr<TOptional<TRDGEventScopeGuard<FRDGScope_RHI>>> RDGEvent;`

#### struct `UE::Landscape::FTextureCopyRequest`  
`struct FTextureCopyRequest`  
_L243-250_
- L245 _public member_ `UTexture2D* Source = nullptr;`
- L246 _public member_ `UTexture* Destination = nullptr;`
- L247 _public member_ `int8 DestinationSlice = 0;`
- L248 _public member_ `ELandscapeTextureUsage TextureUsage = ELandscapeTextureUsage::Unknown;`
- L249 _public member_ `ELandscapeTextureType TextureType = ELandscapeTextureType::Unknown;`

#### struct `UE::Landscape::FTextureCopyChannelMapping`  
`struct FTextureCopyChannelMapping`  
_L258-268_
- desc: Represents the DestinationChannel->SourceChannel binding.DestinationChannel is used as index. For example if the source channel is 1 and the destination channel is 2, then Mappings[2] == 1.
- L260 _public function_ `FTextureCopyChannelMapping() : Mappings`
- L264 _public function_ `int8& operator[](int32 Index)`
- L265 _public function_ `const int8 operator[](int32 Index) const`
- L267 _public member_ `int8 Mappings[4];`

#### class `UE::Landscape::FBatchTextureCopy`  
`class FBatchTextureCopy`  
_L270-291_
- L282 _public prototype_ `bool AddWeightmapCopy(UTexture* InDestination, int8 InDestinationSlice, int8 InDestinationChannel, const ULandscapeComponent* InComponent, ULandscapeLayerInfoObject* InLayerInfo);` — Uses the provided arguments to add proper source/destination entries to internal copy requests. @param	InDestination	The texture used as a destination for the copy. @param	InDestinationSlice	The Texture array slice to write to (use 0 for a Texture2D) @param	InDestinationChannel	The channel used as a destination for the copy. @param	InComponent		The component containing the wanted source weightmap. @param	InLayerInfo		The layer info used to retrieve the proper source weightmap and channel. @return True if the copy has been successfully added.
- L285 _public prototype_ `bool ProcessTextureCopies();` — Process pending internal copy requests.
- L288 _private typedef_ `using FTextureCopyChannelMappingMap = TMap<FTextureCopyRequest, FTextureCopyChannelMapping>;`
- L290 _private member_ `FTextureCopyChannelMappingMap CopyRequests;`

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace Landscape` (scope `UE`)
- L42 _prototype_ `bool DoesPlatformSupportEditLayers(EShaderPlatform InShaderPlatform);` (scope `UE::Landscape`) — Returns true if edit layers (GPU landscape tools) are enabled on this platform : Note: this is intended for the editor but is in runtime code since global shaders need to exist in runtime modules
- L45 _prototype_ `void ModifyShaderCompilerEnvironmentForDebug(FShaderCompilerEnvironment& OutEnvironment);` (scope `UE::Landscape`) — Provides an opportunity to modify the shader compiler environment (for landscape debugging purposes)
- L47 _prototype_ `ELandscapeToolTargetTypeFlags GetLandscapeToolTargetTypeAsFlags(ELandscapeToolTargetType InTargetType);` (scope `UE::Landscape`)
- L48 _prototype_ `ELandscapeToolTargetType GetLandscapeToolTargetTypeSingleFlagAsType(ELandscapeToolTargetTypeFlags InSingleFlag);` (scope `UE::Landscape`)
- L49 _prototype_ `FString GetLandscapeToolTargetTypeFlagsAsString(ELandscapeToolTargetTypeFlags InTargetTypeFlags);` (scope `UE::Landscape`)
- L51 _prototype_ `bool SupportsRuntimeGrassMapGeneration();` (scope `UE::Landscape`)
- L210 _function_ `` (scope `UE::Landscape::FRDGBuilderRecorder::FScopedBreadcrumbEvent::FScopedBreadcrumbEvent`)
- L219 _function_ `` (scope `UE::Landscape::FRDGBuilderRecorder::FScopedBreadcrumbEvent::~FScopedBreadcrumbEvent`)
- L233 _macro_ `#define RDG_RENDER_COMMAND_RECORDER_BREADCRUMB_EVENT(Recorder, Format, ...) FRDGBuilderRecorder::FScopedBreadcrumbEvent ANONYMOUS_VARIABLE(BreadcrumbEvent)(Recorder, TEXT(Format), RDG_EVENT_NAME(Format, ##__VA_ARGS__))`
- L235 _macro_ `#define RDG_RENDER_COMMAND_RECORDER_BREADCRUMB_EVENT(Recorder, Format, ...) do { } while(0)`
- L252 _prototype_ `uint32 GetTypeHash(const FTextureCopyRequest& InKey);` (scope `UE::Landscape`)
- L253 _prototype_ `bool operator==(const FTextureCopyRequest& InEntryA, const FTextureCopyRequest& InEntryB);` (scope `UE::Landscape`)
- L298 _prototype_ `FString GetSharedAssetsPath(const FString& InPath);` (scope `UE::Landscape`) — Returns a generated path used for Landscape Shared Assets @param	InPath	Path used as a basis to generate shared assets path. If /Temp/, it will be replaced by the last valid path used for level. @return Path used for Landscape Shared Assets
- L305 _prototype_ `FString GetSharedAssetsPath(const ULevel* InLevel);` (scope `UE::Landscape`) — Returns a generated path used for Landscape Shared Assets @param	InLevel		Level's Path will be used as a basis to generate shared assets path. If /Temp/, it will be replaced by the last valid path used for level. @return Path used for Landscape Shared Assets
- L313 _prototype_ `FString GetLayerInfoObjectPackageName(const FName& InLayerName, const FString& InPackagePath, FName& OutLayerObjectName);` (scope `UE::Landscape`) — Returns a generated package name for a Layer Info Object @param	InLayerName	The LayerName of the Layer Info Object @param	InPackagePath	Base package path that will be used, should be Current Level SharedAssetPath or the LandscapeEditorObject->TargetLayerAssetFilePath @param	OutLayerObjectName	The generated object name for Layer Info Object
- L321 _prototype_ `ULandscapeLayerInfoObject* CreateTargetLayerInfo(const FName& InLayerName, const FString& InFilePath);` (scope `UE::Landscape`) — Creates a new layer info object, using the default template if available, or a new empty one. Sets asset file name as LayerName_LayerInfo_%d @param	InLayerName	The layer name of the created asset info @param	InFilePath	New asset file path, typically is CurrentLevel/SharedAssetPath or the LandscapeEditorObject->TargetLayerAssetFilePath->DirectoryPath @return a new LandscapeLayerInfoObject.
- L330 _prototype_ `ULandscapeLayerInfoObject* CreateTargetLayerInfo(const FName& InLayerName, const FString& InFilePath, const FString& InFileName);` (scope `UE::Landscape`) — Creates a new layer info object, using the default template if available, or a new empty one at the path: InFilePath/InFilename @param	InLayerName	The layer name of the created asset info @param	InFilePath	New asset file path, typically is CurrentLevel/SharedAssetPath or the LandscapeEditorObject->TargetLayerAssetFilePath->DirectoryPath @param	InFileName 	The unique file name of the created asset @return a new LandscapeLayerInfoObject.
- L333 _prototype_ `bool IsVisibilityLayer(const ULandscapeLayerInfoObject* InLayerInfoObject);` (scope `UE::Landscape`) — Returns true if the provided layer info object is the current visibility layer.
- L340 _prototype_ `UMaterialInstance* CreateToolLandscapeMaterialInstanceConstant(UMaterialInterface* BaseMaterial);` (scope `UE::Landscape`) — Returns a pointer to a newly created ULandscapeMaterialInstanceConstant @param	BaseMaterial	The base material appended to the debug name and set as parent of MaterialInstance @return  Pointer to ULandscapeMaterialInstanceConstant
- L344 _prototype_ `ULandscapeMaterialInstanceConstant* CreateLandscapeLayerThumbnailMIC(FMaterialUpdateContext& MaterialUpdateContext, UMaterialInterface* LandscapeMaterial, FName LayerName);` (scope `UE::Landscape`) — Create a thumbnail material for a given layer. Can return nullptr if the option to disable landscape thumbnails has been turned on
- L347 _prototype_ `FString ConvertTargetLayerNamesToString(const TArrayView<const FName>& InTargetLayerNames);` (scope `UE::Landscape`) — Concatenates the target layer names in parameter into a string
- L357 _prototype_ `bool DeleteActors(const TArray<AActor*>& InActorsToDelete, UWorld* InWorld, bool bInAllowUI);` (scope `UE::Landscape`) — Helper to delete one or multiple actors. @param InActorsToDelete the list of actors to delete. Cannot contain null entries and all actors should be part of the world passed in InWorld @param InWorld world to which all actors to be deleted belong @param bInAllowUI allows the standard delete actors UX to be displayed, allowing the user to remove lingering reference to these actors, etc. @return true if all actors could be properly deleted
- L367 _prototype_ `TArray<FName> RetrieveTargetLayerNamesFromMaterial(UMaterialInterface* InMaterial, bool bIncludeVisibilityLayer = true);` (scope `UE::Landscape`) — Analyzes the material's material expressions and return the landscape target layer names declared in them @param InMaterial the material to analyze @param bIncludeVisibilityLayer when false, removes the landscape visibility layer from the list of names returned by the material @return the list of unique target layer names declared in that material
- L372 _prototype_ `bool LandscapeProxySortPredicate(const TWeakObjectPtr<ALandscapeProxy> APtr, const TWeakObjectPtr<ALandscapeProxy> BPtr);` (scope `UE::Landscape`) — Helper to sort ALandscapeProxy actors by their section base. Compares X axis values by default and Y values if needed
- L379 _namespace_ `namespace UE`
- L379 _namespace_ `namespace Landscape` (scope `UE`)
- L379 _namespace_ `namespace Grass` (scope `UE::Landscape`)
- L382 _prototype_ `TArray<TPair<FName, TObjectPtr<ULandscapeGrassType>>> ConvertToNamedGrassTypesList(const TMap<FName, TObjectPtr<ULandscapeGrassType>>& InNamedGrassTypes);` (scope `UE::Landscape::Grass`)
- L384 _prototype_ `TMap<FName, TObjectPtr<ULandscapeGrassType>> FilterValidNamedGrassTypes(const TMap<FName, TObjectPtr<ULandscapeGrassType>>& InNamedGrassTypes);` (scope `UE::Landscape::Grass`) — From the list of named grass types, only retain those with a valid name and grass type.
