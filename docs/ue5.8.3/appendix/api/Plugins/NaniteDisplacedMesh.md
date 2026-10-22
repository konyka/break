# Plugins / NaniteDisplacedMesh

- module root: `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMesh`
- headers: 5; symbols: 134
- symbol kinds: class=3, delegate=2, enum=2, enumerator=4, function=12, macro=2, member=27, namespace=3, prototype=74, struct=4, typedef=1
- DynamicallyLoadedModuleNames: NaniteBuilder
- PrivateDependencyModuleNames: AssetTools, DerivedDataCache, GeometryCore, ImageCore, MeshBuilder, MeshBuilderCommon, MeshDescription, MeshUtilities, MeshUtilitiesCommon, NaniteUtilities, RHI, RawMesh, RenderCore, SlateCore, StaticMeshDescription
- PrivateIncludePathModuleNames: NaniteBuilder
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMesh/Internal/NaniteDisplacedMeshLog.h` (Internal)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNaniteDisplacedMesh, Log, All);`

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMesh/Private/NaniteDisplacedMeshCompiler.h` (Private)


#### class `FNaniteDisplacedMeshCompilingManager`  
`class FNaniteDisplacedMeshCompilingManager : public IAssetCompilingManager, public FGCObject`  
_L16-91_
- inherits: `IAssetCompilingManager,FGCObject`
- L19 _public prototype_ `static FNaniteDisplacedMeshCompilingManager& Get();`
- L24 _public prototype_ `int32 GetNumRemainingAssets() const override;` — Returns the number of outstanding compilations.
- L29 _public prototype_ `void AddNaniteDisplacedMeshes(TArrayView<UNaniteDisplacedMesh* const> InNaniteDisplacedMeshes);` — Queue nanite displaced meshes to be compiled asynchronously so they are monitored.
- L34 _public prototype_ `void FinishCompilation(TArrayView<UNaniteDisplacedMesh* const> InNaniteDisplacedMeshes);` — Blocks until completion of the requested nanite displaced meshes.
- L39 _public prototype_ `void FinishAllCompilation() override;` — Blocks until completion of all async nanite displaced mesh compilation.
- L44 _public prototype_ `EQueuedWorkPriority GetBasePriority(UNaniteDisplacedMesh* InNaniteDisplacedMeshes) const;` — Returns the priority at which the given nanite displaced mesh should be scheduled.
- L49 _public prototype_ `FQueuedThreadPool* GetThreadPool() const;` — Returns the thread pool where nanite displaced mesh compilation should be scheduled.
- L54 _public prototype_ `void Shutdown() override;` — Cancel any pending work and blocks until it is safe to shut down.
- L57 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L58 _public prototype_ `virtual FString GetReferencerName() const override;`
- L64 _private prototype_ `FNaniteDisplacedMeshCompilingManager();`
- L66 _private prototype_ `FName GetAssetTypeName() const override;`
- L67 _private prototype_ `FTextFormat GetAssetNameFormat() const override;`
- L68 _private prototype_ `TArrayView<FName> GetDependentTypeNames() const override;`
- L71 _private prototype_ `void ProcessAsyncTasks(bool bLimitExecutionTime = false) override;` — Called once per frame, fetches completed tasks and applies them to the scene.
- L73 _private member_ `bool bHasShutdown = false;`
- L74 _private member_ `TSet<TWeakObjectPtr<UNaniteDisplacedMesh>> RegisteredNaniteDisplacedMesh;`
- L77 _private member_ `TSet<TObjectPtr<UNaniteDisplacedMesh>> GCReferedNaniteDisplacedMesh;` — Refer the transient displaced meshes to the GC so that they are not GCed while compiling. Without this a pie session can hitches a lot when the ddc is not primed.
- L79 _private member_ `TUniquePtr<FAsyncCompilationNotification> Notification;`
- L81 _private prototype_ `void FinishCompilationsForGame();`
- L82 _private prototype_ `void Reschedule();`
- L83 _private prototype_ `void ProcessNaniteDisplacedMeshes(bool bLimitExecutionTime, int32 MinBatchSize = 1);`
- L84 _private prototype_ `void UpdateCompilationNotification();`
- L86 _private prototype_ `void PostCompilation(TArrayView<UNaniteDisplacedMesh* const> InNaniteDisplacedMeshes);`
- L87 _private prototype_ `void PostCompilation(UNaniteDisplacedMesh* InNaniteDisplacedMesh);`
- L89 _private prototype_ `void OnPostReachabilityAnalysis();`
- L90 _private member_ `FDelegateHandle PostReachabilityAnalysisHandle;`

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMesh/Public/NaniteDisplacedMesh.h` (Public)


