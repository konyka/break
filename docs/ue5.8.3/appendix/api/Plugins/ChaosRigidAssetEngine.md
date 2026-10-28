# Plugins / ChaosRigidAssetEngine

- module root: `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetEngine`
- headers: 3; symbols: 16
- symbol kinds: class=3, macro=1, member=2, prototype=10
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Core, DataflowCore, DataflowEngine, DataflowEnginePlugin, Engine

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetEngine/Private/PhysicsAssetDataflowContent.h` (Private)


#### class `UPhysicsAssetDataflowContent`  
`class UPhysicsAssetDataflowContent : public UDataflowBaseContent`  
_L18-39_
- reflection: `UCLASS()`
- inherits: `UDataflowBaseContent`
- desc: Dataflow editor content for physics assets
- L24 _public prototype_ `void SetActorProperties(TObjectPtr<AActor>& PreviewActor) const override;`
- L26 _public prototype_ `void SetSkeletalMesh(USkeletalMesh* InMesh);`
- L27 _public prototype_ `void SetPhysicsAsset(UPhysicsAsset* InAsset);`
- L33 _private member_ `TObjectPtr<USkeletalMesh> SkelMesh = nullptr;` — `UPROPERTY()` — Preview mesh to use
- L37 _private member_ `TObjectPtr<UPhysicsAsset> PhysAsset = nullptr;` — `UPROPERTY()` — Physics asset to use (must be compatible with the preview mesh)

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetEngine/Public/PhysicsAssetDataflowAttachment.h` (Public)


#### class `UPhysicsAssetDataflowAttachment`  
`class UPhysicsAssetDataflowAttachment : public UDataflowAttachment`  
_L9-31_
- reflection: `UCLASS()`
- inherits: `UDataflowAttachment`
- L16 _public prototype_ `void WriteDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) const override;` — IDataflowContentOwner
- L17 _public prototype_ `void ReadDataflowContent(const TObjectPtr<UDataflowBaseContent>& DataflowContent) override;`
- L23 _protected prototype_ `TObjectPtr<UDataflowBaseContent> CreateDataflowContent() override;` — IDataflowContentOwner
- L27 _protected prototype_ `FString GetPreviewActorPath() const override;` — UDataflowAttachment

### `Plugins/Experimental/ChaosRigidAsset/Source/ChaosRigidAssetEngine/Public/PreviewSceneControllerComponent.h` (Public)


#### class `UPreviewSceneControllerComponent`  
`class UPreviewSceneControllerComponent : public UActorComponent`  
_L17-33_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- desc: Controller for simulation solver interaction in a dataflow preview scene
- L24 _public prototype_ `void ApplySolverConfig(const FChaosSolverConfiguration& Config);` — `UFUNCTION(BlueprintCallable, Category= PreviewSceneControl)`
- L27 _public prototype_ `void EnableAsyncTick(float InAsyncDt);` — `UFUNCTION(BlueprintCallable, Category= PreviewSceneControl)`
- L30 _public prototype_ `void DisableAsyncTick();` — `UFUNCTION(BlueprintCallable, Category= PreviewSceneControl)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSRIGIDASSETENGINE_API`
