# Plugins / MoverCVDData

- module root: `Plugins/Experimental/Mover/Source/MoverCVDData`
- headers: 1; symbols: 12
- symbol kinds: member=9, prototype=1, struct=2
- PrivateDependencyModuleNames: ChaosVDRuntime
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Experimental/Mover/Source/MoverCVDData/Public/MoverCVDDataWrappers.h` (Public)


#### struct `FMoverCVDSimDataWrapper`  
`struct FMoverCVDSimDataWrapper : public FChaosVDWrapperDataBase`  
_L12-34_
- reflection: `USTRUCT(DisplayName="Mover Sim Data")`
- inherits: `FChaosVDWrapperDataBase`
- L16 _public member_ `static FStringView WrapperTypeName;`
- L19 _public member_ `int32 SolverID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Mover Info")`
- L22 _public member_ `int32 ParticleID = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category="Mover Info")`
- L24 _public member_ `TArray<uint8> SyncStateBytes;`
- L25 _public member_ `TArray<uint8> SyncStateDataCollectionBytes;`
- L26 _public member_ `TArray<uint8> InputCmdBytes;`
- L27 _public member_ `TArray<uint8> InputMoverDataCollectionBytes;`
- L31 _public member_ `TArray<TPair<FName, TArray<uint8>>> LocalSimDataSections;` — Named sections of local simulation data (e.g. LocalSimInput, InternalSimData, DebugSimData). Each section is serialized independently so the origin of each struct is preserved in the CVD viewer.
- L33 _public prototype_ `bool Serialize(FArchive& Ar);`

#### struct `FMoverCVDSimDataContainer`  
`struct FMoverCVDSimDataContainer`  
_L39-44_
- reflection: `USTRUCT()`
- L43 _public member_ `TMap<int32, TArray<TSharedPtr<FMoverCVDSimDataWrapper>>> SimDataBySolverID;`
