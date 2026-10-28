# Plugins / WaterEditor

- module root: `Plugins/Experimental/Water/Source/Editor`
- headers: 22; symbols: 574
- symbol kinds: class=30, enum=2, enumerator=6, function=71, macro=2, member=171, namespace=1, prototype=273, struct=17, typedef=1
- PrivateDependencyModuleNames: ActionableMessage, AdvancedPreviewScene, AssetDefinition, ComponentVisualizers, Core, CoreUObject, DetailCustomizations, DeveloperSettings, EditorFramework, EditorSubsystem, Engine, InputCore, Landscape, LandscapeEditorUtilities, PlacementMode, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd, Water
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: 

### `Plugins/Experimental/Water/Source/Editor/Private/AssetDefinition_WaterWaves.h` (Private)


#### class `UAssetDefinition_WaterWaves`  
`class UAssetDefinition_WaterWaves : public UAssetDefinitionDefault`  
_L10-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L17 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L18 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L19 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const;`
- L20 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Experimental/Water/Source/Editor/Private/JumpFloodComponent2D.h` (Private)


#### class `UJumpFloodComponent2D`  
`class UJumpFloodComponent2D : public UActorComponent`  
_L13-87_
- reflection: `UCLASS(config = Engine, Blueprintable, BlueprintType)`
- inherits: `UActorComponent`
- L18 _public prototype_ `UJumpFloodComponent2D(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L21 _public prototype_ `virtual bool CreateMIDs();` — `UFUNCTION(BlueprintCallable, meta = (Category))`
- L24 _public prototype_ `void AssignRenderTargets(UTextureRenderTarget2D* InRTA, UTextureRenderTarget2D* InRTB);` — `UFUNCTION(BlueprintCallable, meta = (Category))`
- L27 _public prototype_ `void JumpFlood(UTextureRenderTarget2D* SeedRT, float SceneCaptureZ, FLinearColor Curl, bool UseDepth, float ZxLocationT);` — `UFUNCTION(BlueprintCallable, meta = (Category))`
- L30 _public prototype_ `UTextureRenderTarget2D* SingleJumpStep();` — `UFUNCTION(BlueprintCallable, meta = (Category))`
- L33 _public prototype_ `UTextureRenderTarget2D* FindEdges(UTextureRenderTarget2D* SeedRT, float CaptureZ, FLinearColor Curl, bool UseDepth, float ZxLocationT);` — `UFUNCTION(BlueprintCallable, meta = (Category))`
- L36 _public prototype_ `void FindEdges_Debug(UTextureRenderTarget2D* SeedRT, float CaptureZ, FLinearColor Curl, UTextureRenderTarget2D* DestRT, float ZOffset);` — `UFUNCTION(BlueprintCallable, meta = (Category))`
- L39 _public prototype_ `UTextureRenderTarget2D* SingleBlurStep();` — `UFUNCTION(BlueprintCallable, meta = (Category))`
- L43 _public member_ `TObjectPtr<UMaterialInterface> JumpStepMaterial = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Materials"))`
- L46 _public member_ `TObjectPtr<UMaterialInterface> FindEdgesMaterial = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Materials"))`
- L49 _public member_ `TObjectPtr<UMaterialInterface> BlurEdgesMaterial = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Materials"))`
- L52 _public member_ `bool UseBlur = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, meta=(Category="Default"))`
- L55 _public member_ `int32 BlurPasses = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, meta=(Category="Default"))`
- L59 _private member_ `TObjectPtr<UTextureRenderTarget2D> RTA;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Default"))`
- L62 _private member_ `TObjectPtr<UTextureRenderTarget2D> RTB;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, meta = (Category = "Default"))`
- L66 _private member_ `TObjectPtr<UMaterialInstanceDynamic> JumpStepMID;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Transient, meta = (Category = "Debug"))` — Transient properties (exposed only for debugging reasons) :
- L69 _private member_ `TObjectPtr<UMaterialInstanceDynamic> FindEdgesMID;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Transient, meta = (Category = "Debug"))`
- L72 _private member_ `TObjectPtr<UMaterialInstanceDynamic> BlurEdgesMID;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Transient, meta = (Category = "Debug"))`
- L75 _private member_ `int32 RequiredPasses = 0;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Transient, meta = (Category = "Debug"))`
- L78 _private member_ `int32 CompletedPasses = 0;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Transient, meta = (Category = "Debug"))`
- L81 _private member_ `int32 CompletedBlurPasses = 0;` — `UPROPERTY(VisibleAnywhere, AdvancedDisplay, Transient, meta = (Category = "Debug"))`
- L83 _private prototype_ `bool ValidateJumpFloodRenderTargets();`
- L84 _private prototype_ `bool ValidateJumpFloodRequirements();`
- L85 _private prototype_ `UTextureRenderTarget2D* PingPongSource(int32 Offset) const;`
- L86 _private prototype_ `UTextureRenderTarget2D* PingPongTarget(int32 Offset) const;`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterBodyActorFactory.h` (Private)


#### class `UWaterBodyActorFactory`  
`class UWaterBodyActorFactory : public UActorFactory`  
_L11-21_
- reflection: `UCLASS(Abstract, MinimalAPI, config = Editor)`
- inherits: `UActorFactory`
- L15 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L18 _protected function_ `virtual const FWaterBodyDefaults* GetWaterBodyDefaults() const`
- L19 _protected function_ `virtual const FWaterBrushActorDefaults* GetWaterBrushActorDefaults() const`
- L20 _protected prototype_ `virtual bool ShouldOverrideWaterSplineDefaults(const class UWaterSplineComponent* WaterSpline) const;`

#### class `UWaterBodyRiverActorFactory`  
`class UWaterBodyRiverActorFactory : public UWaterBodyActorFactory`  
_L24-31_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UWaterBodyActorFactory`
- L28 _private prototype_ `virtual const FWaterBodyDefaults* GetWaterBodyDefaults() const override;`
- L29 _private prototype_ `virtual const FWaterBrushActorDefaults* GetWaterBrushActorDefaults() const override;`
- L30 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

#### class `UWaterBodyOceanActorFactory`  
`class UWaterBodyOceanActorFactory : public UWaterBodyActorFactory`  
_L34-41_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UWaterBodyActorFactory`
- L38 _private prototype_ `virtual const FWaterBodyDefaults* GetWaterBodyDefaults() const override;`
- L39 _private prototype_ `virtual const FWaterBrushActorDefaults* GetWaterBrushActorDefaults() const override;`
- L40 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

#### class `UWaterBodyLakeActorFactory`  
`class UWaterBodyLakeActorFactory : public UWaterBodyActorFactory`  
_L44-51_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UWaterBodyActorFactory`
- L48 _private prototype_ `virtual const FWaterBodyDefaults* GetWaterBodyDefaults() const override;`
- L49 _private prototype_ `virtual const FWaterBrushActorDefaults* GetWaterBrushActorDefaults() const override;`
- L50 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

#### class `UWaterBodyCustomActorFactory`  
`class UWaterBodyCustomActorFactory : public UWaterBodyActorFactory`  
_L54-60_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UWaterBodyActorFactory`
- L58 _private prototype_ `virtual const FWaterBodyDefaults* GetWaterBodyDefaults() const override;`
- L59 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterBodyBrushCacheContainerThumbnailRenderer.h` (Private)


#### class `UWaterBodyBrushCacheContainerThumbnailRenderer`  
`class UWaterBodyBrushCacheContainerThumbnailRenderer : public UTextureThumbnailRenderer`  
_L9-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTextureThumbnailRenderer`
- L14 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L15 _private prototype_ `virtual void GetThumbnailSize(UObject* Object, float Zoom, uint32& OutWidth, uint32& OutHeight) const override;`
- L16 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`
- L20 _private prototype_ `class UTextureRenderTarget2D* GetRenderTarget(UObject* Object) const;`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterBodyIslandActorFactory.h` (Private)


#### class `UWaterBodyIslandActorFactory`  
`class UWaterBodyIslandActorFactory : public UActorFactory`  
_L8-13_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UActorFactory`
- L12 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterBrushCacheContainer.h` (Private)


#### struct `FWaterBodyBrushCache`  
`struct FWaterBodyBrushCache`  
_L12-21_
- reflection: `USTRUCT(BlueprintType)`
- desc: TODO [jonathan.bard] : rename : this is not a WaterBodyBrushCache, this a simple RenderTarget with a boolean to force an update on it This is also used for caching curves...
- L17 _public member_ `TObjectPtr<UTextureRenderTarget2D> CacheRenderTarget = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")`
- L20 _public member_ `bool CacheIsValid = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")`

#### class `UWaterBodyBrushCacheContainer`  
`class UWaterBodyBrushCacheContainer : public UObject`  
_L24-34_
- reflection: `UCLASS(config = Engine, Blueprintable, BlueprintType)`
- inherits: `UObject`
- L30 _public prototype_ `UWaterBodyBrushCacheContainer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L33 _public member_ `FWaterBodyBrushCache Cache;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(DisplayName="Cache", Category="Default"))`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterBrushManager.h` (Private)


