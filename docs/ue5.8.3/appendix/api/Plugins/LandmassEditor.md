# Plugins / LandmassEditor

- module root: `Plugins/Experimental/Landmass/Source/Editor`
- headers: 5; symbols: 124
- symbol kinds: class=5, delegate=1, enum=1, enumerator=4, function=6, member=44, prototype=61, struct=2
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, Landscape, LevelEditor, UnrealEd

### `Plugins/Experimental/Landmass/Source/Editor/Public/LandmassActor.h` (Public)


#### enum `EBrushBlendMode`  
`enum class EBrushBlendMode : uint8`  
_L18-24_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `AlphaBlend`
- L21 _public enumerator_ `Min`
- L22 _public enumerator_ `Max`
- L23 _public enumerator_ `Additive`

#### class `ALandmassActor`  
`class ALandmassActor : public AActor`  
_L28-154_
- reflection: `UCLASS(Blueprintable, PrioritizeCategories = ("PreviewMode", "LayerOrdering", "BrushSettings", "HeightmapSettings", "WeightmapSettings", "Debug"), hidecategories = (Replication, Input, LOD, Actor, Cooking, Rendering, Collision, HLOD, Physics, Networking, LevelInstance, DataLayers))`
- inherits: `AActor`
- L32 _private prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L35 _public prototype_ `ALandmassActor();`
- L38 _public prototype_ `void CustomTick(float DeltaSeconds);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "Tick")`
- L40 _public function_ `virtual bool IsEditorOnly() const override`
- L42 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;`
- L43 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L46 _public prototype_ `void RenderLayer_Native(const FLandscapeBrushParameters& InParameters);` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = Default)`
- L49 _public prototype_ `void RenderLayer(const FLandscapeBrushParameters& InParameters);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, meta = (ForceAsFunction) , Category = Default)`
- L52 _public prototype_ `void FastPreviewMode();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "PreviewMode", meta = (DisplayPriority = 1))`
- L55 _public prototype_ `void RestoreLandscapeEditing();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "PreviewMode", meta = (DisplayPriority = 2))`
- L58 _public prototype_ `void MoveBrushUp();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "LayerOrdering", meta = (DisplayPriority = 3))`
- L61 _public prototype_ `void MoveBrushDown();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "LayerOrdering", meta = (DisplayPriority = 4))`
- L64 _public prototype_ `void MoveToTop();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "LayerOrdering", meta = (DisplayPriority = 5))`
- L67 _public prototype_ `void MoveToBottom();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "LayerOrdering", meta = (DisplayPriority = 6))`
- L70 _public member_ `float BrushSize = 4096;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BrushSettings", meta = (DisplayPriority = 8))`
- L73 _public member_ `bool DrawToEntireLandscape = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BrushSettings", meta = (DisplayPriority = 9))`
- L76 _public member_ `bool AffectsHeightmap = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BrushSettings", meta = (DisplayPriority = 10))`
- L79 _public member_ `bool AffectsWeightmaps = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BrushSettings", meta = (DisplayPriority = 11))`
- L82 _public member_ `bool AffectsVisibility = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BrushSettings", meta = (DisplayPriority = 12))`
- L85 _public member_ `EBrushBlendMode HeightBlendMode = EBrushBlendMode::AlphaBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeightmapSettings", meta = (DisplayPriority = 13))`
- L88 _public member_ `TObjectPtr<UMaterialInterface> HeightMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HeightmapSettings", meta = (DisplayPriority = 14))`
- L91 _public member_ `EBrushBlendMode WeightMapBlendMode = EBrushBlendMode::AlphaBlend;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeightmapSettings", meta = (DisplayPriority = 15))`
- L94 _public member_ `TObjectPtr<UMaterialInterface> WeightmapMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeightmapSettings", meta = (DisplayPriority = 16))`
- L97 _public member_ `FVector4 BrushExtents;` — `UPROPERTY(BlueprintReadOnly, Category = "Debug", meta = (DisplayPriority = 17))`
- L100 _public member_ `TArray<FName> WeightmapLayers;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta = (DisplayPriority = 18))`
- L103 _public member_ `FLandscapeBrushParameters BrushRenderParameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta = (DisplayPriority = 19))`
- L106 _public member_ `TObjectPtr<ALandmassManagerBase> BrushManager;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug", meta = (DisplayPriority = 20))`
- L109 _public function_ `void SetEditorTickEnabled(bool bEnabled)` — `UFUNCTION(BlueprintCallable, category = "Default")`
- L112 _public prototype_ `void UpdateBrushExtents();` — `UFUNCTION(BlueprintCallable, Category = "Landmass")`
- L115 _public member_ `bool EditorTickIsEnabled = false;` — `UPROPERTY()`
- L118 _public prototype_ `void ActorSelectionChanged(bool bSelected);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "Selection")`
- L120 _public prototype_ `void FindOrSpawnManager();`
- L123 _public prototype_ `void DrawBrushMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = Default)`
- L126 _public prototype_ `void SetMeshExentsMaterial(UMaterialInterface* Material);` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = Default)`
- L129 _public member_ `FOnBrushUpdatedDelegate OnBrushUpdated;` — `UPROPERTY(BlueprintAssignable, Category = "Landmass")`
- L132 _public member_ `TObjectPtr<UMaterialInstanceDynamic> ExtentsPreviewMID;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = "Debug", meta = (DisplayPriority = 21))`
- L135 _public member_ `TObjectPtr<UMaterialInstanceDynamic> HeightmapRenderMID;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = "Debug", meta = (DisplayPriority = 22))`
- L138 _public member_ `TObjectPtr<UMaterialInstanceDynamic> WeightmapRenderMID;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient, Category = "Debug", meta = (DisplayPriority = 23))`
- L141 _private member_ `bool bWasSelected = false;`
- L144 _private member_ `TObjectPtr<UStaticMeshComponent> MeshExtentsQuad;` — `UPROPERTY()`
- L147 _private member_ `TObjectPtr<UStaticMeshComponent> BrushSpriteMesh;` — `UPROPERTY()`
- L149 _private member_ `FDelegateHandle OnActorSelectionChangedHandle;`
- L152 _private prototype_ `void HandleActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);` — Called when the editor selection has changed.

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBrushUpdatedDelegate);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBrushUpdatedDelegate);`

### `Plugins/Experimental/Landmass/Source/Editor/Public/LandmassBPEditorExtension.h` (Public)


#### class `ULandmassBlueprintFunctionLibrary`  
`class ULandmassBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L11-28_
- reflection: `UCLASS(meta = (Namespace = "Landmass"))`
- inherits: `UBlueprintFunctionLibrary`
- L18 _public prototype_ `static bool GetCursorWorldRay(FVector& CameraLocation, FVector& RayOrigin, FVector& RayDirection);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Cursor World Ray", Keywords = "Get Cursor World Ray", UnsafeDuringActorConstruction = "true"), Category = Rendering)`
- L21 _public prototype_ `static void CombineWorldExtents(FVector4 ExtentsA, FVector4 ExtentsB, FVector4& CombinedExtents);` — `UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Get Overlapping World Extents", Keywords = "Combine World Extents", UnsafeDuringActorConstruction = "false"), Category = Landmass)`
- L24 _public prototype_ `static void WorldExtentsToCanvasCoordinates(FVector4 WorldExtents, FLandmassLandscapeInfo LandscapeInfo, FVector2D& ScreenPosition, FVector2D& ScreenSize, FVector2D& CoordinatePosition, FVector2D& CoordinateSize);` — `UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "World Extents to Landmass Coordinates", Keywords = "World Extents to Landmass Coordinates", UnsafeDuringActorConstruction = "false"), Category = Landmass)`
- L27 _public prototype_ `static void ForceUpdateTexture(UTexture* InTexture);` — `UFUNCTION(BlueprintCallable, Category = Rendering)`

### `Plugins/Experimental/Landmass/Source/Editor/Public/LandmassEditorModule.h` (Public)


