# Developer / HierarchicalLODUtilities

- module root: `Source/Developer/HierarchicalLODUtilities`
- headers: 4; symbols: 114
- symbol kinds: class=5, enum=1, enumerator=11, macro=1, member=10, prototype=85, struct=1
- DynamicallyLoadedModuleNames: GeometryProcessingInterfaces, MeshMergeUtilities, MeshReductionInterface, MeshUtilities
- PrivateDependencyModuleNames: BSPUtils, EditorFramework, Engine, MaterialUtilities, MeshDescription, Projects, StaticMeshDescription, UnrealEd
- PrivateIncludePathModuleNames: GeometryProcessingInterfaces
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Developer/HierarchicalLODUtilities/Public/HierarchicalLODProxyProcessor.h` (Public)


#### class `FHierarchicalLODProxyProcessor`  
`class FHierarchicalLODProxyProcessor : public FTSTickerObjectBase`  
_L16-75_
- inherits: `FTSTickerObjectBase`
- L19 _public prototype_ `FHierarchicalLODProxyProcessor();`
- L20 _public prototype_ `~FHierarchicalLODProxyProcessor();`
- L23 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — Begin FTSTickerObjectBase
- L33 _public prototype_ `FGuid AddProxyJob(ALODActor* InLODActor, UHLODProxy* InProxy, const FHierarchicalSimplification& LODSetup);` — AddProxyJob @param InLODActor - LODActor for which the mesh will be generated @param InProxy - The proxy mesh used to store the mesh @param LODSetup - Simplification settings structure @return FGuid - Guid for the job
- L39 _public prototype_ `void ProcessProxy(const FGuid InGuid, TArray<UObject*>& InAssetsToSync);` — Callback function used for processing finished mesh generation jobs @param InGuid - Guid of the finished job @param InAssetsToSync - Assets data created by the job
- L42 _public prototype_ `FCreateProxyDelegate& GetCallbackDelegate();` — Returns the callback delegate which will be passed onto ProxyLOD function
- L44 _public prototype_ `bool IsProxyGenerationRunning() const;`
- L47 _protected prototype_ `void OnMapChange(uint32 MapFlags);` — Called when the map has changed
- L50 _protected prototype_ `void OnNewCurrentLevel();` — Called when the current level has changed
- L53 _protected prototype_ `void ClearProcessingData();` — Clears the processing data array/map
- L69 _private member_ `TMap<FGuid, FProcessData*> JobActorMap;` — Map and array used to store job data
- L70 _private member_ `TArray<FProcessData*> ToProcessJobs;`
- L72 _private member_ `FCreateProxyDelegate CallbackDelegate;` — Delegate to pass onto
- L74 _private member_ `FCriticalSection StateLock;` — Critical section to keep JobActorMap/ToProcessJobs access thread-safe

#### struct `FHierarchicalLODProxyProcessor::FProcessData`  
`struct FProcessData`  
_L56-66_
- desc: Structure storing the data required during processing
- L59 _public member_ `ALODActor* LODActor;` — LODActor instance for which a proxy is generated
- L61 _public member_ `UHLODProxy* Proxy;` — Proxy mesh where the rendering data is stored
- L63 _public member_ `TArray<TStrongObjectPtr<UObject>> AssetObjects;` — Array with resulting asset objects from proxy generation (StaticMesh/Materials/Textures)
- L65 _public member_ `FHierarchicalSimplification LODSetup;` — HLOD settings structure used for creating the proxy

### `Source/Developer/HierarchicalLODUtilities/Public/HierarchicalLODUtilities.h` (Public)


#### class `FHierarchicalLODUtilities`  
`class FHierarchicalLODUtilities : public IHierarchicalLODUtilities`  
_L21-59_
- inherits: `IHierarchicalLODUtilities`
- desc: FHierarchicalLODUtilities implementation
- L24 _public prototype_ `~FHierarchicalLODUtilities() = default;`
- L26 _public prototype_ `virtual void ExtractSubActorsFromLODActor(AActor* Actor, TArray<AActor*>& InOutActors) override;`
- L27 _public prototype_ `virtual float CalculateScreenSizeFromDrawDistance(const float SphereRadius, const FMatrix& ProjectionMatrix, const float Distance) override;`
- L28 _public prototype_ `virtual float CalculateDrawDistanceFromScreenSize(const float SphereRadius, const float ScreenSize, const FMatrix& ProjectionMatrix) override;`
- L29 _public prototype_ `virtual UPackage* CreateOrRetrieveLevelHLODPackage(const ULevel* InLevel, const uint32 HLODLevelIndex) override;`
- L30 _public prototype_ `virtual UPackage* RetrieveLevelHLODPackage(const ULevel* InLevel, const uint32 HLODLevelIndex) override;`
- L31 _public prototype_ `virtual UHLODProxy* CreateOrRetrieveLevelHLODProxy(const ULevel* InLevel, const uint32 HLODLevelIndex) override;`
- L32 _public prototype_ `virtual UHLODProxy* RetrieveLevelHLODProxy(const ULevel* InLevel, const uint32 HLODLevelIndex) override;`
- L33 _public prototype_ `virtual FString GetWildcardOfHLODPackagesForPackage(const FString& PackageName) override;`
- L34 _public prototype_ `virtual FString GetLevelHLODProxyName(const FString& InLevelPackageName, const uint32 HLODLevelIndex) override;`
- L35 _public prototype_ `virtual bool BuildStaticMeshForLODActor(ALODActor* LODActor, UHLODProxy* Proxy, const FHierarchicalSimplification& LODSetup, UMaterialInterface* InBaseMaterial) override;`
- L36 _public prototype_ `virtual EClusterGenerationError ShouldGenerateCluster(AActor* Actor, const int32 HLODLevelIndex) override;`
- L37 _public prototype_ `virtual ALODActor* GetParentLODActor(const AActor* InActor) override;`
- L38 _public prototype_ `virtual void DestroyCluster(ALODActor* InActor) override;`
- L39 _public prototype_ `virtual ALODActor* CreateNewClusterActor(UWorld* InWorld, const int32 InLODLevel, AWorldSettings* WorldSettings) override;`
- L40 _public prototype_ `virtual ALODActor* CreateNewClusterFromActors(UWorld* InWorld, AWorldSettings* WorldSettings, const TArray<AActor*>& InActors, const int32 InLODLevel = 0) override;`
- L41 _public prototype_ `virtual const bool RemoveActorFromCluster(AActor* InActor) override;`
- L42 _public prototype_ `virtual const bool AddActorToCluster(AActor* InActor, ALODActor* InParentActor) override;`
- L43 _public prototype_ `virtual const bool MergeClusters(ALODActor* TargetCluster, ALODActor* SourceCluster) override;`
- L44 _public prototype_ `virtual const bool AreActorsInSamePersistingLevel(const TArray<AActor*>& InActors) override;`
- L45 _public prototype_ `virtual const bool AreClustersInSameHLODLevel(const TArray<ALODActor*>& InLODActors) override;`
- L46 _public prototype_ `virtual const bool AreActorsInSameHLODLevel(const TArray<AActor*>& InActors) override;`
- L47 _public prototype_ `virtual const bool AreActorsClustered(const TArray<AActor*>& InActors) override;`
- L48 _public prototype_ `virtual const bool IsActorClustered(const AActor* InActor) override;`
- L49 _public prototype_ `virtual void ExcludeActorFromClusterGeneration(AActor* InActor) override;`
- L50 _public prototype_ `virtual void DestroyLODActor(ALODActor* InActor) override;`
- L51 _public prototype_ `virtual void ExtractStaticMeshActorsFromLODActor(ALODActor* LODActor, TArray<AActor*> &InOutActors) override;`
- L52 _public prototype_ `virtual void DeleteLODActorsInHLODLevel(UWorld* InWorld, const int32 HLODLevelIndex) override;`
- L53 _public prototype_ `virtual int32 ComputeStaticMeshLODLevel(const TArray<FStaticMeshSourceModel>& SourceModels, const FStaticMeshRenderData* RenderData, const float ScreenSize) override;`
- L54 _public prototype_ `virtual int32 GetLODLevelForScreenSize(const UStaticMeshComponent* StaticMeshComponent, const float ScreenSize) override;`
- L55 _public prototype_ `virtual AHierarchicalLODVolume* CreateVolumeForLODActor(ALODActor* InLODActor, UWorld* InWorld) override;`
- L56 _public prototype_ `virtual void HandleActorModified(AActor* InActor) override;`
- L57 _public prototype_ `virtual bool IsWorldUsedForStreaming(const UWorld* InWorld) override;`
- L58 _public prototype_ `virtual void CleanStandaloneAssetsInPackage(UPackage* InPackage) override;`

### `Source/Developer/HierarchicalLODUtilities/Public/HierarchicalLODUtilitiesModule.h` (Public)


#### class `IHierarchicalLODUtilitiesModule`  
`class IHierarchicalLODUtilitiesModule : public IModuleInterface`  
_L13-19_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual FHierarchicalLODProxyProcessor* GetProxyProcessor() = 0;`
- L18 _public prototype_ `virtual IHierarchicalLODUtilities* GetUtilities() = 0;`

