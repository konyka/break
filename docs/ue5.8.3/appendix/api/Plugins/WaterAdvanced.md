# Plugins / WaterAdvanced

- module root: `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced`
- headers: 9; symbols: 258
- symbol kinds: class=9, delegate=1, enum=2, enumerator=9, function=19, macro=5, member=123, prototype=84, struct=6
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: Core, CoreUObject, DerivedDataCache, DeveloperSettings, EditorFramework, Engine, GameplayTags, Landscape, Niagara, Projects, RenderCore, Slate, SlateCore, TargetPlatform, UnrealEd, Water
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced/Private/ShallowWaterRiverDetails.h` (Private)


#### class `FShallowWaterRiverDetails`  
`class FShallowWaterRiverDetails : public IDetailCustomization`  
_L13-35_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L25 _protected prototype_ `void OnWorldDestroyed(class UWorld* InWorld);`
- L26 _protected prototype_ `void OnPiEEnd();`
- L28 _protected prototype_ `FReply OnResetSelectedSystem();`
- L29 _protected prototype_ `FReply OnBakeSelectedSystem();`
- L32 _private member_ `TWeakObjectPtr<UShallowWaterRiverComponent> Component;`
- L33 _private member_ `IDetailLayoutBuilder* Builder = nullptr;`

### `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced/Public/BasicShallowWaterSubsystem.h` (Public)


#### class `UBasicShallowWaterSubsystem`  
`class UBasicShallowWaterSubsystem : public UShallowWaterSubsystem`  
_L12-21_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Transient)`
- inherits: `UShallowWaterSubsystem`
- L17 _public prototype_ `UBasicShallowWaterSubsystem();`
- L19 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L20 _public prototype_ `virtual bool IsShallowWaterAllowedToInitialize() const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API WATERADVANCED_API`

### `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced/Public/FFTOceanPatchSubsystem.h` (Public)


#### class `UFFTOceanPatchSubsystem`  
`class UFFTOceanPatchSubsystem : public UTickableWorldSubsystem`  
_L15-34_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Transient)`
- inherits: `UTickableWorldSubsystem`
- L20 _public prototype_ `UFFTOceanPatchSubsystem();`
- L22 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L23 _public prototype_ `virtual void PostInitialize() override;`
- L24 _public prototype_ `virtual TStatId GetStatId() const override;`
- L26 _public prototype_ `TObjectPtr<UTextureRenderTarget2D> GetOceanNormalRT(UWorld* World);`
- L27 _public function_ `TObjectPtr<UNiagaraComponent> GetOceanSystem()`
- L30 _protected member_ `TObjectPtr<UShallowWaterSettings> Settings;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Shallow Water")`
- L32 _private member_ `TObjectPtr<UNiagaraComponent> FFTOceanSystem;`
- L33 _private member_ `TObjectPtr<UTextureRenderTarget2D> OceanNormalRT;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API WATERADVANCED_API`

### `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced/Public/ShallowWaterCommon.h` (Public)


#### struct `FShallowWaterSimParameters`  
`struct FShallowWaterSimParameters`  
_L13-21_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `float WorldGridSize = 2000.f;` — `UPROPERTY(EditAnywhere, Category = "Shallow Water")`
- L20 _public member_ `int32 ResolutionMaxAxis = 512;` — `UPROPERTY(EditAnywhere, Category = "Shallow Water")`

#### struct `FShallowWaterPhysicsAssetOverride`  
`struct FShallowWaterPhysicsAssetOverride`  
_L24-30_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `TSoftObjectPtr<UPhysicsAsset> PhysicsAsset;` — `UPROPERTY(EditAnywhere, Category = "Shallow Water")`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogShallowWater, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogShallowWater, Log, All);`

### `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced/Public/ShallowWaterPhysicsAssetOverridesDataAsset.h` (Public)


#### class `UShallowWaterPhysicsAssetOverridesDataAsset`  
`class UShallowWaterPhysicsAssetOverridesDataAsset : public UDataAsset`  
_L17-24_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UDataAsset`
- L23 _public member_ `TMap<FGameplayTag, FShallowWaterPhysicsAssetOverride> Overrides;` — `UPROPERTY(EditAnywhere, Category = "Shallow Water")`

