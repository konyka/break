# Plugins / Avalanche

- module root: `Plugins/VirtualProduction/Avalanche/Source/Avalanche`
- headers: 42; symbols: 650
- symbol kinds: class=28, delegate=1, enum=9, enumerator=37, function=84, macro=4, member=147, namespace=11, prototype=288, struct=24, typedef=5, variable=12
- PrivateDependencyModuleNames: ActorModifierCore, ApplicationCore, AvalancheCamera, AvalancheOutliner, AvalancheRemoteControl, CinematicCamera, CoreUObject, DynamicMaterial, DynamicMaterialEditor, DynamicMesh, GeometryCore, GeometryFramework, GeometryScriptingCore, HeadMountedDisplay, InputCore, MediaCompositing, MovieScene, Niagara, NiagaraCore, ProceduralMeshComponent, Projects, RHI, RawMesh, RemoteControlComponents, RenderCore, Slate, SlateCore, StateTreeModule, StaticMeshDescription, Text3D, TypedElementFramework, UMG, UnrealEd
- PublicDependencyModuleNames: AvalancheAttribute, AvalancheCore, AvalancheRemoteControl, AvalancheSceneTree, AvalancheSequence, AvalancheTag, AvalancheTransition, CinematicCamera, Core, Engine, GeometryCore, GeometryFramework, GeometryScriptingCore, Niagara, RawMesh, RemoteControl, RemoteControlLogic, Text3D
- PublicIncludePathModuleNames: AvalancheEditor, AvalancheOutliner

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Internal/Framework/AvaSplineActor.h` (Internal)


#### class `AAvaSplineActor`  
`class AAvaSplineActor : public AActor`  
_L14-24_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Motion Design Spline Actor")`
- inherits: `AActor`
- desc: Motion Design Spline Actor
- L19 _public prototype_ `AAvaSplineActor();`
- L23 _protected member_ `TObjectPtr<USplineComponent> SplineComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Design")`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Private/AvaModule.h` (Private)


#### class `FAvaModule`  
`class FAvaModule : public IAvaModule`  
_L9-48_
- inherits: `IAvaModule`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `virtual bool SetRuntimeStatProcessingEnabled(bool bEnabled) override;`
- L19 _public prototype_ `virtual bool IsRuntimeStatEnabled(const FString& InName) const override;`
- L20 _public prototype_ `virtual int32 SetRuntimeStatEnabled(const TCHAR* InName, const bool bInEnabled) override;`
- L21 _public function_ `virtual bool ShouldShowRuntimeStats() const override`
- L22 _public prototype_ `virtual TArray<FString> GetEnabledRuntimeStats() const override;`
- L23 _public prototype_ `virtual void OverwriteEnabledRuntimeStats(const TArray<FString>& InEnabledStats) override;`
- L32 _private member_ `TSet<FString> EnabledStats;` — Stats for all Motion Design runtime viewports is centralized here. The state (enabled) of the stats will persist across the lifetime of all game instances so that an enabled stat remains even if playback is stopped.
- L35 _private member_ `bool bRuntimeStatStatProcessingEnabled = false;` — Track if the module will respond to FCoreDelegates::StatCheckEnabled event.
- L38 _private prototype_ `void HandleViewportStatCheckEnabled(const TCHAR* InName, bool& bOutCurrentEnabled, bool& bOutOthersEnabled);` — Delegate handler to see if a stat is enabled
- L41 _private prototype_ `void HandleViewportStatEnabled(const TCHAR* InName);` — Delegate handler for when stats are enabled
- L44 _private prototype_ `void HandleViewportStatDisabled(const TCHAR* InName);` — Delegate handler for when stats are disabled
- L47 _private prototype_ `void HandleViewportStatDisableAll(const bool bInAnyViewport);` — Delegate handler for when all stats are disabled

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Private/Framework/Ticker/AvaTickerSceneProxy.h` (Private)


#### class `UE::Avalanche::FTickerSceneProxy`  
`class FTickerSceneProxy final : public FPrimitiveSceneProxy`  
_L15-66_
- inherits: `FPrimitiveSceneProxy`
- desc: Represents a UAvaTickerComponent to the scene manager.
- L18 _public prototype_ `explicit FTickerSceneProxy(UAvaTickerComponent* InComponent);`
- L23 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L24 _public prototype_ `virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& InViews, const FSceneViewFamily& InViewFamily, uint32 InVisibilityMap, FMeshElementCollector& InCollector) const override;`
- L25 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* InView) const override;`
- L26 _public prototype_ `virtual uint32 GetMemoryFootprint() const override;`
- L27 _public prototype_ `uint32 GetAllocatedSize() const;`
- L31 _private prototype_ `void BuildArrowMesh();`
- L33 _private prototype_ `void BuildEndPlaneMesh();`
- L36 _private prototype_ `void DrawArrowElement(FMeshElementCollector& InCollector, int32 InViewIndex, const FMatrix& InLocalToWorld, FMaterialRenderProxy* InMaterialRenderProxy) const;` — Gets the dynamic mesh element for the start arrow
- L39 _private prototype_ `void DrawEndPlaneElement(FMeshElementCollector& InCollector, int32 InViewIndex, const FMatrix& InLocalToWorld, FMaterialRenderProxy* InMaterialRenderProxy) const;` — Gets the dynamic mesh element for the ending plane
- L41 _private member_ `FStaticMeshVertexBuffers ArrowVertexBuffers;`
- L42 _private member_ `FDynamicMeshIndexBuffer32 ArrowIndexBuffer;`
- L43 _private member_ `FLocalVertexFactory ArrowVertexFactory;`
- L45 _private member_ `FStaticMeshVertexBuffers EndPlaneVertexBuffers;`
- L46 _private member_ `FDynamicMeshIndexBuffer32 EndPlaneIndexBuffer;`
- L47 _private member_ `FLocalVertexFactory EndPlaneVertexFactory;`
- L50 _private member_ `FVector StartLocation;` — The start location (in local space) where active elements start at
- L53 _private member_ `FVector Velocity;` — The velocity (in local space) to move the active elements at
- L56 _private member_ `double DestroyDistance;` — The distance the last part of the active element must cross before it gets destroyed
- L59 _private member_ `FColor DrawColor;` — Draw color for the arrow
- L62 _private member_ `FMatrix LocalArrowMatrix;` — Transformation of StartLocation and Velocity in Local Space
- L65 _private member_ `FMatrix LocalEndPlaneMatrix;` — Transformation of End Location and Inverse Velocity in Local Space

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Avalanche` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Private/Transition/AvaTransitionAttributeLibrary.h` (Private)


#### class `UAvaTransitionAttributeLibrary`  
`class UAvaTransitionAttributeLibrary : public UBlueprintFunctionLibrary`  
_L14-36_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L20 _public prototype_ `static bool AddTagAttribute(UObject* InTransitionNode, const FAvaTagHandle& InTagHandle);` — `UFUNCTION(BlueprintCallable, Category="Scene Attributes", meta=(DefaultToSelf="InTransitionNode"))`
- L23 _public prototype_ `static bool RemoveTagAttribute(UObject* InTransitionNode, const FAvaTagHandle& InTagHandle);` — `UFUNCTION(BlueprintCallable, Category="Scene Attributes", meta=(DefaultToSelf="InTransitionNode"))`
- L26 _public prototype_ `static bool ContainsTagAttribute(UObject* InTransitionNode, const FAvaTagHandle& InTagHandle);` — `UFUNCTION(BlueprintCallable, Category="Scene Attributes", meta=(DefaultToSelf="InTransitionNode"))`
- L29 _public prototype_ `static bool AddNameAttribute(UObject* InTransitionNode, FName InName);` — `UFUNCTION(BlueprintCallable, Category="Scene Attributes", meta=(DefaultToSelf="InTransitionNode"))`
- L32 _public prototype_ `static bool RemoveNameAttribute(UObject* InTransitionNode, FName InName);` — `UFUNCTION(BlueprintCallable, Category="Scene Attributes", meta=(DefaultToSelf="InTransitionNode"))`
- L35 _public prototype_ `static bool ContainsNameAttribute(UObject* InTransitionNode, FName InName);` — `UFUNCTION(BlueprintCallable, Category="Scene Attributes", meta=(DefaultToSelf="InTransitionNode"))`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Private/Transition/AvaTransitionRCLibrary.h` (Private)


