# Plugins / ChaosNiagara

- module root: `Plugins/Experimental/ChaosNiagara/Source/ChaosNiagara`
- headers: 4; symbols: 460
- symbol kinds: class=4, enum=9, enumerator=40, function=38, macro=2, member=214, namespace=3, prototype=136, struct=14
- PrivateDependencyModuleNames: Chaos, Engine, PhysicsCore, Projects, RenderCore, Slate, SlateCore
- PublicDependencyModuleNames: ChaosSolverEngine, Core, CoreUObject, FieldSystemEngine, GeometryCollectionEngine, Niagara, NiagaraCore, NiagaraShader, NiagaraVertexFactories, RHI, VectorVM

### `Plugins/Experimental/ChaosNiagara/Source/ChaosNiagara/Classes/NiagaraDataInterfaceChaosDestruction.h` (Public)


#### struct `FChaosDestructionEvent`  
`struct FChaosDestructionEvent`  
_L24-86_
- reflection: `USTRUCT()`
- L29 _public member_ `FVector Position;` — `UPROPERTY(EditAnywhere, Category = "Chaos Destruction Event")`
- L32 _public member_ `FVector Normal;` — `UPROPERTY(EditAnywhere, Category = "Chaos Destruction Event")`
- L35 _public member_ `FVector Velocity;` — `UPROPERTY(EditAnywhere, Category = "Chaos Destruction Event")`
- L38 _public member_ `FVector AngularVelocity;` — `UPROPERTY(EditAnywhere, Category = "Chaos Destruction Event")`
- L41 _public member_ `float ExtentMin;` — `UPROPERTY(EditAnywhere, Category = "Chaos Destruction Event")`
- L44 _public member_ `float ExtentMax;` — `UPROPERTY(EditAnywhere, Category = "Chaos Destruction Event")`
- L47 _public member_ `int32 ParticleID;` — `UPROPERTY(EditAnywhere, Category = "Chaos Destruction Event")`
- L50 _public member_ `float Time;` — `UPROPERTY(EditAnywhere, Category = "Chaos Destruction Event")`
- L53 _public member_ `int32 Type;` — `UPROPERTY(EditAnywhere, Category = "Chaos Destruction Event")`
- L55 _public function_ `FChaosDestructionEvent() : Position(FVector::ZeroVector) , Normal(FVector::ZeroVector) , Velocity(FVector::ZeroVector) , AngularVelocity(FVector::ZeroVector) , ExtentMin(0.f) , ExtentMax(0.f) , ParticleID() , Time(0.f) , Type(-1)`
- L68 _public function_ `inline bool operator==(const FChaosDestructionEvent& Other) const`
- L82 _public function_ `inline bool operator!=(const FChaosDestructionEvent& Other) const`

#### struct `FSolverData`  
`struct FSolverData`  
_L88-96_
- L90 _public function_ `FSolverData() : Solver(nullptr)`
- L94 _public member_ `FPhysScene_Chaos* PhysScene;`
- L95 _public member_ `Chaos::FPhysicsSolver* Solver;`

#### struct `FNDIChaosDestruction_InstanceData`  
`struct FNDIChaosDestruction_InstanceData`  
_L98-127_
- L100 _public member_ `TArray<FVector> PositionArray;`
- L101 _public member_ `TArray<FVector> VelocityArray;`
- L102 _public member_ `TArray<float> ExtentMinArray;`
- L103 _public member_ `TArray<float> ExtentMaxArray;`
- L104 _public member_ `TArray<float> VolumeArray;`
- L105 _public member_ `TArray<int32> SolverIDArray;`
- L106 _public member_ `TArray<float> DensityArray;`
- L107 _public member_ `TArray<float> FrictionArray;`
- L108 _public member_ `TArray<float> RestitutionArray;`
- L109 _public member_ `TArray<int32> SurfaceTypeArray;`
- L110 _public member_ `TArray<FLinearColor> ColorArray;`
- L112 _public member_ `TArray<FVector> IncomingLocationArray;` — Collision, Breaking, Trailing
- L113 _public member_ `TArray<FVector> IncomingAccumulatedImpulseArray;` — Collision
- L114 _public member_ `TArray<FVector> IncomingNormalArray;` — Collision
- L115 _public member_ `TArray<FVector> IncomingVelocity1Array;` — Collision, Breaking, Trailing
- L116 _public member_ `TArray<FVector> IncomingVelocity2Array;` — Collision
- L117 _public member_ `TArray<FVector> IncomingAngularVelocity1Array;` — Collision, Breaking, Trailing
- L118 _public member_ `TArray<FVector> IncomingAngularVelocity2Array;` — Collision
- L119 _public member_ `TArray<float> IncomingMass1Array;` — Collision, Breaking, Trailing
- L120 _public member_ `TArray<float> IncomingMass2Array;` — Collision
- L121 _public member_ `TArray<float> IncomingTimeArray;` — Collision, Breaking, Trailing
- L123 _public member_ `TArray<FVector> TransformTranslationArray;`
- L124 _public member_ `TArray<FQuat> TransformRotationArray;`
- L125 _public member_ `TArray<FVector> TransformScaleArray;`
- L126 _public member_ `TArray<FVector> BoundsArray;`

#### struct `FNiagaraDIChaosDestruction_GPUData`  
`struct FNiagaraDIChaosDestruction_GPUData`  
_L129-218_
- L131 _public member_ `TArray<FVector3f> PositionArray;`
- L132 _public member_ `TArray<FVector3f> VelocityArray;`
- L133 _public member_ `TArray<float> ExtentMinArray;`
- L134 _public member_ `TArray<float> ExtentMaxArray;`
- L135 _public member_ `TArray<float> VolumeArray;`
- L136 _public member_ `TArray<int32> SolverIDArray;`
- L137 _public member_ `TArray<float> DensityArray;`
- L138 _public member_ `TArray<float> FrictionArray;`
- L139 _public member_ `TArray<float> RestitutionArray;`
- L140 _public member_ `TArray<int32> SurfaceTypeArray;`
- L141 _public member_ `TArray<FLinearColor> ColorArray;`
- L143 _public member_ `TArray<FVector3f> IncomingLocationArray;` — Collision, Breaking, Trailing
- L144 _public member_ `TArray<FVector3f> IncomingAccumulatedImpulseArray;` — Collision
- L145 _public member_ `TArray<FVector3f> IncomingNormalArray;` — Collision
- L146 _public member_ `TArray<FVector3f> IncomingVelocity1Array;` — Collision, Breaking, Trailing
- L147 _public member_ `TArray<FVector3f> IncomingVelocity2Array;` — Collision
- L148 _public member_ `TArray<FVector3f> IncomingAngularVelocity1Array;` — Collision, Breaking, Trailing
- L149 _public member_ `TArray<FVector3f> IncomingAngularVelocity2Array;` — Collision
- L150 _public member_ `TArray<float> IncomingMass1Array;` — Collision, Breaking, Trailing
- L151 _public member_ `TArray<float> IncomingMass2Array;` — Collision
- L152 _public member_ `TArray<float> IncomingTimeArray;` — Collision, Breaking, Trailing
- L154 _public member_ `TArray<FVector3f> TransformTranslationArray;`
- L155 _public member_ `TArray<FQuat4f> TransformRotationArray;`
- L156 _public member_ `TArray<FVector3f> TransformScaleArray;`
- L157 _public member_ `TArray<FVector3f> BoundsArray;`
- L159 _public function_ `void ResetAll()`
- L190 _public member_ `float SolverTime;`
- L191 _public member_ `int32 LastSpawnedPointID;`
- L193 _public member_ `FRDGBufferSRVRef RDGPositionSRV = nullptr;`
- L194 _public member_ `FRDGBufferSRVRef RDGVelocitySRV = nullptr;`
- L195 _public member_ `FRDGBufferSRVRef RDGExtentMinBufferSRV = nullptr;`
- L196 _public member_ `FRDGBufferSRVRef RDGExtentMaxBufferSRV = nullptr;`
- L197 _public member_ `FRDGBufferSRVRef RDGVolumeBufferSRV = nullptr;`
- L198 _public member_ `FRDGBufferSRVRef RDGSolverIDBufferSRV = nullptr;`
- L199 _public member_ `FRDGBufferSRVRef RDGDensityBufferSRV = nullptr;`
- L200 _public member_ `FRDGBufferSRVRef RDGFrictionBufferSRV = nullptr;`
- L201 _public member_ `FRDGBufferSRVRef RDGRestitutionBufferSRV = nullptr;`
- L202 _public member_ `FRDGBufferSRVRef RDGSurfaceTypeBufferSRV = nullptr;`
- L203 _public member_ `FRDGBufferSRVRef RDGColorBufferSRV = nullptr;`
- L204 _public member_ `FRDGBufferSRVRef RDGIncomingLocationBufferSRV = nullptr;`
- L205 _public member_ `FRDGBufferSRVRef RDGIncomingAccumulatedImpulseBufferSRV = nullptr;`
- L206 _public member_ `FRDGBufferSRVRef RDGIncomingNormalBufferSRV = nullptr;`
- L207 _public member_ `FRDGBufferSRVRef RDGIncomingVelocity1BufferSRV = nullptr;`
- L208 _public member_ `FRDGBufferSRVRef RDGIncomingVelocity2BufferSRV = nullptr;`
- L209 _public member_ `FRDGBufferSRVRef RDGIncomingAngularVelocity1BufferSRV = nullptr;`
- L210 _public member_ `FRDGBufferSRVRef RDGIncomingAngularVelocity2BufferSRV = nullptr;`
- L211 _public member_ `FRDGBufferSRVRef RDGIncomingMass1BufferSRV = nullptr;`
- L212 _public member_ `FRDGBufferSRVRef RDGIncomingMass2BufferSRV = nullptr;`
- L213 _public member_ `FRDGBufferSRVRef RDGIncomingTimeBufferSRV = nullptr;`
- L214 _public member_ `FRDGBufferSRVRef RDGTransformTranslationBufferSRV = nullptr;`
- L215 _public member_ `FRDGBufferSRVRef RDGTransformRotationBufferSRV = nullptr;`
- L216 _public member_ `FRDGBufferSRVRef RDGTransformScaleBufferSRV = nullptr;`
- L217 _public member_ `FRDGBufferSRVRef RDGBoundsBufferSRV = nullptr;`

