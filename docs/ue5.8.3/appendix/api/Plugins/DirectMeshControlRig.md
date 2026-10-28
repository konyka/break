# Plugins / DirectMeshControlRig

- module root: `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControlRig`
- headers: 3; symbols: 10
- symbol kinds: class=2, function=1, member=2, prototype=4, struct=1
- PrivateDependencyModuleNames: AnimationCore, ComputeFramework, ControlRig, Core, CoreUObject, DirectMeshControl, DynamicMesh, Engine, GeometryCore, MeshConversion, OptimusCore, RigVM

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControlRig/Public/DirectMeshControlProxyWrapper.h` (Public)


#### class `UDirectMeshControlProxy`  
`class UDirectMeshControlProxy : public UObject`  
_L14-17_
- reflection: `UCLASS(transient)`
- inherits: `UObject`
- desc: UDirectMeshControlProxy is a transient proxy object used by FShapeProxyComponentProviderRegistry to associate a UDirectMeshControlComponent with a Control Rig shape.

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControlRig/Public/DirectMeshControlRigModule.h` (Public)


#### class `FDirectMeshControlRigModule`  
`class FDirectMeshControlRigModule : public IModuleInterface`  
_L10-20_
- inherits: `IModuleInterface`
- desc: FDirectMeshControlRigModule is an editor module that integrates the Direct Mesh Control plugin with the Control Rig system.
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private prototype_ `void OnPostEngineInit() const;` — Called after the engine has finished initializing.

### `Plugins/Experimental/Animation/DirectMeshControl/Source/DirectMeshControlRig/Public/Units/RigUnit_DirectMeshControl.h` (Public)


#### struct `FRigUnit_SetupShapeLibraryFromLayer`  
`struct FRigUnit_SetupShapeLibraryFromLayer : public FRigUnit_DynamicHierarchyBaseMutable`  
_L16-35_
- reflection: `USTRUCT(meta=(DisplayName="Set Shape Library from Layer", Keywords="Direct Mesh Control, Surface Selection", Varying))`
- inherits: `FRigUnit_DynamicHierarchyBaseMutable`
- L20 _public function_ `FRigUnit_SetupShapeLibraryFromLayer()`
- L25 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;`
- L30 _public member_ `FName LayerName;` — `UPROPERTY(meta = (Input))` — The layer to extract
- L34 _public member_ `TArray<FName> GroupNames;` — `UPROPERTY(meta = (Output))` — The extracted groups