#### class `UAvaTransitionRCLibrary`  
`class UAvaTransitionRCLibrary : public UBlueprintFunctionLibrary`  
_L17-29_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L22 _public prototype_ `static bool CompareRCControllerValues(const FAvaTransitionContext& InTransitionContext, const FAvaRCControllerId& InControllerId, EAvaTransitionComparisonResult InValueComparisonType);`
- L25 _public prototype_ `static bool CompareRCControllerValues(UObject* InTransitionNode, const FAvaRCControllerId& InControllerId, EAvaTransitionComparisonResult InValueComparisonType = EAvaTransitionComparisonResult::Different);` — `UFUNCTION(BlueprintPure, DisplayName="Compare RC Controller Values", Category="Transition Logic|Remote Control", meta=(DefaultToSelf="InTransitionNode"))`
- L28 _public prototype_ `static TArray<URCVirtualPropertyBase*> GetChangedRCControllers(UObject* InTransitionNode);` — `UFUNCTION(BlueprintCallable, DisplayName="Get Changed RC Controllers", Category="Transition Logic|Remote Control", meta=(DefaultToSelf="InTransitionNode"))`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/AvaActorUtils.h` (Public)


#### struct `FAvaActorUtils`  
`struct FAvaActorUtils`  
_L15-24_
- L17 _public prototype_ `static FOrientedBox MakeOrientedBox(const FBox& InLocalBox, const FTransform& InWorldTransform);`
- L19 _public prototype_ `static FBox GetActorLocalBoundingBox(const AActor* InActor, bool bIncludeFromChildActors = false, bool bMustBeRegistered = true);`
- L21 _public prototype_ `static FBox GetComponentLocalBoundingBox(const USceneComponent* InComponent);`
- L23 _public prototype_ `static IAvaSceneInterface* GetSceneInterfaceFromActor(const AActor* InActor);`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/AvaAssetTags.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Ava` (scope `UE`)
- L7 _namespace_ `namespace AssetTags` (scope `UE::Ava`)
- L9 _variable_ `constexpr const TCHAR* MotionDesignScene = TEXT("Mot` (scope `UE::Ava::AssetTags`)
- L11 _namespace_ `namespace Values` (scope `UE::Ava::AssetTags`)
- L13 _variable_ `constexpr const TCHAR* Enabled = TEXT("Ena` (scope `UE::Ava::AssetTags::Values`)

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/AvaAttributeContainer.h` (Public)


#### class `UAvaAttributeContainer`  
`class UAvaAttributeContainer : public UObject`  
_L19-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Object providing attribute information of the Scene
- L24 _public prototype_ `void Initialize(UAvaSceneSettings* InSceneSettings);`
- L26 _public prototype_ `bool AddTagAttribute(const FAvaTagHandle& InTagHandle);`
- L27 _public prototype_ `bool RemoveTagAttribute(const FAvaTagHandle& InTagHandle);`
- L28 _public prototype_ `bool ContainsTagAttribute(const FAvaTagHandle& InTagHandle) const;`
- L30 _public prototype_ `bool AddNameAttribute(FName InName);`
- L31 _public prototype_ `bool RemoveNameAttribute(FName InName);`
- L32 _public prototype_ `bool ContainsNameAttribute(FName InName) const;`
- L37 _private member_ `TArray<TObjectPtr<UAvaAttribute>> SceneAttributes;` — `UPROPERTY(Transient)` — In-play Scene Attributes. Can be added to / removed from while in-play

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AVALANCHE_API`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/AvaDefs.h` (Public)


#### enum `EAvaAnchors`  
`enum class EAvaAnchors : uint8`  
_L29-42_
- reflection: `UENUM(BlueprintType)`
- desc: UType 2D space point map. None should not be selectable in the UI. Z: Top, Bottom, VMiddle & Y: Left, Right, HMiddle Expressed as ZY eg TopLeft
- L31 _public enumerator_ `None = UE::Ava::AnchorPoints::None UMETA(Hidden)`
- L32 _public enumerator_ `TopLeft = UE::Ava::AnchorPoints::Top + UE::Ava::AnchorPoints::Left`
- L33 _public enumerator_ `Top = UE::Ava::AnchorPoints::Top + UE::Ava::AnchorPoints::HMiddle`
- L34 _public enumerator_ `TopRight = UE::Ava::AnchorPoints::Top + UE::Ava::AnchorPoints::Right`
- L35 _public enumerator_ `Left = UE::Ava::AnchorPoints::VMiddle + UE::Ava::AnchorPoints::Left`
- L36 _public enumerator_ `Center = UE::Ava::AnchorPoints::VMiddle + UE::Ava::AnchorPoints::HMiddle`
- L37 _public enumerator_ `Right = UE::Ava::AnchorPoints::VMiddle + UE::Ava::AnchorPoints::Right`
- L38 _public enumerator_ `BottomLeft = UE::Ava::AnchorPoints::Bottom + UE::Ava::AnchorPoints::Left`
- L39 _public enumerator_ `Bottom = UE::Ava::AnchorPoints::Bottom + UE::Ava::AnchorPoints::HMiddle`
- L40 _public enumerator_ `BottomRight = UE::Ava::AnchorPoints::Bottom + UE::Ava::AnchorPoints::Right`
- L41 _public enumerator_ `Custom = UE::Ava::AnchorPoints::Custom`

#### enum `EAvaVerticalAlignment`  
`enum class EAvaVerticalAlignment : uint8`  
_L45-50_
- reflection: `UENUM(BlueprintType)`
- L47 _public enumerator_ `Top`
- L48 _public enumerator_ `Center`
- L49 _public enumerator_ `Bottom`

#### enum `EAvaHorizontalAlignment`  
`enum class EAvaHorizontalAlignment : uint8`  
_L53-58_
- reflection: `UENUM(BlueprintType)`
- L55 _public enumerator_ `Left`
- L56 _public enumerator_ `Center`
- L57 _public enumerator_ `Right`

#### enum `EAvaDepthAlignment`  
`enum class EAvaDepthAlignment : uint8`  
_L61-66_
- reflection: `UENUM(BlueprintType)`
- L63 _public enumerator_ `Front`
- L64 _public enumerator_ `Center`
- L65 _public enumerator_ `Back`

#### enum `EAvaColorStyle`  
`enum class EAvaColorStyle : uint8`  
_L165-170_
- reflection: `UENUM(BlueprintType)`
- L167 _public enumerator_ `None`
- L168 _public enumerator_ `Solid`
- L169 _public enumerator_ `LinearGradient`

#### struct `FAvaColorChangeData`  
`struct FAvaColorChangeData`  
_L173-212_
- reflection: `USTRUCT(BlueprintType)`
- L178 _public member_ `EAvaColorStyle ColorStyle;` — `UPROPERTY(Category = "Motion Design", EditAnywhere, BlueprintReadWrite)`
- L181 _public member_ `FLinearColor PrimaryColor;` — `UPROPERTY(Category = "Motion Design", EditAnywhere, BlueprintReadWrite)`
- L184 _public member_ `FLinearColor SecondaryColor;` — `UPROPERTY(Category = "Motion Design", EditAnywhere, BlueprintReadWrite)`
- L187 _public member_ `bool bIsUnlit;` — `UPROPERTY(Category = "Motion Design", EditAnywhere, BlueprintReadWrite)`
- L189 _public function_ `FAvaColorChangeData() : ColorStyle(EAvaColorStyle::None), PrimaryColor(FLinearColor::White), SecondaryColor(FLinearColor::White), bIsUnlit(true)`
- L194 _public function_ `FAvaColorChangeData(EAvaColorStyle InColorStyle, const FLinearColor& InPrimaryColor, const FLinearColor& InSecondaryColor, bool bInIsUnlit) : ColorStyle(InColorStyle), PrimaryColor(InPrimaryColor), SecondaryColor(InSecondaryColor), bIsUnlit(bInIsUnlit)`
- L199 _public function_ `bool operator==(const FAvaColorChangeData& InOtherColorData) const`
- L208 _public function_ `bool operator!=(const FAvaColorChangeData& InOtherColorData) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Ava` (scope `UE`)
- L11 _namespace_ `namespace AnchorPoints` (scope `UE::Ava`)
- L13 _variable_ `constexpr int32 None = 0;` (scope `UE::Ava::AnchorPoints`)
- L14 _variable_ `constexpr int32 Left = 1 << 0;` (scope `UE::Ava::AnchorPoints`) — Y- = 1
- L15 _variable_ `constexpr int32 HMiddle = 1 << 1;` (scope `UE::Ava::AnchorPoints`) — Y/2 = 2
- L16 _variable_ `constexpr int32 Right = 1 << 2;` (scope `UE::Ava::AnchorPoints`) — Y+ = 4
- L17 _variable_ `constexpr int32 Top = 1 << 3;` (scope `UE::Ava::AnchorPoints`) — Z+ = 8
- L18 _variable_ `constexpr int32 VMiddle = 1 << 4;` (scope `UE::Ava::AnchorPoints`) — Z/2 = 16
- L19 _variable_ `constexpr int32 Bottom = 1 << 5;` (scope `UE::Ava::AnchorPoints`) — Z- = 32
- L20 _variable_ `constexpr int32 Horizontal = Left | HMiddle | Right;` (scope `UE::Ava::AnchorPoints`) — Y- to Y+ = 7
- L21 _variable_ `constexpr int32 Vertical = Top | VMiddle | Bottom;` (scope `UE::Ava::AnchorPoints`) — Z+ to Z- = 56
- L22 _variable_ `constexpr int32 Custom = 1 << 6;` (scope `UE::Ava::AnchorPoints`) — Custom = 64
- L69 _function_ `template<typename Enum> constexpr auto ToUnderlyingType(Enum Val)`
- L74 _typedef_ `using AvaAlignment = int32;` — xyz
- L78 _function_ `template<typename AvaAlignment> constexpr EAvaDepthAlignment GetDAlignment(AvaAlignment InAlignment)` — alignment for X (Depth)
- L85 _function_ `template<typename AvaAlignment> constexpr EAvaHorizontalAlignment GetHAlignment(AvaAlignment InAlignment)` — alignment for Y (Horizontal)
- L92 _function_ `template<typename AvaAlignment> constexpr EAvaVerticalAlignment GetVAlignment(AvaAlignment InAlignment)` — alignment for Z (Vertical)
- L99 _function_ `template<typename AvaAlignment> constexpr FVector GetLocationFromAlignment(AvaAlignment InAlignment, FVector Size3D)` — gets an anchor location from an alignment and a size
- L159 _function_ `constexpr AvaAlignment MakeAlignment(EAvaDepthAlignment Depth, EAvaHorizontalAlignment Horizontal, EAvaVerticalAlignment Vertical)` — create alignment value from enums

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/AvaLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAva, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/AvaOutlinerUtils.h` (Public)


