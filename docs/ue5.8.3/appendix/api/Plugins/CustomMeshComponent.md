# Plugins / CustomMeshComponent

- module root: `Plugins/Runtime/CustomMeshComponent/Source/CustomMeshComponent`
- headers: 2; symbols: 16
- symbol kinds: class=2, function=2, macro=1, member=4, prototype=6, struct=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RHI, RenderCore

### `Plugins/Runtime/CustomMeshComponent/Source/CustomMeshComponent/Classes/CustomMeshComponent.h` (Public)


#### struct `FCustomMeshTriangle`  
`struct FCustomMeshTriangle`  
_L15-27_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `FVector Vertex0 = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Triangle)`
- L23 _public member_ `FVector Vertex1 = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Triangle)`
- L26 _public member_ `FVector Vertex2 = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Triangle)`

#### class `UCustomMeshComponent`  
`class UCustomMeshComponent : public UMeshComponent`  
_L31-65_
- reflection: `UCLASS(MinimalAPI, hidecategories=(Object,LOD, Physics, Collision), editinlinenew, meta=(BlueprintSpawnableComponent), ClassGroup=Rendering)`
- inherits: `UMeshComponent`
- desc: Component that allows you to specify custom triangle mesh geometry
- L37 _private prototype_ `bool SetCustomMeshTriangles(const TArray<FCustomMeshTriangle>& Triangles);` — `UFUNCTION(BlueprintCallable, Category="Components|CustomMesh")` — Set the geometry to use on this triangle mesh
- L41 _private prototype_ `void AddCustomMeshTriangles(const TArray<FCustomMeshTriangle>& Triangles);` — `UFUNCTION(BlueprintCallable, Category = "Components|CustomMesh")` — Add to the geometry to use on this triangle mesh.  This may cause an allocation.  Use SetCustomMeshTriangles() instead when possible to reduce allocations.
- L45 _private prototype_ `void ClearCustomMeshTriangles();` — `UFUNCTION(BlueprintCallable, Category = "Components|CustomMesh")` — Removes all geometry from this triangle mesh.  Does not deallocate memory, allowing new geometry to reuse the existing allocation.
- L50 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L54 _private prototype_ `virtual int32 GetNumMaterials() const override;`
- L58 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L62 _private member_ `TArray<FCustomMeshTriangle> CustomMeshTris;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CUSTOMMESHCOMPONENT_API`

### `Plugins/Runtime/CustomMeshComponent/Source/CustomMeshComponent/Public/ICustomMeshComponentPlugin.h` (Public)


#### class `ICustomMeshComponentPlugin`  
`class ICustomMeshComponentPlugin : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline ICustomMeshComponentPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