#### class `FHierarchicalLODUtilitiesModule`  
`class FHierarchicalLODUtilitiesModule : public IHierarchicalLODUtilitiesModule`  
_L24-36_
- inherits: `IHierarchicalLODUtilitiesModule`
- desc: IHierarchicalLODUtilities module interface
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L31 _public prototype_ `virtual FHierarchicalLODProxyProcessor* GetProxyProcessor() override;` — Returns the Proxy processor instance from within this module
- L32 _public prototype_ `virtual IHierarchicalLODUtilities* GetUtilities() override;`
- L34 _private member_ `FHierarchicalLODProxyProcessor* ProxyProcessor;`
- L35 _private member_ `IHierarchicalLODUtilities* Utilities;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HIERARCHICALLODUTILITIES_API`

### `Source/Developer/HierarchicalLODUtilities/Public/IHierarchicalLODUtilities.h` (Public)


#### enum `EClusterGenerationError`  
`enum class EClusterGenerationError : uint32`  
_L18-31_
- L20 _public enumerator_ `None = 0`
- L21 _public enumerator_ `ValidActor = 1 << 1`
- L22 _public enumerator_ `InvalidActor = 1 << 2`
- L23 _public enumerator_ `ActorHiddenInGame = 1 << 3`
- L24 _public enumerator_ `ExcludedActor = 1 << 4`
- L25 _public enumerator_ `LODActor = 1 << 5`
- L26 _public enumerator_ `ActorTooSmall = 1 << 6`
- L27 _public enumerator_ `AlreadyClustered = 1 << 7`
- L28 _public enumerator_ `ComponentHiddenInGame = 1 << 8`
- L29 _public enumerator_ `MoveableComponent = 1 << 9`
- L30 _public enumerator_ `ExcludedComponent = 1 << 10`

