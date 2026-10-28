# Plugins / GeometryDataflowNodes

- module root: `Plugins/Experimental/GeometryDataflow/Source/GeometryDataflowNodes`
- headers: 2; symbols: 25
- symbol kinds: class=1, enum=2, enumerator=8, member=7, namespace=2, prototype=4, struct=1
- PrivateDependencyModuleNames: DynamicMesh
- PublicDependencyModuleNames: Core, CoreUObject, DataflowCore, DataflowEngine, GeometryCore, GeometryFramework

### `Plugins/Experimental/GeometryDataflow/Source/GeometryDataflowNodes/Public/Dataflow/MeshBooleanNodes.h` (Public)


#### enum `EMeshBooleanOperationEnum`  
`enum class EMeshBooleanOperationEnum : uint8`  
_L18-29_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Dataflow_MeshBoolean_Union UMETA(DisplayName = "Union")` — A union of A + B includes everything inside either A or B
- L23 _public enumerator_ `Dataflow_MeshBoolean_Intersect UMETA(DisplayName = "Intersect")` — An intersection of A & B includes only the points inside both A and B, i.e. trimming A by B (and vice versa)
- L25 _public enumerator_ `Dataflow_MeshBoolean_Difference UMETA(DisplayName = "Difference")` — A difference of A - B includes only the points inside A that are outside of B, i.e. subtracting B from A
- L28 _public enumerator_ `Dataflow_Max UMETA(Hidden)` — 256th entry

#### enum `EDataflowMeshBooleanInputMeshEnum`  
`enum class EDataflowMeshBooleanInputMeshEnum : uint8`  
_L33-39_
- reflection: `UENUM(BlueprintType)`
- desc: Enum to select among the input meshes for a Mesh Boolean operation
- L35 _public enumerator_ `None`
- L36 _public enumerator_ `First`
- L37 _public enumerator_ `Second`
- L38 _public enumerator_ `Both`

#### struct `FMeshBooleanDataflowNode`  
`struct FMeshBooleanDataflowNode : public FDataflowNode`  
_L52-91_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Compute a Mesh Boolean between Mesh1 and Mesh2 Supported Boolean Operations: Union (Mesh1 + Mesh2) Difference (Mesh1 - Mesh2; removing what's inside of Mesh2 from Mesh1) Intersection (Mesh1 & Mesh2; removing what's outside of Mesh2 from Mesh1)
- L64 _private member_ `EMeshBooleanOperationEnum Operation = EMeshBooleanOperationEnum::Dataflow_MeshBoolean_Intersect;` — `UPROPERTY(EditAnywhere, Category = "Boolean")` — Boolean operation
- L68 _private member_ `bool bWeldSharedEdges = false;` — `UPROPERTY(EditAnywhere, Category = "Boolean", AdvancedDisplay)` — Whether to weld common edges at the joins of the mesh boolean
- L72 _private member_ `bool bSimplifyAlongNewEdges = true;` — `UPROPERTY(EditAnywhere, Category = "Simplification")` — Whether to simplify the result along new edges
- L75 _private member_ `EDataflowMeshBooleanInputMeshEnum PreserveUVQualityForMesh = EDataflowMeshBooleanInputMeshEnum::First;` — `UPROPERTY(EditAnywhere, Category = "Simplification", AdvancedDisplay, DisplayName="Preserve UV Quality for Mesh", meta=(EditCondition="bSimplifyAlongNewEdges"))`
- L79 _private member_ `TObjectPtr<UDynamicMesh> Mesh1;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh input
- L83 _private member_ `TObjectPtr<UDynamicMesh> Mesh2;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Mesh input
- L87 _private member_ `TObjectPtr<UDynamicMesh> Mesh;` — `UPROPERTY(meta = (DataflowOutput))` — Output mesh
- L89 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L95 _namespace_ `namespace UE`
- L95 _namespace_ `namespace Dataflow` (scope `UE`)
- L97 _prototype_ `void MeshBooleanNodes();` (scope `UE::Dataflow`)

### `Plugins/Experimental/GeometryDataflow/Source/GeometryDataflowNodes/Public/GeometryDataflowNodesPlugin.h` (Public)


#### class `IGeometryDataflowNodesPlugin`  
`class IGeometryDataflowNodesPlugin : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`
