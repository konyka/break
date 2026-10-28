# Plugins / ModularViewports

- module root: `Plugins/Runtime/ModularViewports/Source/ModularViewports`
- headers: 8; symbols: 105
- symbol kinds: class=7, function=11, macro=8, member=24, namespace=7, prototype=48
- PrivateDependencyModuleNames: UnrealEd

### `Plugins/Runtime/ModularViewports/Source/ModularViewports/Public/Camera/CameraViewportClient.h` (Public)


#### class `UE::FCameraViewportClient`  
`class FCameraViewportClient : public FGameplayViewportClient, public FGCObject`  
_L20-80_
- inherits: `FGameplayViewportClient,FGCObject`
- desc: A Viewport Client that renders a single UCameraComponent.
- L22 _private member_ `TWeakObjectPtr<const UCameraComponent> Camera;`
- L23 _private member_ `TWeakObjectPtr<UWorld> ViewStateWorld;`
- L24 _private member_ `FSceneViewStateReference ViewState;`
- L25 _private member_ `ETouchEventFamilies EnabledTouchEventFamilies;`
- L26 _private member_ `ECollisionChannel TouchTraceChannel;`
- L27 _private member_ `float TouchTraceDistance;`
- L28 _private member_ `TWeakObjectPtr<UPrimitiveComponent> TouchedPrimitives[EKeys::NUM_TOUCH_KEYS];`
- L31 _public prototype_ `FCameraViewportClient( const UCameraComponent&, ETouchEventFamilies EnabledTouchEventFamilies = ETouchEventFamilies::All, ECollisionChannel TouchTraceChannel = ECC_Visibility, float TouchTraceDistance = 100000.0f);`
- L37 _public function_ `ECollisionChannel GetTouchTraceChannel() const`
- L42 _public function_ `float GetTouchTraceDistance() const`
- L47 _public function_ `const TWeakObjectPtr<const UCameraComponent>& GetCameraComponent() const`
- L56 _public prototype_ `void CalculateProjectionData(const FViewport& Viewport, FSceneViewProjectionData& OutProjectionData) const;` — Extracts projection data (view rect, rotation matrix, projection matrix) from the camera. Only safe to call within GC Lock.
- L59 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L60 _public prototype_ `virtual FString GetReferencerName() const override;`
- L64 _public prototype_ `virtual UWorld* GetWorld() const override;` — FViewportClient interface
- L65 _public prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;`
- L66 _public prototype_ `virtual bool InputTouch(FViewport* const Viewport, const FTouchId TouchId, const ETouchType::Type Type, const FVector2D& TouchLocation, const float Force, const uint64 Timestamp) override;`
- L71 _protected function_ `void SetTouchTraceChannel(ECollisionChannel InTouchTraceChannel)`
- L76 _protected function_ `void SetTouchTraceDistance(float InTouchTraceDistance)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MODULARVIEWPORTS_API`
- L17 _namespace_ `namespace UE`

### `Plugins/Runtime/ModularViewports/Source/ModularViewports/Public/Components/SceneViewportWidget.h` (Public)


#### class `USceneViewport`  
`class USceneViewport final : public UWidget`  
_L25-114_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWidget`
- desc: UMG wrapper around SViewport + FSceneViewport, which allows you to compose Viewport Clients (e.g. Game Viewport Client) as Slate Widgets. Provides properties/functions for setting up with a GameInstance, Camera, or Player.
- L35 _private member_ `TSoftObjectPtr<UWorld> AutoLoadWorldAsset;` — `UPROPERTY(EditAnywhere, Category = "Viewport")` — This world will be automatically spawned and bound to this widget upon initialization.  If null, the viewport will be blank until a "Show..." function is called.
- L43 _private member_ `uint8 bRenderDirectlyToWindow : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport")` — The Viewport Client will draw directly to the SWindow's backbuffer, skipping Slate composition. Improves performance for real-time clients, but does not allow Slate-level effects to be applied to this widget, and may cause wrong z-order. If this is true and the client early-exits from Draw, the previously rendered frame will not persist.
- L47 _private member_ `uint8 bEnableGammaCorrection : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport", meta = (EditCondition = "!bRenderDirectlyToWindow"))` — Whether or not to enable gamma correction. Doesn't apply when rendering directly to a backbuffer.
- L51 _private member_ `uint8 bReverseGammaCorrection : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport", meta = (EditCondition = "!bRenderDirectlyToWindow"))` — Whether or not to reverse the gamma correction done to the texture in this viewport.  Ignores the bEnableGammaCorrection setting
- L55 _private member_ `uint8 bEnableBlending : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport", meta = (EditCondition = "!bRenderDirectlyToWindow"))` — Allow this viewport to blend with its background.
- L59 _private member_ `uint8 bPreMultipliedAlpha : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport", meta = (EditCondition = "!bRenderDirectlyToWindow"))` — True if the viewport texture has pre-multiplied alpha
- L66 _private member_ `uint8 bIgnoreTextureAlpha : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport", meta = (EditCondition = "!bRenderDirectlyToWindow"))` — If true, the viewport's texture alpha is ignored when performing blending.  In this case only the viewport tint opacity is used If false, the texture alpha is used during blending
- L69 _private member_ `TSharedPtr<SViewport> ViewportWidget;` — The primary SWidget that this UWidget represents.
- L75 _private member_ `TStrongPtrVariant<FViewportClient> Client;` — The currently bound viewport client. FSceneViewport also holds this strongly once Bind() runs, so this field's job is to carry the binding intent between BindGame/BindCamera and a later Bind() (Bind can be deferred when the viewport widget hasn't been built yet). By contract, a UObject-backed variant here is always a UGameViewportClient.
- L78 _private member_ `TUniquePtr<UE::Engine::FAuxiliaryGameInstance> GameInstanceAssembly;` — Stores a Game Instance that is created from AutoLoadWorldAsset (not relevant for ShowGame).
- L80 _private member_ `TSharedPtr<FSceneViewport> SceneViewport;`
- L83 _private prototype_ `USceneViewport(const FObjectInitializer&);`
- L87 _public prototype_ `UGameInstance* GetInnerGameInstance() const;` — `UFUNCTION(BlueprintPure, Category = "MultiWorld")` — If the Auto Load World Asset property of this widget was specified, returns the Game Instance which was spawned as a result.
- L89 _public prototype_ `void ShowGame(const TSoftObjectPtr<UWorld>& Asset);`
- L91 _public prototype_ `void ShowCamera(const UCameraComponent&);`
- L93 _public prototype_ `void ShowPlayer(ULocalPlayer&);`
- L95 _public prototype_ `void Unbind();`
- L99 _private prototype_ `virtual void BeginDestroy() override;` — UObject
- L103 _private prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;` — UVisual
- L108 _private prototype_ `virtual const FText GetPaletteCategory() override;`
- L110 _private prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;`
- L113 _private prototype_ `void Bind();`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MODULARVIEWPORTS_API`

### `Plugins/Runtime/ModularViewports/Source/ModularViewports/Public/Engine/AuxiliaryGameInstance.h` (Public)


#### class `UE::Engine::FAuxiliaryGameInstance`  
`class FAuxiliaryGameInstance final : public FNoncopyable`  
_L32-66_
- inherits: `FNoncopyable`
- desc: Instantiates a given World within a new Game Instance.  Destroying this object will shut down and destroy both. Works across both PIE and non-editor. Use for spatially discontiguous picture-in-picture, second window content, or other multi-tenant scenarios. Produces a "headless" world.  To create players, you must first associate it with a viewport-client.  To spawn player-controllers, you must first associate it with a viewport. Note: BeginPlay is called immediately, *before* any players exist.  This is different from the primary game instance's standalone behavior (but will be familiar to anyone who has developed multiplayer games).  Actors in the world will find that the Player Controller doesn't exist yet on Begin Play.  Getting the Player Controller on BeginPlay is an anti-practice anyhow.  If you put input-binding code in the Player Controller (where it belongs) and use proper abstractions + event-driven orchestration, this will not be a problem. Does NOT support: - In-editor but NOT from-PIE (i.e. from custom editor tools) - Networking/replication - Travel - Multiple instances of the same world asset
- L34 _private member_ `TStrongObjectPtr<UGameInstance> GameInstance;`
- L37 _private member_ `FDelegateHandle EndPIEHandle;`
- L41 _public prototype_ `static TUniquePtr<FAuxiliaryGameInstance> MakeUnique(const TSoftObjectPtr<UWorld>& Asset);`
- L42 _public prototype_ `static TSharedPtr<FAuxiliaryGameInstance> MakeShared(const TSoftObjectPtr<UWorld>& Asset);`
- L44 _private prototype_ `static FAuxiliaryGameInstance* Make(const TSoftObjectPtr<UWorld>& Asset);`
- L46 _private prototype_ `explicit FAuxiliaryGameInstance(UGameInstance&);`
- L53 _private prototype_ `void Teardown();` — Tear down the World, Game Instance, and World Context that this object owns. Idempotent — a second call returns immediately.  Callable from either the destructor or the FEditorDelegates::EndPIE handler.
- L55 _public prototype_ `~FAuxiliaryGameInstance();`
- L57 _public function_ `UGameInstance* GetGameInstance() const`
- L62 _public function_ `UWorld* GetWorld() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODULARVIEWPORTS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Engine` (scope `UE`)

### `Plugins/Runtime/ModularViewports/Source/ModularViewports/Public/Engine/AuxiliaryGameInstanceObject.h` (Public)


#### class `UAuxiliaryGameInstance`  
`class UAuxiliaryGameInstance : public UObject`  
_L22-42_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: UObject wrapper around UE::Engine::FAuxiliaryGameInstance. Lets Blueprint and other UFUNCTION-only APIs hold an FAuxiliaryGameInstance via a regular UObject reference; the wrapped FAuxiliaryGameInstance is destroyed when this UObject is garbage-collected.
- L26 _private member_ `TUniquePtr<UE::Engine::FAuxiliaryGameInstance> Inner;`
- L30 _public prototype_ `static UAuxiliaryGameInstance* Make(const TSoftObjectPtr<UWorld>& Asset);` — Creates a new wrapper that owns a fresh FAuxiliaryGameInstance for the given world asset.
- L32 _public function_ `UE::Engine::FAuxiliaryGameInstance* Get() const`
- L38 _public prototype_ `UGameInstance* GetGameInstance() const;` — `UFUNCTION(BlueprintPure, Category = "AuxiliaryGameInstance")`
- L40 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L41 _public prototype_ `virtual void BeginDestroy() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODULARVIEWPORTS_API`

### `Plugins/Runtime/ModularViewports/Source/ModularViewports/Public/Engine/AuxiliaryGameViewportClient.h` (Public)


#### class `UAuxiliaryGameViewportClient`  
`class UAuxiliaryGameViewportClient : public UGameViewportClient`  
_L17-23_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameViewportClient`
- desc: Game viewport client used by FAuxiliaryGameInstance. Spawns player actor in response to viewport being attached.
- L22 _public prototype_ `virtual void AddAssociation(FViewport& InViewport) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MODULARVIEWPORTS_API`