### `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced/Public/ShallowWaterRiverActor.h` (Public)


#### enum `EShallowWaterRenderState`  
`enum EShallowWaterRenderState : int`  
_L26-34_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `WaterComponent`
- L29 _public enumerator_ `WaterComponentWithBakedSim`
- L30 _public enumerator_ `LiveSim`
- L31 _public enumerator_ `BakedSim`
- L32 _public enumerator_ `DebugRenderBottomContour`
- L33 _public enumerator_ `DebugRenderFoam`

#### class `UShallowWaterRiverComponent`  
`class UShallowWaterRiverComponent : public UPrimitiveComponent`  
_L38-245_
- reflection: `UCLASS(MinimalAPI, BlueprintType, HideCategories = (Physics, Replication, Input, Collision))`
- inherits: `UPrimitiveComponent`
- L45 _public member_ `TObjectPtr <class UNiagaraSystem> NiagaraRiverSimulation;` — `UPROPERTY(EditAnywhere, Category = "Simulation", meta = (DisplayName = "Niagara River Simulation"))`
- L48 _public member_ `int ResolutionMaxAxis;` — `UPROPERTY(EditAnywhere, Category = "Simulation", meta = (DisplayName = "Resolution Max Axis"))`
- L51 _public member_ `float SourceSize;` — `UPROPERTY(EditAnywhere, Category = "Simulation", meta = (DisplayName = "Source Width"))`
- L54 _public member_ `float SimSpeed = 10.f;` — `UPROPERTY(EditAnywhere, Category = "Simulation", meta = (DisplayName = "Speed"))`
- L57 _public member_ `int NumSteps = 10;` — `UPROPERTY(EditAnywhere, Category = "Simulation", meta = (DisplayName = "Num Substeps"))`
- L60 _public member_ `bool bMatchSpline = true;` — `UPROPERTY(EditAnywhere, Category = "Simulation", meta = (DisplayName = "Match Spline"))`
- L63 _public member_ `float MatchSplineHeightAmount = 2.;` — `UPROPERTY(EditAnywhere, Category = "Simulation", meta = (DisplayName = "Match Spline Height Amount", EditCondition = "bMatchSpline"))`
- L66 _public member_ `float RemoveOutsideSplineAmount = 50.;` — `UPROPERTY(EditAnywhere, Category = "Simulation", meta = (DisplayName = "Remove Outside Spline Amount", EditCondition = "bMatchSpline"))`
- L69 _public member_ `bool bDisableCPUThrottling = true;` — `UPROPERTY(EditAnywhere, Category = "Simulation")`
- L72 _public member_ `TArray<TSoftObjectPtr<AWaterBody>> SourceRiverWaterBodies;` — `UPROPERTY(EditAnywhere, Category = "Water", meta = (DisplayName = "Source River Water Bodies"))`
- L75 _public member_ `TArray<TSoftObjectPtr<AWaterBody>> SinkRiverWaterBodies;` — `UPROPERTY(EditAnywhere, Category = "Water", meta = (DisplayName = "Sink River Water Bodies"))`
- L78 _public member_ `TEnumAsByte<EShallowWaterRenderState> RenderState = EShallowWaterRenderState::WaterComponent;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Render State"))`
- L81 _public member_ `TObjectPtr <class UMaterialInstance> BakedSimMaterial;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Baked Sim Material"))`
- L84 _public member_ `TObjectPtr <class UMaterialInstance> BakedSimUnderWaterMaterial;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Baked UnderWater Sim Material"))`
- L87 _public member_ `TObjectPtr <class UMaterialInstance> BakedSimRiverToLakeTransitionMaterial;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Baked Sim River To Lake Transition Material"))`
- L90 _public member_ `TObjectPtr <class UMaterialInstance> BakedSimRiverToOceanTransitionMaterial;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Baked Sim River To Ocean Transition Material"))`
- L93 _public member_ `TObjectPtr <class UMaterialInstance> SplineRiverMaterial;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Spline River Material"))`
- L96 _public member_ `TObjectPtr <class UMaterialInstance> SplineRiverToLakeTransitionMaterial;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Spline River To Lake Transition Material"))`
- L99 _public member_ `TObjectPtr <class UMaterialInstance> SplineRiverToOceanTransitionMaterial;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Spline River To Ocean Transition Material"))`
- L102 _public member_ `TObjectPtr <class UMaterialInstance> SplineRiverUnderWaterMaterial;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Spline River UnderWater Material"))`
- L105 _public member_ `int SmoothingWidth = 5;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Smoothing Width"))`
- L108 _public member_ `float SmoothingCutoff = 500.f;` — `UPROPERTY(EditAnywhere, Category = "Rendering", meta = (DisplayName = "Smoothing Cutoff"))`
- L111 _public member_ `bool bUseVirtualTextures = true;` — `UPROPERTY()`
- L114 _public member_ `FVector2D SimRes;` — `UPROPERTY()`
- L117 _public member_ `float SimDx;` — `UPROPERTY()`
- L120 _public member_ `TObjectPtr<UTexture2D> BakedWaterSurfaceTexture;` — `UPROPERTY()`
- L123 _public member_ `TObjectPtr<UTexture2D> BakedFoamTexture;` — `UPROPERTY()`
- L126 _public member_ `TObjectPtr<UTexture2D> BakedWaterSurfaceNormalTexture;` — `UPROPERTY()`
- L132 _public member_ `bool bUseCapture = true;` — `UPROPERTY(EditAnywhere, Category = "Collisions")`
- L135 _public member_ `bool bRecursivelyAddAttachedActors = false;` — `UPROPERTY(EditAnywhere, Category = "Collisions")`
- L138 _public member_ `TArray<TSoftObjectPtr<AActor>> BottomContourLandscapeActors;` — `UPROPERTY(EditAnywhere, Category = "Collisions")`
- L141 _public member_ `TArray<TSoftObjectPtr<AActor>> BottomContourActors;` — `UPROPERTY(EditAnywhere, Category = "Collisions")`
- L144 _public member_ `TArray<FName> BottomContourTags;` — `UPROPERTY(EditAnywhere, Category = "Collisions")`
- L147 _public member_ `float BottomContourCaptureOffset = 15000.f;` — `UPROPERTY(EditAnywhere, Category = "Collisions")`
- L150 _public member_ `float SceneCaptureLODDistanceFactor = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Collisions", meta = (DisplayName = "Scene Capture LOD Distance Factor"))`
- L153 _public member_ `TArray<TSoftObjectPtr<AActor>> DilatedBottomContourActors;` — `UPROPERTY(EditAnywhere, Category = "Collisions")`
- L156 _public member_ `TArray<FName> DilatedBottomContourTags;` — `UPROPERTY(EditAnywhere, Category = "Collisions")`
- L159 _public member_ `float BottomContourCollisionDilation = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Collisions")`
- L161 _public prototype_ `virtual void PostLoad() override;`
- L163 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L164 _public prototype_ `virtual void BeginPlay() override;`
- L166 _public prototype_ `virtual void OnUnregister() override;`
- L168 _public prototype_ `void UpdateRenderState();`
- L170 _public prototype_ `void SetWaterMIDParameters(UMaterialInstanceDynamic* WaterMID);`
- L173 _public prototype_ `void Rebuild();`
- L175 _public prototype_ `void AddActorsToRawArray(const TArray<TSoftObjectPtr<AActor>>& ActorsArray, TArray<AActor*>& BottomContourActorsRawPtr);`
- L177 _public prototype_ `void AddTaggedActorsToArray(TArray<FName>& TagsToUse, TArray<AActor*>& BottomContourActorsRawPtr);`
- L179 _public prototype_ `void Bake();`
- L181 _public prototype_ `void InitializeVirtualTexture(TObjectPtr<UTexture2D> InTexture);`
- L183 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L186 _public prototype_ `void OnWaterInfoTextureArrayCreated(const UTextureRenderTarget2DArray* InWaterInfoTexture);` — `UFUNCTION()`
- L188 _public function_ `bool ShouldDisableCPUThrottling()`
- L192 _public prototype_ `void SetPaused(bool Pause);` — `UFUNCTION(BlueprintCallable, Category = "Shallow Water River")`
- L197 _protected member_ `TObjectPtr<UNiagaraComponent> RiverSimSystem;` — `UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Shallow Water")` — Asset can be set in Project Settings - Plugins - Water ShallowWaterSimulation
- L200 _protected member_ `TObjectPtr<const UTextureRenderTarget2DArray> WaterInfoTexture;` — `UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Shallow Water")`
- L203 _protected member_ `TObjectPtr<UTextureRenderTarget2D> BakedWaterSurfaceRT;` — `UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Shallow Water")`
- L206 _protected member_ `TObjectPtr<UTextureRenderTarget2D> BakedFoamRT;` — `UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Shallow Water")`
- L209 _protected member_ `TObjectPtr<UTextureRenderTarget2D> BakedWaterSurfaceNormalRT;` — `UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Shallow Water")`
- L212 _protected member_ `TObjectPtr<UBakedShallowWaterSimulationComponent> BakedSim;` — `UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Shallow Water")`
- L214 _protected prototype_ `bool QueryWaterAtSplinePoint(TSoftObjectPtr<AWaterBody> WaterBody, int SplinePoint, FVector& OutPos, FVector& OutTangent, float& OutWidth, float& OutDepth);`
- L215 _protected prototype_ `void ConvertToVirtualTextures();`
- L218 _private member_ `bool bIsInitialized;`
- L219 _private member_ `bool bTickInitialize;`
- L220 _private member_ `bool bRenderStateTickInitialize;`
- L223 _private member_ `TSet <TSoftObjectPtr<AWaterBody>> AllWaterBodies;` — `UPROPERTY()`
- L226 _private member_ `FVector2D WorldGridSize;` — `UPROPERTY()`
- L229 _private member_ `FVector SystemPos;` — `UPROPERTY()`
- L232 _private member_ `TObjectPtr<UTextureRenderTarget2D> NormalDetailRT;` — `UPROPERTY()`
- L235 _private member_ `TObjectPtr<class UNiagaraSystem> OceanPatchSystem;` — `UPROPERTY()`
- L237 _private member_ `FDelegateHandle ShouldDisableCPUThrottlingDelegateHandle;`
- L240 _private prototype_ `TObjectPtr<UTextureRenderTarget2D> GetSharedFFTOceanPatchNormalRTFromSubsystem(UWorld* World);` — Find/create the level set renderer singleton actor as required. Return whether the found or created actor.
- L242 _private prototype_ `FBoxSphereBounds InitializeCaptureDI(const FName &DIName, TArray<AActor*> RawActorPtrArray);`