#### class `AWaterBrushManager`  
`class AWaterBrushManager : public AWaterLandscapeBrush`  
_L28-326_
- reflection: `UCLASS(config = Engine, Blueprintable, BlueprintType)`
- inherits: `AWaterLandscapeBrush`
- L34 _public member_ `TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent2D = nullptr;` — `UPROPERTY()`
- L37 _public member_ `TObjectPtr<UJumpFloodComponent2D> JumpFloodComponent2D = nullptr;` — `UPROPERTY()`
- L41 _public member_ `TObjectPtr<UTextureRenderTarget2D> HeightmapRTA = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, meta = (Category = "Render Targets"))` — RTs
- L44 _public member_ `TObjectPtr<UTextureRenderTarget2D> HeightmapRTB = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, meta=(Category="Render Targets"))`
- L47 _public member_ `TObjectPtr<UTextureRenderTarget2D> JumpFloodRTA;` — `UPROPERTY(VisibleAnywhere, Transient, meta=(Category="Render Targets"))`
- L50 _public member_ `TObjectPtr<UTextureRenderTarget2D> JumpFloodRTB = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, meta=(Category="Render Targets"))`
- L53 _public member_ `TObjectPtr<UTextureRenderTarget2D> DepthAndShapeRT = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, meta=(Category="Render Targets"))`
- L56 _public member_ `TObjectPtr<UTextureRenderTarget2D> WaterDepthAndVelocityRT = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, meta=(Category="Render Targets"))`
- L59 _public member_ `TObjectPtr<UTextureRenderTarget2D> CombinedVelocityAndHeightRTA = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, meta=(Category="Render Targets"))`
- L62 _public member_ `TObjectPtr<UTextureRenderTarget2D> CombinedVelocityAndHeightRTB = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, meta=(Category="Render Targets"))`
- L65 _public member_ `TObjectPtr<UTextureRenderTarget2D> LandscapeRTRef = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, meta=(Category="Render Targets"))`
- L68 _public member_ `TObjectPtr<UTextureRenderTarget2D> WeightmapRTA = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, meta=(Category="Render Targets"))`
- L71 _public member_ `TObjectPtr<UTextureRenderTarget2D> WeightmapRTB = nullptr;` — `UPROPERTY(VisibleAnywhere, Transient, meta=(Category="Render Targets"))`
- L76 _public member_ `TObjectPtr<UMaterialInterface> BrushAngleFalloffMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))` — Brush materials
- L79 _public member_ `TObjectPtr<UMaterialInterface> BrushWidthFalloffMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))`
- L82 _public member_ `TObjectPtr<UMaterialInterface> DistanceFieldCacheMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))`
- L85 _public member_ `TObjectPtr<UMaterialInterface> RenderRiverSplineDepthMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))`
- L89 _public member_ `TObjectPtr<UMaterialInterface> DebugDistanceFieldMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))` — TODO [jonathan.bard] : rename to DebugDistanceFieldMaterial and make it work :
- L92 _public member_ `TObjectPtr<UMaterialInterface> WeightmapMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))`
- L95 _public member_ `TObjectPtr<UMaterialInterface> DrawCanvasMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))`
- L98 _public member_ `TObjectPtr<UMaterialInterface> CompositeWaterBodyTextureMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))`
- L101 _public member_ `TObjectPtr<UMaterialInterface> IslandFalloffMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))`
- L104 _public member_ `TObjectPtr<UMaterialInterface> JumpStepMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))`
- L107 _public member_ `TObjectPtr<UMaterialInterface> FindEdgesMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))`
- L110 _public member_ `TObjectPtr<UMaterialInterface> BlurEdgesMaterial = nullptr;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, meta = (Category = "Brush Materials"))`
- L115 _public member_ `TObjectPtr<UMaterialInstanceDynamic> BrushAngleFalloffMID = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, Transient, meta=(Category="Debug MIDs"))` — MIDs
- L118 _public member_ `TObjectPtr<UMaterialInstanceDynamic> BrushWidthFalloffMID = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, Transient, meta=(Category="Debug MIDs"))`
- L121 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DistanceFieldCacheMID = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, Transient, meta=(Category="Debug MIDs"))`
- L124 _public member_ `TArray<TObjectPtr<UMaterialInstanceDynamic>> RiverSplineMIDs;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, Transient, meta = (Category = "Debug MIDs"))`
- L127 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DebugDistanceFieldMID = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, Transient, meta = (Category = "Debug MIDs"))`
- L130 _public member_ `TObjectPtr<UMaterialInstanceDynamic> WeightmapMID = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, Transient, meta = (Category = "Debug MIDs"))`
- L133 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DrawCanvasMID = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, Transient, meta = (Category = "Debug MIDs"))`
- L136 _public member_ `TObjectPtr<UMaterialInstanceDynamic> CompositeWaterBodyTextureMID = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, Transient, meta = (Category = "Debug MIDs"))`
- L139 _public member_ `TObjectPtr<UMaterialInstanceDynamic> IslandFalloffMID = nullptr;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, BlueprintReadWrite, Transient, meta = (Category = "Debug MIDs"))`
- L143 _public member_ `TMap<TObjectPtr<UCurveFloat>,FWaterBodyBrushCache> BrushCurveRTCache;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient, meta=(Category="Debug"))`
- L146 _public member_ `FVector WorldSize;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta=(Category="Debug"))`
- L149 _public member_ `FIntPoint LandscapeRTRes;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta=(Category="Debug"))`
- L152 _public member_ `FIntPoint LandscapeQuads;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta=(Category="Debug"))`
- L155 _public member_ `FTransform LandscapeTransform;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, meta=(Category="Debug"))`
- L158 _public member_ `bool ShowGradient = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="Debug"))`
- L161 _public member_ `float DistanceDivisor = 0.1f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="Debug"))`
- L164 _public member_ `bool ShowDistance = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="Debug"))`
- L167 _public member_ `bool ShowGrid = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="Debug"))`
- L170 _public member_ `float CanvasSegmentSize = 1024.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="Settings"))`
- L173 _public member_ `float WaterClearHeight = -16384.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="Settings"))`
- L176 _public member_ `float SplineMeshExtension = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="Settings"))`
- L179 _public member_ `bool UseDynamicPreviewRT = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="Debug"))`
- L182 _public member_ `bool DisableBrushTextureEffects = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Category="Debug"))`
- L185 _public member_ `bool bNeedsForceUpdate = false;` — `UPROPERTY()`
- L190 _public member_ `TObjectPtr<UMaterialInterface> FinalizeVelocityHeightMaterial_DEPRECATED = nullptr;` — `UE_DEPRECATED(all, "This material is now useless, the WaterVelocityTexture is now regenerated at runtime (WaterInfoTexture in AWaterZone).")` — `UPROPERTY()`
- L194 _public member_ `TObjectPtr<UMaterialInstanceDynamic> FinalizeVelocityHeightMID_DEPRECATED = nullptr;` — `UE_DEPRECATED(all, "This material instance is now useless, the WaterVelocityTexture is now regenerated at runtime (WaterInfoTexture in AWaterZone).")` — `UPROPERTY()`
- L197 _public prototype_ `AWaterBrushManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L199 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L200 _public prototype_ `virtual void PostLoad() override;`
- L201 _public prototype_ `virtual void BeginDestroy() override;`
- L202 _public prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L203 _public prototype_ `virtual void BeginPlay() override;`
- L204 _public prototype_ `virtual void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph) override;`
- L205 _public prototype_ `virtual void BlueprintOnRenderTargetTexturesUpdated_Native(UTexture2D* VelocityTexture) override;`
- L206 _public prototype_ `virtual void BlueprintWaterBodyChanged_Native(AActor* Actor) override;`
- L207 _public prototype_ `virtual void Initialize_Native(FTransform const& InLandscapeTransform, FIntPoint const& InLandscapeSize, FIntPoint const& InLandscapeRenderTargetSize) override;`
- L208 _public prototype_ `virtual UTextureRenderTarget2D* RenderLayer_Native(const FLandscapeBrushParameters& InParameters) override;`
- L210 _public prototype_ `virtual void GetRenderDependencies(TSet<UObject*>& OutDependencies) override;`
- L214 _public prototype_ `virtual void ForceUpdate();` — `UFUNCTION(BlueprintCallable, meta = (CallInEditor = "true", Category = "Debug"))` — Debug Buttons
- L217 _public prototype_ `virtual void SingleBlurStep();` — `UFUNCTION(BlueprintCallable, meta = (CallInEditor = "true", Category = "Debug"))`
- L220 _public prototype_ `virtual void FindEdges();` — `UFUNCTION(BlueprintCallable, meta = (CallInEditor = "true", Category = "Debug"))`
- L223 _public prototype_ `virtual void SingleJumpStep();` — `UFUNCTION(BlueprintCallable, meta = (CallInEditor = "true", Category = "Debug"))`
- L227 _public prototype_ `virtual void GetWaterCacheKey(AActor* WaterBrush, UWaterBodyBrushCacheContainer*& ContainerObject, FWaterBodyBrushCache& Value);` — `UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "Debug"))`
- L234 _public prototype_ `void SortWaterBodiesForBrushRender(TArray<AWaterBody*>& InOutWaterBodies) const;` — `UFUNCTION(BlueprintNativeEvent)` — Sorts the water bodies in the order they should be rendered when rendering the water brush @param InOutWaterBodies : list of water bodies that needs sorting
- L237 _public prototype_ `void SetupDefaultMaterials();` — `UFUNCTION(BlueprintCallable, meta = (CallInEditor = "true", Category = "Debug"))`
- L270 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L271 _private prototype_ `virtual bool AllocateRTs();`
- L272 _private prototype_ `virtual void SetMPCParams();`
- L274 _private prototype_ `virtual bool SetupRiverSplineRenderMIDs(const FBrushActorRenderContext& BrushActorRenderContext, bool bRestoreMIDs, TArray<UMaterialInterface*>& InOutMIDs);`
- L275 _private prototype_ `virtual void CaptureMeshDepth(const TArrayView<UStaticMeshComponent*>& MeshComponents);`
- L276 _private prototype_ `virtual void CacheBrushDistanceField(const FBrushActorRenderContext& BrushActorRenderContext);`
- L277 _private prototype_ `virtual void DrawCanvasShape(const FBrushActorRenderContext& BrushActorRenderContext);`
- L278 _private prototype_ `virtual void DrawBrushMaterial(const FBrushRenderContext& BrushRenderContext, const FBrushActorRenderContext& BrushActorRenderContext);`
- L279 _private prototype_ `virtual void CaptureRiverDepthAndVelocity(const FBrushActorRenderContext& BrushActorRenderContext);`
- L280 _private prototype_ `virtual void UpdateCurves();`
- L281 _private prototype_ `virtual bool BrushRenderSetup();`
- L282 _private prototype_ `virtual void SetBrushMIDParams(const FBrushRenderContext& BrushRenderContext, FBrushActorRenderContext& BrushActorRenderContext);`
- L283 _private prototype_ `virtual void UpdateCurveCacheKeys();`
- L284 _private prototype_ `virtual void UpdateBrushCacheKeys();`
- L285 _private prototype_ `virtual void RenderBrushActorContext(FBrushRenderContext& BrushRenderContext, FBrushActorRenderContext& BrushActorRenderContext);`
- L286 _private prototype_ `virtual bool CreateMIDs();`
- L287 _private prototype_ `virtual void DistanceFieldCaching(const FBrushActorRenderContext& BrushActorRenderContext);`
- L288 _private prototype_ `virtual void CurvesSmoothingAndTerracing(const FBrushActorRenderContext& BrushActorRenderContext);`
- L289 _private prototype_ `virtual void FalloffAndBlendMode(const FBrushActorRenderContext& BrushActorRenderContext);`
- L290 _private prototype_ `virtual void DisplacementSettings(const FBrushActorRenderContext& BrushActorRenderContext);`
- L291 _private prototype_ `virtual void ApplyWeightmapSettings(const FBrushRenderContext& BrushRenderContext, const FBrushActorRenderContext& BrushActorRenderContext, const FWaterBodyWeightmapSettings& WMSettings);`
- L292 _private prototype_ `virtual void ApplyToCompositeWaterBodyTexture(FBrushRenderContext& BrushRenderContext, const FBrushActorRenderContext& BrushActorRenderContext);`
- L295 _private prototype_ `virtual void CheckForErrors() override;`
- L298 _private prototype_ `UCurveFloat* GetElevationCurveAsset(const FWaterCurveSettings& CurveSettings);`
- L299 _private prototype_ `void ClearCurveCache();`
- L300 _private prototype_ `void OnCurveUpdated(UCurveBase* Curve, EPropertyChangeType::Type ChangeType);`
- L301 _private prototype_ `void ComputeWaterLandscapeInfo(FVector& OutRTWorldLocation, FVector& OutRTWorldSizeVector) const;`
- L304 _private prototype_ `bool DeprecateWaterLandscapeInfo(FVector& OutRTWorldLocation, FVector& OutRTWorldSizeVector);` — HACK [jonathan.bard] : this is only needed for data deprecation, when LandscapeTransform and LandscapeRTRes were not serialized:
- L307 _private prototype_ `void ShowForceUpdateMapCheckError();`
- L310 _private prototype_ `UTextureRenderTarget2D* VelocityPingPongRead(const FBrushRenderContext& BrushRenderContext) const;`
- L311 _private prototype_ `UTextureRenderTarget2D* VelocityPingPongWrite(const FBrushRenderContext& BrushRenderContext) const;`
- L313 _private prototype_ `UTextureRenderTarget2D* HeightPingPongRead(const FBrushRenderContext& BrushRenderContext) const;`
- L314 _private prototype_ `UTextureRenderTarget2D* HeightPingPongWrite(const FBrushRenderContext& BrushRenderContext) const;`
- L316 _private prototype_ `UTextureRenderTarget2D* WeightPingPongRead(const FBrushRenderContext& BrushRenderContext) const;`
- L317 _private prototype_ `UTextureRenderTarget2D* WeightPingPongWrite(const FBrushRenderContext& BrushRenderContext) const;`
- L319 _private prototype_ `static void AddDependencyIfValid(UObject* Dependency, TSet<UObject*>& OutDependencies);`
- L322 _private member_ `bool bKillCache = false;`
- L324 _private member_ `FDelegateHandle OnWorldPostInitHandle;` — HACK [jonathan.bard] : shouldn't be needed anymore once deprecation is done :
- L325 _private member_ `FDelegateHandle OnLevelAddedToWorldHandle;`

