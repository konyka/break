# Plugins / DisplayClusterRemoteControlInterceptor

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterRemoteControlInterceptor`
- headers: 3; symbols: 24
- symbol kinds: class=2, delegate=1, member=5, prototype=16
- PrivateDependencyModuleNames: Core, CoreUObject, DisplayCluster, Engine, RemoteControlInterception, Serialization, UnrealEd

### `Plugins/Runtime/nDisplay/Source/DisplayClusterRemoteControlInterceptor/Private/DisplayClusterRemoteControlInterceptor.h` (Private)


#### class `FDisplayClusterRemoteControlInterceptor`  
`class FDisplayClusterRemoteControlInterceptor : public IRemoteControlInterceptionFeatureInterceptor`  
_L14-62_
- inherits: `IRemoteControlInterceptionFeatureInterceptor`
- desc: Remote control interceptor feature
- L18 _public prototype_ `FDisplayClusterRemoteControlInterceptor();`
- L19 _public prototype_ `virtual ~FDisplayClusterRemoteControlInterceptor();`
- L23 _public prototype_ `virtual ERCIResponse SetObjectProperties(FRCIPropertiesMetadata& InProperties) override;` — IRemoteControlInterceptionCommands interface
- L24 _public prototype_ `virtual ERCIResponse ResetObjectProperties(FRCIObjectMetadata& InObject) override;`
- L25 _public prototype_ `virtual ERCIResponse InvokeCall(FRCIFunctionMetadata& InFunction) override;`
- L26 _public prototype_ `virtual ERCIResponse SetPresetController(FRCIControllerMetadata& InController) override;`
- L31 _private prototype_ `void OnClusterEventBinaryHandler(const FDisplayClusterClusterEventBinary& Event);` — Cluster events handler/dispatcher
- L34 _private prototype_ `void QueueInterceptEvent(const FName& InterceptEventType, const FName& InUniquePath, TArray<uint8>&& InBuffer);` — Queue unique intercept event for sending on next engine tick
- L38 _private prototype_ `void OnReplication_SetObjectProperties (const TArray<uint8>& Buffer);` — Process SetObjectProperties command replication data
- L40 _private prototype_ `void OnReplication_ResetObjectProperties (const TArray<uint8>& Buffer);` — Process ResetObjectProperties command replication data
- L42 _private prototype_ `void OnReplication_InvokeCall (const TArray<uint8>& Buffer);` — Process InvokeCall command replication data
- L44 _private prototype_ `void OnReplication_SetPresetController(const TArray<uint8>& Buffer);` — Process SetPresetController command replication data
- L46 _private prototype_ `void SendReplicationQueue();` — Send the queue of replication events at the end of the tick
- L50 _private member_ `const bool bInterceptOnPrimaryOnly;` — CVar value PrimaryOnly
- L52 _private member_ `FOnClusterEventBinaryListener EventsListener;` — Cluster events listener
- L54 _private member_ `bool bForceApply;` — Force Apply the ERCIResponse
- L61 _private member_ `TMap<FName, TMap<FName, TArray<uint8>>> InterceptQueueMap;` — FName name of the metadata struct FName unique object path + field path TArray<uint8> Metadata struct buffer

### `Plugins/Runtime/nDisplay/Source/DisplayClusterRemoteControlInterceptor/Private/DisplayClusterRemoteControlInterceptorLog.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterRemoteControlInterceptor, Log, All);` — Module-wide log categories
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterRemoteControlInterceptor, Log, All);` — Module-wide log categories

### `Plugins/Runtime/nDisplay/Source/DisplayClusterRemoteControlInterceptor/Private/DisplayClusterRemoteControlInterceptorModule.h` (Private)


#### class `FDisplayClusterRemoteControlInterceptorModule`  
`class FDisplayClusterRemoteControlInterceptorModule : public IModuleInterface`  
_L14-27_
- inherits: `IModuleInterface`
- desc: Remote control interceptor module
- L21 _public prototype_ `virtual void StartupModule() override;`
- L22 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _private member_ `TUniquePtr<IRemoteControlInterceptionFeatureInterceptor> Interceptor;` — RC Interceptor feature instance