### `Plugins/Runtime/ModularViewports/Source/ModularViewports/Public/GameFramework/PlayerViewportClient.h` (Public)


#### class `UE::Engine::UPlayerViewportClient`  
`class UPlayerViewportClient : public UScriptViewportClient`  
_L25-75_
- reflection: `UCLASS(transient, MinimalAPI)`
- inherits: `UScriptViewportClient`
- desc: A Viewport Client that renders a single ULocalPlayer using their camera manager. Halfway between FCameraViewportClient (raw camera, no input) and UGameViewportClient (all players, split-screen). Routes input to the player's controller. Must be constructed via the static Create() factory — direct NewObject<> construction trips an ensure.
- L29 _private member_ `TWeakObjectPtr<ULocalPlayer> Player;`
- L30 _private member_ `bool bFilterInputByPlayer = false;`
- L33 _public prototype_ `UPlayerViewportClient(const FObjectInitializer& ObjectInitializer);`
- L39 _public prototype_ `static UPlayerViewportClient* Create(ULocalPlayer& Player, UObject* Outer = nullptr);` — Creates a UPlayerViewportClient bound to Player.  Returns nullptr if Player is already associated with a non-GameViewportClient viewport client.
- L41 _public function_ `const TWeakObjectPtr<ULocalPlayer>& GetLocalPlayer() const`
- L49 _public function_ `void SetFilterInputByPlayer(bool bFilter)` — When true, gamepad input from devices assigned to other players is ignored. Mouse, keyboard, and touch input always passes through regardless of this setting.
- L54 _public function_ `bool GetFilterInputByPlayer() const`
- L60 _public prototype_ `virtual void BeginDestroy() override;` — UObject interface
- L64 _public prototype_ `virtual UWorld* GetWorld() const override;` — FViewportClient interface
- L65 _public prototype_ `virtual void Draw(FViewport* Viewport, FCanvas* Canvas) override;`
- L66 _public prototype_ `virtual EMouseCursor::Type GetCursor(FViewport* Viewport, int32 X, int32 Y) override;`
- L67 _public prototype_ `virtual bool RequiresUncapturedAxisInput() const override;`
- L68 _public prototype_ `virtual void LostFocus(FViewport* Viewport) override;`
- L69 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L70 _public prototype_ `virtual bool InputAxis(const FInputKeyEventArgs& Args) override;`
- L71 _public prototype_ `virtual bool InputTouch(FViewport* const Viewport, const FTouchId TouchId, const ETouchType::Type Type, const FVector2D& TouchLocation, const float Force, const uint64 Timestamp) override;`
- L72 _public prototype_ `virtual bool InputMotion(FViewport* Viewport, const FInputDeviceId DeviceId, const FVector& Tilt, const FVector& RotationRate, const FVector& Gravity, const FVector& Acceleration, const uint64 Timestamp) override;`
- L73 _public prototype_ `virtual bool InputGesture(FViewport* Viewport, const FInputDeviceId DeviceId, EGestureEvent GestureType, EGesturePhase GesturePhase, const FVector2D& GestureDelta, bool bIsDirectionInvertedFromDevice, const uint64 Timestamp) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MODULARVIEWPORTS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Engine` (scope `UE`)

