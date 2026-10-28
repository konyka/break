# Plugins / VPUtilities

- module root: `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities`
- headers: 19; symbols: 170
- symbol kinds: class=16, delegate=1, enum=3, enumerator=9, function=4, member=47, prototype=88, struct=1, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, Blutility, ConcertClient, EditorFramework, LevelEditor, Projects, RHI, RenderCore, Renderer, Slate, SlateCore, UMGEditor, UnrealEd, VPBookmarkEditor, VPRoles, VREditor, ViewportInteraction, ViewportWidgetOverlay
- PublicDependencyModuleNames: AssetRegistry, CineCameraSceneCapture, CinematicCamera, Core, CoreUObject, Engine, GameplayTags, TimeManagement, UMG, VPBookmark, VPSettings

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Private/VPUtilitiesModule.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVPUtilities, Log, Log);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVPUtilities, Log, Log);`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Actors/VPBookmarkActor.h` (Public)


#### class `AVPBookmarkActor`  
`class AVPBookmarkActor : public AVPViewportTickableActorBase, public IVPInteraction, public IVPBookmarkProvider`  
_L22-156_
- reflection: `UCLASS(HideCategories=(Rendering, Lighting, HLOD, Mobile, Navigation, RayTracing, TextureStreaming), CollapseCategories)`
- inherits: `AVPViewportTickableActorBase,IVPInteraction,IVPBookmarkProvider`
- L28 _public prototype_ `AVPBookmarkActor(const FObjectInitializer& ObjectInitializer);`
- L32 _public member_ `TObjectPtr<UStaticMeshComponent> BookmarkMeshComponent;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")` — Mesh Representation in the world
- L36 _public member_ `TObjectPtr<UTextRenderComponent> NameTextRenderComponent;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")` — Textrender to display bookmark name
- L40 _public member_ `TObjectPtr<USplineMeshComponent> SplineMeshComponent;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")` — Splinemesh
- L44 _public member_ `TObjectPtr<UCineCameraComponent> CameraComponent;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")` — CineCamera
- L48 _public member_ `TObjectPtr<UCineCaptureComponent2D> SceneCaptureComponent;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Components")` — CineCaptureComponent
- L52 _public member_ `FLinearColor BookmarkColor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bookmark", meta = (MultiLine = "true", ExposeOnSpawn = "true"))` — Color of Bookmark in MU Session
- L56 _public member_ `int32 FavoriteLevel = 0;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bookmark")` — Favorite status set by a user
- L60 _public member_ `bool bIsFlagged = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bookmark")` — Whether this was flagged by a user
- L64 _public member_ `FDateTime Timestamp;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookmark")` — DateTime to store creation time
- L68 _public member_ `TObjectPtr<UVPBookmark> BookmarkObject;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Bookmark", meta = (MultiLine = "true"))` — Reference to Editor Bookmark UObject
- L72 _public member_ `bool IsHome;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Bookmark", meta = (MultiLine = "true"))` — Bool to determine if this bookmark should be designated the home location
- L76 _public member_ `TObjectPtr<UTexture2D> SnapshotTexture;` — `UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Snapshot")` — Texture reference to store render of viewpoint
- L80 _public prototype_ `void UpdateBookmarkColor(FLinearColor Color);` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Default")` — Update the mesh color and BookmarkColor variable. Intended for use with multiuser initialization
- L83 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;` — `UPROPERTY(BlueprintReadWrite, Category = "Default")`
- L86 _public member_ `TObjectPtr<UMaterialInterface> BookmarkMaterial;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")`
- L90 _public prototype_ `void CaptureSnapshot();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Snapshot")` — Update SnapshotTexture captured via SceneCaptureComponent
- L94 _public prototype_ `void UpdateTimestamp();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Bookmark")` — Update Timestamp property with current time
- L99 _public prototype_ `void OnBookmarkActivation_Implementation(UVPBookmark* Bookmark, bool bActivate);` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Bookmarks")`
- L102 _public prototype_ `void OnBookmarkChanged_Implementation(UVPBookmark* Bookmark);` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Bookmarks")`
- L105 _public prototype_ `void UpdateBookmarkSplineMeshIndicator_Implementation();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Bookmarks")`
- L108 _public prototype_ `void HideBookmarkSplineMeshIndicator_Implementation();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Bookmarks")`
- L111 _public prototype_ `void GenerateBookmarkName_Implementation();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Bookmarks")`
- L117 _public prototype_ `void OnActorDroppedFromCarry_Implementation();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Interaction")`
- L120 _public prototype_ `void OnActorSelectedForTransform_Implementation();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Interaction")`
- L123 _public prototype_ `void OnActorDroppedFromTransform_Implementation();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Interaction")`
- L127 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L129 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L132 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L137 _private member_ `FRotator BookmarkRotation;` — Actor's rotation
- L140 _private member_ `TObjectPtr<UStaticMesh> BookmarkStaticMesh;` — `UPROPERTY()` — Mesh to use main static mesh component
- L143 _private member_ `TObjectPtr<UMaterial> TextMaterial;` — `UPROPERTY()`
- L146 _private member_ `TObjectPtr<UStaticMesh> SplineStaticMesh;` — `UPROPERTY()`
- L149 _private member_ `TObjectPtr<UMaterialInterface> SplineMaterial;` — `UPROPERTY()`
- L152 _private member_ `TObjectPtr<UMaterialInterface> SplineMaterialInstance;` — `UPROPERTY()`
- L155 _private member_ `TObjectPtr<UMaterialInterface> LabelMaterialInstance;` — `UPROPERTY()`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Actors/VPFullScreenUserWidgetActor.h` (Public)


#### class `AFullScreenUserWidgetActor`  
`class AFullScreenUserWidgetActor : public AInfo`  
_L16-55_
- reflection: `UCLASS(Blueprintable, ClassGroup = "UserInterface", HideCategories = (Actor, Input, Movement, Collision, Rendering, Transformation, LOD), ShowCategories = ("Input|MouseInput", "Input|TouchInput"))`
- inherits: `AInfo`
- desc: Widgets are first rendered to a render target, then that render target is displayed in the world.
- L21 _public prototype_ `AFullScreenUserWidgetActor(const FObjectInitializer& ObjectInitializer);`
- L24 _public prototype_ `virtual void PostInitializeComponents() override;`
- L25 _public prototype_ `virtual void PostLoad() override;`
- L26 _public prototype_ `virtual void PostActorCreated() override;`
- L27 _public prototype_ `virtual void Destroyed() override;`
- L29 _public prototype_ `virtual void BeginPlay() override;`
- L30 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L31 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L34 _public function_ `virtual bool ShouldTickIfViewportsOnly() const override`
- L40 _public prototype_ `UUserWidget* GetUserWidget() const;` — `UFUNCTION(BlueprintCallable, Category = "User Interface")` — Get a pointer to the inner user widget
- L43 _private prototype_ `void RequestEditorDisplay();`
- L44 _private prototype_ `void RequestGameDisplay();`
- L49 _protected member_ `TObjectPtr<UViewportWidgetOverlay> ScreenUserWidget;` — `UPROPERTY(VisibleAnywhere, Instanced, NoClear, Category = "User Interface", meta = (ShowOnlyInnerProperties))`
- L53 _protected member_ `bool bEditorDisplayRequested;` — Display requested and will be executed on the first frame because we can't call BP function in the loading phase

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Actors/VPPassthroughPostProcessVolume.h` (Public)