#### struct `AWaterBrushManager::FBrushActorRenderContext`  
`struct FBrushActorRenderContext`  
_L241-258_
- desc: Internal struct for passing information around when rendering a water brush actor.
- L243 _public function_ `FBrushActorRenderContext(const TWeakInterfacePtr<IWaterBrushActorInterface>& InWaterBrushActor) : WaterBrushActor(InWaterBrushActor)`
- L248 _public function_ `template <typename T> T* TryGetActorAs() const`
- L251 _public function_ `template <typename T> T* GetActorAs() const`
- L253 _public function_ `AActor* GetActor() const`
- L255 _public member_ `TWeakInterfacePtr<IWaterBrushActorInterface> WaterBrushActor;`
- L256 _public member_ `UWaterBodyBrushCacheContainer* CacheContainer = nullptr;`
- L257 _public member_ `UMaterialInstanceDynamic* MID = nullptr;`

#### struct `AWaterBrushManager::FBrushRenderContext`  
`struct FBrushRenderContext`  
_L261-267_
- desc: Internal struct for passing information around when rendering the whole brush.
- L263 _public member_ `bool bHeightmapRender = false;`
- L264 _public member_ `FName WeightmapLayerName;`
- L265 _public member_ `int32 RTIndex = 0;`
- L266 _public member_ `int32 VelocityRTIndex = 0;`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterBrushManagerFactory.h` (Private)


#### class `UWaterBrushManagerFactory`  
`class UWaterBrushManagerFactory : public UActorFactory`  
_L8-13_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UActorFactory`
- L12 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterLandscapeBrush.h` (Private)


#### class `AWaterLandscapeBrush`  
`class AWaterLandscapeBrush : public ALandscapeBlueprintBrush`  
_L19-158_
- reflection: `UCLASS(Blueprintable, Abstract, hidecategories = (Collision, Replication, Input, LOD, Actor, Cooking, Rendering))`
- inherits: `ALandscapeBlueprintBrush`
- L24 _public prototype_ `AWaterLandscapeBrush(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L26 _public prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L27 _public prototype_ `virtual void BeginDestroy() override;`
- L28 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L29 _public prototype_ `virtual void UnregisterAllComponents(bool bForReregister) override;`
- L30 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L34 _public prototype_ `virtual TArray<UE::Landscape::EditLayers::FEditLayerRenderItem> GetRenderItems(const UE::Landscape::EditLayers::FMergeContext* InMergeContext) const override;`
- L39 _public prototype_ `void GetWaterBodies(TSubclassOf<AWaterBody> WaterBodyClass, TArray<AWaterBody*>& OutWaterBodies) const;` — `UFUNCTION(BlueprintCallable, Category = "Water", meta = (DeterminesOutputType = "WaterBodyClass", DynamicOutputParam = "OutWaterBodies"))`
- L42 _public prototype_ `void GetWaterBodyIslands(TSubclassOf<AWaterBodyIsland> WaterBodyIslandClass, TArray<AWaterBodyIsland*>& OutWaterBodyIslands) const;` — `UFUNCTION(BlueprintCallable, Category = "Water", meta = (DeterminesOutputType = "WaterBodyIslandClass", DynamicOutputParam = "OutWaterBodyIslands"))`
- L45 _public prototype_ `void GetActorsAffectingLandscape(TArray<TScriptInterface<IWaterBrushActorInterface>>& OutWaterBrushActors) const;` — `UFUNCTION(BlueprintCallable, Category = "Water")`
- L47 _public function_ `const TArray<TWeakInterfacePtr<IWaterBrushActorInterface>>& GetActorsAffectingLandscape() const`
- L50 _public prototype_ `void BlueprintWaterBodiesChanged();` — `UFUNCTION(BlueprintNativeEvent, meta = (CallInEditor = "true", Category = "Debug"))`
- L51 _public function_ `virtual void BlueprintWaterBodiesChanged_Native()`
- L54 _public prototype_ `void BlueprintWaterBodyChanged(AActor* Actor);` — `UFUNCTION(BlueprintNativeEvent, meta = (CallInEditor = "true", Category = "Debug"))`
- L55 _public function_ `virtual void BlueprintWaterBodyChanged_Native(AActor* Actor)`
- L59 _public function_ `void SetWaterBodyCache(AWaterBody* WaterBody, UObject* InCache)` — `UE_DEPRECATED(all, "Use SetActorCache instead")` — `UFUNCTION(BlueprintCallable, Category = "Cache", meta = (DeprecatedFunction, DeprecationMessage="Use SetActorCache instead"))`
- L63 _public function_ `UObject* GetWaterBodyCache(AWaterBody* WaterBody, TSubclassOf<UObject> CacheClass) const` — `UE_DEPRECATED(all, "Use GetActorCache instead")` — `UFUNCTION(BlueprintCallable, Category = "Cache", meta = (DeterminesOutputType = "CacheClass", DeprecatedFunction, DeprecationMessage = "Use GetActorCache instead"))`
- L67 _public function_ `void ClearWaterBodyCache(AWaterBody* WaterBody)` — `UE_DEPRECATED(all, "Use ClearActorCache instead")` — `UFUNCTION(BlueprintCallable, Category = "Cache", meta = (DeprecatedFunction, DeprecationMessage = "Use ClearActorCache instead"))`
- L70 _public prototype_ `void SetActorCache(AActor* InActor, UObject* InCache);` — `UFUNCTION(BlueprintCallable, Category = "Cache")`
- L73 _public prototype_ `UObject* GetActorCache(AActor* InActor, TSubclassOf<UObject> CacheClass) const;` — `UFUNCTION(BlueprintCallable, Category = "Cache", meta = (DeterminesOutputType = "CacheClass"))`
- L76 _public prototype_ `void ClearActorCache(AActor* InActor);` — `UFUNCTION(BlueprintCallable, Category = "Cache")`
- L79 _public prototype_ `void BlueprintGetRenderTargets(UTextureRenderTarget2D* InHeightRenderTarget, UTextureRenderTarget2D*& OutVelocityRenderTarget);` — `UFUNCTION(BlueprintNativeEvent, meta = (DeprecatedFunction, DeprecationMessage = "This event isn't called anymore, the WaterVelocityTexture is now regenerated at runtime (WaterInfoTexture in AWaterZone)."))`
- L81 _public function_ `virtual void BlueprintGetRenderTargets_Native(UTextureRenderTarget2D* InHeightRenderTarget, UTextureRenderTarget2D*& OutVelocityRenderTarget)` — `UE_DEPRECATED(all, "This function isn't called anymore, the WaterVelocityTexture is now regenerated at runtime (WaterInfoTexture in AWaterZone)")`
- L84 _public prototype_ `void BlueprintOnRenderTargetTexturesUpdated(UTexture2D* VelocityTexture);` — `UFUNCTION(BlueprintNativeEvent, meta = (DeprecatedFunction, DeprecationMessage = "This event isn't called anymore, the WaterVelocityTexture is now regenerated at runtime (WaterInfoTexture in AWaterZone)."))`
- L86 _public function_ `virtual void BlueprintOnRenderTargetTexturesUpdated_Native(UTexture2D* VelocityTexture)` — `UE_DEPRECATED(all, "This function isn't called anymore, the WaterVelocityTexture is now regenerated at runtime (WaterInfoTexture in AWaterZone)")`
- L90 _public function_ `void ForceWaterTextureUpdate()` — `UE_DEPRECATED(all, "This function is now useless, the WaterVelocityTexture is now regenerated at runtime (WaterInfoTexture in AWaterZone).")` — `UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction, DeprecationMessage = "This function is now useless, the WaterVelocityTexture is now regenerated at runtime (WaterInfoTexture in AWaterZone)."))`
- L92 _public prototype_ `void SetTargetLandscape(ALandscape* InTargetLandscape);`
- L94 _public prototype_ `virtual void SetOwningLandscape(ALandscape* InOwningLandscape) override;`
- L96 _public prototype_ `virtual void GetRenderDependencies(TSet<UObject *>& OutDependencies) override;`
- L98 _public prototype_ `virtual void PostLoad() override;`
- L99 _public prototype_ `virtual void PostActorCreated() override;`
- L101 _public prototype_ `void ForceUpdate();`
- L111 _public prototype_ `EWaterBrushStatus CheckWaterBrushStatus();`
- L113 _public prototype_ `virtual void CheckForErrors() override;`
- L115 _public prototype_ `void UpdateActorIcon();`
- L117 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L124 _private prototype_ `void AddActorInternal(AActor* Actor, const UWorld* ThisWorld, UObject* InCache, bool bTriggerEvent, bool bModify);`
- L125 _private prototype_ `void RemoveActorInternal(AActor* Actor);`
- L126 _private prototype_ `void UpdateActors(bool bTriggerEvents = true);`
- L127 _private prototype_ `void UpdateAffectedWeightmaps();`
- L128 _private prototype_ `void ClearActors();`
- L129 _private prototype_ `bool IsActorAffectingLandscape(AActor* Actor) const;`
- L130 _private prototype_ `void RegisterDelegates();`
- L131 _private prototype_ `void OnEditLayersMerged(const struct FOnLandscapeEditLayersMergedParams& InParams);`
- L132 _private prototype_ `void OnWaterBrushActorChanged(const IWaterBrushActorInterface::FWaterBrushActorChangedEventParams& InParams);`
- L133 _private prototype_ `void OnActorsAffectingLandscapeChanged();`
- L134 _private prototype_ `void OnLevelActorAdded(AActor* InActor);`
- L135 _private prototype_ `void OnLevelActorRemoved(AActor* InActor);`
- L140 _public member_ `TObjectPtr<UBillboardComponent> ActorIcon;` — `UPROPERTY(Transient)`
- L144 _private member_ `TArray<TWeakInterfacePtr<IWaterBrushActorInterface>> ActorsAffectingLandscape;`
- L145 _private member_ `FDelegateHandle OnWorldPostInitHandle;`
- L146 _private member_ `FDelegateHandle OnLevelAddedToWorldHandle;`
- L147 _private member_ `FDelegateHandle OnLevelRemovedFromWorldHandle;`
- L148 _private member_ `FDelegateHandle OnLevelActorAddedHandle;`
- L149 _private member_ `FDelegateHandle OnLevelActorDeletedHandle;`
- L150 _private member_ `FDelegateHandle OnActorMovedHandle;`
- L152 _private member_ `FDelegateHandle OnLoadedActorAddedToLevelEventHandle;`
- L153 _private member_ `FDelegateHandle OnLoadedActorRemovedFromLevelEventHandle;`
- L157 _private member_ `TMap<TSoftObjectPtr<AActor>, TObjectPtr<UObject>> Cache;` — `UPROPERTY(Transient, DuplicateTransient, VisibleAnywhere, AdvancedDisplay, meta = (Category = "Debug"))`

#### enum `AWaterLandscapeBrush::EWaterBrushStatus`  
`enum class EWaterBrushStatus : uint8`  
_L104-109_
- L106 _public enumerator_ `Valid`
- L107 _public enumerator_ `MissingLandscapeWithEditLayers`
- L108 _public enumerator_ `MissingFromLandscapeEditLayers`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterSplineComponentVisualizer.h` (Private)


#### class `UWaterSplineComponentVisualizerSelectionState`  
`class UWaterSplineComponentVisualizerSelectionState : public USplineComponentVisualizerSelectionState`  
_L26-61_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `USplineComponentVisualizerSelectionState`
- desc: Selection state data that will be captured by scoped transactions.
- L32 _public function_ `bool GetWaterVelocityIsSelected() const`
- L33 _public function_ `void SetWaterVelocityIsSelected(bool InWaterVelocityIsSelected)`
- L35 _public function_ `bool GetDepthIsSelected() const`
- L36 _public function_ `void SetDepthIsSelected(bool InDepthIsSelected)`
- L38 _public function_ `bool GetRiverWidthIsSelected() const`
- L39 _public function_ `void SetRiverWidthIsSelected(bool InRiverWidthIsSelected)`
- L41 _public function_ `bool GetRiverWidthSelectedPosHandle() const`
- L42 _public function_ `void SetRiverWidthSelectedPosHandle(bool InRiverWidthSelectedPosHandle)`
- L48 _protected member_ `bool bWaterVelocityIsSelected = false;` — `UPROPERTY()` — Whether water velocity handle is selected
- L52 _protected member_ `bool bDepthIsSelected = false;` — `UPROPERTY()` — Whether water depth handle is selected
- L56 _protected member_ `bool bRiverWidthIsSelected = false;` — `UPROPERTY()` — Whether water river width handle is selected
- L60 _protected member_ `bool bRiverWidthSelectedPosHandle = false;` — `UPROPERTY()` — When river width is selected, true if the handle on the positive right vector side was selected

#### struct `HWaterSplineVisProxy`  
`struct HWaterSplineVisProxy : public HComponentVisProxy`  
_L65-72_
- inherits: `HComponentVisProxy`
- desc: Base class for clickable water spline editing proxies
- L67 _public prototype_ `DECLARE_HIT_PROXY( );`
- L69 _public function_ `HWaterSplineVisProxy(const UActorComponent* InComponent) : HComponentVisProxy(InComponent, HPP_Wireframe)`

#### struct `HWaterSplineKeyProxy`  
`struct HWaterSplineKeyProxy : public HWaterSplineVisProxy`  
_L75-85_
- inherits: `HWaterSplineVisProxy`
- desc: Base class for clickable water spline editing proxies associated with a spline key
- L77 _public prototype_ `DECLARE_HIT_PROXY( );`
- L79 _public function_ `HWaterSplineKeyProxy(const UActorComponent* InComponent, int32 InKeyIndex) : HWaterSplineVisProxy(InComponent) , KeyIndex(InKeyIndex)`
- L84 _public member_ `int32 KeyIndex;`

#### struct `HWaterSplineWaterVelocityProxy`  
`struct HWaterSplineWaterVelocityProxy : public HWaterSplineKeyProxy`  
_L88-95_
- inherits: `HWaterSplineKeyProxy`
- desc: Proxy for a water velocity handle
- L90 _public prototype_ `DECLARE_HIT_PROXY( );`
- L92 _public function_ `HWaterSplineWaterVelocityProxy(const UActorComponent* InComponent, int32 InKeyIndex) : HWaterSplineKeyProxy(InComponent, InKeyIndex)`

#### struct `HWaterSplineRiverWidthProxy`  
`struct HWaterSplineRiverWidthProxy : public HWaterSplineKeyProxy`  
_L98-105_
- inherits: `HWaterSplineKeyProxy`
- desc: Proxy for a river width handle
- L100 _public prototype_ `DECLARE_HIT_PROXY( );`
- L102 _public function_ `HWaterSplineRiverWidthProxy(const UActorComponent* InComponent, int32 InKeyIndex) : HWaterSplineKeyProxy(InComponent, InKeyIndex)`

#### struct `HWaterSplineDepthProxy`  
`struct HWaterSplineDepthProxy : public HWaterSplineKeyProxy`  
_L108-115_
- inherits: `HWaterSplineKeyProxy`
- desc: Proxy for a water depth handle
- L110 _public prototype_ `DECLARE_HIT_PROXY( );`
- L112 _public function_ `HWaterSplineDepthProxy(const UActorComponent* InComponent, int32 InKeyIndex) : HWaterSplineKeyProxy(InComponent, InKeyIndex)`

#### struct `HWaterSplineAudioIntensityProxy`  
`struct HWaterSplineAudioIntensityProxy : public HWaterSplineKeyProxy`  
_L118-127_
- inherits: `HWaterSplineKeyProxy`
- desc: Proxy for a water shoreline audio intensity handle
- L120 _public prototype_ `DECLARE_HIT_PROXY( );`
- L122 _public function_ `HWaterSplineAudioIntensityProxy(const UActorComponent* InComponent, int32 InKeyIndex) : HWaterSplineKeyProxy(InComponent, InKeyIndex)`
- L126 _public member_ `int32 KeyIndex;`

#### class `FWaterSplineComponentVisualizer`  
`class FWaterSplineComponentVisualizer : public FSplineComponentVisualizer`  
_L130-194_
- inherits: `FSplineComponentVisualizer`
- desc: SplineComponent visualizer/edit functionality
- L133 _public prototype_ `FWaterSplineComponentVisualizer();`
- L134 _public prototype_ `virtual ~FWaterSplineComponentVisualizer();`
- L137 _public prototype_ `virtual void OnRegister() override;`
- L138 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L139 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click) override;`
- L141 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const override;`
- L142 _public prototype_ `virtual bool HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale) override;`
- L145 _public prototype_ `virtual void GenerateContextMenuSections(FMenuBuilder& InMenuBuilder) const;` — Add menu sections to the context menu
- L148 _public prototype_ `UWaterSplineComponent* GetEditedWaterSplineComponent() const;` — Get the water spline component we are currently editing
- L153 _protected prototype_ `virtual void ClearSelectionState();` — Update the key selection state of the visualizer
- L156 _protected prototype_ `virtual void ChangeSelectionState(int32 Index, bool bIsCtrlHeld);` — Update the key selection state of the visualizer
- L159 _protected prototype_ `const UWaterSplineComponent* UpdateSelectedWaterSplineComponent(HComponentVisProxy* VisProxy);` — Updates the component and selected properties if the component has changed
- L162 _protected prototype_ `void UpdateSelectionState(const int32 KeyIndex);` — Updates selected key prox index.
- L173 _protected prototype_ `bool VisProxyHandleWaterClick(const UWaterSplineComponent* WaterSplineComp, const FViewportClick& Click, float HandleLength, EHandleType HandleType, const FVector& LocalAxis, const FVector& LocalRotAxis);` — Handle water spline metadata vis proxy clicked, returns whether it is the positive or negative end
- L176 _protected prototype_ `float ComputeDelta(UWaterSplineComponent* WaterSplineComp, const FVector& InDeltaTranslate, float InCurrentHandleLength, const FVector& InAxis, float InScale, bool bClampToZero);` — Compute the actual delta based on input delta
- L178 _protected prototype_ `void OnSetVisualizeWaterVelocity();`
- L179 _protected prototype_ `bool CanSetVisualizeWaterVelocity() const;`
- L180 _protected prototype_ `bool IsVisualizingWaterVelocity() const;`
- L182 _protected prototype_ `void OnSetVisualizeRiverWidth();`
- L183 _protected prototype_ `bool CanSetVisualizeRiverWidth() const;`
- L184 _protected prototype_ `bool IsVisualizingRiverWidth() const;`
- L186 _protected prototype_ `void OnSetVisualizeDepth();`
- L187 _protected prototype_ `bool CanSetVisualizeDepth() const;`
- L188 _protected prototype_ `bool IsVisualizingDepth() const;`
- L190 _protected prototype_ `class UWaterSplineMetadata* GetEditedWaterSplineMetaData() const;`
- L193 _protected member_ `TSharedPtr<FUICommandList> WaterSplineComponentVisualizerActions;` — Action command list

#### enum `FWaterSplineComponentVisualizer::EHandleType`  
`enum class EHandleType`  
_L165-170_
- desc: Draw vis proxy handles
- L167 _public enumerator_ `PositiveAxis`
- L168 _public enumerator_ `NegativeAxis`
- L169 _public enumerator_ `Both`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WATEREDITOR_API`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterSplineMetadataDetails.h` (Private)


#### class `UWaterSplineMetadataDetailsFactory`  
`class UWaterSplineMetadataDetailsFactory : public USplineMetadataDetailsFactoryBase`  
_L16-24_
- reflection: `UCLASS()`
- inherits: `USplineMetadataDetailsFactoryBase`
- L21 _public prototype_ `virtual ~UWaterSplineMetadataDetailsFactory() = default;`
- L22 _public prototype_ `virtual TSharedPtr<ISplineMetadataDetails> Create() override;`
- L23 _public prototype_ `virtual UClass* GetMetadataClass() const override;`

#### class `FWaterSplineMetadataDetails`  
`class FWaterSplineMetadataDetails : public ISplineMetadataDetails, public TSharedFromThis<FWaterSplineMetadataDetails>`  
_L26-68_
- inherits: `ISplineMetadataDetails,TSharedFromThis<FWaterSplineMetadataDetails>`
- L29 _public prototype_ `virtual ~FWaterSplineMetadataDetails() = default;`
- L30 _public function_ `virtual FName GetName() const override`
- L31 _public prototype_ `virtual FText GetDisplayName() const override;`
- L32 _public prototype_ `virtual void Update(USplineComponent* InSplineComponent, const TSet<int32>& InSelectedKeys) override;`
- L33 _public prototype_ `virtual void GenerateChildContent(IDetailGroup& InGroup) override;`
- L35 _public member_ `TOptional<float> DepthValue;`
- L36 _public member_ `TOptional<float> RiverWidthValue;`
- L37 _public member_ `TOptional<float> VelocityValue;`
- L38 _public member_ `TOptional<float> AudioIntensityValue;`
- L40 _public member_ `USplineComponent* SplineComp = nullptr;`
- L41 _public member_ `TSet<int32> SelectedKeys;`
- L44 _private prototype_ `void OnBeginSliderMovement();`
- L45 _private prototype_ `void OnEndSliderMovement(float NewValue);`
- L47 _private function_ `EVisibility IsEnabled() const`
- L48 _private function_ `bool IsOnePointSelected() const`
- L50 _private prototype_ `EVisibility IsDepthVisible() const;`
- L51 _private function_ `TOptional<float> GetDepth() const`
- L52 _private prototype_ `void OnSetDepth(float NewValue, ETextCommit::Type CommitInfo);`
- L54 _private prototype_ `EVisibility IsRiverWidthVisible() const;`
- L55 _private function_ `TOptional<float> GetRiverWidth() const`
- L56 _private prototype_ `void OnSetRiverWidth(float NewValue, ETextCommit::Type CommitInfo);`
- L58 _private prototype_ `EVisibility IsVelocityVisible() const;`
- L59 _private function_ `TOptional<float> GetVelocity() const`
- L60 _private prototype_ `void OnSetVelocity(float NewValue, ETextCommit::Type CommitInfo);`
- L62 _private function_ `TOptional<float> GetAudioIntensity() const`
- L63 _private prototype_ `void OnSetAudioIntensity(float NewValue, ETextCommit::Type CommitInfo);`
- L65 _private prototype_ `class UWaterSplineMetadata* GetMetadata() const;`
- L67 _private member_ `TUniquePtr<FScopedTransaction> EditSliderValueTransaction;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ETextCommit`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterUIStyle.h` (Private)