### `Plugins/Runtime/ModularViewports/Source/ModularViewports/Public/ModularViewportsSettings.h` (Public)


#### class `UModularViewportsSettings`  
`class UModularViewportsSettings : public UDeveloperSettings`  
_L16-24_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, meta = (DisplayName = "Modular Viewports"))`
- inherits: `UDeveloperSettings`
- desc: Project settings for the ModularViewports plugin.
- L23 _public member_ `TSubclassOf<UAuxiliaryGameViewportClient> AuxiliaryGameInstanceClass;` — `UPROPERTY(config, EditAnywhere, Category = "Modular Viewports", meta = (MetaClass = "/Script/ModularViewports.AuxiliaryGameViewportClient"))` — Default viewport-client class instantiated for each FAuxiliaryGameInstance.  Performs player setup in its Bind override.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MODULARVIEWPORTS_API`

### `Plugins/Runtime/ModularViewports/Source/ModularViewports/Public/ViewportFunctions.h` (Public)


#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MODULARVIEWPORTS_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Engine` (scope `UE`)
- L25 _prototype_ `TUniquePtr<FSceneViewFamilyContext> MakeGameplayViewFamily(const FViewport& Viewport, const UWorld& World);` (scope `UE::Engine`) — Creates a view family with typical defaults for rendering Game Instance content. Sets up a realtime FSceneViewFamilyContext with engine show flag overrides, HDR viewport state, and a default screen percentage driver.
- L28 _prototype_ `bool TryRenderViewFamily(FSceneViewFamilyContext& ViewFamily, FCanvas& Canvas);` (scope `UE::Engine`) — Renders the given view family to the given canvas using the renderer module (if allowed).
- L34 _prototype_ `SWindow::FArguments ExactPositionWindow(const FVector2f& Position, SWindow::FArguments&& Arguments = SWindow::FArguments());` (scope `UE::Engine`) — Produces SWindow parameters that ensure a specific placement. Use it like: `SArgumentsNew(ExactLocationWindow(FVector2f(100, 100)), SWindow).OtherParam(...)[ Child ]`
- L40 _prototype_ `SWindow::FArguments FixedSizeWindow(FVector2f Size, SWindow::FArguments&& Arguments = SWindow::FArguments());` (scope `UE::Engine`) — Produces SWindow parameters ideal for a fixed-size window. Use it like: `SArgumentsNew(FixedSizeWindow(FVector2f(800, 600)), SWindow).OtherParam(...)[ Child ]`
- L46 _prototype_ `SWindow::FArguments NoControlsWindow(SWindow::FArguments&& Arguments = SWindow::FArguments());` (scope `UE::Engine`) — Produces an SWindow with no exit/minimize/maximize buttons Use it like: `SArgumentsNew(NoControlsWindow(), SWindow).OtherParam(...)[ Child ]`
- L55 _prototype_ `TSharedRef<FSceneViewport> SetupRendering(const TStrongPtrVariant<FViewportClient>& Client, const TSharedRef<SViewport>& ViewportWidget);` (scope `UE::Engine`) — Sets up the FViewportClient to render into the SViewport by creating a FSceneViewport, and performing the typical boilerplate setup steps. - Matches the FSceneViewport's size to that of the given SViewport. - Makes this the SViewport's parent window's primary viewport, unless it does not yet belong to a window, or the window's primary viewport is already set. - Registers the FViewport with GEngine to be drawn every frame.
