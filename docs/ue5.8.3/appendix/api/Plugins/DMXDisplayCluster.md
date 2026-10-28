# Plugins / DMXDisplayCluster

- module root: `Plugins/VirtualProduction/DMX/DMXDisplayCluster/Source/DMXDisplayCluster`
- headers: 2; symbols: 19
- symbol kinds: class=2, function=1, member=7, prototype=9
- PrivateDependencyModuleNames: Core, CoreUObject, DMXProtocol, DMXRuntime, DisplayCluster, Engine
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/DMX/DMXDisplayCluster/Source/DMXDisplayCluster/Private/DMXDisplayClusterModule.h` (Private)


#### class `FDMXDisplayClusterModule`  
`class FDMXDisplayClusterModule : public IModuleInterface`  
_L11-25_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _protected prototype_ `void CreateDMXDisplayClusterReplicator();` — Setup the DisplayCluster replicator
- L24 _protected member_ `TSharedPtr<FDMXDisplayClusterReplicator> DMXDisplayClusterReplicator;` — The replicator instance

### `Plugins/VirtualProduction/DMX/DMXDisplayCluster/Source/DMXDisplayCluster/Private/DMXDisplayClusterReplicator.h` (Private)


#### class `FDMXDisplayClusterReplicator`  
`class FDMXDisplayClusterReplicator : public FTickableGameObject , public TSharedFromThis<FDMXDisplayClusterReplicator>`  
_L15-52_
- inherits: `FTickableGameObject,TSharedFromThis<FDMXDisplayClusterReplicator>`
- desc: Replicates input ports on tick
- L20 _public prototype_ `FDMXDisplayClusterReplicator();`
- L22 _public prototype_ `virtual ~FDMXDisplayClusterReplicator();`
- L26 _private prototype_ `void OnClusterEventReceived(const FDisplayClusterClusterEventBinary& Event);` — Called whena cluster event was received
- L29 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L30 _private function_ `virtual bool IsTickableInEditor() const override`
- L31 _private prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L32 _private prototype_ `virtual TStatId GetStatId() const override;`
- L36 _private member_ `bool bClusterEventEmitter;` — True if it is a cluster event emitter, else it is a cluster event receiver
- L39 _private member_ `ETickableTickType TickType;` — The tick type used (always for emitter, never for listener)
- L42 _private member_ `FOnClusterEventBinaryListener BinaryListener;` — Listen for DisplayCluster DMX events
- L45 _private member_ `TArray<FDMXInputPortSharedRef> CachedInputPorts;` — Input porst currently in use
- L48 _private member_ `TArray<TSharedPtr<FDMXRawListener>> RawListeners;` — Raw listeners for the input ports
- L51 _private member_ `TMap<int32, FDMXSignalSharedPtr> ExternUniverseToSignalForReplicationMap;` — Map of latest Singals that needs be replicated per extern Universe. Used to only replicate latest data on tick.