#### class `FWaterUIStyle`  
`class FWaterUIStyle`  
_L7-20_
- L10 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L16 _public prototype_ `static FName GetStyleSetName();`
- L19 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterWavesAssetFactory.h` (Private)


#### class `UWaterWavesAssetFactory`  
`class UWaterWavesAssetFactory : public UFactory`  
_L9-21_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public prototype_ `UWaterWavesAssetFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface
- L19 _public prototype_ `virtual FText GetToolTip() const override;`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterWavesEditorCommands.h` (Private)


#### class `FWaterWavesEditorCommands`  
`class FWaterWavesEditorCommands : public TCommands<FWaterWavesEditorCommands>`  
_L8-23_
- inherits: `TCommands<FWaterWavesEditorCommands>`
- L11 _public function_ `FWaterWavesEditorCommands() : TCommands<FWaterWavesEditorCommands>( "WaterWavesEditor", NSLOCTEXT("WaterWavesEditor", "Water Waves Editor", "Water Waves Editor Commands"), "EditorViewport", FWaterUIStyle::GetStyleSetName())`
- L19 _public member_ `TSharedPtr<FUICommandInfo> TogglePauseWaveTime;` — Toggle if wave time should be paused
- L22 _public prototype_ `virtual void RegisterCommands() override;` — Register commands

### `Plugins/Experimental/Water/Source/Editor/Private/WaterWavesEditorToolkit.h` (Private)


#### class `FWaterWavesEditorToolkit`  
`class FWaterWavesEditorToolkit : public FAssetEditorToolkit, public FNotifyHook, public FGCObject`  
_L17-67_
- inherits: `FAssetEditorToolkit,FNotifyHook,FGCObject`
- L20 _public prototype_ `void InitWaterWavesEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit);`
- L22 _public function_ `UWaterWavesAssetReference* GetWavesAssetRef()`
- L25 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L26 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L27 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L28 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L31 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L32 _public function_ `virtual FString GetReferencerName() const override`
- L38 _private prototype_ `void ExtendToolbar();`
- L40 _private prototype_ `void FillToolbar(FToolBarBuilder& ToolbarBuilder, const TSharedRef<FUICommandList> InToolkitCommands);`
- L42 _private prototype_ `void BindCommands();`
- L44 _private prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L45 _private prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L48 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);` — Tab spawners
- L49 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);`
- L52 _private prototype_ `void TogglePauseWaveTime();` — Command actions
- L53 _private prototype_ `bool IsWaveTimePaused() const;`
- L55 _private member_ `static const FName ViewportTabId;`
- L56 _private member_ `static const FName PropertiesTabId;`
- L58 _private member_ `TObjectPtr<UWaterWavesAssetReference> WaterWavesAssetRef = nullptr;`
- L61 _private member_ `TSharedPtr<FEditorViewportTabContent> ViewportTabContent;` — Tracking the active viewports in this editor.
- L64 _private member_ `TSharedPtr<IDetailsView> WaterWavesDetailsView;` — Property View
- L66 _private member_ `bool bWaveTimePaused = false;`

### `Plugins/Experimental/Water/Source/Editor/Private/WaterWavesEditorViewport.h` (Private)


#### class `SWaterWavesEditorViewport`  
`class SWaterWavesEditorViewport : public SAssetEditorViewport, public ICommonEditorViewportToolbarInfoProvider, public FGCObject`  
_L19-59_
- inherits: `SAssetEditorViewport,ICommonEditorViewportToolbarInfoProvider,FGCObject`
- L22 _public function_ `SLATE_BEGIN_ARGS(SWaterWavesEditorViewport)`
- L23 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<FWaterWavesEditorToolkit>, WaterWavesEditorToolkit) SLATE_END_ARGS() SWaterWavesEditorViewport();`
- L28 _public prototype_ `void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `virtual TSharedRef<SEditorViewport> GetViewportWidget() override;`
- L32 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L33 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L36 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L37 _public function_ `virtual FString GetReferencerName() const override`
- L43 _public prototype_ `void SetShouldPauseWaveTime(bool bShouldFreeze);`
- L46 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L47 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L48 _protected prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L51 _private member_ `TSharedPtr<FAdvancedPreviewScene> PreviewScene;` — The scene for this viewport.
- L54 _private member_ `TSharedPtr<FEditorViewportClient> EditorViewportClient;` — Editor viewport client
- L56 _private member_ `TWeakPtr<FWaterWavesEditorToolkit> WaterWavesEditorToolkitPtr;`
- L58 _private member_ `TObjectPtr<AWaterBodyCustom> CustomWaterBody = nullptr;`

#### class `FWaterWavesEditorViewportClient`  
`class FWaterWavesEditorViewportClient : public FEditorViewportClient`  
_L64-74_
- inherits: `FEditorViewportClient`
- L67 _public typedef_ `using Super = FEditorViewportClient;`
- L69 _public prototype_ `FWaterWavesEditorViewportClient(FPreviewScene* InPreviewScene, const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr);`
- L72 _public prototype_ `virtual void Tick(float DeltaSeconds) override;` — FEditorViewportClient interface

### `Plugins/Experimental/Water/Source/Editor/Private/WaterZoneActorFactory.h` (Private)


#### class `UWaterZoneActorFactory`  
`class UWaterZoneActorFactory : public UActorFactory`  
_L8-13_
- reflection: `UCLASS(MinimalAPI, config = Editor)`
- inherits: `UActorFactory`
- L12 _private prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`