#### struct `FNiagaraDIChaosDestruction_InstanceDataToPassToRT`  
`struct FNiagaraDIChaosDestruction_InstanceDataToPassToRT`  
_L220-257_
- L222 _public member_ `TArray<FVector3f> PositionArray;`
- L223 _public member_ `TArray<FVector3f> VelocityArray;`
- L224 _public member_ `TArray<float> ExtentMinArray;`
- L225 _public member_ `TArray<float> ExtentMaxArray;`
- L226 _public member_ `TArray<float> VolumeArray;`
- L227 _public member_ `TArray<int32> SolverIDArray;`
- L228 _public member_ `TArray<float> DensityArray;`
- L229 _public member_ `TArray<float> FrictionArray;`
- L230 _public member_ `TArray<float> RestitutionArray;`
- L231 _public member_ `TArray<int32> SurfaceTypeArray;`
- L232 _public member_ `TArray<FLinearColor> ColorArray;`
- L234 _public member_ `TArray<FVector3f> IncomingLocationArray;` — Collision, Breaking, Trailing
- L235 _public member_ `TArray<FVector3f> IncomingAccumulatedImpulseArray;` — Collision
- L236 _public member_ `TArray<FVector3f> IncomingNormalArray;` — Collision
- L237 _public member_ `TArray<FVector3f> IncomingVelocity1Array;` — Collision, Breaking, Trailing
- L238 _public member_ `TArray<FVector3f> IncomingVelocity2Array;` — Collision
- L239 _public member_ `TArray<FVector3f> IncomingAngularVelocity1Array;` — Collision, Breaking, Trailing
- L240 _public member_ `TArray<FVector3f> IncomingAngularVelocity2Array;` — Collision
- L241 _public member_ `TArray<float> IncomingMass1Array;` — Collision, Breaking, Trailing
- L242 _public member_ `TArray<float> IncomingMass2Array;` — Collision
- L243 _public member_ `TArray<float> IncomingTimeArray;` — Collision, Breaking, Trailing
- L245 _public member_ `TArray<FVector3f> TransformTranslationArray;` — Breaking
- L246 _public member_ `TArray<FQuat4f> TransformRotationArray;` — Breaking
- L247 _public member_ `TArray<FVector3f> TransformScaleArray;` — Breaking
- L248 _public member_ `TArray<FVector3f> BoundsArray;` — Breaking
- L250 _public member_ `float SolverTime;`
- L251 _public member_ `int32 LastSpawnedPointID;`
- L253 _public function_ `FNiagaraDIChaosDestruction_InstanceDataToPassToRT()`

#### enum `EDataSortTypeEnum`  
`enum class EDataSortTypeEnum : uint8`  
_L260-269_
- reflection: `UENUM(BlueprintType)`
- L262 _public enumerator_ `ChaosNiagara_DataSortType_NoSorting UMETA(DisplayName = "No Sorting")`
- L263 _public enumerator_ `ChaosNiagara_DataSortType_RandomShuffle UMETA(DisplayName = "Random Shuffle")`
- L264 _public enumerator_ `ChaosNiagara_DataSortType_SortByMassMaxToMin UMETA(DisplayName = "Sort by Mass - Max to Min")`
- L265 _public enumerator_ `ChaosNiagara_DataSortType_SortByMassMinToMax UMETA(DisplayName = "Sort by Mass - Min to Max")`
- L268 _public enumerator_ `ChaosNiagara_Max UMETA(Hidden)` — 256th entry

#### enum `ERandomVelocityGenerationTypeEnum`  
`enum class ERandomVelocityGenerationTypeEnum : uint8`  
_L272-281_
- reflection: `UENUM(BlueprintType)`
- L274 _public enumerator_ `ChaosNiagara_RandomVelocityGenerationType_RandomDistribution UMETA(DisplayName = "Random Distribution")`
- L275 _public enumerator_ `ChaosNiagara_RandomVelocityGenerationType_RandomDistributionWithStreamers UMETA(DisplayName = "Random Distribution with Streamers")`
- L276 _public enumerator_ `ChaosNiagara_RandomVelocityGenerationType_CollisionNormalBased UMETA(DisplayName = "Collision Normal Based (Collision Data Only)")`
- L280 _public enumerator_ `ChaosNiagara_Max UMETA(Hidden)` — 256th entry

#### enum `EDebugTypeEnum`  
`enum class EDebugTypeEnum : uint8`  
_L284-292_
- reflection: `UENUM(BlueprintType)`
- L286 _public enumerator_ `ChaosNiagara_DebugType_NoDebug UMETA(DisplayName = "No Debug")`
- L287 _public enumerator_ `ChaosNiagara_DebugType_ColorBySolver UMETA(DisplayName = "Color by Solver")`
- L288 _public enumerator_ `ChaosNiagara_DebugType_ColorByParticleIndex UMETA(DisplayName = "Color by ParticleIndex")`
- L291 _public enumerator_ `ChaosNiagara_Max UMETA(Hidden)` — 256th entry

#### enum `EDataSourceTypeEnum`  
`enum class EDataSourceTypeEnum : uint8`  
_L295-303_
- reflection: `UENUM(BlueprintType)`
- L297 _public enumerator_ `ChaosNiagara_DataSourceType_Collision UMETA(DisplayName = "Collision Data")`
- L298 _public enumerator_ `ChaosNiagara_DataSourceType_Breaking UMETA(DisplayName = "Breaking Data")`
- L299 _public enumerator_ `ChaosNiagara_DataSourceType_Trailing UMETA(DisplayName = "Trailing Data")`
- L302 _public enumerator_ `ChaosNiagara_Max UMETA(Hidden)` — 256th entry