#### struct `FAvaOutlinerUtils`  
`struct FAvaOutlinerUtils`  
_L16-29_
- desc: Editor Only Outliner Access Functions
- L19 _public prototype_ `static TSharedPtr<IAvaOutliner> EditorGetOutliner(const UWorld* const InWorld);` — Returns the Motion Design outliner from the outliner module at runtime in the editor.
- L22 _public prototype_ `static TArray<AActor*> EditorOutlinerChildActors(TSharedPtr<IAvaOutliner> InOutliner, AActor* const InParentActor = nullptr);` — Returns an array of direct child actors attached to a parent actor or all root level actors if the parent actor is null.
- L28 _public prototype_ `static bool EditorOutlinerItemsToActors(const TArray<FAvaOutlinerItemPtr>& InItems, TArray<AActor*>& OutActors);` — Gets an array of actors from an array of outliner items while maintaining index ordering (for actor outliner items only). Returns false and an empty OutActors if any outliner items are invalid or any actor objects they represent are invalid.

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/AvaScene.h` (Public)


#### class `AAvaScene`  
`class AAvaScene : public AActor, public IAvaSequenceProvider, public IAvaSceneInterface, public IAvaRemoteControlInterface`  
_L27-199_
- reflection: `UCLASS(MinimalAPI, NotPlaceable, Hidden, NotBlueprintable, NotBlueprintType, DisplayName = "Motion Design Scene")`
- inherits: `AActor,IAvaSequenceProvider,IAvaSceneInterface,IAvaRemoteControlInterface`
- L39 _public prototype_ `static void NotifySceneEvent(ESceneAction InAction);`
- L42 _public prototype_ `static AAvaScene* GetScene(ULevel* InLevel, bool bInCreateSceneIfNotFound);`
- L44 _public prototype_ `AAvaScene();`
- L46 _public prototype_ `IAvaSequencePlaybackObject* GetScenePlayback() const;`
- L49 _public function_ `bool ShouldAutoStartMode() const`
- L54 _public prototype_ `void SetAutoStartMode(bool bInAutoStartMode);`
- L56 _public function_ `TArray<uint8>& GetOutlinerData()`
- L58 _public prototype_ `void OnWorldRenamed(UWorld* InWorld);`
- L60 _public prototype_ `void OnGetWorldTags(FAssetRegistryTagsContext Context) const;`
- L64 _public prototype_ `virtual ULevel* GetSceneLevel() const override;`
- L65 _public function_ `virtual UAvaSceneSettings* GetSceneSettings() const override`
- L66 _public function_ `virtual UAvaAttributeContainer* GetAttributeContainer() const override`
- L67 _public function_ `virtual FAvaSceneTree& GetSceneTree() override`
- L68 _public function_ `virtual const FAvaSceneTree& GetSceneTree() const override`
- L69 _public prototype_ `virtual IAvaSequencePlaybackObject* GetPlaybackObject() const override;`
- L70 _public function_ `virtual IAvaSequenceProvider* GetSequenceProvider() override`
- L71 _public function_ `virtual const IAvaSequenceProvider* GetSequenceProvider() const override`
- L72 _public prototype_ `virtual URemoteControlPreset* GetOrCreateRemoteControlPreset(bool bInCallModify=true) override;`
- L73 _public prototype_ `virtual URemoteControlPreset* GetRemoteControlPreset() const override;`
- L74 _public prototype_ `virtual void DestroyRemoteControlPreset(bool bInCallModify=true) override;`
- L75 _public prototype_ `virtual bool IsRemoteControlPresetExpectedToBePresent() const override;`
- L77 _public function_ `virtual FNavigationToolSaveState& GetNavigationToolSaveState() override`
- L82 _public prototype_ `virtual UObject* ToUObject() override;`
- L83 _public prototype_ `virtual UWorld* GetContextWorld() const override;`
- L84 _public prototype_ `virtual bool CreateDirectorInstance(UAvaSequence& InSequence, IMovieScenePlayer& InPlayer, const FMovieSceneSequenceID& InSequenceID, UObject*& OutDirectorInstance) override;`
- L85 _public prototype_ `virtual bool AddSequence(UAvaSequence* InSequence) override;`
- L86 _public prototype_ `virtual uint32 AddSequences(TConstArrayView<UAvaSequence*> InSequences) override;`
- L87 _public prototype_ `virtual void RemoveSequence(UAvaSequence* InSequence) override;`
- L88 _public prototype_ `virtual void SetDefaultSequence(UAvaSequence* InSequence) override;`
- L89 _public prototype_ `virtual UAvaSequence* GetDefaultSequence() const override;`
- L90 _public function_ `virtual const TArray<TObjectPtr<UAvaSequence>>& GetSequences() const override`
- L91 _public function_ `virtual const TArray<TWeakObjectPtr<UAvaSequence>>& GetRootSequences() const override`
- L92 _public function_ `virtual TArray<TWeakObjectPtr<UAvaSequence>>& GetRootSequencesMutable() override`
- L93 _public prototype_ `virtual FName GetSequenceProviderDebugName() const override;`
- L95 _public function_ `virtual TSharedPtr<ISequencer> GetEditorSequencer() const override`
- L96 _public prototype_ `virtual void OnEditorSequencerCreated(const TSharedPtr<ISequencer>& InSequencer) override;`
- L97 _public function_ `virtual bool GetDirectorBlueprint(UAvaSequence& InSequence, UBlueprint*& OutBlueprint) override`
- L99 _public function_ `virtual FSimpleMulticastDelegate& GetOnSequenceTreeRebuilt() override`
- L100 _public prototype_ `virtual void ScheduleRebuildSequenceTree() override;`
- L101 _public prototype_ `virtual void RebuildSequenceTree() override;`
- L105 _public prototype_ `virtual void OnValuesApplied_Implementation() override;`
- L109 _public prototype_ `virtual void PostActorCreated() override;`
- L110 _public prototype_ `virtual void PreInitializeComponents() override;`
- L111 _public prototype_ `virtual void BeginPlay() override;`
- L112 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;`
- L114 _public function_ `virtual bool IsSelectable() const override`
- L115 _public function_ `virtual bool SupportsExternalPackaging() const override`
- L120 _public prototype_ `virtual void PostLoad() override;`
- L121 _public prototype_ `virtual void PostInitializeComponents() override;`
- L122 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type InDuplicateMode) override;`
- L123 _public prototype_ `virtual void PostEditImport() override;`
- L125 _public prototype_ `virtual void PostEditUndo() override;`
- L127 _public prototype_ `virtual void BeginDestroy() override;`
- L130 _public prototype_ `void RegisterObjects();`
- L131 _public prototype_ `void UnregisterObjects();`
- L135 _protected member_ `FAvaSceneTree SceneTree;` — `UPROPERTY()`
- L138 _protected member_ `TObjectPtr<UAvaSceneSettings> SceneSettings;` — `UPROPERTY()`
- L141 _protected member_ `TObjectPtr<UAvaAttributeContainer> AttributeContainer;` — `UPROPERTY()`
- L145 _protected member_ `TObjectPtr<UAvaAttributeContainer> SceneState;` — `UE_DEPRECATED(5.7, "This property is deprecated. Please use AttributeContainer")`
- L149 _protected member_ `TObjectPtr<URemoteControlPreset> RemoteControlPreset;` — `UPROPERTY(Instanced)`
- L153 _protected member_ `TArray<TObjectPtr<UAvaSequence>> Animations;` — `UPROPERTY()` — A List of All Animations, including those that are nested in other Animations
- L157 _protected member_ `TScriptInterface<IAvaSequencePlaybackObject> PlaybackObject;` — `UPROPERTY()` — The Base Playback Scene that is always present to Play Animations
- L161 _protected member_ `TArray<TWeakObjectPtr<UAvaSequence>> RootAnimations;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — A list of only the Root Animations (those without Parent Animations)
- L166 _protected member_ `TArray<uint8> OutlinerData;` — `UPROPERTY()` — Todo: Outliner Editor Object to store the data like filters, options, etc
- L170 _protected member_ `TWeakPtr<ISequencer> EditorSequencer;`
- L172 _protected member_ `FDelegateHandle PreWorldRenameDelegate;`
- L174 _protected member_ `FDelegateHandle WorldTagGetterDelegate;`
- L177 _protected member_ `FSimpleMulticastDelegate OnTreeAnimationRebuilt;`
- L181 _protected member_ `int32 DefaultSequenceIndex = 0;` — `UPROPERTY()` — The index to the animation to use as the default animation
- L183 _protected member_ `bool bPendingAnimTreeUpdate = false;`
- L187 _protected member_ `bool bRemoteControlPresetPresent = true;` — `UPROPERTY()` — Determines whether the remote control preset should be present in this scene
- L192 _protected member_ `bool bAutoStartMode = true;` — `UPROPERTY()` — Whether the motion design mode should auto start
- L196 _protected member_ `FNavigationToolSaveState NavigationToolState;` — `UPROPERTY()` — Saved Sequence Navigator state to restore

#### enum `AAvaScene::ESceneAction`  
`enum class ESceneAction : uint8`  
_L33-38_
- L35 _public enumerator_ `Created`
- L36 _public enumerator_ `Activated`
- L37 _public enumerator_ `Deactivated`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/AvaSceneSettings.h` (Public)


#### class `UAvaSceneSettings`  
`class UAvaSceneSettings : public UObject`  
_L14-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Object containing information about its Scene
- L19 _public function_ `static FName GetSceneAttributesPropertyName()`
- L24 _public function_ `static FName GetSceneRigPropertyName()`
- L29 _public function_ `TConstArrayView<TObjectPtr<UAvaAttribute>> GetSceneAttributes() const`
- L34 _public function_ `FSoftObjectPath GetSceneRig() const`
- L39 _public function_ `void SetSceneRig(const FSoftObjectPath& InSceneRig)`
- L46 _private member_ `TArray<TObjectPtr<UAvaAttribute>> SceneAttributes;` — `UPROPERTY(EditAnywhere, Instanced, Category="Scene Attributes")`
- L49 _private member_ `FSoftObjectPath SceneRig;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/AvaSceneState.h` (Public)


#### Free symbols / members of external scopes

- L12 _typedef_ `typedef UAvaAttributeContainer UAvaSceneState;` — `UE_DEPRECATED(5.7, "UAvaSceneState has been renamed to UAvaAttributeContainer. Use UAvaAttributeContainer instead.")`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/AvaSceneSubsystem.h` (Public)