### `Plugins/Experimental/Water/Source/Editor/Public/CausticsGeneratorActor.h` (Public)


#### class `ACausticsGeneratorActor`  
`class ACausticsGeneratorActor: public AActor`  
_L11-47_
- reflection: `UCLASS(Blueprintable, hidecategories = (Replication, Input, LOD, Actor, Cooking, Rendering, Collision))`
- inherits: `AActor`
- L23 _public member_ `TObjectPtr<USceneComponent> DefaultSceneRoot;` — `UPROPERTY(BlueprintReadWrite, NonTransactional, meta = (Category = "Default"))`
- L27 _public prototype_ `void EditorTick(float DeltaSeconds);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "Tick")`
- L29 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L30 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L33 _public function_ `void SetEditorTickEnabled(bool bEnabled)` — `UFUNCTION(BlueprintCallable, category = "Default")`
- L36 _public member_ `bool EditorTickIsEnabled = false;` — `UPROPERTY(Transient)`
- L39 _public prototype_ `void SpawnWaterPreviewGrid(UHierarchicalInstancedStaticMeshComponent* HISMC, float GridSize, int GridTiles);` — `UFUNCTION(BlueprintCallable, category = "Water Mesh Preview")`
- L42 _public prototype_ `void SpawnCausticParticleGrid(UHierarchicalInstancedStaticMeshComponent* HISMC, float GridSize, int GridTiles);` — `UFUNCTION(BlueprintCallable, category = "Water Mesh Preview")`
- L44 _public prototype_ `ACausticsGeneratorActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`