#### class `AShallowWaterRiver`  
`class AShallowWaterRiver : public AActor`  
_L248-256_
- reflection: `UCLASS(MinimalAPI, BlueprintType, HideCategories = (Physics, Replication, Input, Collision))`
- inherits: `AActor`
- L255 _private member_ `TObjectPtr<UShallowWaterRiverComponent> ShallowWaterRiverComponent;` — `UPROPERTY(VisibleAnywhere, Category = "Shallow Water")` — Asset can be set in Project Settings - Plugins - Water ShallowWaterSimulation

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API WATERADVANCED_API`

### `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced/Public/ShallowWaterSettings.h` (Public)


#### class `UShallowWaterSettings`  
`class UShallowWaterSettings : public UDeveloperSettings`  
_L17-64_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, meta=(DisplayName="Water Advanced"))`
- inherits: `UDeveloperSettings`
- L20 _private prototype_ `UShallowWaterSettings();`
- L23 _public prototype_ `virtual FName GetCategoryName() const override;`
- L26 _public member_ `TSoftObjectPtr<UNiagaraSystem> DefaultShallowWaterNiagaraSimulation;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water Simulation")`
- L28 _public member_ `TSoftObjectPtr<UNiagaraDataChannelAsset> DefaultShallowWaterCollisionNDC;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category = "Shallow Water Simulation")`
- L30 _public member_ `TSoftObjectPtr<UNiagaraSystem> DefaultOceanPatchNiagaraSystem;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water River")`
- L32 _public member_ `FShallowWaterSimParameters ShallowWaterSimParameters;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water Simulation")`
- L34 _public member_ `TSoftObjectPtr<UMaterialParameterCollection> WaterMPC;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water Simulation")`
- L36 _public member_ `FName GridCenterMPCName = FName("Sim` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water Simulation")`
- L38 _public member_ `FName WorldGridSizeMPCName = FName("Flu` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water Simulation")`
- L40 _public member_ `FName ResolutionMaxAxisMPCName = FName("Flu` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water Simulation")`
- L42 _public member_ `FName NormalRTMaterialName = FName("Nor` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water Simulation")`
- L44 _public member_ `FName VelocityRTMaterialName = FName("Vel` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water Simulation")`
- L46 _public member_ `FName NormalRTNiagaraName = FName("Nor` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water Simulation")`
- L48 _public member_ `FName VelocityRTNiagaraName = FName("Vel` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Shallow Water Simulation")`
- L50 _public member_ `bool UseDefaultShallowWaterSubsystem = false;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category = "Shallow Water Simulation")`
- L52 _public member_ `bool OutputVelocity = false;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category = "Shallow Water Simulation")`
- L55 _public member_ `int32 MaxActivePawnNum = 6;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Interaction")`
- L57 _public member_ `int32 MaxImpulseForceNum = 6;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Interaction")`
- L60 _public member_ `TSoftObjectPtr<UShallowWaterPhysicsAssetOverridesDataAsset> PhysicsAssetProxiesDataAsset;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Interaction")` — Default overrides. Game Feature Plugin can register their own overrides asset with subsystem RegisterPhysicsAssetOverridesDataAsset()
- L63 _public member_ `bool bVisualizeActivePawn;` — `UPROPERTY(Config, BlueprintReadOnly, EditAnywhere, Category="Debug")`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API WATERADVANCED_API`

### `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced/Public/ShallowWaterSubsystem.h` (Public)


#### enum `EShallowWaterCollisionContextType`  
`enum class EShallowWaterCollisionContextType : uint8`  
_L27-32_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `Pawn`
- L30 _public enumerator_ `Vehicle` — Pawn as driver or pawn as passenger
- L31 _public enumerator_ `Custom`

#### struct `FShallowWaterCollisionContext`  
`struct FShallowWaterCollisionContext`  
_L36-71_
- reflection: `USTRUCT()`
- desc: Shallow Water Rigid Body collision
- L40 _public function_ `FShallowWaterCollisionContext()`
- L41 _public function_ `FShallowWaterCollisionContext(EShallowWaterCollisionContextType InType, USkeletalMeshComponent* InComponent) : Type(InType) , WeakComponent(InComponent)`
- L53 _public member_ `EShallowWaterCollisionContextType Type = EShallowWaterCollisionContextType::Pawn;`
- L56 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> WeakComponent = nullptr;` — `UPROPERTY()`
- L59 _public member_ `uint32 UniqueID = 0;` — #todo Theoretically not enough as unique identification since Component->GetUniqueID() is "reused so it is only unique while the object is alive"
- L61 _public function_ `bool IsValidAndAlive() const`
- L63 _public function_ `bool operator==(const FShallowWaterCollisionContext& Other) const`

