# Plugins / PPMChainGraph

- module root: `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraph`
- headers: 6; symbols: 82
- symbol kinds: class=6, delegate=1, enum=4, enumerator=15, function=3, member=29, prototype=21, struct=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Projects, RHI, RenderCore, Renderer, Slate, SlateCore, UnrealEd

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraph/Private/PPMChainGraphSceneViewExtension.h` (Private)


#### class `FPPMChainGraphSceneViewExtension`  
`class FPPMChainGraphSceneViewExtension : public FSceneViewExtensionBase`  
_L12-34_
- inherits: `FSceneViewExtensionBase`
- desc: Scene View Extension responsible for going through all PPM Chain Graph Components and rendering graphs into scene color.
- L15 _public prototype_ `FPPMChainGraphSceneViewExtension(const FAutoRegister& AutoRegister, UPPMChainGraphWorldSubsystem* InWorldSubsystem);`
- L18 _public prototype_ `virtual void SubscribeToPostProcessingPass(EPostProcessingPass PassId, const FSceneView& View, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled) override;`
- L20 _public prototype_ `virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;`
- L21 _public prototype_ `FScreenPassTexture AfterPostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, FPostProcessMaterialInputs& InOutInputs, EPostProcessingPass InCurrentPass, const TArray<TSharedPtr<FPPMChainGraphProxy>>& OutChainGraphProxies);`
- L23 _public function_ `virtual void PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override`
- L29 _private prototype_ `void GatherChainGraphProxies(TArray<TSharedPtr<FPPMChainGraphProxy>>& OutChainGraphProxies, const FSceneView& InView, const FSceneViewFamily& InViewFamily, EPPMChainGraphExecutionLocation InPointOfExecution);`
- L32 _private member_ `const FSceneView* CachedView = nullptr;`
- L33 _private member_ `TWeakObjectPtr<UPPMChainGraphWorldSubsystem> WorldSubsystem;`

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraph/Private/PPMChainGraphWorldSubsystem.h` (Private)