### `Plugins/Experimental/Water/Source/Editor/Public/WaterBodyActorDetailCustomization.h` (Public)


#### class `FWaterBodyActorDetailCustomization`  
`class FWaterBodyActorDetailCustomization : public IDetailCustomization`  
_L9-58_
- inherits: `IDetailCustomization`
- L12 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L17 _public function_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)`
- L39 _private function_ `bool IsWaveSupported(const TArray<TWeakObjectPtr<UObject>>& SelectedObjects) const`

### `Plugins/Experimental/Water/Source/Editor/Public/WaterEditorModule.h` (Public)


#### class `IWaterEditorModuleInterface`  
`class IWaterEditorModuleInterface : public IModuleInterface`  
_L18-22_
- inherits: `IModuleInterface`

#### class `FWaterEditorModule`  
`class FWaterEditorModule : public IWaterEditorModuleInterface`  
_L24-53_
- inherits: `IWaterEditorModuleInterface`
- L27 _public prototype_ `virtual void StartupModule() override;`
- L29 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _public function_ `static EAssetTypeCategories::Type GetAssetCategory()`
- L33 _public prototype_ `TSharedRef<FWaterWavesEditorToolkit> CreateWaterWaveAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UObject* WavesAsset);`
- L36 _private prototype_ `void RegisterComponentVisualizer(FName ComponentClassName, TSharedPtr<FComponentVisualizer> Visualizer);`
- L38 _private prototype_ `void OnLevelActorAddedToWorld(AActor* Actor);`
- L40 _private prototype_ `void CheckForWaterCollisionProfile();`
- L42 _private prototype_ `void AddWaterCollisionProfile();`
- L46 _private member_ `TArray<FName> RegisteredComponentClassNames;` — Array of component class names we have registered, so we know what to unregister afterwards
- L48 _private member_ `static EAssetTypeCategories::Type WaterAssetCategory;`
- L50 _private member_ `TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;`
- L52 _private member_ `FDelegateHandle OnLoadCollisionProfileConfigHandle;`

#### Free symbols / members of external scopes

- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWaterEditor, Log, All);`

