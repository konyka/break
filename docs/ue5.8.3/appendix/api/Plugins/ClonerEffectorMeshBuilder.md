# Plugins / ClonerEffectorMeshBuilder

- module root: `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorMeshBuilder`
- headers: 1; symbols: 58
- symbol kinds: enum=1, enumerator=10, function=2, member=13, prototype=27, struct=5
- PrivateDependencyModuleNames: CoreUObject, DynamicMesh, Engine, GeometryCore, GeometryFramework, GeometryScriptingCore, MeshConversion, MeshDescription, ModelingComponents, Niagara, NiagaraCore, ProceduralMeshComponent, StaticMeshDescription
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffectorMeshBuilder/Public/CEMeshBuilder.h` (Public)


#### enum `ECEMeshBuilderComponentType`  
`enum class ECEMeshBuilderComponentType : uint16`  
_L24-36_
- desc: Enumerates all component type that can be converted
- L26 _public enumerator_ `None = 0`
- L27 _public enumerator_ `DynamicMeshComponent = 1 << 1`
- L28 _public enumerator_ `SkeletalMeshComponent = 1 << 2`
- L29 _public enumerator_ `BrushComponent = 1 << 3`
- L30 _public enumerator_ `ProceduralMeshComponent = 1 << 4`
- L31 _public enumerator_ `InstancedStaticMeshComponent = 1 << 5`
- L32 _public enumerator_ `SplineMeshComponent = 1 << 6`
- L33 _public enumerator_ `StaticMeshComponent = 1 << 7`
- L34 _public enumerator_ `NiagaraComponent = 1 << 8`
- L35 _public enumerator_ `All = DynamicMeshComponent | SkeletalMeshComponent | BrushComponent | ProceduralMeshComponent | InstancedStaticMeshComponent | SplineMeshComponent | StaticMeshComponent | NiagaraComponent`

#### struct `FCEMeshBuilder`  
`struct FCEMeshBuilder`  
_L40-174_
- reflection: `USTRUCT()`
- desc: Struct used to build a mesh based out of other meshes class
- L70 _public member_ `static const FCEMeshBuilderParams DefaultBuildParams;`
- L71 _public member_ `static const FCEMeshBuilderAppendParams DefaultAppendParams;`
- L74 _public prototype_ `static bool HasAnyGeometry(UActorComponent* InComponent);` — Checks if the component contains any geometry data
- L77 _public prototype_ `static bool IsActorSupported(const AActor* InActor);` — Does the mesh builder supports this actor
- L80 _public prototype_ `static bool IsComponentSupported(const UActorComponent* InComponent);` — Does the mesh builder supports this component
- L82 _public prototype_ `FCEMeshBuilder();`
- L84 _public function_ `int32 GetMeshInstanceCount() const`
- L89 _public function_ `int32 GetMeshCount() const`
- L94 _public prototype_ `TArray<uint32> GetMeshIndexes() const;`
- L97 _public prototype_ `void Reset();` — Resets the builder and clears data
- L100 _public prototype_ `TArray<UPrimitiveComponent*> AppendActor(const AActor* InActor, const FTransform& InTransform, const FCEMeshBuilderAppendParams& InParams = DefaultAppendParams);` — Appends supported components within actor
- L103 _public prototype_ `bool AppendComponent(const UStaticMeshComponent* InComponent, const FTransform& InTransform = FTransform::Identity);` — Appends Static Mesh component
- L106 _public prototype_ `bool AppendComponent(UProceduralMeshComponent* InComponent, const FTransform& InTransform = FTransform::Identity);` — Appends Procedural Mesh component
- L109 _public prototype_ `bool AppendComponent(UBrushComponent* InComponent, const FTransform& InTransform = FTransform::Identity);` — Appends Brush component
- L112 _public prototype_ `bool AppendComponent(const USkeletalMeshComponent* InComponent, const FTransform& InTransform = FTransform::Identity);` — Appends Skeletal Mesh component
- L115 _public prototype_ `bool AppendComponent(UDynamicMeshComponent* InComponent, const FTransform& InTransform = FTransform::Identity);` — Appends Dynamic Mesh component
- L118 _public prototype_ `bool AppendComponent(UInstancedStaticMeshComponent* InComponent, const FTransform& InTransform = FTransform::Identity);` — Appends Instanced Static Mesh component
- L121 _public prototype_ `bool AppendComponent(USplineMeshComponent* InComponent, const FTransform& InTransform = FTransform::Identity);` — Appends Spline Mesh component
- L124 _public prototype_ `bool AppendComponent(UNiagaraComponent* InComponent, const FTransform& InTransform = FTransform::Identity);` — Appends Niagara component
- L127 _public prototype_ `bool AppendMesh(const UDynamicMesh* InMesh, const TArray<TWeakObjectPtr<UMaterialInterface>>& InMaterials, const FTransform& InTransform = FTransform::Identity);` — Appends a dynamic mesh
- L130 _public prototype_ `bool AppendMesh(UStaticMesh* InMesh, const TArray<TWeakObjectPtr<UMaterialInterface>>& InMaterials, const FTransform& InTransform = FTransform::Identity);` — Appends a static mesh
- L133 _public prototype_ `bool BuildDynamicMesh(UDynamicMesh* OutMesh, TArray<TWeakObjectPtr<UMaterialInterface>>& OutMaterials, const FCEMeshBuilderParams& InParams = DefaultBuildParams);` — Builds a dynamic mesh by merging all the mesh data imported
- L136 _public prototype_ `bool BuildStaticMesh(UStaticMesh* OutMesh, TArray<TWeakObjectPtr<UMaterialInterface>>& OutMaterials, const FCEMeshBuilderParams& InParams = DefaultBuildParams);` — Builds a static mesh by merging all the mesh data imported
- L139 _public prototype_ `bool BuildStaticMesh(int32 InInstanceIndex, UStaticMesh* OutMesh, FCEMeshInstanceData& OutMeshInstance);` — Builds a static mesh for the specific instance index
- L142 _public prototype_ `bool BuildDynamicMesh(int32 InInstanceIndex, UDynamicMesh* OutMesh, FCEMeshInstanceData& OutMeshInstance);` — Builds a dynamic mesh for the specific instance index
- L145 _public prototype_ `bool BuildStaticMesh(uint32 InMeshIndex, UStaticMesh* OutMesh, TArray<FCEMeshInstanceData>& OutMeshInstances);` — Builds a static mesh for the specific mesh index
- L148 _public prototype_ `bool BuildDynamicMesh(uint32 InMeshIndex, UDynamicMesh* OutMesh, TArray<FCEMeshInstanceData>& OutMeshInstances);` — Builds a dynamic mesh for the specific mesh index
- L151 _private prototype_ `static bool DynamicMeshToStaticMesh(UDynamicMesh* InMesh, UStaticMesh* OutMesh, const TArray<TWeakObjectPtr<UMaterialInterface>>& InMaterials);`
- L162 _private prototype_ `FCEMeshInstance* AddMeshInstance(uint32 InMeshIndex, const FTransform& InTransform, const TArray<TWeakObjectPtr<UMaterialInterface>>& InMaterials, TFunctionRef<bool(UE::Geometry::FDynamicMesh3&)> InCreateMeshFunction);`
- L164 _private prototype_ `bool AppendPrimitiveComponent(const UObject* InMeshObject, UPrimitiveComponent* InComponent, const FTransform& InTransform);`
- L166 _private prototype_ `void ClearOutputMesh() const;`
- L168 _private member_ `TMap<uint32, UE::Geometry::FDynamicMesh3> Meshes;`
- L170 _private member_ `TArray<FCEMeshInstance> MeshInstances;`
- L173 _private member_ `TObjectPtr<UDynamicMesh> OutputDynamicMesh;` — `UPROPERTY()`

#### struct `FCEMeshBuilder::FCEMeshInstanceData`  
`struct FCEMeshInstanceData`  
_L44-51_
- L47 _public member_ `FTransform Transform;` — Transform to apply on the mesh instance
- L50 _public member_ `TArray<TWeakObjectPtr<UMaterialInterface>> MeshMaterials;` — Materials applied on this instance

#### struct `FCEMeshBuilder::FCEMeshBuilderParams`  
`struct FCEMeshBuilderParams`  
_L53-59_
- L56 _public member_ `bool bMergeMaterials = false;` — Merge same meshes material slot in the final result
- L58 _public member_ `bool bNotifyMeshChangeEvents = false;` — Whether to call the PreMeshChangedEvent and MeshChangedEvents during the build

#### struct `FCEMeshBuilder::FCEMeshBuilderAppendParams`  
`struct FCEMeshBuilderAppendParams`  
_L61-68_
- L64 _public member_ `ECEMeshBuilderComponentType ComponentTypes = ECEMeshBuilderComponentType::All;` — Component types to append
- L67 _public member_ `TSet<UPrimitiveComponent*> ExcludeComponents;` — Specific excluded components

#### struct `FCEMeshBuilder::FCEMeshInstance`  
`struct FCEMeshInstance`  
_L153-160_
- L156 _public member_ `uint32 MeshIndex;` — Index of the mesh to use for this instance
- L159 _public member_ `FCEMeshInstanceData MeshData;` — Data linked to this mesh instance