#### class `UAvaSceneSubsystem`  
`class UAvaSceneSubsystem : public UTickableWorldSubsystem`  
_L18-70_
- reflection: `UCLASS(MinimalAPI, BlueprintType, DisplayName = "Motion Design Scene Subsystem")`
- inherits: `UTickableWorldSubsystem`
- L23 _public prototype_ `void RegisterSceneInterface(ULevel* InLevel, IAvaSceneInterface* InSceneInterface);`
- L25 _public prototype_ `FTSTicker& GetTicker();`
- L28 _public prototype_ `IAvaSceneInterface* GetSceneInterface() const;` — Gets the Scene Interface for the World's Persistent Level
- L31 _public prototype_ `IAvaSceneInterface* GetSceneInterface(const ULevel* InLevel) const;` — Gets the Scene Interface for the provided Level
- L34 _public prototype_ `static IAvaSceneInterface* FindSceneInterface(const ULevel* InLevel);` — Returns the first interface found in the given Level, if any
- L38 _public prototype_ `bool IsReadyToPlay(const UObject* InContextObject) const;` — `UFUNCTION(BlueprintPure, Category="Motion Design", meta=(DefaultToSelf="InContextObject"))` — Determines whether the motion design is ready for play
- L42 _public prototype_ `void FlushBuilds();` — `UFUNCTION(BlueprintCallable, Category="Motion Design", meta=(DefaultToSelf="InContextObject"))` — Completes all pending work from Motion Design build systems (e.g. Text3D)
- L51 _public prototype_ `static TArray<AActor*> GatherSceneTreeActors(const UObject* InContextObject, const AActor* InParentActor=nullptr, bool bInIncludeDescendants=true);` — `UFUNCTION(BlueprintCallable, Category="Motion Design", meta=(DefaultToSelf="InContextObject"))` — Gathers actors in order of their appearance in the tree @param InContextObject the context object to get the level from @param InParentActor if specified, only the children (and optionally including descendants) of this actor will be considered. If not specified, all the actors in the context level will be used. @param bInIncludeDescendants if specified, descendants of the given parent actor will also be considered.
- L55 _protected prototype_ `virtual void PostInitialize() override;`
- L56 _protected prototype_ `virtual bool DoesSupportWorldType(const EWorldType::Type InWorldType) const override;`
- L60 _protected prototype_ `virtual bool IsTickableInEditor() const override;`
- L61 _protected prototype_ `virtual void Tick(float InDeltaTime) override;`
- L62 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L67 _private member_ `FTSTicker Ticker;` — Ticker for motion design elements
- L69 _private member_ `TMap<TWeakObjectPtr<ULevel>, TWeakInterfacePtr<IAvaSceneInterface>> SceneInterfaces;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API AVALANCHE_API`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Framework/AvaGameInstance.h` (Public)


#### struct `FAvaInstancePlaySettings`  
`struct FAvaInstancePlaySettings`  
_L18-25_
- L20 _public member_ `const FAvaInstanceSettings& Settings;`
- L21 _public member_ `FName ChannelName;`
- L22 _public member_ `UTextureRenderTarget2D* RenderTarget;`
- L23 _public member_ `FIntPoint ViewportSize;`
- L24 _public member_ `const FAvaViewportQualitySettings& QualitySettings;`

#### class `UAvaGameInstance`  
`class UAvaGameInstance : public UGameInstance, public FTickableGameObject`  
_L28-173_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Motion Design Game Instance")`
- inherits: `UGameInstance,FTickableGameObject`
- L33 _public prototype_ `UAvaGameInstance();`
- L39 _public prototype_ `static UAvaGameInstance* Create(UObject* InOuter);` — Creates a new Motion Design Game instance from the given Motion Design Template Asset. Supported asset types: UWorld (Level).
- L42 _public prototype_ `UE_INTERNAL bool CreateWorld();` — Create the game world
- L44 _public function_ `bool IsWorldCreated() const`
- L46 _public function_ `UWorld* GetPlayWorld() const`
- L48 _public prototype_ `bool BeginPlayWorld(const FAvaInstancePlaySettings& InWorldPlaySettings);`
- L56 _public prototype_ `void RequestEndPlayWorld(bool bForceImmediate);` — The end play is normally requested to be done on the next Tick(). This is to avoid having the world destroyed while within the Tick() of that world. However, when shutting down, we need to force the end play to be done immediately because there will not a be a next Tick().
- L58 _public prototype_ `void RequestUnloadWorld(bool bForceImmediate);`
- L60 _public function_ `bool IsWorldPlaying() const`
- L65 _public prototype_ `void CancelWorldRequests();` — Cancel any pending EndPlayWorld or UnloadWorld requests.
- L71 _public prototype_ `void UpdateSceneViewportSize(const FIntPoint& InViewportSize);` — The output channels can be resized during playback, if this happens, the scene viewport needs to be updated to reflect the change.
- L73 _public prototype_ `void UpdateRenderTarget(UTextureRenderTarget2D* InRenderTarget);`
- L75 _public prototype_ `UTextureRenderTarget2D* GetRenderTarget() const;`
- L80 _public function_ `bool IsRenderTargetReady() const` — Returns true if the render target has been rendered and is ready to be used for output.
- L85 _public function_ `void ResetRenderTargetReady()` — Reset the flag so the OnRenderTargetReady event can be called again on the next render.
- L91 _public function_ `TSharedPtr<FSceneViewport> GetSceneViewport() const` — @brief Get the currently playing scene viewport. @remark Only valid within a BeginPlay()/EndPlay() scope. Null otherwise.
- L97 _public function_ `UAvaGameViewportClient* GetAvaGameViewportClient() const` — @brief Get the currently playing game viewport client. @remark Only valid within a BeginPlay()/EndPlay() scope. Null otherwise.
- L99 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAvaGameInstanceEvent, UAvaGameInstance* , FName );`
- L102 _public function_ `static FOnAvaGameInstanceEvent& GetOnEndPlay()` — Event called on EndPlayWorld().
- L105 _public function_ `static FOnAvaGameInstanceEvent& GetOnRenderTargetReady()` — Event called when the render target becomes ready.
- L109 _protected prototype_ `void EditorTick(float InDeltaSeconds);`
- L112 _protected prototype_ `void TickInternal(float InDeltaSeconds);`
- L114 _protected prototype_ `void UnloadWorld(bool bInShutdown);`
- L115 _protected prototype_ `void EndPlayWorld();`
- L116 _protected prototype_ `void OnEndFrameTick();`
- L117 _protected prototype_ `void OnEnginePreExit();`
- L120 _protected prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L121 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L125 _protected prototype_ `virtual bool IsTickableInEditor() const override;`
- L126 _protected prototype_ `virtual UWorld* GetTickableGameObjectWorld() const override;`
- L130 _protected prototype_ `virtual ULocalPlayer* CreateInitialPlayer(FString& OutError) override;`
- L134 _protected prototype_ `virtual void BeginDestroy() override;`
- L138 _protected member_ `TObjectPtr<UWorld> PlayWorld;` — `UPROPERTY(Transient)`
- L141 _protected member_ `TObjectPtr<ULocalPlayer> LocalPlayer;` — `UPROPERTY(Transient)`
- L144 _protected member_ `TObjectPtr<UAvaGameViewportClient> ViewportClient;` — `UPROPERTY(Transient)`
- L146 _protected member_ `TSharedPtr<FSceneViewport> Viewport;`
- L149 _protected member_ `FName PlayingChannelName;` — Channel this game instance is playing on.
- L151 _protected member_ `bool bWorldCreated = false;`
- L152 _protected member_ `bool bRequestUnloadWorld = false;`
- L153 _protected member_ `bool bWorldPlaying = false;`
- L154 _protected member_ `bool bRequestEndPlayWorld = false;`
- L155 _protected member_ `bool bIsRenderTargetReady = false;`
- L158 _protected member_ `TUniquePtr<FRenderCommandFence> RenderTargetFence;` — Render command fence to ensure the render target has been rendered.
- L162 _protected member_ `TPimplPtr<class FAvaGameInstanceEditorTicker> WorldTickerEditor;` — Ticker implementation for the game instance to tick the world in editor engine
- L166 _protected member_ `uint64 TickedFrame = 0;` — Last frame that was ticked
- L169 _protected member_ `FDelegateHandle EnginePreExitHandle;` — Handle to delegate for EnginePreExit event.
- L171 _protected member_ `static FOnAvaGameInstanceEvent OnEndPlay;`
- L172 _protected member_ `static FOnAvaGameInstanceEvent OnRenderTargetReady;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AVALANCHE_API`
- L99 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAvaGameInstanceEvent, UAvaGameInstance* , FName );`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Framework/AvaGameViewportClient.h` (Public)


#### class `UAvaGameViewportClient`  
`class UAvaGameViewportClient : public UGameViewportClient`  
_L15-35_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Motion Design Game Viewport Client")`
- inherits: `UGameViewportClient`
- L21 _public prototype_ `virtual void Draw(FViewport* InViewport,FCanvas* InCanvas) override;`
- L22 _public prototype_ `virtual bool IsStatEnabled(const FString& InName) const override;`
- L25 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& InCollector);`
- L27 _public prototype_ `void SetRenderTarget(UTextureRenderTarget2D* InRenderTarget);`
- L29 _public function_ `UTextureRenderTarget2D* GetRenderTarget() const`
- L32 _private member_ `TArray<FSceneViewStateReference> ViewStates;`
- L34 _private member_ `TWeakObjectPtr<UTextureRenderTarget2D> RenderTarget;`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Framework/AvaGizmoComponent.h` (Public)


#### struct `FAvaGizmoComponentPrimitiveValues`  
`struct FAvaGizmoComponentPrimitiveValues`  
_L11-81_
- reflection: `USTRUCT()`
- desc: Stores original per-primitive visibility properties. Used for restoration when component removed.
- L17 _public member_ `bool bCastShadow = true;` — `UPROPERTY()` — Controls whether the primitive component should cast a shadow or not.
- L21 _public member_ `bool bIsVisible = true;` — `UPROPERTY()` — Whether to completely draw the primitive; if false, the primitive is not drawn, does not cast a shadow.
- L25 _public member_ `bool bIsHiddenInGame = false;` — `UPROPERTY()` — Whether to hide the primitive in game, if the primitive is Visible.
- L29 _public member_ `bool bVisibleInReflectionCaptures = true;` — `UPROPERTY()` — If true, this component will be visible in reflection captures.
- L33 _public member_ `bool bVisibleInRealTimeSkyCaptures = true;` — `UPROPERTY()` — If true, this component will be visible in real-time sky light reflection captures.
- L37 _public member_ `bool bVisibleInRayTracing = true;` — `UPROPERTY()` — If true, this component will be visible in ray tracing effects. Turning this off will remove it from ray traced reflections, shadows, etc.
- L41 _public member_ `bool bVisibleInReflections = true;` — `UPROPERTY()` — If true, this component will be visible in ray traced reflections. Screen space traces will ignore this flag, as they directly sample SceneColor.
- L45 _public member_ `bool bAffectDistanceFieldLighting = true;` — `UPROPERTY()` — Controls whether the primitive should affect dynamic distance field lighting methods.  This flag is only used if CastShadow is true.
- L49 _public member_ `bool bAffectDynamicIndirectLighting = true;` — `UPROPERTY()` — Controls whether the primitive should influence indirect lighting.
- L53 _public member_ `bool bAffectIndirectLightingWhileHidden = true;` — `UPROPERTY()` — Controls whether the primitive should affect indirect lighting when hidden. This flag is only used if bAffectDynamicIndirectLighting is true.
- L57 _public member_ `bool bDrawWireframe = false;` — `UPROPERTY()` — Currently only applies to dynamic meshes.
- L61 _public member_ `FLinearColor WireframeColor = FLinearColor(0.0, 0.5, 1.0, 1.0);` — `UPROPERTY()` — The color of the wireframe when drawn.
- L65 _public member_ `bool bRendersCustomDepth = false;` — `UPROPERTY()` — Whether to render to the custom depth buffer.
- L69 _public member_ `uint8 CustomStencilId = 0;` — `UPROPERTY()` — The custom stencil id, if applicable.
- L73 _public member_ `bool bRendersInMainPass = true;` — `UPROPERTY()` — Whether to render in the main pass.
- L77 _public member_ `bool bRendersDepth = true;` — `UPROPERTY()` — Whether to render to the depth buffer.
- L80 _public member_ `TArray<TObjectPtr<UMaterialInterface>> Materials;` — `UPROPERTY()`