#### class `ILandmassEditorModuleInterface`  
`class ILandmassEditorModuleInterface : public IModuleInterface`  
_L8-10_
- inherits: `IModuleInterface`

### `Plugins/Experimental/Landmass/Source/Editor/Public/LandmassErosionBrushBase.h` (Public)


#### class `ALandmassErosionBrushBase`  
`class ALandmassErosionBrushBase : public ALandscapeBlueprintBrushBase`  
_L13-61_
- reflection: `UCLASS(Blueprintable, hidecategories = (Replication, Input, LOD, Actor, Cooking, Rendering))`
- inherits: `ALandscapeBlueprintBrushBase`
- L17 _private prototype_ `virtual void OnConstruction(const FTransform& Transform) override;`
- L21 _public prototype_ `ALandmassErosionBrushBase();`
- L23 _public function_ `virtual bool IsEditorOnly() const override`
- L28 _public prototype_ `virtual void SetTargetLandscape(ALandscape* InOwningLandscape);` — `UFUNCTION(BlueprintCallable, category = "Landmass")` — Adds the brush to the given landscape, removing it from any previous one. This differs from SetOwningLandscape in that SetOwningLandscape is called by the landscape itself from AddBrushToLayer to update the manager.
- L31 _public prototype_ `ALandscape* GetLandscape();` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L34 _public prototype_ `void ActorSelectionChanged(bool bSelected);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "Selection")`
- L36 _public prototype_ `void FindAndAssignLandscape();`
- L40 _public prototype_ `virtual void SetOwningLandscape(class ALandscape* InOwningLandscape) override;` — ALandscapeBlueprintBrushBase
- L41 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L45 _private member_ `bool bWasSelected = false;`
- L47 _private member_ `FDelegateHandle OnActorSelectionChangedHandle;`
- L50 _private prototype_ `void HandleActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);` — Called when the editor selection has changed.
- L58 _private member_ `TObjectPtr<ALandscape> DetailPanelLandscape;` — `UPROPERTY(EditAnywhere, Category = Landscape, Transient, meta = (DisplayName = "Landscape"))` — The owning landscape.

#### Free symbols / members of external scopes

- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LandmassErosionBrush, Display, All);`

### `Plugins/Experimental/Landmass/Source/Editor/Public/LandmassManagerBase.h` (Public)


#### struct `FBrushDataTree`  
`struct FBrushDataTree`  
_L14-39_
- reflection: `USTRUCT(BlueprintType)`
- L17 _public function_ `FBrushDataTree()`
- L22 _public member_ `int32 CurrentLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L24 _public member_ `int32 ParentIndex;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L26 _public member_ `TArray<TObjectPtr<ALandmassActor>> BrushActors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L28 _public member_ `int32 Index_x0y0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L30 _public member_ `int32 Index_x1y0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L32 _public member_ `int32 Index_x0y1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L34 _public member_ `int32 Index_x1y1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L36 _public member_ `int32 ChildDataCount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L38 _public member_ `FVector4 NodeExtents;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`

#### struct `FLandmassLandscapeInfo`  
`struct FLandmassLandscapeInfo`  
_L42-56_
- reflection: `USTRUCT(BlueprintType)`
- L45 _public function_ `FLandmassLandscapeInfo()`
- L50 _public member_ `FTransform LandscapeTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L52 _public member_ `FIntPoint LandscapeQuads;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L54 _public member_ `FIntPoint RenderTargetResolution;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`

#### class `ALandmassManagerBase`  
`class ALandmassManagerBase : public ALandscapeBlueprintBrushBase`  
_L59-165_
- reflection: `UCLASS(Blueprintable, hidecategories = (Replication, Input, LOD, Actor, Cooking, Rendering))`
- inherits: `ALandscapeBlueprintBrushBase`
- L65 _public prototype_ `ALandmassManagerBase();`
- L67 _public function_ `virtual bool IsEditorOnly() const override`
- L70 _public member_ `TArray<FBrushDataTree> BrushNodeData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quadtree)`
- L73 _public member_ `FLandmassLandscapeInfo LandscapeInformation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L76 _public member_ `int32 BrushTreeDepth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quadtree)`
- L79 _public member_ `TArray<TObjectPtr<ALandmassActor>> LandmassBrushes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Landmass)`
- L84 _public prototype_ `virtual void SetTargetLandscape(ALandscape* InOwningLandscape);` — `UFUNCTION(BlueprintCallable, category = "Landmass")` — Adds the brush to the given landscape, removing it from any previous one. This differs from SetOwningLandscape in that SetOwningLandscape is called by the landscape itself from AddBrushToLayer to update the manager.
- L86 _public prototype_ `int32 Convert2DTo1D(const FIntPoint& Index2D, int32 XSize);`
- L89 _public prototype_ `void PopulateNodeTree();` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L92 _public prototype_ `TArray<ALandmassActor*> GetActorsWithinModifiedNodes(TArray<int32>& InModifiedNodes);` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L95 _public prototype_ `void UpdateChildDataCounts();` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L98 _public prototype_ `void ConsolidateNodes(TArray<int32>& NodesToConsolidate);` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L101 _public prototype_ `TArray<int32> GetNodesWithinExtents(FVector4& InExtents);` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L104 _public prototype_ `TArray<int32> RemoveBrushFromTree(ALandmassActor* BrushToRemove);` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L107 _public prototype_ `TArray<ALandmassActor*> SortBrushes(TArray<ALandmassActor*> BrushArrayToMatch, TArray<ALandmassActor*> ActorsToSort);` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L110 _public prototype_ `void AddBrushToTree(ALandmassActor* BrushToAdd, FVector4 InExtents, bool InMapToWholeLandscape, FVector4& ModifiedExtents, TArray<ALandmassActor*>& InvalidatedBrushes, TArray<int32>& ModifiedNodes);` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L113 _public prototype_ `void AddBrushToArray(ALandmassActor* BrushToAdd);` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L116 _public prototype_ `void RequestUpdateFromBrush(ALandmassActor* BrushRequestingUpdate);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (ForceAsFunction), Category = Default)`
- L119 _public prototype_ `void DrawBrushMaterial(ALandmassActor* Brush, UMaterialInterface* BrushMaterial);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, meta = (ForceAsFunction, DefaultToSelf = "Brush"), Category = Default)`
- L122 _public prototype_ `void LaunchLandmassEditor(ALandmassActor* BrushRequestingEditor);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (ForceAsFunction), Category = Default)`
- L125 _public prototype_ `void TogglePreviewMode(bool bEnablePreviewMode);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, meta = (ForceAsFunction), Category = Default)`
- L129 _public prototype_ `void SetCaptureBoundaryNormals(bool bInCaptureBoundaryNormals);` — `UE_DEPRECATED(5.6, "This no longer has an effect")` — `UFUNCTION(BlueprintCallable, Category = Default)`
- L131 _public prototype_ `void MoveBrushUp(ALandmassActor* BrushToMove);`
- L132 _public prototype_ `void MoveBrushDown(ALandmassActor* BrushToMove);`
- L133 _public prototype_ `void MoveBrushToTop(ALandmassActor* BrushToMove);`
- L134 _public prototype_ `void MoveBrushToBottom(ALandmassActor* BrushToMove);`
- L137 _public prototype_ `ALandscape* GetLandscape();` — `UFUNCTION(BlueprintCallable, category = "Landmass")`
- L140 _public prototype_ `void ActorSelectionChanged(bool bSelected);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "Selection")`
- L144 _public prototype_ `virtual void SetOwningLandscape(class ALandscape* InOwningLandscape) override;` — ALandscapeBlueprintBrushBase
- L145 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L149 _private member_ `bool bWasSelected = false;`
- L151 _private member_ `FDelegateHandle OnActorSelectionChangedHandle;`
- L154 _private prototype_ `void HandleActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);` — Called when the editor selection has changed.
- L162 _private member_ `TObjectPtr<ALandscape> DetailPanelLandscape;` — `UPROPERTY(EditAnywhere, Category = Landscape, Transient, meta = (DisplayName = "Landscape"))` — The owning landscape.

#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LandmassManager, Display, All);`
