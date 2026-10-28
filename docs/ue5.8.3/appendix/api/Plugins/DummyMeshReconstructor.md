# Plugins / DummyMeshReconstructor

- module root: `Plugins/Runtime/MeshReconstruction/DummyMeshReconstructor/Source/DummyMeshReconstructor`
- headers: 2; symbols: 10
- symbol kinds: class=1, member=1, prototype=8
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MRMesh

### `Plugins/Runtime/MeshReconstruction/DummyMeshReconstructor/Source/DummyMeshReconstructor/Public/DummyMeshReconstructor.h` (Public)


#### class `UDummyMeshReconstructor`  
`class UDummyMeshReconstructor : public UMeshReconstructorBase`  
_L12-36_
- reflection: `UCLASS(BlueprintType, meta = (Experimental))`
- inherits: `UMeshReconstructorBase`
- L18 _public prototype_ `virtual void StartReconstruction() override;`
- L20 _public prototype_ `virtual void StopReconstruction() override;`
- L22 _public prototype_ `virtual void PauseReconstruction() override;`
- L24 _public prototype_ `virtual bool IsReconstructionStarted() const override;`
- L26 _public prototype_ `virtual bool IsReconstructionPaused() const override;`
- L28 _public prototype_ `virtual void ConnectMRMesh(UMRMeshComponent* Mesh) override;`
- L30 _public prototype_ `virtual void DisconnectMRMesh() override;`
- L34 _private prototype_ `void EnsureImplExists();`
- L35 _private member_ `TSharedPtr<FDummyMeshReconstructor> ReconstructorImpl;`

### `Plugins/Runtime/MeshReconstruction/DummyMeshReconstructor/Source/DummyMeshReconstructor/Public/DummyMeshReconstructorModule.h` (Public)
_(no declarations extracted)_