#### class `UAvaGizmoComponent`  
`class UAvaGizmoComponent : public UActorComponent`  
_L85-258_
- reflection: `UCLASS(DisplayName = "Motion Design Gizmo Component", meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Add to an actor to indicate it's used as a Gizmo.
- L90 _public prototype_ `UAvaGizmoComponent();`
- L92 _public prototype_ `virtual void PostLoad() override;`
- L95 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L98 _public prototype_ `virtual void OnRegister() override;`
- L99 _public prototype_ `virtual void OnUnregister() override;`
- L101 _public prototype_ `virtual void OnComponentCreated() override;`
- L102 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L105 _public prototype_ `void ApplyGizmoValues();` — Applies the gizmo values to all primitive components in the parent actor.
- L108 _public prototype_ `void RestoreComponentValues();` — Applies the original (visibility etc) property values to the Actor. Use prior to component removal.
- L112 _public function_ `const bool IsGizmoEnabled() const` — Whether "gizmo mode" is enabled.
- L115 _public prototype_ `void SetGizmoEnabled(const bool bInIsEnabled);` — Sets whether "gizmo mode" is enabled.
- L118 _public prototype_ `bool AppliesToChildActors() const;` — Whether the settings apply to child actors or not.
- L121 _public prototype_ `void SetApplyToChildActors(bool bInValue);` — Sets whether the settings apply to child actors or not.
- L124 _public prototype_ `UMaterialInterface* GetMaterial() const;` — The (optional) material to use.
- L127 _public prototype_ `void SetMaterial(UMaterialInterface* InMaterial);` — Set the material to use.
- L130 _public prototype_ `void SetMaterialToDefault();` — Sets the material to engine default.
- L134 _public prototype_ `void SetMaterialToSeeThrough();` — `UE_DEPRECATED(5.8, "SetMaterialToSeeThrough deprecated. Unused.")` — Set the material to a see through one.
- L137 _public prototype_ `bool CastsShadow() const;` — Whether the primitive component should cast a shadow or not.
- L140 _public prototype_ `void SetCastShadow(bool bInValue);` — Controls whether the primitive component should cast a shadow or not.
- L143 _public prototype_ `bool IsVisibleInEditor() const;` — Whether to completely draw the primitive; if false, the primitive is not drawn, does not cast a shadow.
- L146 _public prototype_ `void SetVisibleInEditor(bool bInValue);` — Whether to completely draw the primitive; if false, the primitive is not drawn, does not cast a shadow.
- L149 _public prototype_ `bool IsHiddenInGame() const;` — Whether to hide the primitive in game, if the primitive is Visible.
- L152 _public prototype_ `void SetHiddenInGame(bool bInValue);` — Whether to hide the primitive in game, if the primitive is Visible.
- L155 _public prototype_ `bool RendersInMainPass() const;` — Whether to render in the main pass.
- L158 _public prototype_ `void SetRenderInMainPass(const bool bInValue);` — Sets whether to render in the main pass.
- L161 _public prototype_ `bool RendersDepth() const;` — Whether to render to the depth buffer.
- L164 _public prototype_ `void SetRenderDepth(const bool bInValue);` — Sets whether to render to the depth buffer.
- L167 _public prototype_ `bool ShowsWireframe() const;` — Whether to draw the mesh wireframe, currently only applicable to Dynamic Meshes.
- L170 _public prototype_ `void SetShowWireframe(bool bInValue);` — Whether to draw the mesh wireframe, currently only applicable to Dynamic Meshes.
- L173 _public prototype_ `void SetWireframeColor(const FLinearColor& InColor);` — The color of the wireframe when drawn.
- L176 _public prototype_ `bool SetsStencil() const;` — Whether to render to the custom depth/stencil buffer.
- L179 _public prototype_ `void SetsStencil(const bool bInSetStencil);` — Sets whether to render to the custom depth/stencil buffer.
- L182 _public prototype_ `const uint8 GetStencilId() const;` — The custom stencil id, if applicable.
- L185 _public prototype_ `void SetStencilId(const uint8 InStencilId);` — Sets the custom stencil id, if applicable.
- L189 _private prototype_ `void StoreComponentValues();` — Stores all primitive component values (that this overrides). Call before applying gizmo values.
- L191 _private prototype_ `void OnPostRegisterParentComponents(AActor* InActor);`
- L193 _private prototype_ `void ForEachPrimitiveComponent(TFunctionRef<void(UPrimitiveComponent*)> InFunc);`
- L196 _private prototype_ `void ApplyToEachPrimitiveComponent(TFunctionRef<void(UPrimitiveComponent*)> InFunc);` — Variation of ForEachPrimitiveComponent that checks various flags.
- L199 _protected member_ `FDelegateHandle PostRegisterComponentsHandle;`
- L203 _protected member_ `bool bIsGizmoEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsGizmoEnabled", Setter = "SetGizmoEnabled", Category = "Rendering", meta = (DisplayPriority = -99, AllowPrivateAccess = "true"))` — Whether "gizmo mode" is enabled.
- L207 _protected member_ `bool bAreGizmoValuesApplied = false;` — `UPROPERTY()` — Whether the gizmo values are actually applied.
- L211 _protected member_ `bool bApplyToChildActors = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "AppliesToChildActors", Setter = "SetApplyToChildActors", Category = "Rendering", AdvancedDisplay, meta = (AllowPrivateAccess = "true"))` — Whether the settings apply to child actors or not.
- L215 _protected member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — Material that overrides all others attached to the parent actor, if specified.
- L219 _protected member_ `bool bCastShadow = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "CastsShadow", Setter = "SetCastShadow", Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — Controls whether the primitive component should cast a shadow or not.
- L223 _protected member_ `bool bIsVisibleInEditor = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsVisibleInEditor", Setter = "SetVisibleInEditor", Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — Whether to completely draw the primitive; if false, the primitive is not drawn, does not cast a shadow.
- L227 _protected member_ `bool bIsHiddenInGame = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "IsHiddenInGame", Setter = "SetHiddenInGame", Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — Whether to hide the primitive in game, if the primitive is Visible.
- L231 _protected member_ `bool bRenderInMainPass = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "RendersInMainPass", Setter = "SetRenderInMainPass", Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — Whether to render in the main pass.
- L235 _protected member_ `bool bRenderDepth = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "RendersDepth", Setter = "SetRenderDepth", Category = "Rendering", meta = (AllowPrivateAccess = "true"))` — Whether to render to the depth buffer.
- L239 _protected member_ `bool bDrawWireframe = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "ShowsWireframe", Setter = "SetShowWireframe", Category = "Rendering", meta = (InlineEditConditionToggle, AllowPrivateAccess = "true"))` — Currently only applies to dynamic meshes.
- L243 _protected member_ `FLinearColor WireframeColor = FLinearColor(0.0, 0.5, 1.0, 1.0);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "Auto", Setter, Category = "Rendering", meta = (EditCondition = "bDrawWireframe", AllowPrivateAccess = "true"))` — The color of the wireframe when drawn.
- L247 _protected member_ `bool bSetStencil = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = "SetsStencil", Setter = "SetsStencil", Category = "Rendering", meta = (InlineEditConditionToggle, AllowPrivateAccess = "true"))` — Whether to render to the custom depth/stencil buffer.
- L251 _protected member_ `uint8 StencilId = 150;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter = "SetStencilId", Category = "Rendering", meta = (EditCondition = "bSetStencil", AllowPrivateAccess = "true"))` — The custom stencil id, if applicable.
- L255 _protected member_ `TMap<FSoftComponentReference, FAvaGizmoComponentPrimitiveValues> ComponentValues;` — `UPROPERTY()` — Original values to restore upon component removal.
- L257 _protected member_ `std::atomic<bool> bIsRestoringValues = false;`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Framework/AvaInstanceSettings.h` (Public)


#### struct `FAvaInstanceSettings`  
`struct FAvaInstanceSettings`  
_L11-25_
- reflection: `USTRUCT()`
- desc: Settings applied when instancing a Motion Design Asset for playback.
- L17 _public member_ `bool bEnableLoadSubPlayables = true;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — Enable loading dependent levels as sub-playables.
- L24 _public member_ `bool bDefaultPlayableTransitionWaitForSequences = false;` — `UPROPERTY(config, EditAnywhere, Category = Settings)` — For default playable transitions (when there is no transition tree), wait for the sequences to finish before ending the transition.

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Framework/AvaNullActor.h` (Public)


#### class `AAvaNullActor`  
`class AAvaNullActor : public AActor`  
_L15-33_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Null Actor")`
- inherits: `AActor`
- desc: Null Actor (Empty Group)
- L20 _public member_ `static const FString DefaultLabel;`
- L22 _public prototype_ `AAvaNullActor();`
- L26 _public prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L32 _protected member_ `TObjectPtr<UAvaNullComponent> NullComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Framework/AvaNullComponent.h` (Public)


#### class `UAvaNullComponent`  
`class UAvaNullComponent : public USceneComponent`  
_L9-15_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Null Component")`
- inherits: `USceneComponent`
- L14 _public prototype_ `UAvaNullComponent();`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Framework/AvaSoftAssetPtr.h` (Public)


#### enum `EMotionDesignAssetType`  
`enum class EMotionDesignAssetType`  
_L7-11_
- L9 _public enumerator_ `Unknown`
- L10 _public enumerator_ `World`

#### struct `FAvaSoftAssetPath`  
`struct FAvaSoftAssetPath`  
_L17-27_
- desc: Motion Design Extension to FSoftObjectPath. Adding the class information along to resolve about a Motion Design Asset without loading anything.
- L19 _public member_ `FSoftClassPath AssetClassPath;`
- L20 _public member_ `FSoftObjectPath AssetPath;`
- L22 _public function_ `bool IsNull() const`
- L23 _public function_ `const FSoftObjectPath& ToSoftObjectPath() const`
- L24 _public function_ `EMotionDesignAssetType GetAssetType(bool bInLoadIfUnknown = true) const`
- L26 _public prototype_ `static EMotionDesignAssetType GetAssetTypeFromClass(const FSoftClassPath& InAssetClassPath, bool bInLoadIfUnknown = true);`

#### struct `FAvaSoftAssetPtr`  
`struct FAvaSoftAssetPtr`  
_L34-58_
- L36 _public member_ `FSoftClassPath AssetClassPath;`
- L39 _public member_ `TSoftObjectPtr<UObject> AssetPtr;` — We need to use the template, it is the only way we can assign it from another SoftObjetPtr.
- L43 _public function_ `bool IsNull() const` — Warning: IsValid() for an AssetPtr will cause the asset to be loaded. Using IsNull() is the only option we have.
- L45 _public function_ `const FSoftObjectPath& ToSoftObjectPath() const`
- L52 _public prototype_ `EMotionDesignAssetType GetAssetType(bool bInLoadIfUnknown = true) const;` — @brief Determines the asset type from the given class path or by loading the object. @param bInLoadIfUnknown If the type can't be determined by the class path, the object is loaded to check it's type. @return One of the recognized asset types for Motion Design playables.
- L54 _public function_ `FORCEINLINE bool operator==(const FAvaSoftAssetPtr& Rhs) const`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Framework/Ticker/AvaTickerActor.h` (Public)