#### class `IHierarchicalLODUtilities`  
`class IHierarchicalLODUtilities`  
_L38-178_
- desc: IHierarchicalLODUtilities module interface
- L41 _public prototype_ `virtual ~IHierarchicalLODUtilities() = default;`
- L49 _public prototype_ `virtual void ExtractSubActorsFromLODActor(AActor* Actor, TArray<AActor*>& InOutActors) = 0;` — Recursively retrieves Actors from a LODActor and its child LODActors @param Actor - LODActor instance @param InOutComponents - Will hold the StaticMeshComponents
- L52 _public prototype_ `virtual float CalculateScreenSizeFromDrawDistance(const float SphereRadius, const FMatrix& ProjectionMatrix, const float Distance) = 0;` — Computes the Screensize of the given Sphere taking into account the ProjectionMatrix and distance
- L54 _public prototype_ `virtual float CalculateDrawDistanceFromScreenSize(const float SphereRadius, const float ScreenSize, const FMatrix& ProjectionMatrix) = 0;`
- L57 _public prototype_ `virtual UPackage* CreateOrRetrieveLevelHLODPackage(const ULevel* InLevel, const uint32 HLODLevelIndex) = 0;` — Creates or retrieves the HLOD package that is created for the given level
- L60 _public prototype_ `virtual UPackage* RetrieveLevelHLODPackage(const ULevel* InLevel, const uint32 HLODLevelIndex) = 0;` — Retrieves the HLOD package that is created for the given level
- L63 _public prototype_ `virtual UHLODProxy* CreateOrRetrieveLevelHLODProxy(const ULevel* InLevel, const uint32 HLODLevelIndex) = 0;` — Creates or retrieves the HLOD proxy that is created for the given level
- L66 _public prototype_ `virtual UHLODProxy* RetrieveLevelHLODProxy(const ULevel* InLevel, const uint32 HLODLevelIndex) = 0;` — Retrieves the HLOD proxy that is created for the given level
- L69 _public prototype_ `virtual FString GetWildcardOfHLODPackagesForPackage(const FString& PackageName) = 0;` — Retrieves a wildcard that includes all possible HLOD packagenames that could be used by the given package.
- L72 _public prototype_ `virtual FString GetLevelHLODProxyName(const FString& InLevelPackageName, const uint32 HLODLevelIndex) = 0;` — Get the name of a HLOD proxy given the name of a level's package
- L81 _public prototype_ `virtual bool BuildStaticMeshForLODActor(ALODActor* LODActor, UHLODProxy* Proxy, const FHierarchicalSimplification& LODSetup, UMaterialInterface* InBaseMaterial) = 0;` — Builds a virtual mesh object for the given LODACtor @param LODActor - Actor to build the mesh for @param Outer - Outer object to store the mesh in @return UStaticMesh*
- L89 _public prototype_ `virtual EClusterGenerationError ShouldGenerateCluster(AActor* Actor, const int32 HLODLevelIndex) = 0;` — Returns whether or not the given actor is eligible for creating a HLOD cluster creation @param Actor - Actor to check for if it is eligible for cluster generation @return EClusterGenerationError
- L92 _public prototype_ `virtual ALODActor* GetParentLODActor(const AActor* InActor) = 0;` — Returns the ALODActor parent for the given InActor, nullptr if none available
- L95 _public prototype_ `virtual void DestroyCluster(ALODActor* InActor) = 0;` — Deletes the given cluster's data and instance in the world
- L98 _public prototype_ `virtual ALODActor* CreateNewClusterActor(UWorld* InWorld, const int32 InLODLevel, AWorldSettings* WorldSettings) = 0;` — Creates a new cluster actor in the given InWorld with InLODLevel as HLODLevel
- L101 _public prototype_ `virtual ALODActor* CreateNewClusterFromActors(UWorld* InWorld, AWorldSettings* WorldSettings, const TArray<AActor*>& InActors, const int32 InLODLevel = 0) = 0;` — Creates a new cluster in InWorld with InActors as sub actors
- L104 _public prototype_ `virtual const bool RemoveActorFromCluster(AActor* InActor) = 0;` — Removes the given actor from it's parent cluster
- L107 _public prototype_ `virtual const bool AddActorToCluster(AActor* InActor, ALODActor* InParentActor) = 0;` — Adds an actor to the given cluster
- L110 _public prototype_ `virtual const bool MergeClusters(ALODActor* TargetCluster, ALODActor* SourceCluster) = 0;` — Merges two clusters together
- L113 _public prototype_ `virtual const bool AreActorsInSamePersistingLevel(const TArray<AActor*>& InActors) = 0;` — Checks if all actors have the same outer world
- L116 _public prototype_ `virtual const bool AreClustersInSameHLODLevel(const TArray<ALODActor*>& InLODActors) = 0;` — Checks if all clusters are in the same HLOD level
- L119 _public prototype_ `virtual const bool AreActorsInSameHLODLevel(const TArray<AActor*>& InActors) = 0;` — Checks if all actors are in the same HLOD level
- L122 _public prototype_ `virtual const bool AreActorsClustered(const TArray<AActor*>& InActors) = 0;` — Checks if all actors are part of a cluster
- L125 _public prototype_ `virtual const bool IsActorClustered(const AActor* InActor) = 0;` — Checks if an actor is clustered
- L128 _public prototype_ `virtual void ExcludeActorFromClusterGeneration(AActor* InActor) = 0;` — Excludes an actor from the cluster generation process
- L135 _public prototype_ `virtual void DestroyLODActor(ALODActor* InActor) = 0;` — Destroys an LODActor instance @param InActor - ALODActor to destroy
- L143 _public prototype_ `virtual void ExtractStaticMeshActorsFromLODActor(ALODActor* LODActor, TArray<AActor*> &InOutActors) = 0;` — Extracts all the virtual Mesh Actors from the given LODActor's SubActors array @param LODActor - LODActors to check the SubActors array for @param InOutActors - Array to fill with virtual Mesh Actors
- L146 _public prototype_ `virtual void DeleteLODActorsInHLODLevel(UWorld* InWorld, const int32 HLODLevelIndex) = 0;` — Deletes all the ALODActors with the given HLODLevelIndex inside off InWorld
- L149 _public prototype_ `virtual int32 ComputeStaticMeshLODLevel(const TArray<FStaticMeshSourceModel>& SourceModels, const FStaticMeshRenderData* RenderData, const float ScreenSize) = 0;` — Computes which LOD level of a Mesh corresponds to the given Distance (calculates closest ScreenSize with distance)
- L152 _public prototype_ `virtual int32 GetLODLevelForScreenSize(const UStaticMeshComponent* StaticMeshComponent, const float ScreenSize) = 0;` — Computes the LODLevel for a StaticMeshComponent taking into account the ScreenSize
- L160 _public prototype_ `virtual AHierarchicalLODVolume* CreateVolumeForLODActor(ALODActor* InLODActor, UWorld* InWorld) = 0;` — Creates a HierarchicalLODVolume using the bounds of a given LODActor @param InLODActor - LODActor to create the volume for @param InWorld - World to spawn the volume in. If null, will spawn in the same level as InLODActor. @return AHierarchicalLODVolume*
- L166 _public prototype_ `virtual void HandleActorModified(AActor* InActor) = 0;` — Handles changes in actors for the current world, checks if InActor is part of a HLOD cluster and if so set its dirty-flag @param InActor - Actor to check and find cluster for
- L171 _public prototype_ `virtual bool IsWorldUsedForStreaming(const UWorld* InWorld) = 0;` — Checks whether or not the given InWorld is used as a streaming level by any other World in the level @param InWorld - World to check whether or not it is used as a streaming level
- L177 _public prototype_ `virtual void CleanStandaloneAssetsInPackage(UPackage* InPackage) = 0;` — Cleans any standalone flags for meshes, textures and materials. This ensures that they get garbage collected when not referenced any more. @param InPackage	The HLOD package to clean

#### Free symbols / members of external scopes

- L33 _prototype_ `ENUM_CLASS_FLAGS(EClusterGenerationError);`