#### class `UPPMChainGraphWorldSubsystem`  
`class UPPMChainGraphWorldSubsystem : public UTickableWorldSubsystem`  
_L23-66_
- reflection: `UCLASS()`
- inherits: `UTickableWorldSubsystem`
- desc: World subsystem that is responsible for gathering and keeping track of PPM Chain Graph components.
- L29 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — Subsystem Init/Deinit
- L30 _public prototype_ `virtual void Deinitialize() override;`
- L32 _public function_ `virtual bool IsTickableInEditor() const`
- L33 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L36 _public function_ `virtual TStatId GetStatId() const override` — For profiling.
- L39 _public prototype_ `void AddPPMChainGraphComponent(TWeakObjectPtr<UPPMChainGraphExecutorComponent> InComponent);` — Adds a PPM Chain Graph component to the list of components to potentially be rendered.
- L42 _public prototype_ `void RemovePPMChainGraphComponent(TWeakObjectPtr<UPPMChainGraphExecutorComponent> InComponent);` — Removes a PPM Chain Graph component. Typically this means that the component is removed from the world.
- L45 _private prototype_ `void GatherActivePasses();` — Populates Active passes set to be used by SVE to subscribe to the active passes.
- L48 _private member_ `TSharedPtr<class FPPMChainGraphSceneViewExtension, ESPMode::ThreadSafe> SceneViewExtension;`
- L50 _private member_ `FCriticalSection ComponentAccessCriticalSection;`
- L55 _private member_ `TSet<TWeakObjectPtr<UPPMChainGraphExecutorComponent>> PPMChainGraphComponents;` — All active chain graph components currently present in associated world.
- L60 _private member_ `TSet<uint32> ActivePasses;` — Aggregation of active passes, so that Scene View Extension knows to which passes to subscribe. uint32 value Reflects EPPMChainGraphExecutionLocation
- L62 _private member_ `FCriticalSection ActiveAccessCriticalSection;`

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraph/Public/PPMChainGraph.h` (Public)


#### enum `EPPMChainGraphPPMInputId`  
`enum class EPPMChainGraphPPMInputId : uint8`  
_L16-25_
- reflection: `UENUM()`
- L18 _public enumerator_ `PPMInputMaping_Unassigned UMETA(DisplayName = "Unassigned")`
- L20 _public enumerator_ `PPMInputMaping_0 UMETA(DisplayName = "PostProcessInput0")` — Map to equivalent input in Scene Textures node in the material.
- L21 _public enumerator_ `PPMInputMaping_1 UMETA(DisplayName = "PostProcessInput1")`
- L22 _public enumerator_ `PPMInputMaping_2 UMETA(DisplayName = "PostProcessInput2")`
- L23 _public enumerator_ `PPMInputMaping_3 UMETA(DisplayName = "PostProcessInput3")`
- L24 _public enumerator_ `PPMInputMaping_4 UMETA(DisplayName = "PostProcessInput4")`

#### enum `EPPMChainGraphOutput`  
`enum class EPPMChainGraphOutput : uint8`  
_L29-42_
- reflection: `UENUM()`
- L34 _public enumerator_ `PPMOutput_SceneColor UMETA(DisplayName = "Write Back into Scene Color")` — Write back into Scene Color.
- L40 _public enumerator_ `PPMOutput_RenderTarget UMETA(DisplayName = "Temporary Render Target")` — Writes into a temporary render target to be used later in the chain. Users need to provide the name for the render target for future identification.

#### enum `EPPMChainGraphExecutionLocation`  
`enum class EPPMChainGraphExecutionLocation : uint8`  
_L46-59_
- reflection: `UENUM()`
- L49 _public enumerator_ `PrePostProcess UMETA(DisplayName = "Before Post Processing")` — Default place of execution right before the rest of post processing starts.
- L55 _public enumerator_ `AfterMotionBlur = 2 UMETA(DisplayName = "After Motion Blur")` — SSR Input isn't supported. AfterSSRInput				UMETA(DisplayName = "After SSR Input"), This is eventually mapped to equivalent execution location enum: ISceneViewExtension::EPostProcessingPass.
- L56 _public enumerator_ `AfterToneMap UMETA(DisplayName = "After Tonemap")`
- L57 _public enumerator_ `AfterFXAA UMETA(DisplayName = "After FXAA")`
- L58 _public enumerator_ `AfterVisualizeDepthOfField UMETA(DisplayName = "After Visualize Depth of Field")`

#### struct `FPPMChainGraphInput`  
`struct FPPMChainGraphInput`  
_L66-72_
- reflection: `USTRUCT(BlueprintType)`
- desc: This struct is used for customizing Input and External Texture input selection.
- L71 _public member_ `FString InputId;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)`

#### struct `FPPMChainGraphPostProcessPass`  
`struct FPPMChainGraphPostProcessPass`  
_L76-106_
- reflection: `USTRUCT(Blueprintable)`
- L82 _public member_ `bool bEnabled = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Pass Settings")` — Is pass enabled.
- L86 _public member_ `TMap<EPPMChainGraphPPMInputId, FPPMChainGraphInput> Inputs;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Post Process Pass Inputs")` — Inputs from previous passes. Map this to Scene Texture node in Post Process Material.
- L92 _public member_ `TObjectPtr<UMaterial> PostProcessMaterial;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Post Process Pass Material")` — Which material should be executed during this pass.
- L101 _public member_ `EPPMChainGraphOutput Output = EPPMChainGraphOutput::PPMOutput_SceneColor;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Post Process Pass Output")` — Where should this pass write to. By selecting Temporary Render Target as an option, Users can avoid writing directly into Scene Color. For example this pass can operate on textures other than Scene Color to be used in one of the later passes. Keep in mind that the final pass will always write back into Scene Color.
- L105 _public member_ `FString TemporaryRenderTargetId;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Post Process Pass Output", meta = (EditCondition = "Output == EPPMChainGraphOutput::PPMOutput_RenderTarget", EditConditionHides))` — Use this to identify the Output of the current pass to be used later.

#### class `UPPMChainGraph`  
`class UPPMChainGraph : public UObject`  
_L115-143_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Post Process Material Chain Graph"))`
- inherits: `UObject`
- desc: Post Process Material Chain Graph defines a collection of Post Process Material of passes that are executed one after another. Individual passes can write into Scene Color or Temporary render target, but at the end of chain graph the combined result is always written into Scene Color.
- L121 _public prototype_ `UPPMChainGraph(const FObjectInitializer& ObjectInitializer);`
- L129 _public member_ `EPPMChainGraphExecutionLocation PointOfExecution;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Graph Execution Settings")` — Identifies at which point of post processing this graph is going to be executed. These are different to the setting in Post Process Material.
- L135 _public member_ `TMap<FString, TObjectPtr<UTexture2D>> ExternalTextures;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "External Inputs")` — External textures and rendertargets that can be mapped to Scene Texture Inputs.
- L142 _public member_ `TArray<FPPMChainGraphPostProcessPass> Passes;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Post Process Passes", meta = (TitleProperty = "TemporaryRenderTargetId"))` — Post Process Material Passes. Each pass can write into the Scene Color or into a temporary render target that can be referenced in subsequent passes. At the end of all passes the result is always written into Scene Color.

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraph/Public/PPMChainGraphActor.h` (Public)


#### class `APPMChainGraphActor`  
`class APPMChainGraphActor : public AActor`  
_L12-27_
- reflection: `UCLASS(Blueprintable, meta = (DisplayName = "Post Process Material Chain Graph Actor"))`
- inherits: `AActor`
- L17 _public member_ `TObjectPtr<UPPMChainGraphExecutorComponent> PPMChainGraphExecutorComponent;` — `UPROPERTY(Category = MediaPlate, VisibleAnywhere, BlueprintReadOnly)`
- L23 _public member_ `TObjectPtr<class UBillboardComponent> SpriteComponent;` — `UPROPERTY(Transient)` — Billboard component for this actor.

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraph/Public/PPMChainGraphComponent.h` (Public)