#### enum `ELocationFilteringModeEnum`  
`enum class ELocationFilteringModeEnum : uint8`  
_L306-313_
- reflection: `UENUM(BlueprintType)`
- L308 _public enumerator_ `ChaosNiagara_LocationFilteringMode_Inclusive UMETA(DisplayName = "Inclusive")`
- L309 _public enumerator_ `ChaosNiagara_LocationFilteringMode_Exclusive UMETA(DisplayName = "Exclusive")`
- L312 _public enumerator_ `ChaosNiagara_Max UMETA(Hidden)` — 256th entry

#### enum `ELocationXToSpawnEnum`  
`enum class ELocationXToSpawnEnum : uint8`  
_L316-325_
- reflection: `UENUM(BlueprintType)`
- L318 _public enumerator_ `ChaosNiagara_LocationXToSpawn_None UMETA(DisplayName = "None")`
- L319 _public enumerator_ `ChaosNiagara_LocationXToSpawn_Min UMETA(DisplayName = "Min <= LocationX")`
- L320 _public enumerator_ `ChaosNiagara_LocationXToSpawn_Max UMETA(DisplayName = "LocationX <= Max")`
- L321 _public enumerator_ `ChaosNiagara_LocationXToSpawn_MinMax UMETA(DisplayName = "Min <= LocationX <= Max")`
- L324 _public enumerator_ `ChaosNiagara_Max UMETA(Hidden)` — 256th entry

#### enum `ELocationYToSpawnEnum`  
`enum class ELocationYToSpawnEnum : uint8`  
_L328-337_
- reflection: `UENUM(BlueprintType)`
- L330 _public enumerator_ `ChaosNiagara_LocationYToSpawn_None UMETA(DisplayName = "None")`
- L331 _public enumerator_ `ChaosNiagara_LocationYToSpawn_Min UMETA(DisplayName = "Min <= LocationY")`
- L332 _public enumerator_ `ChaosNiagara_LocationYToSpawn_Max UMETA(DisplayName = "LocationY <= Max")`
- L333 _public enumerator_ `ChaosNiagara_LocationYToSpawn_MinMax UMETA(DisplayName = "Min <= LocationY <= Max")`
- L336 _public enumerator_ `ChaosNiagara_Max UMETA(Hidden)` — 256th entry

#### enum `ELocationZToSpawnEnum`  
`enum class ELocationZToSpawnEnum : uint8`  
_L340-349_
- reflection: `UENUM(BlueprintType)`
- L342 _public enumerator_ `ChaosNiagara_LocationZToSpawn_None UMETA(DisplayName = "None")`
- L343 _public enumerator_ `ChaosNiagara_LocationZToSpawn_Min UMETA(DisplayName = "Min <= LocationZ")`
- L344 _public enumerator_ `ChaosNiagara_LocationZToSpawn_Max UMETA(DisplayName = "LocationZ <= Max")`
- L345 _public enumerator_ `ChaosNiagara_LocationZToSpawn_MinMax UMETA(DisplayName = "Min <= LocationZ <= Max")`
- L348 _public enumerator_ `ChaosNiagara_Max UMETA(Hidden)` — 256th entry

