# Plugins / AvalancheDataLink

- module root: `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLink`
- headers: 6; symbols: 40
- symbol kinds: class=4, delegate=1, function=2, macro=1, member=13, prototype=17, struct=2
- PrivateDependencyModuleNames: Avalanche, DataLinkJson, Engine, Json, JsonUtilities, PropertyBindingUtils, RemoteControl, RemoteControlLogic
- PublicDependencyModuleNames: AvalancheRemoteControl, Core, CoreUObject, DataLink

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLink/Private/AvaDataLinkLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaDataLink, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaDataLink, Log, All);`

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLink/Private/AvaDataLinkProcessor.h` (Private)


#### class `UAvaDataLinkProcessor`  
`class UAvaDataLinkProcessor : public UDataLinkProcessor`  
_L11-17_
- reflection: `UCLASS(Abstract)`
- inherits: `UDataLinkProcessor`
- L16 _protected prototype_ `IAvaSceneInterface* GetSceneInterface() const;`

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLink/Private/RemoteControl/AvaDataLinkRCProcessor.h` (Private)


#### class `UAvaDataLinkRCProcessor`  
`class UAvaDataLinkRCProcessor : public UAvaDataLinkProcessor`  
_L15-42_
- reflection: `UCLASS(DisplayName="Motion Design Data Link Remote Control Processor")`
- inherits: `UAvaDataLinkProcessor`
- L21 _protected prototype_ `virtual void OnProcessOutput(const FDataLinkExecutor& InExecutor, FConstStructView InOutputDataView) override;`
- L24 _protected prototype_ `URemoteControlPreset* GetRemoteControlPreset() const;`
- L35 _protected prototype_ `void ForEachResolvedController(const FDataLinkExecutor& InExecutor, URemoteControlPreset* InPreset, FStructView InTargetDataView, TFunctionRef<void(const FResolvedController&)> InFunction);` — Iterates each controller resolved from the controller mappings
- L39 _private member_ `TArray<FAvaDataLinkControllerMapping> ControllerMappings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Motion Design Data Link", DisplayName="Output Field to Controller Mappings", meta=(AllowPrivateAccess="true"))`

#### struct `UAvaDataLinkRCProcessor::FResolvedController`  
`struct FResolvedController`  
_L26-32_
- L28 _public member_ `const FAvaDataLinkControllerMapping* Mapping;`
- L29 _public member_ `TObjectPtr<URCController> Controller;`
- L30 _public member_ `FProperty* TargetProperty;`
- L31 _public member_ `uint8* TargetMemory;`

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLink/Public/AvaDataLinkActor.h` (Public)


#### class `AAvaDataLinkActor`  
`class AAvaDataLinkActor : public AActor`  
_L11-43_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Data Link Actor", HideCategories=(Activation, Actor, AssetUserData, Collision, Cooking, DataLayers, HLOD, Input, LevelInstance, Mobility, Navigation, Networking, Physics, Rendering, Replication, Tags, Transform, WorldPartition))`
- inherits: `AActor`
- L16 _public prototype_ `AAvaDataLinkActor();`
- L19 _public prototype_ `void ExecuteDataLinkInstances();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category="Motion Design Data Link")`
- L22 _public prototype_ `void StopDataLinkInstances();` — `UFUNCTION(BlueprintCallable, CallInEditor, Category="Motion Design Data Link")`
- L25 _public prototype_ `virtual void BeginPlay() override;`
- L27 _public prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L32 _public prototype_ `virtual void BeginDestroy() override;`
- L35 _public prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bInSessionEnded, bool bInCleanupResources);`
- L38 _public member_ `TArray<TObjectPtr<UAvaDataLinkInstance>> DataLinkInstances;` — `UPROPERTY(EditAnywhere, Instanced, Category="Motion Design Data Link")`
- L42 _public member_ `bool bExecuteOnBeginPlay = false;` — `UPROPERTY(EditAnywhere, Category="Motion Design Data Link")` — Whether to automatically execute the data link instances on Begin Play

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLink/Public/AvaDataLinkInstance.h` (Public)


#### class `UAvaDataLinkInstance`  
`class UAvaDataLinkInstance : public UObject`  
_L16-62_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, DisplayName="Motion Design Data Link Instance")`
- inherits: `UObject`
- L22 _public prototype_ `void Execute();` — Starts a new active data link execution, stopping the existing if any
- L25 _public prototype_ `void Stop();` — Stops the active data link execution if any
- L27 _public function_ `static FName GetDataLinkInstancePropertyName()`
- L32 _public function_ `static FName GetOutputProcessorsPropertyName()`
- L39 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* InSpecificSubclass);`
- L41 _public prototype_ `virtual void PostLoad() override;`
- L46 _private prototype_ `FString BuildContextName() const;`
- L50 _private member_ `FDataLinkInstance DataLinkInstance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Motion Design Data Link", meta=(AllowPrivateAccess="true"))`
- L53 _private member_ `TArray<TObjectPtr<UDataLinkProcessor>> OutputProcessors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Motion Design Data Link", meta=(AllowPrivateAccess="true"))`
- L58 _private member_ `TArray<FAvaDataLinkControllerMapping> ControllerMappings_DEPRECATED;` — `UE_DEPRECATED(5.7, "ControllerMappings in Data Link Instance is deprecated. Use Output Processors instead")` — `UPROPERTY()`
- L61 _private member_ `TSharedPtr<FDataLinkExecutor> Executor;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API AVALANCHEDATALINK_API`

### `Plugins/VirtualProduction/AvalancheDataLink/Source/AvalancheDataLink/Public/RemoteControl/AvaDataLinkControllerMapping.h` (Public)


#### struct `FAvaDataLinkControllerMapping`  
`struct FAvaDataLinkControllerMapping`  
_L9-18_
- reflection: `USTRUCT(BlueprintType, DisplayName="Motion Design Data Link RC Controller Mapping")`
- L14 _public member_ `FString OutputFieldName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Data Link")`
- L17 _public member_ `FAvaRCControllerId TargetController;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Data Link")`