#### class `AVPPassthroughPostProcessVolume`  
`class AVPPassthroughPostProcessVolume : public APostProcessVolume`  
_L14-72_
- reflection: `UCLASS(MinimalAPI, DisplayName="VP Passthrough Post Process Volume")`
- inherits: `APostProcessVolume`
- desc: AVPPassthroughPostProcessVolume is derived from APostProcessVolume. Its function is to provide a Post Process Volume offers a clean passthrough of colors into display space, with no additional post-processing. This is done by customizing some of the default values.
- L19 _public function_ `AVPPassthroughPostProcessVolume()`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Actors/VPRootActor.h` (Public)


#### class `AVPRootActor`  
`class AVPRootActor : public AActor`  
_L23-81_
- reflection: `UCLASS(meta = (DisplayName = "VP Root Actor"), hidecategories=(Actor, Collision, Input, HLOD, Replication))`
- inherits: `AActor`
- desc: AVPRootActor
- L28 _public prototype_ `AVPRootActor(const FObjectInitializer& ObjectInitializer);`
- L33 _public member_ `TObjectPtr<UMeshComponent> RealWorldSceneRepresentation;` — `UPROPERTY(EditDefaultsOnly, Category = "Virtual Production")` — Actor used to show the size of the scene.
- L37 _public member_ `TObjectPtr<ACineCameraActor> CinematicCamera;` — `UPROPERTY(EditAnywhere, Category = "Virtual Production")` — Actor used to show the size of the scene.
- L41 _private member_ `bool bAreComponentsVisible;` — `UPROPERTY()`
- L47 _protected member_ `TObjectPtr<UBillboardComponent> SpriteComponent;` — `UPROPERTY()` — Billboard used to see the scene in the editor
- L51 _protected member_ `TObjectPtr<UArrowComponent> ArrowComponent;` — `UPROPERTY()` — Arrow used to see the orientation of the scene in the editor
- L55 _public member_ `bool bMoveLevelWithActor;` — `UPROPERTY(EditAnywhere, Category = "Virtual Production")`
- L57 _public member_ `bool bReentrantPostEditMove;`
- L63 _public prototype_ `ACineCameraActor* GetCineCameraActor() const;` — `UFUNCTION(BlueprintNativeEvent, Category = "Virtual Production")` — Get the current camera used by the virtual production.
- L65 _public prototype_ `virtual void BeginPlay() override;`
- L69 _public prototype_ `void ToggleComponentsVisibility();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Virtual Production")`
- L72 _public prototype_ `void MoveLevelToRootActor();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category = "Virtual Production")`
- L74 _public prototype_ `virtual void CheckForErrors() override;`
- L75 _public prototype_ `virtual void PostEditMove(bool bFinished) override;`
- L76 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L80 _private prototype_ `void SetComponentsVisibility(bool bVisible);`