#### class `UNiagaraDataInterfaceChaosDestruction`  
`class UNiagaraDataInterfaceChaosDestruction : public UNiagaraDataInterface`  
_L353-773_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Category = "Chaos Niagara", meta = (DisplayName = "Chaos Destruction Data"))`
- inherits: `UNiagaraDataInterface`
- desc: Data Interface allowing sampling of Chaos Destruction data.
- L360 _public member_ `TSet<TObjectPtr<AChaosSolverActor>> ChaosSolverActorSet;` — `UPROPERTY(EditAnywhere, Category = "Solver", meta = (DisplayName = "Chaos Solver"))` — Chaos Solver
- L364 _public member_ `EDataSourceTypeEnum DataSourceType;` — `UPROPERTY(EditAnywhere, Category = "Solver Data", meta = (DisplayName = "Data Source"))`
- L368 _public member_ `int32 DataProcessFrequency;` — `UPROPERTY(EditAnywhere, Category = "Solver Data", meta = (DisplayName = "Data Process Frequency", UIMin = 0))` — Number of times the RBD collision data gets processed every second
- L372 _public member_ `int32 MaxNumberOfDataEntriesToSpawn;` — `UPROPERTY(EditAnywhere, Category = "Solver Data", meta = (DisplayName = "Max Number of Data to Spawn Particles", UIMin = 0))` — Maximum number of collision/breaking/trailing entry used for spawning particles every time data from the physics solver gets processed
- L376 _public member_ `bool DoSpawn;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings", meta = (DisplayName = "Spawn Particles"))` — Turn on/off particle spawning
- L380 _public member_ `FVector2D SpawnMultiplierMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings", meta = (DisplayName = "Spawn Count Min/Max", UIMin = 0))` — For every collision random number of particles will be spawned in the range of [SpawnMultiplierMin, SpawnMultiplierMax]
- L384 _public member_ `float SpawnChance;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings", meta = (DisplayName = "Chance to Spawn", UIMin = 0.f, UIMax = 1.f))` — For every collision random number of particles will be spawned in the range of [SpawnMultiplierMin, SpawnMultiplierMax]
- L388 _public member_ `FVector2D ImpulseToSpawnMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Min/Max Collision Impulse To Spawn Particles", UIMin = 0.0))` — Min/Max collision accumulated impulse to spawn particles
- L392 _public member_ `FVector2D SpeedToSpawnMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Min/Max Speed To Spawn Particles", UIMin = 0.0))` — Min/Max speed to spawn particles
- L396 _public member_ `FVector2D MassToSpawnMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Min/Max Mass To Spawn Particles", UIMin = 0.0))` — Min/Max mass to spawn particles
- L400 _public member_ `FVector2D ExtentMinToSpawnMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Min/Max ExtentMin To Spawn Particles", UIMin = 0.0))` — Min/Max ExtentMin to spawn particles
- L404 _public member_ `FVector2D ExtentMaxToSpawnMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Min/Max ExtentMax To Spawn Particles", UIMin = 0.0))` — Min/Max ExtentMax to spawn particles
- L408 _public member_ `FVector2D VolumeToSpawnMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Min/Max Volume To Spawn Particles", UIMin = 0.0))` — Min/Max volume to spawn particles
- L412 _public member_ `FVector2D SolverTimeToSpawnMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Min/Max SolverTime To Spawn Particles", UIMin = 0.0))` — Min/Max solver time mass to spawn particles
- L416 _public member_ `int32 SurfaceTypeToSpawn;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "SurfaceType To Spawn Particles", UIMin = 0.0))` — SurfaceType to spawn particles
- L420 _public member_ `ELocationFilteringModeEnum LocationFilteringMode;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Location Filtering Mode"))` — Location Filtering Mode
- L424 _public member_ `ELocationXToSpawnEnum LocationXToSpawn;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "LocationX To Spawn Particles"))` — How to use LocationX to filter
- L428 _public member_ `FVector2D LocationXToSpawnMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Min/Max LocationX To Spawn Particles", UIMin = 0.0))` — Min/Max LocationX to spawn particles
- L432 _public member_ `ELocationYToSpawnEnum LocationYToSpawn;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "LocationY To Spawn Particles"))` — How to use LocationY to filter
- L436 _public member_ `FVector2D LocationYToSpawnMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Min/Max LocationY To Spawn Particles", UIMin = 0.0))` — Min/Max LocationY to spawn particles
- L440 _public member_ `ELocationZToSpawnEnum LocationZToSpawn;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "LocationZ To Spawn Particles"))` — How to use LocationZ to filter
- L444 _public member_ `FVector2D LocationZToSpawnMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Thresholds to Spawn", meta = (DisplayName = "Min/Max LocationZ To Spawn Particles", UIMin = 0.0))` — Min/Max LocationX to spawn particles
- L448 _public member_ `float TrailMinSpeedToSpawn;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Trailing - Thresholds to Spawn", meta = (DisplayName = "Min Speed To Spawn Trailing Particles", UIMin = 0.0))` — Min Linear Speed to generate trailing particles
- L454 _public member_ `EDataSortTypeEnum DataSortingType;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings - Sorting Solver Data", meta = (DisplayName = "Sorting Method"))` — Sorting method to sort the collision data
- L458 _public member_ `bool bGetExternalCollisionData;` — `UPROPERTY(VisibleAnywhere, Category = "Collision Data Settings", meta = (DisplayName = "Get External Collision Mesh and Physical Data"))` — TODO: Explanatory comment
- L462 _public member_ `bool DoSpatialHash;` — `UPROPERTY(EditAnywhere, Category = "Collision Data Settings", meta = (DisplayName = "Spatial Hash Collision/Breaking Data", UIMin = 0.0))`
- L466 _public member_ `FVector SpatialHashVolumeMin;` — `UPROPERTY(EditAnywhere, Category = "SpatialHash Settings", meta = (DisplayName = "SpatialHash Volume Min"))` — SpatialHash volume min
- L470 _public member_ `FVector SpatialHashVolumeMax;` — `UPROPERTY(EditAnywhere, Category = "SpatialHash Settings", meta = (DisplayName = "SpatialHash Volume Max"))` — SpatialHash volume max
- L474 _public member_ `FVector SpatialHashVolumeCellSize;` — `UPROPERTY(EditAnywhere, Category = "SpatialHash Settings", meta = (DisplayName = "SpatialHash Volume CellSize"))` — SpatialHash volume resolution
- L478 _public member_ `int32 MaxDataPerCell;` — `UPROPERTY(EditAnywhere, Category = "SpatialHash Settings", meta = (DisplayName = "Max Number of Collision/Breaking Per Cell", UIMin = 1))`
- L482 _public member_ `bool bApplyMaterialsFilter;` — `UPROPERTY(EditAnywhere, Category = "Data Settings", meta = (DisplayName = "Apply Materials Filter"))` — Materials Filter
- L486 _public member_ `TSet<TObjectPtr<UPhysicalMaterial>> ChaosBreakingMaterialSet;` — `UPROPERTY(EditAnywhere, Category = "Data Settings", meta = (DisplayName = "Filtered Materials", EditCondition = bApplyMaterialsFilter))` — TODO: Explanatory comment
- L490 _public member_ `bool bGetExternalBreakingData;` — `UPROPERTY(EditAnywhere, Category = "Data Settings", meta = (DisplayName = "Get External Breaking Mesh and Physical Data"))` — TODO: Explanatory comment
- L494 _public member_ `bool bGetExternalTrailingData;` — `UPROPERTY(VisibleAnywhere, Category = "Data Settings", meta = (DisplayName = "Get External Trailing Mesh and Physical Data"))` — TODO: Explanatory comment
- L498 _public member_ `FVector2D RandomPositionMagnitudeMinMax;` — `UPROPERTY(EditAnywhere, Category = "Spawn Position Settings", meta = (DisplayName = "Position Random Spread Magnitude Min/Max", UIMin = 0.0))` — Random displacement value for the particle spawn position
- L502 _public member_ `float InheritedVelocityMultiplier;` — `UPROPERTY(EditAnywhere, Category = "Velocity Settings - Inherited Velocity", meta = (DisplayName = "Inherited Velocity Multiplier"))` — How much of the collision velocity gets inherited
- L508 _public member_ `ERandomVelocityGenerationTypeEnum RandomVelocityGenerationType;` — `UPROPERTY(EditAnywhere, Category = "Velocity Settings - Random Generation", meta = (DisplayName = "Velocity Model"))` — The method used to create the random velocities for the newly spawned particles
- L512 _public member_ `FVector2D RandomVelocityMagnitudeMinMax;` — `UPROPERTY(EditAnywhere, Category = "Velocity Settings", meta = (DisplayName = "Velocity Random Magnitude Min/Max", UIMin = 0.0))` — Every particles will be spawned with random velocity with magnitude in the range of [RandomVelocityMagnitudeMin, RandomVelocityMagnitudeMax]
- L516 _public member_ `float SpreadAngleMax;` — `UPROPERTY(EditAnywhere, Category = "Velocity Settings - Collision Normal Based Velocity Model", meta = (DisplayName = "Spread Angle Max [Degrees]", UIMin = 0.0))` — /
- L520 _public member_ `FVector VelocityOffsetMin;` — `UPROPERTY(EditAnywhere, Category = "Velocity Settings", meta = (DisplayName = "Velocity Offset Min"))` — Min Offset value added to spawned particles velocity
- L524 _public member_ `FVector VelocityOffsetMax;` — `UPROPERTY(EditAnywhere, Category = "Velocity Settings", meta = (DisplayName = "Velocity Offset Max"))` — Max Offset value added to spawned particles velocity
- L528 _public member_ `FVector2D FinalVelocityMagnitudeMinMax;` — `UPROPERTY(EditAnywhere, Category = "Velocity Settings", meta = (DisplayName = "Final Velocity Magnitude Maximum"))` — Clamp particles velocity
- L531 _public member_ `float MaxLatency;` — `UPROPERTY(EditAnywhere, Category = "Spawn Settings", meta = (DisplayName = "Max Latency"))`
- L535 _public member_ `EDebugTypeEnum DebugType;` — `UPROPERTY(EditAnywhere, Category = "Debug Settings", meta = (DisplayName = "Debug Visualization"))` — Debug visualization method
- L543 _public prototype_ `virtual void PostInitProperties() override;` — UObject Interface
- L544 _public prototype_ `virtual void PostLoad() override;`
- L545 _public prototype_ `virtual void BeginDestroy() override;`
- L547 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L552 _public prototype_ `virtual bool InitPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance) override;` — UNiagaraDataInterface Interface
- L553 _public prototype_ `virtual void DestroyPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance) override;`
- L554 _public prototype_ `virtual bool PerInstanceTick(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance, float DeltaSeconds) override;`
- L555 _public prototype_ `virtual int32 PerInstanceDataSize() const override;`
- L557 _public prototype_ `virtual void GetVMExternalFunction(const FVMExternalFunctionBindingInfo& BindingInfo, void* InstanceData, FVMExternalFunction &OutFunc) override;`
- L558 _public prototype_ `virtual bool Equals(const UNiagaraDataInterface* Other) const override;`
- L559 _public function_ `virtual bool CanExecuteOnTarget(ENiagaraSimTarget Target) const override`
- L561 _public function_ `virtual bool HasPreSimulateTick() const override`
- L565 _public prototype_ `virtual bool AppendCompileHash(FNiagaraCompileHashVisitor* InVisitor) const override;`
- L566 _public prototype_ `virtual void GetParameterDefinitionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, FString& OutHLSL) override;`
- L567 _public prototype_ `virtual bool GetFunctionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, const FNiagaraDataInterfaceGeneratedFunction& FunctionInfo, int FunctionInstanceIndex, FString& OutHLSL) override;`
- L569 _public prototype_ `virtual void BuildShaderParameters(FNiagaraShaderParametersBuilder& ShaderParametersBuilder) const override;`
- L570 _public prototype_ `virtual void SetShaderParameters(const FNiagaraDataInterfaceSetShaderParametersContext& Context) const override;`
- L575 _public prototype_ `template<typename ParticleIDParamType> void GetPosition(FVectorVMExternalFunctionContext& Context);` — EXPOSED FUNCTIONS
- L578 _public prototype_ `template<typename ParticleIDParamType> void GetNormal(FVectorVMExternalFunctionContext& Context);`
- L581 _public prototype_ `template<typename ParticleIDParamType> void GetVelocity(FVectorVMExternalFunctionContext& Context);`
- L584 _public prototype_ `template<typename ParticleIDParamType> void GetAngularVelocity(FVectorVMExternalFunctionContext& Context);`
- L587 _public prototype_ `template<typename ParticleIDParamType> void GetExtentMin(FVectorVMExternalFunctionContext& Context);`
- L590 _public prototype_ `template<typename ParticleIDParamType> void GetExtentMax(FVectorVMExternalFunctionContext& Context);`
- L593 _public prototype_ `template<typename ParticleIDParamType> void GetVolume(FVectorVMExternalFunctionContext& Context);`
- L596 _public prototype_ `template<typename TimeParamType> void GetParticleIdsToSpawnAtTime(FVectorVMExternalFunctionContext& Context);`
- L599 _public prototype_ `template<typename ParticleIDParamType> void GetPointType(FVectorVMExternalFunctionContext& Context);`
- L602 _public prototype_ `template<typename ParticleIDParamType> void GetColor(FVectorVMExternalFunctionContext& Context);`
- L605 _public prototype_ `template<typename ParticleIDParamType> void GetSolverTime(FVectorVMExternalFunctionContext& Context);`
- L608 _public prototype_ `template<typename ParticleIDParamType> void GetDensity(FVectorVMExternalFunctionContext& Context);`
- L611 _public prototype_ `template<typename ParticleIDParamType> void GetFriction(FVectorVMExternalFunctionContext& Context);`
- L614 _public prototype_ `template<typename ParticleIDParamType> void GetRestitution(FVectorVMExternalFunctionContext& Context);`
- L617 _public prototype_ `template<typename ParticleIDParamType> void GetSize(FVectorVMExternalFunctionContext& Context);`
- L620 _public prototype_ `template<typename ParticleIDParamType> void GetTransform(FVectorVMExternalFunctionContext& Context);`
- L623 _public prototype_ `template<typename ParticleIDParamType> void GetSurfaceType(FVectorVMExternalFunctionContext& Context);`
- L626 _public prototype_ `template<typename ParticleIDParamType> void GetCollisionData(FVectorVMExternalFunctionContext& Context);`
- L629 _public prototype_ `template<typename ParticleIDParamType> void GetBreakingData(FVectorVMExternalFunctionContext& Context);`
- L632 _public prototype_ `template<typename ParticleIDParamType> void GetTrailingData(FVectorVMExternalFunctionContext& Context);`
- L635 _public function_ `inline static bool CollisionDataSortByMassPredicateMaxToMin(const Chaos::FCollidingDataExt& Lhs, const Chaos::FCollidingDataExt& Rhs)` — Sort predicates to sort data
- L640 _public function_ `inline static bool CollisionDataSortByMassPredicateMinToMax(const Chaos::FCollidingDataExt& Lhs, const Chaos::FCollidingDataExt& Rhs)`
- L645 _public function_ `inline static bool CollisionDataRandomShuffleSortPredicate(const Chaos::FCollidingDataExt& Lhs, const Chaos::FCollidingDataExt& Rhs)`
- L650 _public function_ `inline static bool BreakingDataSortByMassPredicateMaxToMin(const Chaos::FBreakingDataExt& Lhs, const Chaos::FBreakingDataExt& Rhs)`
- L655 _public function_ `inline static bool BreakingDataSortByMassPredicateMinToMax(const Chaos::FBreakingDataExt& Lhs, const Chaos::FBreakingDataExt& Rhs)`
- L660 _public function_ `inline static bool BreakingDataRandomShuffleSortPredicate(const Chaos::FBreakingDataExt& Lhs, const Chaos::FBreakingDataExt& Rhs)`
- L665 _public function_ `inline static bool TrailingDataSortByMassPredicateMaxToMin(const Chaos::FTrailingDataExt& Lhs, const Chaos::FTrailingDataExt& Rhs)`
- L670 _public function_ `inline static bool TrailingDataSortByMassPredicateMinToMax(const Chaos::FTrailingDataExt& Lhs, const Chaos::FTrailingDataExt& Rhs)`
- L675 _public function_ `inline static bool TrailingDataRandomShuffleSortPredicate(const Chaos::FTrailingDataExt& Lhs, const Chaos::FTrailingDataExt& Rhs)`
- L680 _public function_ `inline int32 GetLastSpawnedPointID()`
- L684 _public function_ `inline float GetSolverTime()`
- L689 _public prototype_ `virtual void ProvidePerInstanceDataForRenderThread(void* DataForRenderThread, void* PerInstanceData, const FNiagaraSystemInstanceID& SystemInstance) override;`
- L693 _protected prototype_ `virtual void GetFunctionsInternal(TArray<FNiagaraFunctionSignature>& OutFunctions) const override;`
- L696 _protected prototype_ `void RegisterWithSolverEventManager(Chaos::FPhysicsSolver* Solver);`
- L697 _protected prototype_ `virtual bool CopyToInternal(UNiagaraDataInterface* Destination) const override;`
- L699 _protected prototype_ `void ResetInstData(FNDIChaosDestruction_InstanceData* InstData);`
- L701 _protected prototype_ `void HandleCollisionEvents(const Chaos::FCollisionEventData& Event);`
- L702 _protected prototype_ `void FilterAllCollisions(TArray<Chaos::FCollidingDataExt>& AllCollisionsArray);`
- L704 _protected prototype_ `void SortCollisions(TArray<Chaos::FCollidingDataExt>& CollisionsArray);`
- L706 _protected prototype_ `void GetCollisionsToSpawnFromCollisions(TArray<Chaos::FCollidingDataExt>& AllCollisionsArray, TArray<Chaos::FCollidingDataExt>& CollisionsToSpawnArray);`
- L709 _protected prototype_ `int32 SpawnParticlesFromCollision(FSolverData SolverData, Chaos::FCollidingDataExt& Collision, FNDIChaosDestruction_InstanceData* InstData, float TimeData_MapsCreated, int32 IdxSolver);`
- L715 _protected prototype_ `void HandleBreakingEvents(const Chaos::FBreakingEventData& Event);`
- L716 _protected prototype_ `void FilterAllBreakings(TArray<Chaos::FBreakingDataExt>& AllBreakingsArray);`
- L718 _protected prototype_ `void SortBreakings(TArray<Chaos::FBreakingDataExt>& BreakingsArray);`
- L720 _protected prototype_ `void GetBreakingsToSpawnFromBreakings(TArray<Chaos::FBreakingDataExt>& AllBreakingsArray, TArray<Chaos::FBreakingDataExt>& BreakingsToSpawnArray);`
- L723 _protected prototype_ `int32 SpawnParticlesFromBreaking(FSolverData SolverData, Chaos::FBreakingDataExt& Breaking, FNDIChaosDestruction_InstanceData* InstData, float TimeData_MapsCreated, int32 IdxSolver);`
- L729 _protected prototype_ `void HandleTrailingEvents(const Chaos::FTrailingEventData& Event);`
- L730 _protected prototype_ `void FilterAllTrailings(TArray<Chaos::FTrailingDataExt>& AllTrailingsArray);`
- L732 _protected prototype_ `void SortTrailings(TArray<Chaos::FTrailingDataExt>& TrailingsArray);`
- L734 _protected prototype_ `void GetTrailingsToSpawnFromTrailings(TArray<Chaos::FTrailingDataExt>& AllTrailingsArray, TArray<Chaos::FTrailingDataExt>& TrailingsToSpawnArray);`
- L737 _protected prototype_ `int32 SpawnParticlesFromTrailing(FSolverData SolverData, Chaos::FTrailingDataExt& Trailing, FNDIChaosDestruction_InstanceData* InstData, float TimeData_MapsCreated, int32 IdxSolver);`
- L743 _protected prototype_ `bool CollisionCallback(FNDIChaosDestruction_InstanceData* InstData);`
- L744 _protected prototype_ `bool BreakingCallback(FNDIChaosDestruction_InstanceData* InstData);`
- L745 _protected prototype_ `bool TrailingCallback(FNDIChaosDestruction_InstanceData* InstData);`
- L747 _protected prototype_ `virtual void PushToRenderThreadImpl() override;`
- L750 _protected member_ `int32 LastSpawnedPointID;` — `UPROPERTY()`
- L753 _protected member_ `float LastSpawnTime;` — `UPROPERTY()`
- L756 _protected member_ `TArray<FVector> ColorArray;` — Colors for debugging particles
- L759 _protected member_ `float SolverTime;` — `UPROPERTY()`
- L762 _protected member_ `float TimeStampOfLastProcessedData;` — `UPROPERTY()`
- L764 _protected member_ `bool ShouldSpawn;`
- L766 _protected member_ `TArray<FSolverData> Solvers;`
- L767 _protected member_ `TArray<Chaos::FCollidingDataExt> CollisionEvents;`
- L768 _protected member_ `TArray<Chaos::FBreakingDataExt> BreakingEvents;`
- L769 _protected member_ `TArray<Chaos::FTrailingDataExt> TrailingEvents;`
- L772 _protected member_ `TSet<TWeakObjectPtr<UGeometryCollectionComponent>> TrailingGeometryCollectionComponents;` — geometry collection to track for trailing

