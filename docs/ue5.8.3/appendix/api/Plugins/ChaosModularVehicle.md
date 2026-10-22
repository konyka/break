# Plugins / ChaosModularVehicle

- module root: `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicle`
- headers: 2; symbols: 20
- symbol kinds: class=2, function=3, macro=1, member=2, namespace=1, prototype=10, typedef=1
- PublicDependencyModuleNames: Chaos, ChaosVehiclesCore, Core, CoreUObject, Engine

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicle/Public/ChaosModularVehicle/ChaosModularVehiclePlugin.h` (Public)


#### class `IChaosModularVehiclePlugin`  
`class IChaosModularVehiclePlugin : public IModuleInterface`  
_L13-46_
- inherits: `IModuleInterface`
- L24 _public function_ `static inline IChaosModularVehiclePlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicle/Public/ChaosModularVehicle/ModularSimCollection.h` (Public)


#### class `FModularSimCollection`  
`class FModularSimCollection : public FGeometryCollection`  
_L19-51_
- inherits: `FGeometryCollection`
- desc: class CHAOSMODULARVEHICLE_API FModularSimCollection : public FTransformCollection
- L23 _public typedef_ `typedef FGeometryCollection Super;` — typedef FTransformCollection Super;
- L25 _public prototype_ `FModularSimCollection();`
- L26 _public prototype_ `FModularSimCollection(FModularSimCollection&) = delete;`
- L27 _public prototype_ `FModularSimCollection& operator=(const FModularSimCollection&) = delete;`
- L28 _public prototype_ `FModularSimCollection(FModularSimCollection&&) = default;`
- L29 _public prototype_ `FModularSimCollection& operator=(FModularSimCollection&&) = default;`
- L34 _public prototype_ `static FModularSimCollection* NewModularSimulationCollection(const FTransformCollection& Base);` — Create a GeometryCollection from Vertex and Indices arrays
- L35 _public prototype_ `static FModularSimCollection* NewModularSimulationCollection();`
- L36 _public prototype_ `static void Init(FModularSimCollection* Collection);`
- L42 _public member_ `static const FName SimModuleIndexAttribute;` — Index of simulation module associated with each transform node FManagedArray<int32> SimModuleIndex = this->FindAttribute<int32>("SimModuleIndex",FGeometryCollection::TransformGroup);
- L43 _public member_ `TManagedArray<int32> SimModuleIndex;`
- L46 _public prototype_ `void GenerateSimTree();` — TODO: need to do this conversion somewhere - putting here for now
- L49 _protected prototype_ `void Construct();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CHAOSMODULARVEHICLE_API`
- L10 _namespace_ `namespace Chaos`
- L53 _function_ `inline Chaos::FChaosArchive& operator<<(Chaos::FChaosArchive& Ar, FModularSimCollection& Value)`