#### class `UVPWorldAssetUserData`  
`class UVPWorldAssetUserData : public UAssetUserData`  
_L88-95_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetUserData`
- desc: UVPWorldAssetUserData
- L94 _public member_ `TLazyObjectPtr<AVPRootActor> LastSelectedRootActor;` — `UPROPERTY(EditAnywhere, Category = "Virtual Production")`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Actors/VPViewportTickableActorBase.h` (Public)


#### enum `EVPViewportTickableFlags`  
`enum class EVPViewportTickableFlags : uint8`  
_L12-18_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L14 _public enumerator_ `Editor = 1 << 0`
- L15 _public enumerator_ `Game = 1 << 1`
- L16 _public enumerator_ `EditorPreview = 1 << 2`
- L17 _public enumerator_ `GamePreview = 1 << 3`

#### class `AVPViewportTickableActorBase`  
`class AVPViewportTickableActorBase : public AActor`  
_L25-55_
- reflection: `UCLASS(Abstract)`
- inherits: `AActor`
- desc: Actor that tick in the Editor viewport with the event EditorTick.
- L30 _public prototype_ `AVPViewportTickableActorBase(const FObjectInitializer& ObjectInitializer);`
- L33 _public prototype_ `void EditorTick(float DeltaSeconds);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "Tick")`
- L36 _public prototype_ `void EditorDestroyed();` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "Utilities")`
- L40 _public prototype_ `void EditorLockLocation(bool bSetLockLocation);` — `UFUNCTION(CallInEditor, BlueprintCallable, Category = "Editor")` — Sets the LockLocation variable to disable movement from the translation gizmo
- L49 _public member_ `EVPViewportTickableFlags ViewportTickType;` — `UPROPERTY(EditDefaultsOnly, Category = "Actor Tick", meta = (Bitmask, BitmaskEnum = "/Script/VPUtilities.EVPViewportTickableType"))` — Where the actor should be ticked. Editor = Tick in the editor viewport. Use the event EditorTick. Game = Tick in game even if we are only ticking the viewport. Use the event Tick. Preview = Tick if the actor is present in any editing tool like Blueprint or Material graph. Use EditorTick.
- L52 _public prototype_ `virtual bool ShouldTickIfViewportsOnly() const override;` — If true, actor is ticked even if TickType==LEVELTICK_ViewportsOnly
- L53 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L54 _public prototype_ `virtual void Destroyed() override;`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/IVPContextMenuProvider.h` (Public)


