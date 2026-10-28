# Plugins / PCGFastGeoInterop

- module root: `Plugins/Experimental/PCGInterops/PCGFastGeoInterop/Source/PCGFastGeoInterop`
- headers: 3; symbols: 30
- symbol kinds: class=3, function=6, member=8, prototype=13
- PrivateDependencyModuleNames: FastGeoStreaming, PCG
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/PCGInterops/PCGFastGeoInterop/Source/PCGFastGeoInterop/Private/Components/PCGManagedFastGeoContainer.h` (Private)


#### class `UPCGManagedFastGeoContainer`  
`class UPCGManagedFastGeoContainer : public UPCGManagedResource`  
_L14-36_
- reflection: `UCLASS()`
- inherits: `UPCGManagedResource`
- L20 _public prototype_ `virtual bool Release(bool bHardRelease, TSet<TSoftObjectPtr<AActor>>& OutActorsToDelete) override;`
- L21 _public function_ `virtual bool ReleaseOnTeardown() const override`
- L24 _public function_ `void SetFastGeoContainer(UFastGeoContainer* InFastGeo)`
- L27 _public function_ `void SetObjectReferences(TArray<TObjectPtr<UObject>>&& InObjectReferences)` — Set references to objects to be kept alive.
- L31 _protected member_ `TObjectPtr<UFastGeoContainer> FastGeo;` — `UPROPERTY(Transient)`
- L35 _protected member_ `TArray<TObjectPtr<UObject>> ObjectReferences;` — `UPROPERTY(Transient)` — Referenced objects to be kept alive.

### `Plugins/Experimental/PCGInterops/PCGFastGeoInterop/Source/PCGFastGeoInterop/Private/Compute/PrimitiveFactories/PCGPrimitiveFactoryFastGeoPISMC.h` (Private)


#### class `FPCGPrimitiveFactoryFastGeoPISMC`  
`class FPCGPrimitiveFactoryFastGeoPISMC : public IPCGPrimitiveFactoryISMBase`  
_L15-48_
- inherits: `IPCGPrimitiveFactoryISMBase`
- L19 _public prototype_ `virtual bool IsRenderStateCreated() const override;`
- L20 _public function_ `virtual int32 GetNumPrimitives() const override`
- L21 _public prototype_ `virtual FPrimitiveSceneProxy* GetSceneProxy(int32 InPrimitiveIndex) const override;`
- L22 _public function_ `virtual bool IsPrimitiveValid(int32 InPrimitiveIndex) const override`
- L23 _public prototype_ `virtual int32 GetNumInstances(int32 InPrimitiveIndex, int32 InCellID) const override;`
- L24 _public prototype_ `virtual int32 GetNumInstancesTotal(int32 InPrimitiveIndex) const override;`
- L25 _public prototype_ `virtual bool IsAnyRenderStateDirty() const override;`
- L29 _public prototype_ `virtual void Initialize(FParameters&& InParameters) override;`
- L30 _public prototype_ `virtual bool Create(FPCGContext* InContext) override;`
- L31 _public prototype_ `virtual FBox GetMeshBounds(int32 InPrimitiveIndex) const override;`
- L35 _protected prototype_ `TArray<TObjectPtr<UObject>> CollectObjectReferences();`
- L38 _protected member_ `TArray<FPCGPrimitiveInfo> PrimitiveInfos;`
- L39 _protected member_ `FPCGPackedCustomData CustomPrimitiveData;`
- L41 _protected member_ `TArray<FWeakFastGeoComponent> Components;`
- L42 _protected member_ `TArray<int32> InstanceCounts;`
- L43 _protected member_ `TArray<FBox> MeshBounds;`
- L47 _protected member_ `TSharedRef<bool> bFastGeoRegistered = MakeShared<bool>(false);` — Shared so the OnRegistered lambda can safely write to it even if this factory is destroyed before the container finishes registration.

### `Plugins/Experimental/PCGInterops/PCGFastGeoInterop/Source/PCGFastGeoInterop/Public/PCGFastGeoInteropModule.h` (Public)


#### class `FPCGFastGeoInteropModule`  
`class FPCGFastGeoInteropModule final : public IModuleInterface`  
_L9-21_
- inherits: `IModuleInterface`
- desc: Module for experimental plugin that provides access to FastGeo components. To be removed when FastGeo exits experimental.
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _public function_ `virtual bool SupportsDynamicReloading() override`
- L19 _public prototype_ `void OnFastGeoComponentsPreRecreate(const TArray<struct FFastGeoRegisteredComponent>& InComponents) const;`
