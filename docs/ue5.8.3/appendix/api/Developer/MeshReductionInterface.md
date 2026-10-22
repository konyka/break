# Developer / MeshReductionInterface

- module root: `Source/Developer/MeshReductionInterface`
- headers: 4; symbols: 76
- symbol kinds: class=6, delegate=4, function=5, member=20, prototype=40, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Developer/MeshReductionInterface/Private/MeshReductionManagerModule.h` (Private)


#### class `FMeshReductionManagerModule`  
`class FMeshReductionManagerModule : public IMeshReductionManagerModule`  
_L10-43_
- inherits: `IMeshReductionManagerModule`
- L13 _public prototype_ `FMeshReductionManagerModule();`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `virtual IMeshReduction* GetStaticMeshReductionInterface() const override;` — Returns the mesh reduction plugin if available.
- L22 _public prototype_ `virtual IMeshReduction* GetSkeletalMeshReductionInterface() const override;` — Returns the mesh reduction plugin if available.
- L25 _public prototype_ `virtual IMeshMerging* GetMeshMergingInterface() const override;` — Returns the mesh merging plugin if available.
- L27 _public prototype_ `virtual IMeshMerging* GetDistributedMeshMergingInterface() const override;`
- L29 _public prototype_ `virtual void OnModuleConfigurationCompleted(FSimpleDelegate Delegate) override;`
- L33 _private member_ `IMeshReduction* StaticMeshReduction;` — Cached pointer to the mesh reduction interface.
- L35 _private member_ `IMeshReduction* SkeletalMeshReduction;` — Cached pointer to the mesh reduction interface.
- L37 _private member_ `IMeshMerging* MeshMerging;` — Cached pointer to the mesh merging interface.
- L39 _private member_ `IMeshMerging* DistributedMeshMerging;` — Cached pointer to the distributed mesh merging interface.
- L41 _private member_ `bool bConfigurationCompleted = false;`
- L42 _private member_ `FSimpleMulticastDelegate ConfigurationCompletedDelegate;`

### `Source/Developer/MeshReductionInterface/Public/IMeshReductionInterfaces.h` (Public)


#### class `IMeshReduction`  
`class IMeshReduction`  
_L16-63_
- desc: Mesh reduction interface.
- L19 _public prototype_ `virtual ~IMeshReduction() = default;`
- L28 _public prototype_ `virtual void ReduceMeshDescription( FMeshDescription& OutReducedMesh, float& OutMaxDeviation, const FMeshDescription& InMesh, const FOverlappingCorners& InOverlappingCorners, const struct FMeshReductionSettings& ReductionSettings ) = 0;` — Reduces the raw mesh using the provided reduction settings. @param OutReducedMesh - Upon return contains the reduced mesh. @param OutMaxDeviation - Upon return contains the maximum distance by which the reduced mesh deviates from the original. @param InMesh - The mesh to reduce. @param ReductionSettings - Setting with which to reduce the mesh.
- L40 _public prototype_ `virtual bool ReduceSkeletalMesh( class USkeletalMesh* SkeletalMesh, int32 LODIndex, const class ITargetPlatform* TargetPlatform ) = 0;` — Reduces the provided skeletal mesh. @returns true if reduction was successful.
- L48 _public prototype_ `virtual const FString& GetVersionString() const = 0;` — Returns a unique string identifying both the reduction plugin itself and the version of the plugin.
- L53 _public prototype_ `virtual bool IsSupported() const = 0;` — Returns true if mesh reduction is supported
- L58 _public prototype_ `virtual bool IsReductionActive(const struct FMeshReductionSettings &ReductionSettings) const = 0;` — Returns true if mesh reduction is active. Active mean there will be a reduction of the vertices or triangle number
- L59 _public prototype_ `virtual bool IsReductionActive(const struct FMeshReductionSettings& ReductionSettings, uint32 NumVertices, uint32 NumTriangles) const = 0;`
- L61 _public prototype_ `virtual bool IsReductionActive(const struct FSkeletalMeshOptimizationSettings &ReductionSettings) const = 0;`
- L62 _public prototype_ `virtual bool IsReductionActive(const struct FSkeletalMeshOptimizationSettings &ReductionSettings, uint32 NumVertices, uint32 NumTriangles) const = 0;`

#### struct `FMergeCompleteData`  
`struct FMergeCompleteData`  
_L70-86_
- desc: Data used for passing back the data resulting from a completed mesh merging operation
- L73 _public member_ `class UPackage* InOuter;` — Outer object to store/save UObjects
- L75 _public member_ `FString ProxyBasePackageName;` — Base package name for the proxy mesh UObjects
- L77 _public member_ `FMeshProxySettings InProxySettings;` — Merge/Proxy settings structure
- L79 _public member_ `FCreateProxyDelegate CallbackDelegate;` — Callback delegate object used as a callback when the job finishes
- L81 _public member_ `TArray<const UStaticMeshComponent*> ImposterComponents;` — List of Components containing imposter LODs
- L83 _public member_ `TArray<UStaticMeshComponent*> StaticMeshComponents;` — List of Components incorporated into the Proxy Mesh
- L85 _public member_ `UMaterialInterface* BaseMaterial;` — Base material to instance for the proxy material

#### class `IMeshMerging`  
`class IMeshMerging`  
_L94-121_
- desc: Mesh merging interface.
- L97 _public prototype_ `virtual ~IMeshMerging() = default;`
- L99 _public function_ `virtual void ProxyLOD(const TArray<struct FMeshMergeData>& InData, const struct FMeshProxySettings& InProxySettings, const TArray<struct FFlattenMaterial>& InputMaterials, const FGuid InJobGUID)`
- L104 _public function_ `virtual void ProxyLOD(const TArray<struct FInstancedMeshMergeData>& InData, const struct FMeshProxySettings& InProxySettings, const TArray<struct FFlattenMaterial>& InputMaterials, const FGuid InJobGUID)`
- L109 _public function_ `virtual void AggregateLOD()`
- L111 _public prototype_ `virtual FString GetName() = 0;`
- L116 _public function_ `virtual bool bSupportsParallelMaterialBake()` — Does this tool support baking materials in parallel
- L118 _public member_ `FProxyCompleteDelegate CompleteDelegate;`
- L119 _public member_ `FProxyFailedDelegate FailedDelegate;`
- L120 _public member_ `FBakeMaterialsDelegate BakeMaterialsDelegate;`

#### class `IMeshReductionModule`  
`class IMeshReductionModule : public IModuleInterface, public IModularFeature`  
_L126-156_
- inherits: `IModuleInterface,IModularFeature`
- desc: Mesh reduction module interface.
- L132 _public prototype_ `virtual class IMeshReduction* GetStaticMeshReductionInterface() = 0;` — Retrieve the static mesh reduction interface.
- L137 _public prototype_ `virtual class IMeshReduction* GetSkeletalMeshReductionInterface() = 0;` — Retrieve the static mesh reduction interface.
- L142 _public prototype_ `virtual class IMeshMerging* GetMeshMergingInterface() = 0;` — Retrieve the mesh merging interface.
- L147 _public prototype_ `virtual class IMeshMerging* GetDistributedMeshMergingInterface() = 0;` — Retrieve the distributed mesh merging interface.
- L149 _public prototype_ `virtual FString GetName() = 0;`
- L152 _public function_ `static const FName GetModularFeatureName()` — Modular feature name to register for retrieval during runtime

#### Free symbols / members of external scopes

- L65 _delegate_ `DECLARE_DELEGATE_ThreeParams(FProxyCompleteDelegate, struct FMeshDescription&, struct FFlattenMaterial&, const FGuid);`
- L65 _prototype_ `DECLARE_DELEGATE_ThreeParams(FProxyCompleteDelegate, struct FMeshDescription&, struct FFlattenMaterial&, const FGuid);`
- L66 _delegate_ `DECLARE_DELEGATE_TwoParams(FProxyFailedDelegate, const FGuid, const FString&);`
- L66 _prototype_ `DECLARE_DELEGATE_TwoParams(FProxyFailedDelegate, const FGuid, const FString&);`
- L67 _delegate_ `DECLARE_DELEGATE_TwoParams(FCreateProxyDelegate, const FGuid, TArray<UObject*>&);`
- L67 _prototype_ `DECLARE_DELEGATE_TwoParams(FCreateProxyDelegate, const FGuid, TArray<UObject*>&);`
- L90 _delegate_ `DECLARE_DELEGATE_OneParam(FBakeMaterialsDelegate, TArray<FFlattenMaterial>&);`
- L90 _prototype_ `DECLARE_DELEGATE_OneParam(FBakeMaterialsDelegate, TArray<FFlattenMaterial>&);`

### `Source/Developer/MeshReductionInterface/Public/IMeshReductionManagerModule.h` (Public)


#### class `IMeshReductionManagerModule`  
`class IMeshReductionManagerModule : public IModuleInterface`  
_L11-28_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual IMeshReduction* GetStaticMeshReductionInterface() const = 0;` — Returns the mesh reduction plugin if available.
- L18 _public prototype_ `virtual IMeshReduction* GetSkeletalMeshReductionInterface() const = 0;` — Returns the mesh reduction plugin if available.
- L21 _public prototype_ `virtual IMeshMerging* GetMeshMergingInterface() const = 0;` — Returns the mesh merging plugin if available.
- L24 _public prototype_ `virtual IMeshMerging* GetDistributedMeshMergingInterface() const = 0;` — Returns the distributed mesh merging plugin if available.
- L27 _public prototype_ `virtual void OnModuleConfigurationCompleted(FSimpleDelegate Delegate) = 0;` — Register a delegate that will fire when the module configuration is completed.