#### class `AAvaTickerActor`  
`class AAvaTickerActor : public AActor`  
_L11-32_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Ticker Actor")`
- inherits: `AActor`
- L16 _public prototype_ `AAvaTickerActor();`
- L18 _public function_ `UAvaTickerComponent* GetTickerComponent() const`
- L25 _public prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L31 _protected member_ `TObjectPtr<UAvaTickerComponent> TickerComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Ticker")`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Framework/Ticker/AvaTickerComponent.h` (Public)


#### enum `EAvaTickerQueueLimitType`  
`enum class EAvaTickerQueueLimitType : uint8`  
_L11-20_
- reflection: `UENUM()`
- L13 _public enumerator_ `None UMETA(Hidden)`
- L16 _public enumerator_ `DisableQueueing` — No new elements will be queued if queue is full
- L19 _public enumerator_ `DiscardOldest` — New elements will be queued by discarding the oldest (front of queue)

#### struct `FAvaTickerElement`  
`struct FAvaTickerElement`  
_L23-57_
- reflection: `USTRUCT()`
- L27 _public prototype_ `FAvaTickerElement() = default;`
- L29 _public prototype_ `explicit FAvaTickerElement(AActor* InActor);`
- L31 _public prototype_ `bool operator==(const FAvaTickerElement& InOther) const;`
- L34 _public prototype_ `bool IsValid() const;` — Whether the element is a valid element
- L37 _public prototype_ `void SetVisibility(bool bInVisible);` — Sets the game and editor visibility of the element
- L40 _public prototype_ `FVector GetElementLocation() const;` — Retrieves the world space location of the element
- L43 _public prototype_ `void SetLocation(const FVector& InLocation);` — Moves the given element to the given world space location
- L46 _public prototype_ `void Displace(const FVector& InDisplacement);` — Moves the given element by the given displacement vector
- L49 _public prototype_ `void Destroy();` — Destroys the element
- L52 _public prototype_ `void GetBounds(FVector& OutOrigin, FVector& OutExtents) const;` — Gets the bounds for the element
- L56 _public member_ `TObjectPtr<AActor> Actor;` — `UPROPERTY()` — Actor mapped to this ticker element

#### class `UAvaTickerComponent`  
`class UAvaTickerComponent : public UPrimitiveComponent`  
_L60-211_
- reflection: `UCLASS(MinimalAPI, Blueprintable, DisplayName="Motion Design Ticker Component")`
- inherits: `UPrimitiveComponent`
- L65 _public prototype_ `UAvaTickerComponent();`
- L69 _public prototype_ `bool CanQueueElements() const;` — `UFUNCTION(BlueprintPure, Category="Ticker")` — Returns whether the queue can be added to
- L78 _public prototype_ `bool QueueActor(AActor* InActor, bool bInDestroyOnFailure = true);` — `UFUNCTION(BlueprintCallable, Category="Ticker")` — Adds the given actor to the queue @param InActor the actor to queue @param bInDestroyOnFailure whether to destroy the actor if it failed to be queued @return true if the actor was successfully queued
- L81 _public function_ `FVector GetStartLocation() const` — `UFUNCTION(BlueprintPure, Category="Ticker")`
- L87 _public prototype_ `void SetStartLocation(const FVector& InStartLocation);` — `UFUNCTION(BlueprintCallable, Category="Ticker")`
- L90 _public function_ `double GetDestroyDistance() const` — `UFUNCTION(BlueprintPure, Category="Ticker")`
- L96 _public prototype_ `void SetDestroyDistance(double InDestroyDistance);` — `UFUNCTION(BlueprintCallable, Category="Ticker")`
- L99 _public function_ `FVector GetVelocity() const` — `UFUNCTION(BlueprintPure, Category="Ticker")`
- L105 _public prototype_ `void SetVelocity(const FVector& InVelocity);` — `UFUNCTION(BlueprintCallable, Category="Ticker")`
- L108 _public function_ `double GetPadding() const` — `UFUNCTION(BlueprintPure, Category="Ticker")`
- L114 _public prototype_ `void SetPadding(double InPadding);` — `UFUNCTION(BlueprintCallable, Category="Ticker")`
- L117 _public function_ `bool ShouldLimitQueue() const` — `UFUNCTION(BlueprintPure, Category="Ticker")`
- L123 _public prototype_ `void SetLimitQueue(bool bInLimitQueue);` — `UFUNCTION(BlueprintCallable, Category="Ticker")`
- L126 _public function_ `int32 GetQueueLimitCount() const` — `UFUNCTION(BlueprintPure, Category="Ticker")`
- L132 _public prototype_ `void SetQueueLimitCount(int32 InQueueLimitCount);` — `UFUNCTION(BlueprintCallable, Category="Ticker")`
- L135 _public function_ `EAvaTickerQueueLimitType GetQueueLimitType() const` — `UFUNCTION(BlueprintPure, Category="Ticker")`
- L141 _public prototype_ `void SetQueueLimitType(EAvaTickerQueueLimitType InQueueLimitType);` — `UFUNCTION(BlueprintCallable, Category="Ticker")`
- L144 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L148 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& InLocalToWorld) const override;`
- L152 _public prototype_ `virtual void TickComponent(float InDeltaTime, ELevelTick InTickType, FActorComponentTickFunction* InThisTickFunction) override;`
- L156 _protected prototype_ `bool IsQueueFull() const;`
- L159 _protected prototype_ `bool QueueElement(FAvaTickerElement&& InElement, bool bInDestroyOnFailure);` — Adds the given element to the queue
- L162 _protected prototype_ `FVector GetWorldStartLocation() const;` — Retrieves the start location transformed to World Space
- L165 _protected prototype_ `FVector GetWorldDestroyDisplacement() const;` — Retrieves the destroy displacement transformed to World Space
- L168 _protected prototype_ `FVector GetWorldVelocity() const;` — Retrieves the velocity transformed to World Space
- L171 _protected prototype_ `void TryDequeueElement();` — Removes the first element from the queue and activates it if the last active element isn't on the way
- L174 _protected prototype_ `void UpdateActiveElements(float InDeltaTime);` — Updates the active elements to move with the given velocity
- L178 _protected member_ `TArray<FAvaTickerElement> ActiveElements;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Elements being moved by this ticker
- L182 _protected member_ `TArray<FAvaTickerElement> QueuedElements;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Elements currently hidden, awaiting to become available
- L186 _protected member_ `FVector StartLocation = FVector(0, 500, 0);` — `UPROPERTY(EditAnywhere, Category="Ticker", meta=(AllowPrivateAccess="true"))` — The start location (in local space) where active elements start at
- L190 _protected member_ `double DestroyDistance = 1000.0;` — `UPROPERTY(EditAnywhere, Category="Ticker", meta=(AllowPrivateAccess="true"))` — The distance the last part of the active element must cross before it gets destroyed
- L194 _protected member_ `FVector Velocity = FVector(0, -200, 0);` — `UPROPERTY(EditAnywhere, Category="Ticker", meta=(AllowPrivateAccess="true"))` — The velocity (in local space) to move the active elements at
- L198 _protected member_ `double Padding = 30.0;` — `UPROPERTY(EditAnywhere, Category="Ticker", meta=(AllowPrivateAccess="true"))` — Padding between the active ticker elements
- L202 _protected member_ `bool bLimitQueue = true;` — `UPROPERTY(EditAnywhere, Category="Ticker|Queue", meta=(AllowPrivateAccess="true"))` — Indicates whether to limit the queue when it gets past a certain number of elements
- L206 _protected member_ `int32 QueueLimitCount = 2;` — `UPROPERTY(EditAnywhere, Category="Ticker|Queue", meta=(EditCondition="bLimitQueue", EditConditionHides, ClampMin=0, AllowPrivateAccess="true"))` — The number of items allowed in the queue
- L210 _protected member_ `EAvaTickerQueueLimitType QueueLimitType = EAvaTickerQueueLimitType::DisableQueueing;` — `UPROPERTY(EditAnywhere, Category="Ticker|Queue", meta=(EditCondition="bLimitQueue", EditConditionHides, AllowPrivateAccess="true"))` — The handling method when the queue is full

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHE_API`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/IAvaModule.h` (Public)


#### class `IAvaModule`  
`class IAvaModule : public IModuleInterface`  
_L9-48_
- inherits: `IModuleInterface`
- L12 _public function_ `static IAvaModule& Get()`
- L21 _public prototype_ `virtual bool SetRuntimeStatProcessingEnabled(bool bEnabled) = 0;` — Allow the AvaModule to process the FCoreDelegates::StatCheckEnabled event. This is an equivalent logic as using GStatProcessingViewportClient.
- L26 _public prototype_ `virtual bool IsRuntimeStatEnabled(const FString& InName) const = 0;` — Returns true if the specified stat is enabled.
- L32 _public prototype_ `virtual int32 SetRuntimeStatEnabled(const TCHAR* InName, const bool bInEnabled) = 0;` — Set a specific stat to either enabled or disabled (returns the number of remaining enabled stats) This applies to all the Motion Design instance viewports.
- L37 _public prototype_ `virtual bool ShouldShowRuntimeStats() const = 0;` — Returns true if there are runtime stats enabled.
- L42 _public prototype_ `virtual TArray<FString> GetEnabledRuntimeStats() const = 0;` — Returns the list of enabled runtime stats.
- L47 _public prototype_ `virtual void OverwriteEnabledRuntimeStats(const TArray<FString>& InEnabledStats) = 0;` — Overwrite the enabled runtime stats with provided ones.

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/IAvaSceneInterface.h` (Public)


#### class `UAvaSceneInterface`  
`class UAvaSceneInterface : public UInterface`  
_L25-28_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for the driver class of an Motion Design Scene This interface's purpose is to provide access to scene data and to core interfaces in the Scene

#### class `IAvaSceneInterface`  
`class IAvaSceneInterface`  
_L30-73_
- L35 _public prototype_ `virtual ULevel* GetSceneLevel() const = 0;`
- L37 _public prototype_ `virtual UAvaSceneSettings* GetSceneSettings() const = 0;`
- L39 _public prototype_ `virtual UAvaAttributeContainer* GetAttributeContainer() const = 0;`
- L42 _public function_ `virtual UAvaAttributeContainer* GetSceneState() const` — `UE_DEPRECATED(5.7, "GetSceneState deprecated. Use GetAttributeContainer instead")`
- L47 _public prototype_ `virtual const FAvaSceneTree& GetSceneTree() const = 0;`
- L49 _public prototype_ `virtual FAvaSceneTree& GetSceneTree() = 0;`
- L51 _public prototype_ `virtual IAvaSequenceProvider* GetSequenceProvider() = 0;`
- L53 _public prototype_ `virtual const IAvaSequenceProvider* GetSequenceProvider() const = 0;`
- L55 _public prototype_ `virtual IAvaSequencePlaybackObject* GetPlaybackObject() const = 0;`
- L58 _public prototype_ `virtual URemoteControlPreset* GetOrCreateRemoteControlPreset(bool bInCallModify=true) = 0;` — Retrieve the remote control preset, or create one if there's no preset present
- L61 _public prototype_ `virtual URemoteControlPreset* GetRemoteControlPreset() const = 0;` — Gets the remote control preset of the scene
- L68 _public prototype_ `virtual bool IsRemoteControlPresetExpectedToBePresent() const = 0;` — Whether the remote control preset is expected to be present in this scene
- L71 _public prototype_ `virtual FNavigationToolSaveState& GetNavigationToolSaveState() = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Materials/AvaMaterialUtils.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Ava` (scope `UE`)
- L15 _prototype_ `bool MaterialHasParameter(const UMaterialInterface& InMaterial, const FName InParameterName, const EMaterialParameterType InParameterType);` (scope `UE::Ava`) — Checks for the presence of a named parameter in the given material.
- L18 _prototype_ `bool MaterialHasParameters(const UMaterialInterface& InMaterial, const TConstArrayView<TPair<FName, EMaterialParameterType>> InParameters, TArray<FString>& OutMissingParameters);` (scope `UE::Ava`) — Checks for the presence of a series of named parameters in the given material.

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/RemoteControl/AvaRCSequenceBehavior.h` (Public)


#### class `UAvaRCSequenceBehavior`  
`class UAvaRCSequenceBehavior : public URCBehaviour`  
_L9-12_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URCBehaviour`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/RemoteControl/AvaRCSequenceBehaviorNode.h` (Public)