#### struct `FNiagaraDataInterfaceProxyChaosDestruction`  
`struct FNiagaraDataInterfaceProxyChaosDestruction : public FNiagaraDataInterfaceProxy`  
_L775-790_
- inherits: `FNiagaraDataInterfaceProxy`
- L777 _public prototype_ `virtual void ConsumePerInstanceDataFromGameThread(void* PerInstanceData, const FNiagaraSystemInstanceID& Instance) override;`
- L778 _public function_ `virtual int32 PerInstanceDataPassedToRenderThreadSize() const override`
- L780 _public prototype_ `virtual void PostSimulate(const FNDIGpuComputePostSimulateContext& Context) override;`
- L782 _public prototype_ `void CreatePerInstanceData(const FNiagaraSystemInstanceID& SystemInstance);`
- L784 _public prototype_ `void DestroyInstanceData(const FNiagaraSystemInstanceID& SystemInstance);`
- L786 _public member_ `float SolverTime;`
- L787 _public member_ `int32 LastSpawnedPointID;`
- L789 _public member_ `TMap<FNiagaraSystemInstanceID, FNiagaraDIChaosDestruction_GPUData> SystemsToGPUInstanceData;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API CHAOSNIAGARA_API`
- L16 _namespace_ `namespace Chaos`
- L17 _namespace_ `namespace Chaos`
- L18 _namespace_ `namespace Chaos`