### `Plugins/Experimental/Water/Source/Editor/Public/WaterEditorSettings.h` (Public)


#### struct `FWaterBrushActorDefaults`  
`struct FWaterBrushActorDefaults`  
_L25-39_
- reflection: `USTRUCT()`
- L29 _public prototype_ `FWaterBrushActorDefaults();`
- L32 _public member_ `FWaterCurveSettings CurveSettings;` — `UPROPERTY(EditAnywhere, config, Category = Terrain)`
- L35 _public member_ `FWaterBodyHeightmapSettings HeightmapSettings;` — `UPROPERTY(EditAnywhere, config, Category = Terrain)`
- L38 _public member_ `TMap<FName, FWaterBodyWeightmapSettings> LayerWeightmapSettings;` — `UPROPERTY(EditAnywhere, config, Category = Terrain)`

#### struct `FWaterZoneActorDefaults`  
`struct FWaterZoneActorDefaults`  
_L42-62_
- reflection: `USTRUCT()`
- L46 _public prototype_ `FWaterZoneActorDefaults();`
- L48 _public prototype_ `UMaterialInterface* GetFarDistanceMaterial() const;`
- L51 _public member_ `float FarDistanceMeshExtent = 4000000.0f;` — `UPROPERTY(EditAnywhere, config, Category = Mesh)`
- L54 _public member_ `float NewWaterZoneScale = 1.0f;` — `UPROPERTY(EditAnywhere, config, Category = Mesh)`
- L57 _public member_ `FIntPoint RenderTargetResolution = FIntPoint(1024, 1024);` — `UPROPERTY(EditAnywhere, config, Category = Texture)`
- L61 _protected member_ `TSoftObjectPtr<UMaterialInterface> FarDistanceMaterial;` — `UPROPERTY(EditAnywhere, Config, Category = Mesh)`

#### struct `FWaterBodyDefaults`  
`struct FWaterBodyDefaults`  
_L66-100_
- reflection: `USTRUCT()`
- L70 _public prototype_ `FWaterBodyDefaults();`
- L73 _public member_ `FWaterSplineCurveDefaults SplineDefaults;` — `UPROPERTY(EditAnywhere, config, Category = "Water Spline")`
- L76 _public prototype_ `UMaterialInterface* GetWaterMaterial() const;`
- L77 _public function_ `FSoftObjectPath GetWaterMaterialPath() const`
- L79 _public prototype_ `UMaterialInterface* GetWaterStaticMeshMaterial() const;`
- L80 _public function_ `FSoftObjectPath GetWaterStaticMeshMaterialPath() const`
- L82 _public prototype_ `UMaterialInterface* GetWaterHLODMaterial() const;`
- L83 _public function_ `FSoftObjectPath GetWaterHLODMaterialPath() const`
- L85 _public prototype_ `UMaterialInterface* GetUnderwaterPostProcessMaterial() const;`
- L86 _public function_ `FSoftObjectPath GetUnderwaterPostProcessMaterialPath() const`
- L90 _protected member_ `TSoftObjectPtr<UMaterialInterface> WaterMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Rendering)`
- L93 _protected member_ `TSoftObjectPtr<UMaterialInterface> WaterStaticMeshMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Rendering)`
- L96 _protected member_ `TSoftObjectPtr<UMaterialInterface> WaterHLODMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Rendering)`
- L99 _protected member_ `TSoftObjectPtr<UMaterialInterface> UnderwaterPostProcessMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Rendering)`

#### struct `FWaterBodyRiverDefaults`  
`struct FWaterBodyRiverDefaults : public FWaterBodyDefaults`  
_L103-124_
- reflection: `USTRUCT()`
- inherits: `FWaterBodyDefaults`
- L107 _public prototype_ `FWaterBodyRiverDefaults();`
- L110 _public member_ `FWaterBrushActorDefaults BrushDefaults;` — `UPROPERTY(EditAnywhere, config, Category = Terrain)`
- L112 _public prototype_ `UMaterialInterface* GetRiverToOceanTransitionMaterial() const;`
- L113 _public function_ `FSoftObjectPath GetRiverToOceanTransitionTransitionMaterialPath() const`
- L115 _public prototype_ `UMaterialInterface* GetRiverToLakeTransitionMaterial() const;`
- L116 _public function_ `FSoftObjectPath GetRiverToLakeTransitionTransitionMaterialPath() const`
- L120 _protected member_ `TSoftObjectPtr<UMaterialInterface> RiverToOceanTransitionMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Rendering)`
- L123 _protected member_ `TSoftObjectPtr<UMaterialInterface> RiverToLakeTransitionMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Rendering)`

#### struct `FWaterBodyLakeDefaults`  
`struct FWaterBodyLakeDefaults : public FWaterBodyDefaults`  
_L128-139_
- reflection: `USTRUCT()`
- inherits: `FWaterBodyDefaults`
- L132 _public prototype_ `FWaterBodyLakeDefaults();`
- L135 _public member_ `FWaterBrushActorDefaults BrushDefaults;` — `UPROPERTY(EditAnywhere, config, Category = Terrain)`
- L138 _public member_ `TObjectPtr<UWaterWavesBase> WaterWaves = nullptr;` — `UPROPERTY(EditAnywhere, Instanced, Category = Wave)`

#### struct `FWaterBodyOceanDefaults`  
`struct FWaterBodyOceanDefaults : public FWaterBodyDefaults`  
_L143-154_
- reflection: `USTRUCT()`
- inherits: `FWaterBodyDefaults`
- L147 _public prototype_ `FWaterBodyOceanDefaults();`
- L150 _public member_ `FWaterBrushActorDefaults BrushDefaults;` — `UPROPERTY(EditAnywhere, config, Category = Terrain)`
- L153 _public member_ `TObjectPtr<UWaterWavesBase> WaterWaves = nullptr;` — `UPROPERTY(EditAnywhere, Instanced, Category = Wave)`

#### struct `FWaterBodyCustomDefaults`  
`struct FWaterBodyCustomDefaults : public FWaterBodyDefaults`  
_L158-170_
- reflection: `USTRUCT()`
- inherits: `FWaterBodyDefaults`
- L162 _public prototype_ `FWaterBodyCustomDefaults();`
- L164 _public prototype_ `UStaticMesh* GetWaterMesh() const;`
- L165 _public function_ `FSoftObjectPath GetWaterMeshPath() const`
- L169 _private member_ `TSoftObjectPtr<UStaticMesh> WaterMesh;` — `UPROPERTY(EditAnywhere, config, Category = Rendering)`

#### struct `FWaterBodyIslandDefaults`  
`struct FWaterBodyIslandDefaults`  
_L174-182_
- reflection: `USTRUCT()`
- L178 _public prototype_ `FWaterBodyIslandDefaults();`
- L181 _public member_ `FWaterBrushActorDefaults BrushDefaults;` — `UPROPERTY(EditAnywhere, config, Category = Terrain)`