#### struct `FPPMChainGraphProxy`  
`struct FPPMChainGraphProxy`  
_L15-22_
- L17 _public member_ `TObjectPtr<ACameraActor> CameraOwner;`
- L19 _public member_ `EPPMChainGraphExecutionLocation PointOfExecution;`
- L20 _public member_ `TMap<FString, TObjectPtr<UTexture2D>> ExternalTextures;`
- L21 _public member_ `TArray<TSharedPtr<FPPMChainGraphPostProcessPass>> Passes;`

#### enum `ECameraViewHandling`  
`enum class ECameraViewHandling : uint8`  
_L25-29_
- reflection: `UENUM()`
- L27 _public enumerator_ `IgnoreCameraViews UMETA(DisplayName = "Ignore Selected Camera Views")`
- L28 _public enumerator_ `RenderOnlyInSelectedCameraViews UMETA(DisplayName = "Render Only In Selected Camera Views")`

#### class `UPPMChainGraphExecutorComponent`  
`class UPPMChainGraphExecutorComponent : public USceneComponent`  
_L32-83_
- reflection: `UCLASS(hidecategories = (Transform, Collision, Object, Physics, SceneComponent, PostProcessVolume, Projection, Rendering, PlanarReflection), ClassGroup = Rendering, editinlinenew, meta = (BlueprintSpawnableComponent, DisplayName = "Post Process Material Chain Graph Executor Component"))`
- inherits: `USceneComponent`
- L36 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L37 _public prototype_ `virtual void BeginDestroy() override;`
- L42 _public prototype_ `TArray<TSharedPtr<FPPMChainGraphProxy>> GetChainGraphRenderProxies(EPPMChainGraphExecutionLocation InPointOfExecution);` — Get a copy of Render Proxies for rendering graphs.
- L45 _public prototype_ `bool IsActiveDuringPass_GameThread(EPPMChainGraphExecutionLocation InPointOfExecution);` — Identifies if this component needs to render during the specified pass.
- L50 _public member_ `ECameraViewHandling CameraViewHandlingMode = ECameraViewHandling::IgnoreCameraViews;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera View Settings")` — PPM Chain Graph Component can either exclude selected cameras from being rendered or render only in selected camera views.
- L58 _public member_ `TArray<TSoftObjectPtr<ACameraActor>> CameraList;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera View Settings")` — Depending on the selection in the option above the following cameras will either: 1. Be ignored and will not get PPM Chain Graph rendered into. 2. Or rendered only in selected camera views.
- L62 _public member_ `TArray<TObjectPtr<UPPMChainGraph>> PPMChainGraphs;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Post Process Material Chain Graphs")` — A list of graphs to be executed.
- L66 _private prototype_ `void TransferState();` — Transfers the render state on game thread.
- L69 _private prototype_ `void ProcessWarnings();` — Process aggregated warnings and notify the user.
- L73 _private member_ `FCriticalSection StateTransferCriticalSection;` — Critical section for tranfering state for rendering.
- L76 _private member_ `TWeakObjectPtr<UPPMChainGraphWorldSubsystem> PPMChainGraphSubsystem;` — Reference to the subsystem to add or remove this component to the list of Graphs to be considered.
- L79 _private member_ `TMap<EPPMChainGraphExecutionLocation, TArray<TSharedPtr<FPPMChainGraphProxy>>> PPMChainGraphsRenderProxies;` — Populated on Game thread and used on Render thread for thread safety. Stored against the location of execution.
- L82 _private member_ `TSharedPtr<void> AggregatedWarnings;` — Collects warnings notifying users of invalid data in graphs or issues with ComponentAttachement.

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPPMChainGraph, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPPMChainGraph, Log, All);`

### `Plugins/Experimental/PostProcessMaterialChainGraph/Source/PostProcessMaterialChainGraph/Public/PPMChainGraphModule.h` (Public)


#### class `FPostProcessMaterialChainGraphModule`  
`class FPostProcessMaterialChainGraphModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