#### class `UAvaRCSequenceBehaviorNode`  
`class UAvaRCSequenceBehaviorNode : public URCBehaviourNode`  
_L12-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `URCBehaviourNode`
- desc: Performs an action (e.g. Play, Stop) for a defined Motion Design sequence
- L17 _public prototype_ `UAvaRCSequenceBehaviorNode();`
- L21 _protected prototype_ `bool Execute(URCBehaviour* InBehavior) const override;`
- L22 _protected prototype_ `bool IsSupported(URCBehaviour* InBehavior) const override;`
- L23 _protected prototype_ `void OnPassed(URCBehaviour* InBehavior) const;`
- L24 _protected prototype_ `UClass* GetBehaviourClass() const override;`
- L30 _private member_ `FAvaSequenceName SequenceName;` — `UPROPERTY(EditAnywhere, Category="Sequence")` — Sequence name to play
- L34 _private member_ `EAvaSequenceActionType SequenceAction = EAvaSequenceActionType::Play;` — `UPROPERTY(EditAnywhere, Category="Sequence")` — Action to perform for the given sequence
- L38 _private member_ `FAvaSequencePlayParams PlaySettings;` — `UPROPERTY(EditAnywhere, Category="Sequence", meta=(EditCondition="SequenceAction==EAvaSequenceActionType::Play", EditConditionHides))` — Sequence Play Settings

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Transition/Conditions/AvaSceneContainsTagAttributeCondition.h` (Public)


#### struct `FAvaSceneContainsTagAttributeConditionInstanceData`  
`struct FAvaSceneContainsTagAttributeConditionInstanceData`  
_L15-34_
- reflection: `USTRUCT()`
- L21 _public member_ `EAvaTransitionSceneType SceneType = EAvaTransitionSceneType::This;` — `UPROPERTY(EditAnywhere, Category="Parameter")` — Whether the scene to check should be this scene or other scene
- L25 _public member_ `EAvaTransitionLayerCompareType LayerType = EAvaTransitionLayerCompareType::Same;` — `UPROPERTY(EditAnywhere, Category="Parameter", meta=(EditCondition="SceneType==EAvaTransitionSceneType::Other", EditConditionHides))` — Which Layer should be queried for the Scene Attributes
- L29 _public member_ `FAvaTagHandleContainer SpecificLayers;` — `UPROPERTY(EditAnywhere, Category="Parameter", meta=(EditCondition="SceneType==EAvaTransitionSceneType::Other && LayerType==EAvaTransitionLayerCompareType::MatchingTag", EditConditionHides))` — Specific layer tags to check
- L33 _public member_ `FAvaTagHandle TagAttribute;` — `UPROPERTY(EditAnywhere, Category="Parameter")` — The Tag Attribute to check if it's contained in the scene(s) or not

#### struct `FAvaSceneContainsTagAttributeConditionBase`  
`struct FAvaSceneContainsTagAttributeConditionBase : public FAvaTransitionCondition`  
_L37-70_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FAvaTransitionCondition`
- L41 _public typedef_ `using FInstanceDataType = FAvaSceneContainsTagAttributeConditionInstanceData;`
- L43 _public prototype_ `FAvaSceneContainsTagAttributeConditionBase() = default;`
- L45 _public function_ `FAvaSceneContainsTagAttributeConditionBase(bool bInInvertCondition) : bInvertCondition(bInInvertCondition)`
- L52 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L54 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L55 _public prototype_ `virtual bool Link(FStateTreeLinker& InLinker) override;`
- L59 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& InContext) const override;`
- L62 _public prototype_ `bool ContainsTagAttribute(FStateTreeExecutionContext& InContext) const;`
- L64 _public prototype_ `TArray<const FAvaTransitionScene*> GetTransitionScenes(FStateTreeExecutionContext& InContext) const;`
- L67 _protected member_ `bool bInvertCondition = false;`
- L69 _protected member_ `TStateTreeExternalDataHandle<UAvaSceneSubsystem> SceneSubsystemHandle;`

#### struct `FAvaSceneContainsTagAttributeCondition`  
`struct FAvaSceneContainsTagAttributeCondition : public FAvaSceneContainsTagAttributeConditionBase`  
_L73-81_
- reflection: `USTRUCT(DisplayName="A scene contains tag attribute", Category="Scene Attributes")`
- inherits: `FAvaSceneContainsTagAttributeConditionBase`
- L77 _public function_ `FAvaSceneContainsTagAttributeCondition() : FAvaSceneContainsTagAttributeConditionBase( false)`

#### struct `FAvaNoSceneContainsTagAttributeCondition`  
`struct FAvaNoSceneContainsTagAttributeCondition : public FAvaSceneContainsTagAttributeConditionBase`  
_L84-92_
- reflection: `USTRUCT(DisplayName="No scene contains tag attribute", Category="Scene Attributes")`
- inherits: `FAvaSceneContainsTagAttributeConditionBase`
- L88 _public function_ `FAvaNoSceneContainsTagAttributeCondition() : FAvaSceneContainsTagAttributeConditionBase( true)`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Transition/Conditions/AvaTransitionRCControllerMatchCondition.h` (Public)


#### struct `FAvaTransitionRCControllerMatchConditionInstanceData`  
`struct FAvaTransitionRCControllerMatchConditionInstanceData`  
_L15-24_
- reflection: `USTRUCT()`
- L20 _public member_ `FAvaRCControllerId ControllerId;` — `UPROPERTY(EditAnywhere, Category="Parameter")`
- L23 _public member_ `EAvaTransitionComparisonResult ValueComparisonType = EAvaTransitionComparisonResult::None;` — `UPROPERTY(EditAnywhere, Category="Parameter")`

#### struct `FAvaTransitionRCControllerMatchCondition`  
`struct FAvaTransitionRCControllerMatchCondition : public FAvaTransitionCondition`  
_L27-46_
- reflection: `USTRUCT(DisplayName="Compare RC Controller Values", Category="Remote Control")`
- inherits: `FAvaTransitionCondition`
- L31 _public typedef_ `using FInstanceDataType = FAvaTransitionRCControllerMatchConditionInstanceData;`
- L35 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L37 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L38 _public prototype_ `virtual bool Link(FStateTreeLinker& InLinker) override;`
- L42 _public prototype_ `virtual bool TestCondition(FStateTreeExecutionContext& InContext) const override;`
- L45 _public member_ `TStateTreeExternalDataHandle<UAvaSceneSubsystem> SceneSubsystemHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Transition/Extensions/IAvaTransitionRCExtension.h` (Public)


#### class `IAvaRCTransitionExtension`  
`class IAvaRCTransitionExtension : public IAvaTransitionExtension`  
_L13-28_
- inherits: `IAvaTransitionExtension`
- L16 _public member_ `static constexpr const TCHAR* ExtensionIdentifier = TEXT("IAv`
- L25 _public prototype_ `virtual EAvaTransitionComparisonResult CompareControllers(const FGuid& InControllerId , const FAvaTransitionContext& InMyContext , const FAvaTransitionContext& InOtherContext) const = 0;` — Compares the values of an RC controller with the given ControllerId between two transition contexts @param InControllerId the Id of the controller to compare @param InMyContext the first transition context to use @param InOtherContext the second transition context to use @return the comparison result whether same, different, or none (none meaning that the values could not be properly compared)

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Transition/Tasks/AvaSceneAddTagAttributeTask.h` (Public)


#### struct `FAvaSceneAddTagAttributeTask`  
`struct FAvaSceneAddTagAttributeTask : public FAvaSceneTask`  
_L9-22_
- reflection: `USTRUCT(DisplayName="Add tag attribute to this scene", Category="Scene Attributes")`
- inherits: `FAvaSceneTask`
- L15 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L20 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& InContext, const FStateTreeTransitionResult& InTransition) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Transition/Tasks/AvaSceneRemoveTagAttributeTask.h` (Public)


#### struct `FAvaSceneRemoveTagAttributeTask`  
`struct FAvaSceneRemoveTagAttributeTask : public FAvaSceneTask`  
_L9-22_
- reflection: `USTRUCT(DisplayName="Remove tag attribute from this scene", Category="Scene Attributes")`
- inherits: `FAvaSceneTask`
- L15 _public prototype_ `virtual FText GetDescription(const FGuid& InId, FStateTreeDataView InInstanceDataView, const IStateTreeBindingLookup& InBindingLookup, EStateTreeNodeFormatting InFormatting) const override;`
- L20 _public prototype_ `virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& InContext, const FStateTreeTransitionResult& InTransition) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Transition/Tasks/AvaSceneTask.h` (Public)


#### struct `FAvaSceneTaskInstanceData`  
`struct FAvaSceneTaskInstanceData`  
_L13-19_
- reflection: `USTRUCT()`
- L18 _public member_ `FAvaTagHandle TagAttribute;` — `UPROPERTY(EditAnywhere, Category="Parameter")`

#### struct `FAvaSceneTask`  
`struct FAvaSceneTask : public FAvaTransitionTask`  
_L22-36_
- reflection: `USTRUCT(meta=(Hidden))`
- inherits: `FAvaTransitionTask`
- L26 _public typedef_ `using FInstanceDataType = FAvaSceneTaskInstanceData;`
- L29 _public function_ `virtual const UStruct* GetInstanceDataType() const override`
- L30 _public prototype_ `virtual bool Link(FStateTreeLinker& InLinker) override;`
- L33 _public prototype_ `IAvaSceneInterface* GetScene(FStateTreeExecutionContext& InContext) const;`
- L35 _public member_ `TStateTreeExternalDataHandle<UAvaSceneSubsystem> SceneSubsystemHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Viewport/AvaCineCameraActor.h` (Public)


#### class `AAvaCineCameraActor`  
`class AAvaCineCameraActor : public ACineCameraActor`  
_L16-35_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Motion Design Cine Camera Actor")`
- inherits: `ACineCameraActor`
- desc: Motion Design Cine Camera Actor is derived from Cine Camera Actor. Its function is to provide a Cine Camera which can be used right away inside Motion Design. This is done by customizing some of its default values. In particular, Motion Design Editor configuration property "Camera Distance" is used to initialize camera position and manual focus. See: Editor Preferences --> Motion Design --> Editor Settings --> Camera Distance
- L23 _public prototype_ `AAvaCineCameraActor(const FObjectInitializer& ObjectInitializer);`
- L29 _public prototype_ `void Configure(float InCameraDistance);` — Initialize the camera with Motion Design scene default values: field of view, camera position, focus distance. @param InCameraDistance: camera distance value, used to initialize camera position and manual focus distance
- L34 _private member_ `float DefaultCameraDistance;` — `UPROPERTY()` — The CameraDistance value used when configuring this AvaCineCamera

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Viewport/AvaPostProcessVolume.h` (Public)


#### class `AAvaPostProcessVolume`  
`class AAvaPostProcessVolume : public APostProcessVolume`  
_L14-20_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Motion Design Post Process Volume")`
- inherits: `APostProcessVolume`
- desc: Motion Design Post Process Volume is derived from Post Process Volume. Its function is to provide a Post Process which can be used right away inside Motion Design. This is done by customizing some of the default values.
- L19 _public prototype_ `AAvaPostProcessVolume();`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Viewport/AvaViewportQualitySettings.h` (Public)


#### struct `FAvaViewportQualitySettingsFeature`  
`struct FAvaViewportQualitySettingsFeature`  
_L12-33_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public function_ `FAvaViewportQualitySettingsFeature()`
- L17 _public function_ `FAvaViewportQualitySettingsFeature(const FString& InName, const bool bInEnabled) : Name(InName), bEnabled(bInEnabled)`
- L21 _public function_ `bool operator==(const FAvaViewportQualitySettingsFeature& InOther) const`
- L28 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality")` — The name of the feature in the engine show flags.
- L32 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality")` — True if this engine feature show flag should be enabled.