#### class `UVPContextMenuProvider`  
`class UVPContextMenuProvider : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(BlueprintType)`
- inherits: `UInterface`

#### class `IVPContextMenuProvider`  
`class IVPContextMenuProvider : public IInterface`  
_L19-27_
- inherits: `IInterface`
- L26 _public prototype_ `void OnCreateContextMenu();` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/IVPInteraction.h` (Public)


#### class `UVPInteraction`  
`class UVPInteraction : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(BlueprintType)`
- inherits: `UInterface`

#### class `IVPInteraction`  
`class IVPInteraction : public IInterface`  
_L19-40_
- inherits: `IInterface`
- L29 _public prototype_ `void OnActorDroppedFromCarry();` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "VirtualScouting|Interaction", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Called when actor is dropped from Carry state by the VREd interactor
- L34 _public prototype_ `void OnActorSelectedForTransform();` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "VirtualScouting|Interaction", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Called when an actor is selected by the VREd interactor
- L39 _public prototype_ `void OnActorDroppedFromTransform();` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, BlueprintCallable, Category = "VirtualScouting|Interaction", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))` — Called when dropped by VRTool

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Libraries/VPBlueprintLibrary.h` (Public)


#### class `UVPBlueprintLibrary`  
`class UVPBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L21-120_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Functionality added to prototype the VR scouting tools
- L29 _public prototype_ `static void Refresh3DEditorViewport();` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Refresh the desktop 3D viewport so that it updates changes even when not set to 'Realtime'
- L33 _public prototype_ `static AVPViewportTickableActorBase* SpawnVPTickableActor(UObject* ContextObject, const TSubclassOf<AVPViewportTickableActorBase> ActorClass, const FVector Location, const FRotator Rotation);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Spawn a virtual production tickable actor
- L37 _public prototype_ `static AActor* SpawnBookmarkAtCurrentLevelEditorPosition(const TSubclassOf<AActor> ActorClass, const FVPBookmarkCreationContext CreationContext, const FVector Offset, const bool bFlattenRotation = true);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Spawn a virtual production bookmark
- L41 _public prototype_ `static bool JumpToBookmarkInLevelEditor(const UVPBookmark* Bookmark);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Jump to a virtual production bookmark
- L45 _public prototype_ `static FGameplayTagContainer GetVirtualProductionRole();` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — The machine role(s) in a virtual production context.
- L49 _public prototype_ `static FTransform GetEditorViewportTransform();` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Get the location of the 2D viewport camera
- L54 _public prototype_ `static FTransform GetEditorVRHeadTransform();` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta = (DeprecatedFunction, DeprecationMessage = "VR Editor mode is deprecated; use the XR Creative Framework plugin instead."))` — Get the location of the VR HMD
- L59 _public prototype_ `static FTransform GetEditorVRRoomTransform();` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta = (DeprecatedFunction, DeprecationMessage = "VR Editor mode is deprecated; use the XR Creative Framework plugin instead."))` — Get the VR room transform (the playable area shown as a wireframe cage on Vive and Rift
- L64 _public prototype_ `static void SetGrabSpeed(const float Speed);` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta = (DeprecatedFunction, DeprecationMessage = "VR Editor mode is deprecated; use the XR Creative Framework plugin instead."))` — Set the VR grab speed cvar
- L69 _public prototype_ `static bool IsVREditorModeActive();` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta = (DeprecatedFunction, DeprecationMessage = "VR Editor mode is deprecated; use the XR Creative Framework plugin instead."))` — Get whether the user is in editor VR mode
- L74 _public prototype_ `static FVector GetVREditorLaserHoverLocation();` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta = (DeprecatedFunction, DeprecationMessage = "VR Editor mode is deprecated; use the XR Creative Framework plugin instead."))` — Get the hitlocation of the interaction controller's laser pointer, in world space
- L79 _public prototype_ `static FVector GetLeftInteractorLocation();` — `UE_DEPRECATED(5.7, "VR Editor mode is deprecated; use the XR Creative Framework plugin instead.")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta = (DeprecatedFunction, DeprecationMessage = "VR Editor mode is deprecated; use the XR Creative Framework plugin instead."))` — Get the location of the left interactor, in world space
- L83 _public prototype_ `static bool EditorUndo();` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Trigger an UnrealEd Undo
- L87 _public prototype_ `static bool EditorRedo();` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Trigger an UnrealEd Redo
- L92 _public prototype_ `static bool EditorDuplicate();` — `UE_DEPRECATED(5.7, "Use UEditorActorSubsystem::DuplicateSelectedActors instead.")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta = (DeprecatedFunction, DeprecationMessage = "Use UEditorActorSubsystem::DuplicateSelectedActors instead."))` — Trigger an UnrealEd Duplicate
- L97 _public prototype_ `static bool EditorDeleteSelectedObjects();` — `UE_DEPRECATED(5.7, "Use UEditorActorSubsystem::DeleteSelectedActors instead.")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta = (DeprecatedFunction, DeprecationMessage = "Use UEditorActorSubsystem::DeleteSelectedActors instead."))` — Trigger an UnrealEd Delete
- L104 _public prototype_ `static UWorld* GetEditorWorld();` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production")` — Wrapper around UUnrealEditorSubsystem::GetEditorWorld. Used because you can't get the subsystem without being an editor utility actor.
- L107 _public prototype_ `static void VPBookmarkSplineMeshIndicatorSetStartAndEnd(USplineMeshComponent* SplineMesh);` — `UFUNCTION(BlueprintCallable, Category = "VPBookmarks")`
- L110 _public prototype_ `static void VPBookmarkSplineMeshIndicatorDisable(USplineMeshComponent* SplineMesh);` — `UFUNCTION(BlueprintCallable, Category = "VPBookmarks")`
- L114 _public prototype_ `static void SortActorsByName(UPARAM(Ref) TArray<AActor*>& Actors, bool Ascending = true);` — `UFUNCTION(BlueprintCallable, Category = "VPBookmarks")` — Sort actors by actor label
- L118 _public prototype_ `static void SortVPBookmarkActorsByTimestamp(UPARAM(Ref) TArray<AVPBookmarkActor*>& Actors, bool Ascending = true);` — `UFUNCTION(BlueprintCallable, Category = "VPBookmarks")` — Sort VPBookmarkActors by Timestamp parameter

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Libraries/VPCameraBlueprintLibrary.h` (Public)


#### enum `EVPCameraRigSpawnLinearApproximationMode`  
`enum class UE_DEPRECATED(5.5,"Code will be removed from UE5.7") EVPCameraRigSpawnLinearApproximationMode : uint8`  
_L14-19_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `None UMETA(Display = "No Approximation")` — We won't do linear approximation, instead using the Spline as constructed initially.
- L17 _public enumerator_ `Density` — LinearApproximationParam will be used as a density value
- L18 _public enumerator_ `IntegrationStep` — LinearApproximationParam will be used as the Integration step in Unreal Units.

#### struct `FVPCameraRigSpawnParams`  
`struct UE_DEPRECATED(5.5,"Code will be removed from UE5.7") FVPCameraRigSpawnParams`  
_L24-65_
- reflection: `USTRUCT(BlueprintType)`
- desc: Parameters used to custom the CameraRig that's created.
- L28 _public prototype_ `FVPCameraRigSpawnParams();`
- L34 _public member_ `bool bUseWorldSpace;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(Transient, BlueprintReadWrite, Category="Camera Rig", meta=(DeprecatedProperty, DeprecationMessage="This property deprecated"))` — Use world space (as opposed to local space) for points.
- L42 _public member_ `bool bUseFirstPointAsSpawnLocation;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(Transient, BlueprintReadWrite, Category = "Camera Rig", meta=(DeprecatedProperty, DeprecationMessage="This property deprecated"))` — Use the first vector of input as the spawn transform. Causes RigTransform to be completely ignored.
- L50 _public member_ `EVPCameraRigSpawnLinearApproximationMode LinearApproximationMode;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(Transient, BlueprintReadWrite, Category = "Camera Rig", meta=(DeprecatedProperty, DeprecationMessage="This property deprecated"))` — Causes a linear approximation of the spline points to be generated instead of relying purely on the passed in points / curves.
- L64 _public member_ `float LinearApproximationParam;` — `UE_DEPRECATED(5.5,"This property will be removed from UE5.7")` — `UPROPERTY(Transient, BlueprintReadWrite, Category = "Camera Rig", meta=(DeprecatedProperty, DeprecationMessage="This property deprecated"))` — This is only used if LinearApproximationMode is not None. When mode is Density: See FSplinePositionLinearApproximation::Build. When mode is IntegrationStep: Integration step (in CM) between approximation points. Decreasing this value will increase the number of spline points and will therefore increase the accuracy (at the cost of increased complexity).

#### class `UVPCameraBlueprintLibrary`  
`class UE_DEPRECATED(5.5,"Code will be removed from UE5.7") UVPCameraBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L68-92_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L75 _public prototype_ `static ACameraRig_Rail* SpawnDollyTrackFromPoints(UObject* WorldContextObject, UPARAM(ref) const TArray<FTransform>& Points, ESplinePointType::Type InterpType = ESplinePointType::Linear);` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L79 _public prototype_ `static ACameraRig_Rail* SpawnDollyTrackFromPointsSmooth(UObject* WorldContextObject, UPARAM(ref) const TArray<FTransform>& Points, ESplinePointType::Type InterpType = ESplinePointType::Linear);` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L83 _public prototype_ `static ACameraRig_Rail* SpawnCameraRigFromActors(UObject* WorldContextObject, const FTransform& RigTransform, const TArray<AActor*>& Actors, const FVPCameraRigSpawnParams& Params);` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L87 _public prototype_ `static ACameraRig_Rail* SpawnCameraRigFromPoints(UObject* WorldContextObject, const FTransform& RigTransform, const TArray<FVector>& Points, const FVPCameraRigSpawnParams& Params);` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`
- L91 _public prototype_ `static ACameraRig_Rail* SpawnCameraRigFromSelectedActors(UObject* WorldContextObject, const FTransform& RigTransform, const FVPCameraRigSpawnParams& Params);` — `UE_DEPRECATED(5.5,"Code will be removed from UE5.7")` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production", meta=(DeprecatedFunction, DeprecationMessage="This function will be removed from UE5.7"))`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Libraries/VPRenderingBlueprintLibrary.h` (Public)


#### class `UVPRenderingBlueprintLibrary`  
`class UVPRenderingBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L14-37_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library supporting Virtual Production rendering use cases.
- L29 _public prototype_ `static void GenerateSceneViewExtensionIsActiveFunctorForViewportType( FSceneViewExtensionIsActiveFunctor& OutIsActiveFunction, bool bPIE = false, bool bSIE = false, bool bEditorActive = false, bool bGamePrimary = false );` — `UFUNCTION(BlueprintPure, Category = "Virtual Production|Rendering")` — Returns a functor to activate a scene view extension when the FViewport in the SceneViewExtensionContext is selectively: - PIE - SIE - Editor's active - Game's primary If it is none of the above, it emits no opinion about activating the Scene View Extension.

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/VPBookmarkSettings.h` (Public)


#### class `UVPBookmarkSettings`  
`class UVPBookmarkSettings : public UObject`  
_L9-33_
- reflection: `UCLASS(Config = VirtualProductionUtilities)`
- inherits: `UObject`
- L16 _public member_ `FSoftObjectPath BookmarkMeshPath;` — `UPROPERTY(config, EditAnywhere, Category = "VP Bookmark", meta = (AllowedClasses = "/Script/Engine.StaticMesh", DisplayName = "Bookmark Mesh"))` — Bookmark mesh to use for Bookmark actor
- L20 _public member_ `FSoftObjectPath BookmarkMaterialPath;` — `UPROPERTY(config, EditAnywhere, Category = "VP Bookmark", meta = (AllowedClasses = "/Script/Engine.MaterialInterface", DisplayName = "Bookmark Mesh Material"))` — Bookmark mesh material to use for Bookmark actor
- L24 _public member_ `FSoftObjectPath BookmarkSplineMeshPath;` — `UPROPERTY(config, EditAnywhere, Category = "VP Bookmark", meta = (AllowedClasses = "/Script/Engine.StaticMesh", DisplayName = "Bookmark Spline Mesh"))` — Bookmark spline mesh to use for Bookmark actor
- L28 _public member_ `FSoftObjectPath BookmarkSplineMeshMaterialPath;` — `UPROPERTY(config, EditAnywhere, Category = "VP Bookmark", meta = (AllowedClasses = "/Script/Engine.MaterialInterface", DisplayName = "Bookmark Spline Material"))` — Bookmark spline mesh material to use for Bookmark actor
- L32 _public member_ `FSoftObjectPath BookmarkLabelMaterialPath;` — `UPROPERTY(config, EditAnywhere, Category = "VP Bookmark", meta = (AllowedClasses = "/Script/Engine.MaterialInterface", DisplayName = "Bookmark Label Material"))` — Bookmark label material class to use for Bookmark actor

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/VPGameMode.h` (Public)