#### class `UWaterEditorSettings`  
`class UWaterEditorSettings : public UDeveloperSettings`  
_L189-324_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, meta=(DisplayName="Water Editor"))`
- inherits: `UDeveloperSettings`
- desc: Implements the editor settings for the Water plugin.
- L194 _public prototype_ `UWaterEditorSettings();`
- L196 _public function_ `virtual FName GetCategoryName() const override`
- L198 _public prototype_ `TSubclassOf<AWaterZone> GetWaterZoneClass() const;`
- L199 _public function_ `FSoftClassPath GetWaterZoneClassPath() const`
- L201 _public prototype_ `TSubclassOf<AWaterLandscapeBrush> GetWaterManagerClass() const;`
- L202 _public function_ `FSoftClassPath GetWaterManagerClassPath() const`
- L204 _public prototype_ `UMaterialInterface* GetDefaultBrushAngleFalloffMaterial() const;`
- L205 _public function_ `FSoftObjectPath GetDefaultBrushAngleFalloffMaterialPath() const`
- L207 _public prototype_ `UMaterialInterface* GetDefaultBrushIslandFalloffMaterial() const;`
- L208 _public function_ `FSoftObjectPath GetDefaultBrushIslandFalloffMaterialPath() const`
- L210 _public prototype_ `UMaterialInterface* GetDefaultBrushWidthFalloffMaterial() const;`
- L211 _public function_ `FSoftObjectPath GetDefaultBrushWidthFalloffMaterialPath() const`
- L213 _public prototype_ `UMaterialInterface* GetDefaultBrushWeightmapMaterial() const;`
- L214 _public function_ `FSoftObjectPath GetDefaultBrushWeightmapMaterialPath() const`
- L216 _public prototype_ `UMaterialInterface* GetDefaultCacheDistanceFieldCacheMaterial() const;`
- L217 _public function_ `FSoftObjectPath GetDefaultCacheDistanceFieldCacheMaterialPath() const`
- L219 _public prototype_ `UMaterialInterface* GetDefaultCompositeWaterBodyTextureMaterial() const;`
- L220 _public function_ `FSoftObjectPath GetDefaultCompositeWaterBodyTextureMaterialPath() const`
- L222 _public prototype_ `UMaterialInterface* GetDefaultJumpFloodStepMaterial() const;`
- L223 _public function_ `FSoftObjectPath GetDefaultJumpFloodStepMaterialPath() const`
- L225 _public prototype_ `UMaterialInterface* GetDefaultBlurEdgesMaterial() const;`
- L226 _public function_ `FSoftObjectPath GetDefaultBlurEdgesMaterialPath() const`
- L228 _public prototype_ `UMaterialInterface* GetDefaultFindEdgesMaterial() const;`
- L229 _public function_ `FSoftObjectPath GetDefaultFindEdgesMaterialPath() const`
- L231 _public prototype_ `UMaterialInterface* GetDefaultDrawCanvasMaterial() const;`
- L232 _public function_ `FSoftObjectPath GetDefaultDrawCanvasMaterialPath() const`
- L234 _public prototype_ `UMaterialInterface* GetDefaultRenderRiverSplineDepthsMaterial() const;`
- L235 _public function_ `FSoftObjectPath GetDefaultRenderRiverSplineDepthsMaterialPath() const`
- L237 _public function_ `bool GetShouldUpdateWaterMeshDuringInteractiveChanges() const`
- L242 _public member_ `TEnumAsByte<TextureGroup> TextureGroupForGeneratedTextures;` — `UPROPERTY(EditAnywhere, config, Category = Rendering)` — The texture group to use for generated textures such as the combined velocity and height texture
- L246 _public member_ `int32 MaxWaterVelocityAndHeightTextureSize;` — `UPROPERTY(EditAnywhere, config, Category = Rendering, meta=(ClampMin=1, ClampMax=2048))` — Maximum size of the water velocity/height texture for a WaterZoneActor
- L250 _public member_ `float VisualizeWaterVelocityScale = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (ClampMin = "0.1", UIMin = "0.1"))` — Scale factor for visualizing water velocity
- L254 _public member_ `TSoftObjectPtr<UMaterialParameterCollection> LandscapeMaterialParameterCollection;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)` — Material Parameter Collection for everything landscape-related
- L258 _public member_ `FWaterZoneActorDefaults WaterZoneActorDefaults;` — `UPROPERTY(EditAnywhere, config, Category = ActorDefaults)` — Default values for base WaterMesh actor
- L261 _public member_ `FWaterBodyRiverDefaults WaterBodyRiverDefaults;` — `UPROPERTY(EditAnywhere, config, Category = ActorDefaults)` — Default values for base WaterBodyRiver actor
- L265 _public member_ `FWaterBodyLakeDefaults WaterBodyLakeDefaults;` — `UPROPERTY(EditAnywhere, config, Category = ActorDefaults)` — Default values for base WaterBodyLake actor
- L269 _public member_ `FWaterBodyOceanDefaults WaterBodyOceanDefaults;` — `UPROPERTY(EditAnywhere, config, Category = ActorDefaults)` — Default values for base WaterBodyOcean actor
- L273 _public member_ `FWaterBodyCustomDefaults WaterBodyCustomDefaults;` — `UPROPERTY(EditAnywhere, config, Category = ActorDefaults)` — Default values for base WaterBodyCustom actor
- L277 _public member_ `FWaterBodyIslandDefaults WaterBodyIslandDefaults;` — `UPROPERTY(EditAnywhere, config, Category = ActorDefaults)` — Default values for base WaterBodyIsland actor
- L282 _private member_ `bool bUpdateWaterMeshDuringInteractiveChanges = false;` — `UPROPERTY(EditAnywhere, config, Category = Brush)` — Allows the water mesh to be updated when the water body's shape is modified interactively (e.g. when dragging a spline point). Set to false if the performance when editing a water body gets too bad (the water mesh will be properly updated when the dragging operation is done).
- L286 _private member_ `FSoftClassPath WaterZoneClassPath;` — `UPROPERTY(EditAnywhere, config, Category = Water, meta = (MetaClass = "/Script/Water.WaterZone"))` — Class of the water zone to be used
- L290 _private member_ `FSoftClassPath WaterManagerClassPath;` — `UPROPERTY(EditAnywhere, config, Category = Brush, meta = (MetaClass = "/Script/WaterEditor.WaterLandscapeBrush"), AdvancedDisplay)` — Class of the water brush to be used in landscape
- L293 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultBrushAngleFalloffMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`
- L296 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultBrushIslandFalloffMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`
- L299 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultBrushWidthFalloffMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`
- L302 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultBrushWeightmapMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`
- L305 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultCacheDistanceFieldCacheMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`
- L308 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultCompositeWaterBodyTextureMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`
- L311 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultJumpFloodStepMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`
- L314 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultBlurEdgesMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`
- L317 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultFindEdgesMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`
- L320 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultDrawCanvasMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`
- L323 _private member_ `TSoftObjectPtr<UMaterialInterface> DefaultRenderRiverSplineDepthsMaterial;` — `UPROPERTY(EditAnywhere, config, Category = Brush, AdvancedDisplay)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API WATEREDITOR_API`

### `Plugins/Experimental/Water/Source/Editor/Public/WaterEditorSubsystem.h` (Public)


#### class `UWaterEditorSubsystem`  
`class UWaterEditorSubsystem : public UEditorSubsystem, public IWaterEditorServices`  
_L18-65_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem,IWaterEditorServices`
- L22 _private prototype_ `UWaterEditorSubsystem();`
- L24 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L25 _public prototype_ `virtual void Deinitialize() override;`
- L27 _public function_ `UMaterialParameterCollection* GetLandscapeMaterialParameterCollection() const`
- L30 _public prototype_ `virtual void RegisterWaterActorSprite(UClass* InClass, UTexture2D* Texture) override;`
- L31 _public prototype_ `virtual UTexture2D* GetWaterActorSprite(UClass* InClass) const override;`
- L32 _public function_ `virtual UTexture2D* GetErrorSprite() const override`
- L34 _public prototype_ `virtual bool TryMarkPackageAsModified(UPackage* ModifiedPackage) override;`
- L35 _public prototype_ `virtual bool HasAnyModifiedPackages() const override;`
- L36 _public prototype_ `virtual void ForEachModifiedPackage(const TFunctionRef<bool(UPackage*)>& Func) const override;`
- L37 _public prototype_ `virtual void ClearModifiedPackages() override;`
- L38 _public prototype_ `virtual void DirtyAllModifiedPackages() override;`
- L40 _public prototype_ `virtual bool GetShouldUpdateWaterMeshDuringInteractiveChanges() const override;`
- L44 _private prototype_ `UWorld* GetEditorWorld() const;`
- L46 _private prototype_ `void UpdateModifiedPackagesMessage();`
- L48 _private prototype_ `void OnPackageDirtied(UPackage* Package);`
- L49 _private prototype_ `void OnMapChanged(UWorld* InWorld, EMapChangeType InChangeType);`
- L52 _private member_ `TObjectPtr<UMaterialParameterCollection> LandscapeMaterialParameterCollection;` — `UPROPERTY()`
- L55 _private member_ `TMap<TObjectPtr<UClass>, TObjectPtr<UTexture2D>> WaterActorSprites;` — `UPROPERTY()`
- L57 _private member_ `TObjectPtr<UTexture2D> DefaultWaterActorSprite;` — `UPROPERTY()`
- L59 _private member_ `TObjectPtr<UTexture2D> ErrorSprite;` — `UPROPERTY()`
- L62 _private member_ `TSet<TWeakObjectPtr<UPackage>, TWeakObjectPtrSetKeyFuncs<TWeakObjectPtr<UPackage>>> PackagesNeedingDirtying;` — Set of water body packages which have been silently modified but not dirtied.
- L64 _private member_ `bool bSuppressOnDirtyEvents = false;`