### `Plugins/Experimental/ChaosNiagara/Source/ChaosNiagara/Classes/NiagaraDataInterfacePhysicsField.h` (Public)


#### struct `FNDIFieldRenderData`  
`struct FNDIFieldRenderData`  
_L15-22_
- desc: Data stored per physics asset instance on the render thread
- L18 _public member_ `class FPhysicsFieldResource* FieldResource;` — Field render resource for gpu
- L21 _public member_ `float TimeSeconds = 0.0;` — Time in seconds

#### struct `FNDIPhysicsFieldData`  
`struct FNDIPhysicsFieldData`  
_L25-46_
- desc: Data stored per physics asset instance on the game thread
- L28 _public prototype_ `void Init(FNiagaraSystemInstance* SystemInstance);` — Initialize the resource
- L31 _public prototype_ `void Update(FNiagaraSystemInstance* SystemInstance);` — Update the commands
- L34 _public prototype_ `void Release();` — Release the buffers
- L37 _public member_ `class FPhysicsFieldResource* FieldResource;` — Field render resource for gpu
- L40 _public member_ `TArray<FFieldSystemCommand> FieldCommands;` — Field system commands for cpu
- L43 _public member_ `float TimeSeconds = 0.0;` — Time in seconds
- L45 _public member_ `FNiagaraLWCConverter LWCConverter;`

#### class `UNiagaraDataInterfacePhysicsField`  
`class UNiagaraDataInterfacePhysicsField : public UNiagaraDataInterface`  
_L50-108_
- reflection: `UCLASS(MinimalAPI, EditInlineNew, Category = "Chaos", meta = (DisplayName = "Physics Field"))`
- inherits: `UNiagaraDataInterface`
- desc: Data Interface for the strand base
- L55 _public prototype_ `UNiagaraDataInterfacePhysicsField();`
- L58 _public prototype_ `virtual void PostInitProperties() override;` — UObject Interface
- L61 _public prototype_ `virtual void GetVMExternalFunction(const FVMExternalFunctionBindingInfo& BindingInfo, void* InstanceData, FVMExternalFunction& OutFunc) override;` — UNiagaraDataInterface Interface
- L62 _public function_ `virtual bool CanExecuteOnTarget(ENiagaraSimTarget Target) const override`
- L64 _public function_ `virtual bool ShouldCompile(EShaderPlatform ShaderPlatform) const override`
- L67 _public prototype_ `virtual bool InitPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance) override;`
- L68 _public prototype_ `virtual void DestroyPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance)override;`
- L69 _public prototype_ `virtual bool PerInstanceTickPostSimulate(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance, float DeltaSeconds) override;`
- L70 _public function_ `virtual int32 PerInstanceDataSize()const override`
- L71 _public prototype_ `virtual bool Equals(const UNiagaraDataInterface* Other) const override;`
- L72 _public function_ `virtual bool HasPostSimulateTick() const override`
- L76 _public prototype_ `virtual bool AppendCompileHash(FNiagaraCompileHashVisitor* InVisitor) const override;`
- L77 _public prototype_ `virtual void GetParameterDefinitionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, FString& OutHLSL) override;`
- L78 _public prototype_ `virtual bool GetFunctionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, const FNiagaraDataInterfaceGeneratedFunction& FunctionInfo, int FunctionInstanceIndex, FString& OutHLSL) override;`
- L79 _public prototype_ `virtual bool UpgradeFunctionCall(FNiagaraFunctionSignature& FunctionSignature) override;`
- L81 _public prototype_ `virtual void BuildShaderParameters(FNiagaraShaderParametersBuilder& ShaderParametersBuilder) const override;`
- L82 _public prototype_ `virtual void SetShaderParameters(const FNiagaraDataInterfaceSetShaderParametersContext& Context) const override;`
- L84 _public prototype_ `virtual void ProvidePerInstanceDataForRenderThread(void* DataForRenderThread, void* PerInstanceData, const FNiagaraSystemInstanceID& SystemInstance) override;`
- L87 _public prototype_ `void SamplePhysicsVectorField(FVectorVMExternalFunctionContext& Context);` — Sample the vector field
- L90 _public prototype_ `void SamplePhysicsScalarField(FVectorVMExternalFunctionContext& Context);` — Sample the scalar field
- L93 _public prototype_ `void SamplePhysicsIntegerField(FVectorVMExternalFunctionContext& Context);` — Sample the integer field
- L96 _public prototype_ `void GetPhysicsFieldResolution(FVectorVMExternalFunctionContext& Context);` — Get the field resolution
- L99 _public prototype_ `void GetPhysicsFieldBounds(FVectorVMExternalFunctionContext& Context);` — Get the field bounds
- L103 _protected prototype_ `virtual void GetFunctionsInternal(TArray<FNiagaraFunctionSignature>& OutFunctions) const override;`
- L107 _protected prototype_ `virtual bool CopyToInternal(UNiagaraDataInterface* Destination) const override;` — Copy one niagara DI to this