#### struct `FShallowWaterCollisionTracker_Actor`  
`struct FShallowWaterCollisionTracker_Actor`  
_L77-95_
- desc: CollisionTracker that records the actor affecting the waterbody, used by logs or fishing lures etc., where the collision is handled by Niagara Data Channel and the subsystem isn't aware of them without a tracking device. This is intended as a solution.
- L79 _public function_ `FShallowWaterCollisionTracker_Actor()`
- L80 _public function_ `FShallowWaterCollisionTracker_Actor(float InTimeSpawned, float InLifespan, TWeakObjectPtr<AActor> InCollisionActor) : TimeSpawned(InTimeSpawned), Lifespan(InLifespan), CollisionActor(InCollisionActor)`
- L84 _public prototype_ `void GetOverlappingWaterBodies(TSet<AWaterBody*>& WaterBodies) const;`
- L85 _public function_ `bool IsValid(const float CurrentTime) const`
- L87 _public member_ `float TimeSpawned = 0;`
- L88 _public member_ `float Lifespan = 10.f;`
- L89 _public member_ `TWeakObjectPtr<AActor> CollisionActor = nullptr;`
- L91 _public function_ `bool operator==(const FShallowWaterCollisionTracker_Actor& Other) const`

#### struct `FShallowWaterCollisionTracker_Direct`  
`struct FShallowWaterCollisionTracker_Direct`  
_L100-113_
- desc: CollisionTracker that directly records the water body affected, used by Impacts
- L102 _public function_ `FShallowWaterCollisionTracker_Direct()`
- L103 _public function_ `FShallowWaterCollisionTracker_Direct(float InTimeSpawned, float InLifespan, TWeakObjectPtr<AWaterBody> InWaterBody) : TimeSpawned(InTimeSpawned), Lifespan(InLifespan), WaterBody(InWaterBody)`
- L107 _public function_ `AWaterBody* GetOverlappingWaterBody() const`
- L108 _public function_ `bool IsValid(const float CurrentTime) const`
- L110 _public member_ `float TimeSpawned = 0;`
- L111 _public member_ `float Lifespan = 10.f;`
- L112 _public member_ `TWeakObjectPtr<AWaterBody> WaterBody = nullptr;`