### `Source/Developer/MeshReductionInterface/Public/MeshReductionModule.h` (Public)


#### class `FMeshReductionModule`  
`class FMeshReductionModule : public IModuleInterface`  
_L10-37_
- inherits: `IModuleInterface`
- L13 _public prototype_ `FMeshReductionModule();`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `virtual IMeshReduction* GetStaticMeshReductionInterface();` — Returns the mesh reduction plugin if available.
- L22 _public prototype_ `virtual IMeshReduction* GetSkeletalMeshReductionInterface();` — Returns the mesh reduction plugin if available.
- L25 _public prototype_ `virtual IMeshMerging* GetMeshMergingInterface();` — Returns the mesh merging plugin if available.
- L27 _public prototype_ `virtual IMeshMerging* GetDistributedMeshMergingInterface();`
- L30 _private member_ `IMeshReduction* StaticMeshReduction;` — Cached pointer to the mesh reduction interface.
- L32 _private member_ `IMeshReduction* SkeletalMeshReduction;` — Cached pointer to the mesh reduction interface.
- L34 _private member_ `IMeshMerging* MeshMerging;` — Cached pointer to the mesh merging interface.
- L36 _private member_ `IMeshMerging* DistributedMeshMerging;` — Cached pointer to the distributed mesh merging interface.
