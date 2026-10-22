# Plugins / DataflowMedialSkeleton

- module root: `Plugins/Experimental/GeometryDataflow/Source/DataflowMedialSkeleton`
- headers: 2; symbols: 5
- symbol kinds: class=1, member=1, prototype=2, struct=1
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, GeometryAlgorithms

### `Plugins/Experimental/GeometryDataflow/Source/DataflowMedialSkeleton/Public/Dataflow/DataflowMedialSkeleton.h` (Public)


#### struct `FDataflowMedialSkeleton`  
`struct FDataflowMedialSkeleton`  
_L12-18_
- reflection: `USTRUCT()`
- desc: A set of spheres and associated connectivity corresponding to a sampled medial skeleton of a target mesh
- L17 _public member_ `UE::Geometry::MedialAxis::FMedialSkeleton Skeleton;`

### `Plugins/Experimental/GeometryDataflow/Source/DataflowMedialSkeleton/Public/DataflowMedialSkeletonModule.h` (Public)


#### class `IGeometryDataflowMedialSkeletonPlugin`  
`class IGeometryDataflowMedialSkeletonPlugin : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`