#### class `UShallowWaterSubsystem`  
`class UShallowWaterSubsystem : public UTickableWorldSubsystem`  
_L117-310_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UTickableWorldSubsystem`
- L122 _public prototype_ `UShallowWaterSubsystem();`
- L123 _public prototype_ `virtual void PostInitialize() override;`
- L124 _public prototype_ `virtual void OnWorldBeginPlay(UWorld& InWorld) override;`
- L125 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L126 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L127 _public prototype_ `virtual TStatId GetStatId() const override;`
- L129 _public prototype_ `virtual void InitializeShallowWater();`
- L136 _public prototype_ `virtual bool IsShallowWaterAllowedToInitialize() const;` — Note: A world subsystem is always created and activated even when the plugin (GFP or not) it resides in is completely disabled When the subclass of this class is a Game Feature Plugin. This can be used to limit when ShallowWater is actually enabled by checking GameFeaturesSubsystem.GetPluginURLByName(PluginName, PluginURL)) and GameFeaturesSubsystem.IsGameFeaturePluginActive(PluginURL, true)
- L137 _public prototype_ `bool IsShallowWaterInitialized() const;`
- L138 _public prototype_ `APawn* GetNonSpectatorPawnFromWeakController() const;`
- L139 _public prototype_ `TOptional<FVector> GetCameraLocationFromWeakController() const;`
- L144 _public prototype_ `APawn* GetTheMostRelevantPlayerPawn() const;` — Think of this as a cursor that in most time locks on the current player pawn If the player doesn't have a physical pawn (e.g. spectating), the cursor jump around and lock on the nearest pawn to the camera If there is no relevant pawn (all eliminate), returns nullptr
- L145 _public function_ `virtual FGameplayTagContainer GetVehicleTags(FShallowWaterCollisionContext Context) const`
- L147 _public prototype_ `void CreateRTs();`
- L148 _public prototype_ `void InitializeParameters();`
- L152 _public prototype_ `void UpdateGridMovement();` — @param WaterBody
- L155 _public prototype_ `void RegisterImpact(FVector ImpactPosition, FVector ImpactVelocity, float ImpactRadius);` — `UFUNCTION(BlueprintCallable, Category = "Shallow Water")`
- L157 _public prototype_ `void FlushPendingImpacts();`
- L158 _public prototype_ `void WriteImpactToNDC(FVector ImpactPosition, FVector ImpactVelocity, float ImpactRadius);`
- L160 _public function_ `virtual ECollisionChannel GetImpactCollisionChannel()` — Override to return the ECC channel of bullets
- L165 _public prototype_ `void SetWaterBodyMIDParameters(AWaterBody* WaterBody);` — `UFUNCTION(BlueprintCallable, Category = "Shallow Water")` — Manually set MID parameters for water bodies before they collide with any pawns or CollisionTrackers
- L167 _public prototype_ `void TryUpdateWaterBodyMIDParameters(UWaterBodyComponent* WaterBodyComponent);`
- L168 _public function_ `float GetGridSize() const`
- L169 _public function_ `int32 GetGridResolution() const`
- L174 _public prototype_ `void RegisterPhysicsAssetProxiesDataAsset(const UShallowWaterPhysicsAssetOverridesDataAsset* Proxies);` — Add PA overrides. Designed to be called by Game Feature Plugins.
- L179 _protected member_ `TObjectPtr<UNiagaraComponent> ShallowWaterNiagaraSimulation;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Shallow Water")` — Asset can be set in Project Settings - Plugins - Water ShallowWaterSimulation
- L190 _protected prototype_ `virtual TSet<AWaterBody*> GetAllOverlappingWaterBodiesAndUpdateCollisionTrackers();` — `UFUNCTION(BlueprintCallable, Category="Shallow Water")` — WaterBody is used for: Get water data texture Get water zone Get character location projected onto water surface Check if character or vehicle is 'in water' @return Should be the the water body touched by the most relevant pawn. If that's not available we try to find water body touched by nearby pawns, sorted by significance.
- L195 _protected prototype_ `void AddCollisionTrackerForActor(AActor* CollisionTrackerActor, float MaxLifespan = 60.f);` — `UFUNCTION(BlueprintCallable, Category="Shallow Water")` — @param MaxLifespan    Max lifespan in case RemoveCollisionTrackerForActor() is not called on tracker destroy, which could causing the sim to keep active indefinitely
- L197 _protected prototype_ `void RemoveCollisionTrackerForActor(AActor* CollisionTrackerActor);` — `UFUNCTION(BlueprintCallable, Category="Shallow Water")`
- L199 _protected prototype_ `virtual TSet<AWaterBody*> GetOverlappingWaterBodiesFromPawns() const;`
- L200 _protected prototype_ `void GetOverlappingWaterBodiesFromActorTrackersAndUpdate(TSet<AWaterBody*>& WaterBodies);`
- L201 _protected prototype_ `void GetOverlappingWaterBodiesFromDirectTrackersAndUpdate(TSet<AWaterBody*>& WaterBodies);`
- L202 _protected prototype_ `void UpdateOverlappingWaterBodiesHistory(TArray<AWaterBody*> OverlappingWaterBodies);`
- L203 _protected prototype_ `bool ShouldSimulateThisFrame() const;`
- L204 _protected prototype_ `void ClearTickCache();`
- L210 _protected member_ `static FName ColliderComponentTag;`
- L213 _protected prototype_ `virtual int32 UpdateActivePawns();` — Override to get most relevant pawns every frame, this also sets up the per-tick cache that is reset with ClearTickCache
- L216 _protected prototype_ `virtual TOptional<FShallowWaterCollisionContext> GetCollisionContextFromPawn(APawn* InPawn) const;` — By default getting the first SKM, if is ACharacter, get 'Mesh' component Override if e.g. The pawn is driving a boat, return SKM of boat instead
- L218 _protected prototype_ `void CleanUpVehicleCollisionProxies();` — Remove invalid references. The owning actor may get destroyed.
- L219 _protected prototype_ `void UpdateCollisionForPendingContexts();`
- L220 _protected prototype_ `void EnableCollisionForContext(const FShallowWaterCollisionContext& Context);`
- L221 _protected prototype_ `void DisableCollisionForContext(const FShallowWaterCollisionContext& Context);`
- L223 _protected prototype_ `void DisableCollisionForVehicle(const FShallowWaterCollisionContext& Context);` — VehicleCollisionProxies is handled inside
- L225 _protected prototype_ `virtual float GetColliderMaxRange() const;`
- L227 _protected prototype_ `virtual TArray<APawn*> GetPawnsInRange(const bool bShouldSortBySignificance = false) const;` — For overriden functions: Do not use GetTheMostRelevantPlayerPawn() inside to avoid loop. Use local controlled pawn location or camera location instead
- L228 _protected prototype_ `virtual TArray<APawn*> GetPawnsInRange(const FVector ObservingLocation, const bool bShouldSortBySignificance = false) const;`
- L233 _protected prototype_ `void SetSimParametersForWaterZone(AWaterZone* WaterZone);` — WaterBody
- L234 _protected prototype_ `bool TryGetOrWaitForWaterInfoTextureFromWaterBody(AWaterBody* CurrentWaterBody);`
- L235 _protected prototype_ `void TryGetOrWaitForWaterInfoTextureFromWaterBodies(TSet<AWaterBody*> CurrentWaterBodies);`
- L237 _protected prototype_ `void OnWaterInfoTextureArrayCreated(const UTextureRenderTarget2DArray* WaterInfoTexture);` — `UFUNCTION()`
- L240 _protected member_ `TWeakObjectPtr<const UTextureRenderTarget2DArray> WaterInfoTexture;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Shallow Water")`
- L242 _protected member_ `TObjectPtr<UTextureRenderTarget2D> NormalRT;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Shallow Water")`
- L244 _protected member_ `TObjectPtr<UTextureRenderTarget2D> VelocityRT;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Shallow Water")`
- L247 _protected member_ `TObjectPtr<UShallowWaterSettings> Settings;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Shallow Water")`
- L249 _protected member_ `TObjectPtr<UMaterialParameterCollection> MPC;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Shallow Water")`
- L253 _protected member_ `TArray<TWeakObjectPtr<APawn>> ActivePawns;` — Consistent record through multiple frames since we want active pawns that affects the fluidsim to remain active Even when it's less significant than newly available pawns. Fluidsim enabled for different pawns each frame is bad.
- L255 _protected member_ `FVector PreviousProjectedLocation = FVector::ZeroVector;`
- L256 _protected member_ `TWeakObjectPtr<APlayerController> WeakPlayerController;`
- L259 _protected member_ `bool bTickCacheValid = false;` — Cached variables only valid during a tick
- L260 _protected member_ `APawn* CachedCursorPawn = nullptr;`
- L261 _protected member_ `TArray<APawn*> CachedPawnsInRange;`
- L262 _protected member_ `TWeakObjectPtr<AWaterBody> BestWaterBody;`
- L265 _private member_ `float LastTimeOverlappingAnyWaterBody = -FLT_MAX;`
- L267 _private member_ `TArray<TWeakObjectPtr<AWaterBody>> LastOverlappingWaterBodies_Internal;` — Should only be managed by UpdateOverlappingWaterBodiesHistory()
- L269 _private member_ `bool bIsShallowWaterInitialized = false;`
- L271 _private member_ `bool bInitializationAsyncLoadsAttempted = false;`
- L273 _private member_ `TSet<TWeakObjectPtr<AWaterZone>> WaterZonesWithMaterialsInitialized;`
- L282 _private member_ `TArray<PendingImpact> PendingImpacts;`
- L283 _private member_ `bool bFlushPendingImpactsNextTick;`
- L285 _private member_ `TSet<TWeakObjectPtr<UWaterBodyComponent>> WaterBodyComponentsWithProperMIDParameters;`
- L286 _private member_ `TArray<TWeakObjectPtr<AWaterBody>> PendingWaterBodiesToSetMIDOnInitialize;`
- L292 _private member_ `TArray<FShallowWaterCollisionContext> PreviousContexts;` — `UPROPERTY()` — Collision Context
- L295 _private member_ `TArray<FShallowWaterCollisionContext> PendingContexts;` — `UPROPERTY()` — 'Pending' also includes contexts already with collision enabled that will be skipped
- L297 _private member_ `TMap<FShallowWaterCollisionContext, TObjectPtr<USkeletalMeshComponent>> VehicleCollisionProxies;` — `UPROPERTY()`
- L299 _private member_ `FTimerHandle WaitForPlayerControllerHandle;`
- L301 _private prototype_ `void OnLocalPlayerControllerBecomesValid(APlayerController* InPlayerController);` — `UFUNCTION()`
- L303 _private prototype_ `void OnLocalPlayerPawnBecomesValid(APawn* OldPawn, APawn* NewPawn);` — `UFUNCTION()`
- L305 _private member_ `TArray<FShallowWaterCollisionTracker_Actor> Tracker_Actors;`
- L306 _private member_ `TArray<FShallowWaterCollisionTracker_Direct> Tracker_Directs;`
- L309 _private member_ `TMap<FGameplayTag, FShallowWaterPhysicsAssetOverride> RegisteredPhysicsAssetProxies;` — Overrides collected from RegisterPhysicsAssetOverridesDataAsset

#### struct `UShallowWaterSubsystem::PendingImpact`  
`struct PendingImpact`  
_L275-280_
- L277 _public member_ `FVector ImpactPosition;`
- L278 _public member_ `FVector ImpactVelocity;`
- L279 _public member_ `float ImpactRadius;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API WATERADVANCED_API`
- L67 _function_ `friend uint32 GetTypeHash(const FShallowWaterCollisionContext& Context)`

### `Plugins/Experimental/WaterAdvanced/Source/WaterAdvanced/Public/WaterAdvanced.h` (Public)


#### class `FWaterAdvancedModule`  
`class FWaterAdvancedModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
