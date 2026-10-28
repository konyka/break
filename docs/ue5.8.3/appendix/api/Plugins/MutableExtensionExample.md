# Plugins / MutableExtensionExample

- module root: `Plugins/Experimental/MutableExtensionExample/Source/MutableExtensionExample`
- headers: 5; symbols: 25
- symbol kinds: class=1, member=7, prototype=13, struct=4
- PrivateDependencyModuleNames: CustomizableObject
- PublicDependencyModuleNames: Core, CoreUObject, MutableRuntime

### `Plugins/Experimental/MutableExtensionExample/Source/MutableExtensionExample/Public/MeshClipSphere.h` (Public)


#### struct `FMeshClipSphere`  
`struct FMeshClipSphere : public UE::Mutable::FExternalOperation`  
_L11-23_
- reflection: `USTRUCT(DisplayName = "Mesh Clip With Sphere")`
- inherits: `UE::Mutable::FExternalOperation`
- L15 _public prototype_ `virtual ~FMeshClipSphere() override = default;`
- L16 _public prototype_ `virtual TArray<TPair<FText, const UScriptStruct*>> GetInputs() const override;`
- L17 _public prototype_ `virtual TPair<FText, const UScriptStruct*> GetOutput() const override;`
- L18 _public prototype_ `virtual void Evaluate(UE::Mutable::FContext& Context) const override;`
- L20 _public member_ `const static FText TextInputMesh;`
- L22 _public member_ `const static FText TextInputPrimitiveSphere;`

### `Plugins/Experimental/MutableExtensionExample/Source/MutableExtensionExample/Public/MeshIdentity.h` (Public)


#### struct `FMeshIdentity`  
`struct FMeshIdentity : public UE::Mutable::FExternalOperation`  
_L11-21_
- reflection: `USTRUCT(DisplayName = "Mesh Identity")`
- inherits: `UE::Mutable::FExternalOperation`
- L15 _public prototype_ `virtual ~FMeshIdentity() override = default;`
- L16 _public prototype_ `virtual TArray<TPair<FText, const UScriptStruct*>> GetInputs() const override;`
- L17 _public prototype_ `virtual TPair<FText, const UScriptStruct*> GetOutput() const override;`
- L18 _public prototype_ `virtual void Evaluate(UE::Mutable::FContext& Context) const override;`
- L20 _public member_ `const static FText TextInputMesh;`

### `Plugins/Experimental/MutableExtensionExample/Source/MutableExtensionExample/Public/MeshNoise.h` (Public)


#### struct `FMeshNoise`  
`struct FMeshNoise : public UE::Mutable::FExternalOperation`  
_L11-28_
- reflection: `USTRUCT(DisplayName = "Mesh Noise")`
- inherits: `UE::Mutable::FExternalOperation`
- L15 _public prototype_ `virtual TArray<TPair<FText, const UScriptStruct*>> GetInputs() const override;`
- L16 _public prototype_ `virtual TPair<FText, const UScriptStruct*> GetOutput() const override;`
- L17 _public prototype_ `virtual void Evaluate(UE::Mutable::FContext& Context) const override;`
- L19 _public member_ `const static FText TextInputMesh;`
- L21 _public member_ `const static FText TextInputFactor;`
- L27 _public member_ `int32 Seed = 0;` — `UPROPERTY(EditAnywhere, Category = "Mesh Noise")` — Operation constant. This value will be copied when compiling a Customizable Object, hence it can not be changed at runtime. If a value needs to change at runtime, it must be a Parameter.

### `Plugins/Experimental/MutableExtensionExample/Source/MutableExtensionExample/Public/MutableExtensionExampleModule.h` (Public)


#### class `FMutableExtensionExampleModule`  
`class FMutableExtensionExampleModule : public IModuleInterface`  
_L8-12_
- inherits: `IModuleInterface`
- L10 _private prototype_ `virtual void StartupModule() override;`
- L11 _private prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/MutableExtensionExample/Source/MutableExtensionExample/Public/PrimitiveSphere.h` (Public)


#### struct `FPrimitiveSphere`  
`struct FPrimitiveSphere`  
_L9-15_
- reflection: `USTRUCT(DisplayName = "Sphere")`
- L14 _public member_ `FSphere3d Sphere;` — `UPROPERTY(EditAnywhere, Category = Primitive)`