#### struct `FNaniteDisplacedMeshDisplacementMap`  
`struct FNaniteDisplacedMeshDisplacementMap`  
_L25-67_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public member_ `TObjectPtr<UTexture2D> Texture;` — `UPROPERTY(EditAnywhere, Category = Displacement)`
- L33 _public member_ `float Magnitude = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Displacement)`
- L36 _public member_ `float Center = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Displacement)`
- L42 _public member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = Texture, AdvancedDisplay, meta = (ClampMin = 0, ClampMax = 7))` — UV channel used for sampling the displacement texture.
- L48 _public member_ `int32 MaskUVChannel = 1;` — `UPROPERTY(EditAnywhere, Category = Texture, AdvancedDisplay, meta = (ClampMin = -1, ClampMax = 7))` — UV channel used for masking the displacement. If the value is -1, then no masking is applied.
- L50 _public prototype_ `bool operator==(const FNaniteDisplacedMeshDisplacementMap& Other) const = default;`
- L51 _public prototype_ `bool operator!=(const FNaniteDisplacedMeshDisplacementMap& Other) const = default;`
- L53 _public function_ `bool IsEquivalent(const FNaniteDisplacedMeshDisplacementMap& Other) const`
- L63 _public function_ `bool GenerateDisplacement() const`

#### struct `FNaniteDisplacedMeshParams`  
`struct FNaniteDisplacedMeshParams`  
_L70-125_
- reflection: `USTRUCT(BlueprintType)`
- L77 _public member_ `TObjectPtr<UStaticMesh> BaseMesh;` — `UPROPERTY(EditAnywhere, Category = Mesh)`
- L81 _public member_ `float RelativeError = 0.03f;` — `UPROPERTY(EditAnywhere, Category = Mesh, meta = (ClampMin = 0.1, ClampMax = 1))` — Controls the precisions of the tesselation, lower values leads to higher precision and denser meshes.
- L84 _public member_ `TArray<FNaniteDisplacedMeshDisplacementMap> DisplacementMaps;` — `UPROPERTY(EditAnywhere, Category = Texture)`
- L87 _public function_ `FNaniteDisplacedMeshParams() : BaseMesh(nullptr) , RelativeError(0.03f)` — Default settings.
- L92 _public prototype_ `bool operator==(const FNaniteDisplacedMeshParams& Other) const = default;`
- L93 _public prototype_ `bool operator!=(const FNaniteDisplacedMeshParams& Other) const = default;`
- L95 _public function_ `bool IsEquivalent(const FNaniteDisplacedMeshParams& Other) const`
- L115 _public prototype_ `void ClearInvalidAssetsForDisplacement();`
- L120 _public prototype_ `bool IsDisplacementRequired() const;` — Does the settings would result in the creation of some rendering data
- L122 _public prototype_ `static bool CanUseAssetForDisplacement(const UObject* InAsset);`

#### struct `FValidatedNaniteDisplacedMeshParams`  
`struct FValidatedNaniteDisplacedMeshParams`  
_L128-160_
- L130 _public function_ `FValidatedNaniteDisplacedMeshParams(const FNaniteDisplacedMeshParams& InParams) : ValidatedParams(InParams)`
- L136 _public function_ `FValidatedNaniteDisplacedMeshParams(FNaniteDisplacedMeshParams&& InParams) : ValidatedParams(MoveTemp(InParams))`
- L145 _public prototype_ `bool IsDisplacementRequired() const;` — Does the settings would result in the creation of some rendering data
- L147 _public function_ `operator const FNaniteDisplacedMeshParams&() const`
- L153 _public function_ `FNaniteDisplacedMeshParams ConvertToNaniteDisplacedMeshParams()` — Consume the validated nanite displaced mesh params
- L159 _private member_ `FNaniteDisplacedMeshParams ValidatedParams;`

#### struct `FNaniteData`  
`struct FNaniteData`  
_L164-170_
- L166 _public member_ `TPimplPtr<Nanite::FResources> ResourcesPtr;`
- L169 _public member_ `Nanite::FMeshDataSectionArray MeshSections;` — Material section information that matches displaced mesh.

#### class `UNaniteDisplacedMesh`  
`class UNaniteDisplacedMesh : public UObject, public IInterface_AsyncCompilation`  
_L173-294_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IInterface_AsyncCompilation`
- L180 _public prototype_ `UNaniteDisplacedMesh(const FObjectInitializer& Init);`
- L182 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L183 _public prototype_ `virtual void PostLoad() override;`
- L184 _public prototype_ `virtual void BeginDestroy() override;`
- L185 _public prototype_ `virtual bool IsReadyForFinishDestroy() override;`
- L186 _public prototype_ `virtual bool NeedsLoadForTargetPlatform(const ITargetPlatform* TargetPlatform) const override;`
- L188 _public prototype_ `void InitResources();`
- L189 _public prototype_ `void ReleaseResources();`
- L191 _public prototype_ `bool HasValidNaniteData() const;`
- L193 _public function_ `inline Nanite::FResources* GetNaniteData()`
- L198 _public function_ `inline const Nanite::FResources* GetNaniteData() const`
- L203 _public function_ `inline const Nanite::FMeshDataSectionArray& GetMeshSections() const`
- L209 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L210 _public prototype_ `virtual void BeginCacheForCookedPlatformData(const ITargetPlatform* TargetPlatform) override;`
- L211 _public prototype_ `virtual bool IsCachedCookedPlatformDataLoaded(const ITargetPlatform* TargetPlatform) override;`
- L212 _public prototype_ `virtual void ClearAllCachedCookedPlatformData() override;`
- L215 _public prototype_ `bool IsCompiling() const override;` — Returns whether or not the asset is currently being compiled
- L220 _public prototype_ `bool TryCancelAsyncTasks();` — Try to cancel any pending async tasks. Returns true if there is no more async tasks pending, false otherwise.
- L223 _public prototype_ `bool IsAsyncTaskComplete() const;` — Returns false if there is currently an async task running
- L229 _public prototype_ `bool WaitForAsyncTasks(float TimeLimitSeconds);` — Wait until all async tasks are complete, up to a time limit Returns true if all tasks are completed
- L232 _public prototype_ `void FinishAsyncTasks();` — Make sure all async tasks are completed before returning
- L236 _private prototype_ `void Reschedule(FQueuedThreadPool* InThreadPool, EQueuedWorkPriority InPriority);`
- L242 _public member_ `FNaniteDisplacedMeshParams Parameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameters, meta=(EditCondition = "bIsEditable"))`
- L250 _public member_ `bool bIsEditable = true;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Asset, AdvancedDisplay)` — Was this asset created by a procedural tool? This flag is generally set by tool that created the asset. It's used to tell the users that they shouldn't modify the asset by themselves.
- L254 _private member_ `bool bIsInitialized = false;`
- L257 _private member_ `FNaniteData Data;` — Data used to render this displaced mesh with Nanite.
- L259 _private member_ `FRenderCommandFence ReleaseResourcesFence;`
- L262 _private prototype_ `FIoHash CreateDerivedDataKeyHash(const ITargetPlatform* TargetPlatform);`
- L263 _private prototype_ `FIoHash BeginCacheDerivedData(const ITargetPlatform* TargetPlatform);`
- L264 _private prototype_ `bool PollCacheDerivedData(const FIoHash& KeyHash) const;`
- L265 _private prototype_ `void EndCacheDerivedData(const FIoHash& KeyHash);`
- L268 _private prototype_ `FNaniteData& CacheDerivedData(const ITargetPlatform* TargetPlatform);` — Synchronously cache and return derived data for the target platform.
- L270 _private member_ `FIoHash DataKeyHash;`
- L271 _private member_ `TMap<FIoHash, TUniquePtr<FNaniteData>> DataByPlatformKeyHash;`
- L272 _private member_ `TMap<FIoHash, TPimplPtr<FNaniteBuildAsyncCacheTask>> CacheTasksByKeyHash;`
- L274 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnNaniteDisplacedMeshRenderingDataChanged);`
- L275 _private member_ `FOnNaniteDisplacedMeshRenderingDataChanged OnRenderingDataChanged;`
- L280 _public typedef_ `typedef FOnNaniteDisplacedMeshRenderingDataChanged::FDelegate FOnRebuild;`
- L281 _public prototype_ `FDelegateHandle RegisterOnRenderingDataChanged(const FOnRebuild& Delegate);`
- L282 _public prototype_ `void UnregisterOnRenderingDataChanged(FDelegateUserObject Unregister);`
- L283 _public prototype_ `void UnregisterOnRenderingDataChanged(FDelegateHandle Handle);`
- L285 _public prototype_ `void NotifyOnRenderingDataChanged();`
- L291 _private prototype_ `DECLARE_EVENT_OneParam(UNaniteDisplacedMesh, FOnNaniteDisplacmentMeshDependenciesChanged, UNaniteDisplacedMesh*);`
- L292 _private member_ `static FOnNaniteDisplacmentMeshDependenciesChanged OnDependenciesChanged;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API NANITEDISPLACEDMESH_API`
- L274 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnNaniteDisplacedMeshRenderingDataChanged);`
- L291 _delegate_ `DECLARE_EVENT_OneParam(UNaniteDisplacedMesh, FOnNaniteDisplacmentMeshDependenciesChanged, UNaniteDisplacedMesh*);`

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMesh/Public/NaniteDisplacedMeshAlgo.h` (Public)


#### enum `UE::NaniteDisplacedMesh::EDisplacementOptions`  
`enum class EDisplacementOptions : int32`  
_L15-22_
- L18 _public enumerator_ `None = 0` — No custom displacement behavior.
- L21 _public enumerator_ `IgnoreNonNormalizedDisplacementUVs = 1 << 0` — Will ignore any displacement when the displacement map's UVs are outside the range [0, 1].

#### enum `EDisplaceNaniteMeshOptions::Type`  
`enum Type : int32`  
_L36-43_
- L39 _public enumerator_ `None = 0` — No custom displacement behavior.
- L42 _public enumerator_ `IgnoreNonNormalizedDisplacementUVs = 1 << 0` — Will ignore any displacement when the displacement map's UVs are outside the range [0, 1].

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NaniteDisplacedMesh` (scope `UE`)
- L24 _prototype_ `bool DisplaceNaniteMesh( const FNaniteDisplacedMeshParams& Parameters, FMeshBuildVertexData& Verts, TArray<uint32>& Indexes, TArray<int32>& MaterialIndexes, FBounds3f& VertexBounds, EDisplacementOptions Options = EDisplacementOptions::None );` (scope `UE::NaniteDisplacedMesh`)
- L34 _namespace_ `namespace EDisplaceNaniteMeshOptions`
- L48 _function_ `inline bool DisplaceNaniteMesh( const FNaniteDisplacedMeshParams& Parameters, const uint32 NumTextureCoord, FMeshBuildVertexData& Verts, TArray<uint32>& Indexes, TArray<int32>& MaterialIndexes, FBounds3f& VertexBounds, EDisplaceNaniteMeshOptions::Type Options = EDisplaceNaniteMeshOptions::None )` — `UE_DEPRECATED(5.7, "Please use UE::NaniteDisplacedMesh::DisplaceNaniteMesh instead.")`

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMesh/Public/NaniteDisplacedMeshComponent.h` (Public)


#### class `UNaniteDisplacedMeshComponent`  
`class UNaniteDisplacedMeshComponent : public UStaticMeshComponent`  
_L17-48_
- reflection: `UCLASS(MinimalAPI, ClassGroup=Rendering, hidecategories=(Object,Activation,Collision,"Components|Activation",Physics), editinlinenew, meta=(BlueprintSpawnableComponent))`
- inherits: `UStaticMeshComponent`
- L22 _public prototype_ `virtual void PostLoad() override;`
- L24 _public prototype_ `virtual void BeginDestroy() override;`
- L26 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L27 _public prototype_ `virtual void OnRegister() override;`
- L29 _public prototype_ `virtual const Nanite::FResources* GetNaniteResources() const;`
- L31 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L34 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L35 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L36 _public prototype_ `virtual void PostEditUndo() override;`
- L38 _public prototype_ `void OnRebuild();`
- L43 _public member_ `TObjectPtr<class UNaniteDisplacedMesh> DisplacedMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Displacement)`
- L46 _private prototype_ `void UnbindCallback();`
- L47 _private prototype_ `void BindCallback();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NANITEDISPLACEDMESH_API`