#### class `AVPGameMode`  
`class AVPGameMode : public AGameMode`  
_L19-33_
- reflection: `UCLASS(abstract)`
- inherits: `AGameMode`
- L25 _private member_ `TObjectPtr<AVPRootActor> RootActor;` — `UPROPERTY(transient, BlueprintGetter = "GetRootActor", Category = "Virtual Production")`
- L29 _public function_ `AVPRootActor* GetRootActor() const` — `UFUNCTION(BlueprintGetter, Category = "Virtual Production")`
- L32 _public prototype_ `virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/VPTimecodeCustomTimeStep.h` (Public)


#### Free symbols / members of external scopes

- L12 _typedef_ `using UVPTimecodeCustomTimeStep UE_DEPRECATED(5.8, "UVPTimecodeCustomTimeStep has`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Widgets/Fullscreen/VPFullScreenUserWidget_PostProcess.h` (Public)
_(no declarations extracted)_

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Widgets/Fullscreen/VPFullScreenUserWidget_PostProcessBase.h` (Public)
_(no declarations extracted)_

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Widgets/Fullscreen/VPFullScreenUserWidget_PostProcessWithSVE.h` (Public)
_(no declarations extracted)_

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Widgets/VPAssetThumbnailWrapperWidget.h` (Public)