#### struct `FNDIPhysicsFieldProxy`  
`struct FNDIPhysicsFieldProxy : public FNiagaraDataInterfaceProxy`  
_L111-127_
- inherits: `FNiagaraDataInterfaceProxy`
- desc: Proxy to send data to gpu
- L114 _public function_ `virtual int32 PerInstanceDataPassedToRenderThreadSize() const override` — Get the size of the data that will be passed to render
- L117 _public prototype_ `virtual void ConsumePerInstanceDataFromGameThread(void* PerInstanceData, const FNiagaraSystemInstanceID& Instance) override;` — Get the data that will be passed to render
- L120 _public prototype_ `void InitializePerInstanceData(const FNiagaraSystemInstanceID& SystemInstance);` — Initialize the per instance data
- L123 _public prototype_ `void DestroyPerInstanceData(const FNiagaraSystemInstanceID& SystemInstance);` — Destroy the proxy data if necessary
- L126 _public member_ `TMap<FNiagaraSystemInstanceID, FNDIFieldRenderData> SystemInstancesToProxyData;` — List of proxy data for each system instances

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CHAOSNIAGARA_API`

### `Plugins/Experimental/ChaosNiagara/Source/ChaosNiagara/Public/ChaosNiagara.h` (Public)


#### class `FChaosNiagaraModule`  
`class FChaosNiagaraModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/ChaosNiagara/Source/ChaosNiagara/Public/NiagaraDataInterfaceGeometryCollection.h` (Public)


#### struct `FNDIGeometryCollectionArrays`  
`struct FNDIGeometryCollectionArrays`  
_L16-63_
- desc: Arrays in which the cpu datas will be str
- L18 _public member_ `TArray<FVector4f> WorldTransformBuffer;`
- L19 _public member_ `TArray<FVector4f> PrevWorldTransformBuffer;`
- L20 _public member_ `TArray<FVector4f> WorldInverseTransformBuffer;`
- L21 _public member_ `TArray<FVector4f> PrevWorldInverseTransformBuffer;`
- L22 _public member_ `TArray<FVector4f> BoundsBuffer;`
- L23 _public member_ `TArray<FTransform> ComponentRestTransformBuffer;`
- L24 _public member_ `TArray<uint32> ElementIndexToTransformBufferMapping;`
- L26 _public function_ `FNDIGeometryCollectionArrays()`
- L31 _public function_ `FNDIGeometryCollectionArrays(uint32 Num)`
- L36 _public function_ `void CopyFrom(const FNDIGeometryCollectionArrays* Other)`
- L49 _public function_ `void Resize(uint32 Num)`
- L62 _public member_ `uint32 NumPieces = 100;`

#### struct `FNDIGeometryCollectionBuffer`  
`struct FNDIGeometryCollectionBuffer : public FRenderResource`  
_L66-105_
- inherits: `FRenderResource`
- desc: Render buffers that will be used in hlsl functions
- L69 _public prototype_ `virtual void InitRHI(FRHICommandListBase& RHICmdList) override;` — Init the buffer
- L72 _public prototype_ `virtual void ReleaseRHI() override;` — Release the buffer
- L75 _public function_ `virtual FString GetFriendlyName() const override` — Get the resource name
- L78 _public member_ `FReadBuffer WorldTransformBuffer;` — World transform buffer
- L81 _public member_ `FReadBuffer PrevWorldTransformBuffer;` — Inverse transform buffer
- L84 _public member_ `FReadBuffer WorldInverseTransformBuffer;` — World transform buffer
- L87 _public member_ `FReadBuffer PrevWorldInverseTransformBuffer;` — Inverse transform buffer
- L90 _public member_ `FReadBuffer BoundsBuffer;` — Element extent buffer
- L93 _public member_ `TRefCountPtr<FRDGPooledBuffer> ComponentRestTransformBuffer;` — Per-element transform buffer
- L96 _public member_ `TArray<uint8> DataToUpload;` — Raw data for the transform buffer
- L99 _public member_ `int32 NumPieces;` — number of transforms
- L101 _public function_ `void SetNumPieces(int32 Num)`

#### struct `FResolvedNiagaraGeometryCollection`  
`struct FResolvedNiagaraGeometryCollection`  
_L107-116_
- L109 _public prototype_ `const UGeometryCollection* GetGeometryCollection() const;`
- L110 _public prototype_ `FTransform GetComponentRootTransform(FNiagaraSystemInstance* SystemInstance) const;`
- L111 _public prototype_ `FTransform GetComponentSpaceTransform(int32 TransformIndex) const;`
- L112 _public prototype_ `TArray<FTransform> GetLocalRestTransforms() const;`
- L114 _public member_ `TWeakObjectPtr<UGeometryCollection> Collection;`
- L115 _public member_ `TWeakObjectPtr<UGeometryCollectionComponent> Component;`

#### struct `FNDIGeometryCollectionData`  
`struct FNDIGeometryCollectionData`  
_L119-156_
- desc: Data stored per physics asset instance
- L122 _public prototype_ `void Init(class UNiagaraDataInterfaceGeometryCollection* Interface, FNiagaraSystemInstance* SystemInstance);` — Initialize the cpu datas
- L125 _public prototype_ `void Update(class UNiagaraDataInterfaceGeometryCollection* Interface, FNiagaraSystemInstance* SystemInstance);` — Update the gpu datas
- L128 _public prototype_ `void Release();` — Release the buffers
- L130 _public prototype_ `ETickingGroup ComputeTickingGroup();`
- L133 _public member_ `ETickingGroup TickingGroup;` — The instance ticking group
- L136 _public member_ `FTransform RootTransform;` — Actor or geometry collection component world transform, adjusted by lwc system tile
- L139 _public member_ `FVector3f BoundsOrigin;` — Geometry Collection Bounds
- L141 _public member_ `FVector3f BoundsExtent;`
- L144 _public member_ `FNDIGeometryCollectionBuffer* AssetBuffer = nullptr;` — Physics asset Gpu buffer
- L147 _public member_ `FNDIGeometryCollectionArrays* AssetArrays = nullptr;` — Physics asset Cpu arrays
- L150 _public member_ `bool bHasPendingComponentTransformUpdate = false;` — Flag when there pending transform writes that need to go back to the component
- L153 _public member_ `bool bNeedsRenderUpdate = false;` — True if we need to upload new data to the gpu
- L155 _public member_ `FResolvedNiagaraGeometryCollection ResolvedSource;`

#### enum `ENDIGeometryCollection_SourceMode`  
`enum class ENDIGeometryCollection_SourceMode : uint8`  
_L159-181_
- reflection: `UENUM()`
- L168 _public enumerator_ `Default` — Default behavior follows the order of. - Use "Source" when specified (either set explicitly or via blueprint with Set Niagara Geometry Collection Component). - Use Parameter Binding if valid - Find Geometry Collection Component, Attached Actor, Attached Component - Falls back to 'Default Geometry Collection' specified on the data interface
- L171 _public enumerator_ `Source` — Only use "Source" (either set explicitly or via blueprint with Set Niagara Geometry Collection Component).
- L174 _public enumerator_ `AttachParent` — Only use the parent actor or component the system is attached to.
- L177 _public enumerator_ `DefaultCollectionOnly` — Only use the "Default Geometry Collection" specified.
- L180 _public enumerator_ `ParameterBinding` — Only use the parameter binding.

#### class `UNiagaraDataInterfaceGeometryCollection`  
`class UNiagaraDataInterfaceGeometryCollection : public UNiagaraDataInterface`  
_L185-289_
- reflection: `UCLASS(EditInlineNew, Category = "Chaos", meta = (DisplayName = "Geometry Collection"), MinimalAPI)`
- inherits: `UNiagaraDataInterface`
- desc: Data Interface for the Collisions
- L190 _private prototype_ `SHADER_PARAMETER(FVector3f, BoundsMin) SHADER_PARAMETER(FVector3f, BoundsMax) SHADER_PARAMETER(int32, NumPieces) SHADER_PARAMETER(FVector3f, RootTransform_Translation) SHADER_PARAMETER(FQuat4f, RootTransform_Rotation) SHADER_PARAMETER(FVector3f, RootTransform_Scale) SHADER_PARAMETER_SRV(Buffer<float4>, WorldTransformBuffer) SHADER_PARAMETER_SRV(Buffer<float4>, PrevWorldTransformBuffer) SHADER_PARAMETER_SRV(Buffer<float4>, WorldInverseTransformBuffer) SHADER_PARAMETER_SRV(Buffer<float4>, PrevWorldInverseTransformBuffer) SHADER_PARAMETER_SRV(Buffer<float4>, BoundsBuffer) SHADER_PARAMETER_RDG_BUFFER_SRV(ByteAddressBuffer, ElementTransforms) END_SHADER_PARAMETER_STRUCT() UPROPERTY(EditAnywhere, Category = "Geometry Collection") ENDIGeometryCollection_SourceMode SourceMode = ENDIGeometryCollection_SourceMode::Default;`
- L211 _private member_ `TSoftObjectPtr<UGeometryCollection> PreviewCollection;` — `UPROPERTY(EditAnywhere, Category = "Geometry Collection")` — Geometry collection used to sample from when not overridden by a source actor from the scene. Only available in editor for previewing. This is removed in cooked builds.
- L216 _private member_ `TObjectPtr<UGeometryCollection> DefaultGeometryCollection;` — `UPROPERTY(EditAnywhere, Category = "Geometry Collection", meta = (EditConditionHides, EditCondition = "SourceMode == ENDIGeometryCollection_SourceMode::Default || SourceMode == ENDIGeometryCollection_SourceMode::DefaultCollectionOnly"))` — GeometryCollection used to sample from when not overridden by a source actor from the scene. This reference is NOT removed from cooked builds.
- L220 _private member_ `TSoftObjectPtr<AGeometryCollectionActor> GeometryCollectionActor;` — `UPROPERTY(EditAnywhere, Category = "Geometry Collection", meta = (DisplayName = "Source Actor", EditConditionHides, EditCondition = "SourceMode == ENDIGeometryCollection_SourceMode::Default || SourceMode == ENDIGeometryCollection_SourceMode::Source"))` — The source actor from which to sample. Takes precedence over the direct geometry collection. Note that this can only be set when used as a user variable on a niagara component in the world.
- L224 _private member_ `TObjectPtr<UGeometryCollectionComponent> SourceComponent;` — `UPROPERTY(Transient)` — The source component from which to sample. Takes precedence over the direct mesh. Not exposed to the user, only indirectly accessible from blueprints.
- L228 _private member_ `FNiagaraUserParameterBinding GeometryCollectionUserParameter;` — `UPROPERTY(EditAnywhere, Category = "Geometry Collection", meta = (EditConditionHides, EditCondition = "SourceMode == ENDIGeometryCollection_SourceMode::Default || SourceMode == ENDIGeometryCollection_SourceMode::ParameterBinding"))` — Reference to a user parameter if we're reading one.
- L232 _private member_ `bool bIncludeIntermediateBones = false;` — `UPROPERTY(EditAnywhere, Category = "Geometry Collection")` — If true then this data interface will also read and write intermediate bones or geometry, otherwise only leaf nodes are considered
- L235 _private prototype_ `virtual void PostInitProperties() override;` — UObject Interface
- L238 _private prototype_ `virtual void GetVMExternalFunction(const FVMExternalFunctionBindingInfo& BindingInfo, void* InstanceData, FVMExternalFunction& OutFunc) override;` — UNiagaraDataInterface Interface
- L239 _private function_ `virtual bool CanExecuteOnTarget(ENiagaraSimTarget Target) const override`
- L240 _private prototype_ `virtual bool InitPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance) override;`
- L241 _private prototype_ `virtual void DestroyPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance)override;`
- L242 _private prototype_ `virtual bool PerInstanceTick(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance, float DeltaSeconds) override;`
- L243 _private function_ `virtual int32 PerInstanceDataSize()const override`
- L244 _private prototype_ `virtual bool PerInstanceTickPostSimulate(void* PerInstanceData, FNiagaraSystemInstance* InSystemInstance, float DeltaSeconds) override;`
- L245 _private prototype_ `virtual bool Equals(const UNiagaraDataInterface* Other) const override;`
- L246 _private function_ `virtual bool HasPreSimulateTick() const override`
- L247 _private function_ `virtual bool HasPostSimulateTick() const override`
- L248 _private function_ `virtual bool PostSimulateCanOverlapFrames() const override`
- L249 _private function_ `virtual bool HasTickGroupPrereqs() const override`
- L250 _private prototype_ `virtual ETickingGroup CalculateTickGroup(const void* PerInstanceData) const override;`
- L255 _private prototype_ `virtual bool AppendCompileHash(FNiagaraCompileHashVisitor* InVisitor) const override;`
- L256 _private prototype_ `virtual void GetParameterDefinitionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, FString& OutHLSL) override;`
- L257 _private prototype_ `virtual bool GetFunctionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, const FNiagaraDataInterfaceGeneratedFunction& FunctionInfo, int FunctionInstanceIndex, FString& OutHLSL) override;`
- L258 _private prototype_ `virtual bool UpgradeFunctionCall(FNiagaraFunctionSignature& FunctionSignature) override;`
- L260 _private prototype_ `virtual void BuildShaderParameters(FNiagaraShaderParametersBuilder& ShaderParametersBuilder) const override;`
- L261 _private prototype_ `virtual void SetShaderParameters(const FNiagaraDataInterfaceSetShaderParametersContext& Context) const override;`
- L263 _private prototype_ `virtual void ProvidePerInstanceDataForRenderThread(void* DataForRenderThread, void* PerInstanceData, const FNiagaraSystemInstanceID& SystemInstance) override;`
- L267 _private prototype_ `void GetNumGeometryElements(FVectorVMExternalFunctionContext& Context);` — VM functions
- L268 _private prototype_ `void GetElementBounds(FVectorVMExternalFunctionContext& Context);`
- L269 _private prototype_ `void GetElementTransformCS(FVectorVMExternalFunctionContext& Context);`
- L270 _private prototype_ `void SetElementTransformCS(FVectorVMExternalFunctionContext& Context);`
- L271 _private prototype_ `void SetElementTransformWS(FVectorVMExternalFunctionContext& Context);`
- L272 _private prototype_ `void GetActorTransform(FVectorVMExternalFunctionContext& Context);`
- L276 _protected prototype_ `virtual void GetFunctionsInternal(TArray<FNiagaraFunctionSignature>& OutFunctions) const override;`
- L280 _protected prototype_ `virtual bool CopyToInternal(UNiagaraDataInterface* Destination) const override;` — Copy one niagara DI to this
- L283 _private prototype_ `void ResolveGeometryCollection(FNiagaraSystemInstance* SystemInstance, FNDIGeometryCollectionData* InstanceData);`
- L284 _private prototype_ `bool ResolveGeometryCollectionFromDirectSource(FResolvedNiagaraGeometryCollection& ResolvedSource);`
- L285 _private prototype_ `bool ResolveGeometryCollectionFromAttachParent(FNiagaraSystemInstance* SystemInstance, FResolvedNiagaraGeometryCollection& ResolvedSource);`
- L286 _private prototype_ `bool ResolveGeometryCollectionFromActor(AActor* Actor, FResolvedNiagaraGeometryCollection& ResolvedSource);`
- L287 _private prototype_ `bool ResolveGeometryCollectionFromDefaultCollection(FResolvedNiagaraGeometryCollection& ResolvedSource);`
- L288 _private prototype_ `bool ResolveGeometryCollectionFromParameterBinding(UObject* UserParameter, FResolvedNiagaraGeometryCollection& ResolvedSource);`

#### struct `FNDIGeometryCollectionProxy`  
`struct FNDIGeometryCollectionProxy : public FNiagaraDataInterfaceProxy`  
_L292-311_
- inherits: `FNiagaraDataInterfaceProxy`
- desc: Proxy to send data to gpu
- L295 _public function_ `virtual int32 PerInstanceDataPassedToRenderThreadSize() const override` — Get the size of the data that will be passed to render
- L298 _public prototype_ `virtual void ConsumePerInstanceDataFromGameThread(void* PerInstanceData, const FNiagaraSystemInstanceID& Instance) override;` — Get the data that will be passed to render
- L301 _public prototype_ `void InitializePerInstanceData(const FNiagaraSystemInstanceID& SystemInstance);` — Initialize the Proxy data buffer
- L304 _public prototype_ `void DestroyPerInstanceData(const FNiagaraSystemInstanceID& SystemInstance);` — Destroy the proxy data if necessary
- L307 _public prototype_ `virtual void PreStage(const FNDIGpuComputePreStageContext& Context) override;` — Launch all pre stage functions
- L310 _public member_ `TMap<FNiagaraSystemInstanceID, FNDIGeometryCollectionData> SystemInstancesToProxyData;` — List of proxy data for each system instances
