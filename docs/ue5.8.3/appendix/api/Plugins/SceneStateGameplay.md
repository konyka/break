# Plugins / SceneStateGameplay

- module root: `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplay`
- headers: 5; symbols: 46
- symbol kinds: class=4, function=4, macro=4, member=5, namespace=3, prototype=24, struct=1, variable=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, SceneState

### `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplay/Private/SceneStateComponentInstanceData.h` (Private)


#### struct `FSceneStateComponentInstanceData`  
`struct FSceneStateComponentInstanceData : public FActorComponentInstanceData`  
_L12-36_
- reflection: `USTRUCT()`
- inherits: `FActorComponentInstanceData`
- L16 _public function_ `FSceneStateComponentInstanceData() : SceneStatePlayer(nullptr)`
- L21 _public prototype_ `explicit FSceneStateComponentInstanceData(const USceneStateComponent* InSourceComponent);`
- L23 _public function_ `USceneStateComponentPlayer* GetSceneStatePlayer() const`
- L29 _public prototype_ `virtual bool ContainsData() const override;`
- L30 _public prototype_ `virtual void ApplyToComponent(UActorComponent* InComponent, const ECacheApplyPhase InCacheApplyPhase) override;`
- L31 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L35 _private member_ `TObjectPtr<USceneStateComponentPlayer> SceneStatePlayer;`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplay/Public/SceneStateActor.h` (Public)


#### class `ASceneStateActor`  
`class ASceneStateActor : public AActor`  
_L14-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L19 _public member_ `static const FLazyName SceneStateComponentName;`
- L21 _public prototype_ `ASceneStateActor(const FObjectInitializer& InObjectInitializer);`
- L23 _public function_ `USceneStateComponent* GetSceneStateComponent() const`
- L28 _public prototype_ `void SetSceneStateClass(TSubclassOf<USceneStateObject> InSceneStateClass);`
- L30 _public prototype_ `TSubclassOf<USceneStateObject> GetSceneStateClass() const;`
- L33 _public prototype_ `USceneStateObject* GetSceneState() const;` — `UFUNCTION(BlueprintCallable, Category = "Scene State")`
- L37 _private member_ `TObjectPtr<USceneStateComponent> SceneStateComponent;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Scene State", meta=(AllowPrivateAccess="true"))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEGAMEPLAY_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplay/Public/SceneStateComponent.h` (Public)


#### class `USceneStateComponent`  
`class USceneStateComponent : public UActorComponent`  
_L15-50_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L20 _public member_ `static const FLazyName SceneStatePlayerName;`
- L22 _public prototype_ `USceneStateComponent(const FObjectInitializer& InObjectInitializer);`
- L24 _public function_ `USceneStateComponentPlayer* GetSceneStatePlayer() const`
- L29 _public prototype_ `TSubclassOf<USceneStateObject> GetSceneStateClass() const;`
- L31 _public prototype_ `void SetSceneStateClass(TSubclassOf<USceneStateObject> InSceneStateClass);`
- L34 _public prototype_ `USceneStateObject* GetSceneState() const;` — `UFUNCTION(BlueprintCallable, Category = "Scene State")`
- L36 _public prototype_ `void ApplyComponentInstanceData(FSceneStateComponentInstanceData* InComponentInstanceData);`
- L39 _public prototype_ `virtual void InitializeComponent() override;`
- L40 _public prototype_ `virtual void OnRegister() override;`
- L41 _public prototype_ `virtual void BeginPlay() override;`
- L42 _public prototype_ `virtual void TickComponent(float InDeltaTime, ELevelTick InTickType, FActorComponentTickFunction* InThisTickFunction) override;`
- L43 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type InEndPlayReason) override;`
- L44 _public prototype_ `virtual TStructOnScope<FActorComponentInstanceData> GetComponentInstanceData() const override;`
- L49 _private member_ `TObjectPtr<USceneStateComponentPlayer> SceneStatePlayer;` — `UPROPERTY(VisibleAnywhere, Instanced, Category="Scene State", meta=(ShowInnerProperties))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEGAMEPLAY_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplay/Public/SceneStateComponentPlayer.h` (Public)


#### class `USceneStateComponentPlayer`  
`class USceneStateComponentPlayer : public USceneStatePlayer`  
_L15-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USceneStatePlayer`
- desc: Scene State Player for Scene State Components
- L20 _protected prototype_ `AActor* GetActor() const;`
- L23 _protected prototype_ `virtual bool OnGetContextName(FString& OutContextName) const override;`
- L24 _protected prototype_ `virtual bool OnGetContextObject(UObject*& OutContextObject) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SCENESTATEGAMEPLAY_API`

### `Plugins/VirtualProduction/SceneState/Source/SceneStateGameplay/Public/SceneStateGameplaySchema.h` (Public)


#### class `USceneStateGameplaySchema`  
`class USceneStateGameplaySchema : public USceneStateSchema`  
_L24-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USceneStateSchema`
- desc: Schema for scene states played via the Scene State Component / Actor context
- L31 _protected prototype_ `virtual bool OnIsTaskStructAllowed(TSubScriptStructOf<FSceneStateTask> InTaskStruct) const override;`
- L33 _protected prototype_ `virtual TSubclassOf<UObject> OnGetContextObjectClass() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SCENESTATEGAMEPLAY_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace SceneState` (scope `UE`)
- L12 _namespace_ `namespace Editor` (scope `UE::SceneState`)
- L18 _variable_ `const FLazyName MD_GameplayTask(TEXT("Game` (scope `UE::SceneState::Editor`) — Metadata to identify a task as a gameplay task Derived tasks will NOT be recognized as 'GameplayTask' unless they also specify this metadata.