#### enum `EAssetThumbnailDisplayMode`  
`enum class EAssetThumbnailDisplayMode : uint8`  
_L13-17_
- reflection: `UENUM()`
- L15 _public enumerator_ `EditorThumbnail`
- L16 _public enumerator_ `FallbackImage`

#### class `UVPAssetThumbnailWrapperWidget`  
`class UVPAssetThumbnailWrapperWidget : public UWidget`  
_L25-93_
- reflection: `UCLASS(DisplayName = "Asset Thumbnail Widget (Editor & Game)")`
- inherits: `UWidget`
- desc: Version of UAssetThumbnailWidget that compiles in packaged games. In editor builds, a thumbnail widget is displayed. In packaged builds, a fallback SImage is displayed.
- L32 _public prototype_ `void SetEditorThumbnailResolution(const FIntPoint& NewResolution);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the resolution of the editor thumbnail
- L34 _public prototype_ `FIntPoint GetEditorThumbnailResolution() const;` — `UFUNCTION(BlueprintPure, Category = "Appearance")`
- L41 _public prototype_ `UObject* GetEditorAssetWidget() const;` — `UFUNCTION(BlueprintPure, Category = "Appearance")` — Gets the widget used for displaying in editor. Returns nullptr in non-editor builds. This type must be cast to UAssetThumbnailWidget manually (due to Unreal Header Tool restrictions).
- L45 _public prototype_ `void SetAsset(const FAssetData& AssetData);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the asset to display. Has no effect in non-editor builds.
- L48 _public prototype_ `void SetAssetByObject(UObject* Object);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the asset to display. Has no effect in non-editor builds.
- L52 _public prototype_ `void SetFallbackBrush(const FSlateBrush& NewFallbackBrush);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the fallback image to display.
- L54 _public function_ `FSlateBrush GetFallbackBrush() const` — `UFUNCTION(BlueprintGetter, Category = "Appearance")`
- L58 _public prototype_ `void SetDisplayMode(EAssetThumbnailDisplayMode Mode = EAssetThumbnailDisplayMode::FallbackImage);` — `UFUNCTION(BlueprintCallable, Category = "Appearance")` — Sets the display mode. Only has an effect in editor builds because packaged games always display in FallbackImage mode.
- L61 _public prototype_ `virtual void SynchronizeProperties() override;`
- L62 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L63 _public prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L65 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L73 _private member_ `FSlateBrush FallbackBrush;` — `UPROPERTY(EditAnywhere, BlueprintGetter = GetFallbackBrush, BlueprintSetter = SetFallbackBrush, Category = "Appearance")` — Fallback brush to draw
- L78 _private member_ `TObjectPtr<UObject> AssetWidget;` — `UPROPERTY(Instanced)` — The content for the editor version. Is an instance of UAssetThumbnailWidget but for non-editor builds UHT does not find the type so UObject here.
- L82 _private member_ `EAssetThumbnailDisplayMode DisplayMode = EAssetThumbnailDisplayMode::EditorThumbnail;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetDisplayMode, AdvancedDisplay, Category = "Appearance")` — How the widget is supposed to be displayed.
- L86 _private member_ `TSharedPtr<SImage> Fallback;` — The fallback image
- L89 _private member_ `TSharedPtr<SWidgetSwitcher> Content;` — Holds the contents: either ThumbnailRenderer or a fallback SImage.
- L92 _private prototype_ `void UpdateNativeAssetThumbnailWidget();` — Updates or creates ThumbnailRenderer and sets the contents of DisplayedWidget.

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPUtilities/Public/Widgets/VPFullScreenUserWidget.h` (Public)
_(no declarations extracted)_