#### struct `FAvaViewportQualitySettings`  
`struct FAvaViewportQualitySettings`  
_L43-84_
- reflection: `USTRUCT(BlueprintType)`
- desc: Motion Design Viewport Quality Settings Advanced render and quality viewport settings to control performance for a given Viewport. Human-readable and blueprint-able structure that holds flags for the FShowEngineFlags structure. Can convert FShowEngineFlags to FAvaViewportQualitySettings and apply FAvaViewportQualitySettings to a FShowEngineFlags structure.
- L47 _public prototype_ `static TArray<FAvaViewportQualitySettingsFeature> DefaultFeatures();`
- L48 _public prototype_ `static TArray<FAvaViewportQualitySettingsFeature> AllFeatures(const bool bUseAllFeatures);`
- L50 _public prototype_ `static FAvaViewportQualitySettings Default();`
- L51 _public prototype_ `static FAvaViewportQualitySettings Preset(const FText& InPresetName);`
- L52 _public prototype_ `static FAvaViewportQualitySettings All(const bool bUseAllFeatures);`
- L54 _public prototype_ `static void FeatureNameAndTooltipText(const FString& InFeatureName, FText& OutNameText, FText& OutTooltipText);`
- L56 _public prototype_ `static FAvaViewportQualitySettingsFeature* FindFeatureByName(TArray<FAvaViewportQualitySettingsFeature>& InFeatures, const FString& InFeatureName);`
- L57 _public prototype_ `static const FAvaViewportQualitySettingsFeature* FindFeatureByName(const TArray<FAvaViewportQualitySettingsFeature>& InFeatures, const FString& InFeatureName);`
- L59 _public prototype_ `static void VerifyIntegrity(TArray<FAvaViewportQualitySettingsFeature>& InFeatures);`
- L61 _public prototype_ `static void SortFeaturesByDisplayText(TArray<FAvaViewportQualitySettingsFeature>& InFeatures);`
- L63 _public prototype_ `FAvaViewportQualitySettings();`
- L64 _public prototype_ `FAvaViewportQualitySettings(ENoInit NoInit);`
- L65 _public prototype_ `FAvaViewportQualitySettings(const bool bInUseAllFeatures);`
- L66 _public prototype_ `FAvaViewportQualitySettings(const FEngineShowFlags& InShowFlags);`
- L67 _public prototype_ `FAvaViewportQualitySettings(const TArray<FAvaViewportQualitySettingsFeature>& InFeatures);`
- L69 _public prototype_ `bool operator==(const FAvaViewportQualitySettings& InOther) const;`
- L70 _public prototype_ `bool operator!=(const FAvaViewportQualitySettings& InOther) const;`
- L73 _public prototype_ `void Apply(FEngineShowFlags& InFlags);` — Applies the settings to the FEngineShowFlags structure provided.
- L75 _public prototype_ `void EnableFeaturesByName(const bool bInEnabled, const TArray<FString>& InFeatureNames);`
- L77 _public prototype_ `void VerifyIntegrity();`
- L79 _public prototype_ `void SortFeaturesByDisplayText();`
- L83 _public member_ `TArray<FAvaViewportQualitySettingsFeature> Features;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, EditFixedSize, Category = "Quality", meta = (EditFixedOrder))` — Advanced viewport client engine features indexed by FEngineShowFlags names.

#### struct `FAvaViewportQualitySettingsPreset`  
`struct FAvaViewportQualitySettingsPreset`  
_L87-109_
- reflection: `USTRUCT(BlueprintType)`
- L91 _public member_ `static const FText NoLumen;`
- L92 _public member_ `static const FText Reduced;`
- L94 _public function_ `FAvaViewportQualitySettingsPreset()`
- L95 _public function_ `FAvaViewportQualitySettingsPreset(const FText& InPresetName, const FAvaViewportQualitySettings& InQualitySettings) : PresetName(InPresetName), QualitySettings(InQualitySettings)`
- L99 _public function_ `bool operator==(const FAvaViewportQualitySettingsPreset& InOther) const`
- L105 _public member_ `FText PresetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preset")`
- L108 _public member_ `FAvaViewportQualitySettings QualitySettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preset")`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Viewport/Interaction/AvaSnapPoint.h` (Public)


#### struct `FAvaSnapPoint`  
`struct FAvaSnapPoint`  
_L8-106_
- L11 _protected prototype_ `FAvaSnapPoint(const UObject* InOuter, EAvaAnchors InAnchor, const FVector& InLocation, int32 InPointIndex);`
- L14 _public prototype_ `static FAvaSnapPoint CreateScreenSnapPoint(EAvaAnchors InAnchor, const FVector2f& InLocation);`
- L15 _public prototype_ `static FAvaSnapPoint CreateGuideSnapPoint(float Offset, EOrientation Orientation);`
- L16 _public prototype_ `static FAvaSnapPoint CreateSelectionSnapPoint(EAvaAnchors InAnchor, const FVector& InLocation, EAvaDepthAlignment InDepth);`
- L17 _public prototype_ `static FAvaSnapPoint CreateActorSnapPoint(const AActor* InActor, EAvaAnchors InAnchor, const FVector& InLocation, EAvaDepthAlignment InDepth);`
- L18 _public prototype_ `static FAvaSnapPoint CreateActorCustomSnapPoint(const AActor* InActor, const FVector& InLocation, int32 PointIndex);`
- L19 _public prototype_ `static FAvaSnapPoint CreateActorIndexedSnapPoint(const AActor* InActor, EAvaAnchors InAnchor, const FVector& InLocation, int32 PointIndex);`
- L20 _public prototype_ `static FAvaSnapPoint CreateLocalActorSnapPoint(EAvaAnchors InAnchor, const FVector& InLocation, EAvaDepthAlignment InDepth);`
- L21 _public prototype_ `static FAvaSnapPoint CreateLocalActorCustomSnapPoint(const FVector& InLocation, int32 PointIndex);`
- L22 _public prototype_ `static FAvaSnapPoint CreateLocalActorIndexedSnapPoint(EAvaAnchors InAnchor, const FVector& InLocation, int32 PointIndex);`
- L23 _public prototype_ `static FAvaSnapPoint CreateComponentSnapPoint(const USceneComponent* InComponent, EAvaAnchors InAnchor, const FVector& InLocation, EAvaDepthAlignment InDepth);`
- L24 _public prototype_ `static FAvaSnapPoint CreateComponentCustomSnapPoint(const USceneComponent* InComponent, const FVector& InLocation, int32 PointIndex);`
- L25 _public prototype_ `static FAvaSnapPoint CreateComponentIndexedSnapPoint(const USceneComponent* InComponent, EAvaAnchors InAnchor, const FVector& InLocation, int32 PointIndex);`
- L26 _public prototype_ `static FAvaSnapPoint CreateLocalComponentSnapPoint(EAvaAnchors InAnchor, const FVector& InLocation, EAvaDepthAlignment InDepth);`
- L27 _public prototype_ `static FAvaSnapPoint CreateLocalComponentCustomSnapPoint(const FVector& InLocation, int32 PointIndex);`
- L28 _public prototype_ `static FAvaSnapPoint CreateLocalComponentIndexedSnapPoint(EAvaAnchors InAnchor, const FVector& InLocation, int32 PointIndex);`
- L29 _public prototype_ `static FAvaSnapPoint CreateBoundsSnapPoint(EAvaAnchors InAnchor, const FVector& InLocation, EAvaDepthAlignment InDepth);`
- L30 _public prototype_ `static FAvaSnapPoint CreateNullSnapPoint();`
- L32 _public function_ `static FAvaSnapPoint CreateActorSnapPoint(const AActor* InActor, EAvaAnchors InAnchor, const FVector2D& InLocation)`
- L37 _public function_ `static FAvaSnapPoint CreateActorCustomSnapPoint(const AActor* InActor, const FVector2D& InLocation, int32 PointIndex)`
- L42 _public function_ `static FAvaSnapPoint CreateActorIndexedSnapPoint(const AActor* InActor, EAvaAnchors InAnchor, const FVector2D& InLocation, int32 PointIndex)`
- L47 _public function_ `static FAvaSnapPoint CreateLocalActorSnapPoint(EAvaAnchors InAnchor, const FVector2D& InLocation)`
- L52 _public function_ `static FAvaSnapPoint CreateLocalActorCustomSnapPoint(const FVector2D& InLocation, int32 PointIndex)`
- L57 _public function_ `static FAvaSnapPoint CreateLocalActorIndexedSnapPoint(EAvaAnchors InAnchor, const FVector2D& InLocation, int32 PointIndex)`
- L62 _public function_ `static FAvaSnapPoint CreateComponentSnapPoint(const USceneComponent* InComponent, EAvaAnchors InAnchor, const FVector2D& InLocation)`
- L67 _public function_ `static FAvaSnapPoint CreateComponentCustomSnapPoint(const USceneComponent* InComponent, const FVector2D& InLocation, int32 PointIndex)`
- L72 _public function_ `static FAvaSnapPoint CreateComponentIndexedSnapPoint(const USceneComponent* InComponent, EAvaAnchors InAnchor, const FVector2D& InLocation, int32 PointIndex)`
- L77 _public function_ `static FAvaSnapPoint CreateLocalComponentSnapPoint(EAvaAnchors InAnchor, const FVector2D& InLocation)`
- L82 _public function_ `static FAvaSnapPoint CreateLocalComponentCustomSnapPoint(const FVector2D& InLocation, int32 PointIndex)`
- L87 _public function_ `static FAvaSnapPoint CreateLocalComponentIndexedSnapPoint(EAvaAnchors InAnchor, const FVector2D& InLocation, int32 PointIndex)`
- L92 _public member_ `TWeakObjectPtr<const UObject> Outer;`
- L93 _public member_ `EAvaAnchors Anchor;`
- L94 _public member_ `FVector Location;`
- L95 _public member_ `int32 PointIndex;`
- L97 _public prototype_ `FString ToString() const;`
- L99 _public prototype_ `bool IsScreenSnapPoint() const;`
- L101 _public prototype_ `bool IsGuideSnapPoint() const;`
- L103 _public prototype_ `bool IsSelectionSnapPoint() const;`
- L105 _public prototype_ `bool IsActorSnapPoint() const;`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Viewport/Interaction/AvaViewportPostProcessInfo.h` (Public)


#### enum `EAvaViewportPostProcessType_Deprecated`  
`enum class EAvaViewportPostProcessType_Deprecated : uint8`  
_L11-19_
- reflection: `UENUM()`
- L13 _public enumerator_ `None`
- L14 _public enumerator_ `Background`
- L15 _public enumerator_ `RedChannel`
- L16 _public enumerator_ `GreenChannel`
- L17 _public enumerator_ `BlueChannel`
- L18 _public enumerator_ `AlphaChannel`

#### struct `FAvaViewportPostProcessInfo_Deprecated`  
`struct FAvaViewportPostProcessInfo_Deprecated`  
_L22-34_
- reflection: `USTRUCT()`
- L27 _public member_ `EAvaViewportPostProcessType_Deprecated Type = EAvaViewportPostProcessType_Deprecated::None;` — `UPROPERTY()`
- L30 _public member_ `TSoftObjectPtr<UTexture> Texture = nullptr;` — `UPROPERTY()`
- L33 _public member_ `float Opacity = 1.0f;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Viewport/Interaction/IAvaGizmoObject.h` (Public)


#### class `UAvaGizmoObjectInterface`  
`class UAvaGizmoObjectInterface : public UInterface`  
_L17-20_
- reflection: `UINTERFACE(Blueprintable)`
- inherits: `UInterface`
- desc: Interface for objects that can be (optionally) represented as gizmos. Toggling only occurs in-editor, but objects can be gizmos at runtime (ie. used for booleans only)

#### class `IAvaGizmoObjectInterface`  
`class IAvaGizmoObjectInterface`  
_L22-30_
- L29 _public prototype_ `void ToggleGizmo(const UAvaGizmoComponent* InGizmoComponent, const bool bShowAsGizmo = true);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Editor")` — Whether to show the callee as a gizmo or not

### `Plugins/VirtualProduction/Avalanche/Source/Avalanche/Public/Viewport/Interaction/IAvaSnapPointGenerator.h` (Public)


#### class `UAvaSnapPointGenerator`  
`class UAvaSnapPointGenerator : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`

#### class `IAvaSnapPointGenerator`  
`class IAvaSnapPointGenerator`  
_L15-21_
- L20 _public prototype_ `virtual TArray<FAvaSnapPoint> GetLocalSnapPoints() const = 0;`
