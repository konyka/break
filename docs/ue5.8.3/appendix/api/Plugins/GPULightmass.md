# Plugins / GPULightmass

- module root: `Plugins/Experimental/GPULightmass/Source/GPULightmass`
- headers: 24; symbols: 1101
- symbol kinds: class=67, delegate=1, enum=3, enumerator=7, function=233, macro=1, member=465, namespace=10, prototype=240, struct=46, typedef=24, variable=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, EditorFramework, Engine, IntelOIDN, Landscape, Projects, RHI, RenderCore, Renderer, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core
- PublicIncludePathModuleNames: Shaders

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/CompactingObjectPool.h` (Private)


#### class `FCompactingObjectHandleBase`  
`class FCompactingObjectHandleBase`  
_L9-108_
- desc: A handle to an object in a pool which moves and compacts its content.
- L14 _protected member_ `TSparseArray<int32>* HandleAllocator = nullptr;` — To allow objects contaning handles to be moved freely (relocatable outside of the handle tracking system), we use an extra level of indirection so that handles are referenced by their indices ('address') in the handle allocator array.
- L15 _protected member_ `int32 HandleAddress = INDEX_NONE;`
- L18 _protected member_ `TSet<int32>* HandleTrackingTable = nullptr;` — Pointer to the corresponding tracking table so that we can unregister the handle from the tracking table when it is destructed.
- L22 _public prototype_ `FCompactingObjectHandleBase() = default;` — Default constructor which takes the default values defined below
- L24 _public function_ `FCompactingObjectHandleBase(int32 ObjectAddress, TSet<int32>* HandleTrackingTable, TSparseArray<int32>* HandleAllocator) : HandleAllocator(HandleAllocator) , HandleTrackingTable(HandleTrackingTable)`
- L40 _public function_ `void Unregister()`
- L53 _public function_ `~FCompactingObjectHandleBase()`
- L61 _public function_ `FCompactingObjectHandleBase& operator=(const FCompactingObjectHandleBase& Other)`
- L69 _public function_ `FCompactingObjectHandleBase(const FCompactingObjectHandleBase& Other)`
- L77 _public function_ `bool operator==(const FCompactingObjectHandleBase& Other) const` — This operator checks if two handles point to the same object (including invalid object), not for comparing handle addresses
- L82 _public function_ `int32 GetObjectAddress() const`
- L87 _public function_ `bool IsInitialized() const`
- L92 _public function_ `int32 GetObjectAddressChecked() const`
- L98 _public function_ `bool PointsToValidObject() const`
- L103 _public function_ `int32 GetValidObjectAddress() const`

#### class `FDynamicallyIndexableContainer`  
`class FDynamicallyIndexableContainer`  
_L111-111_
- desc: A tag to prevent user from putting arbitrary containers into TObjectHandle's ObjectStorage ptr (which is practically void*)

#### class `TObjectHandle`  
`template<typename ObjectType> class TObjectHandle : public FCompactingObjectHandleBase`  
_L114-131_
- inherits: `FCompactingObjectHandleBase`
- L116 _private typedef_ `using ObjectAccessorFuncType = ObjectType& (*)(FDynamicallyIndexableContainer* ObjectStorage, int32 ObjectAddress);`
- L119 _private member_ `FDynamicallyIndexableContainer* ObjectStorage = nullptr;`
- L120 _private member_ `ObjectAccessorFuncType ObjectAccessor = nullptr;`
- L123 _public prototype_ `TObjectHandle() = default;`
- L124 _public function_ `TObjectHandle(int32 ObjectAddress, TSet<int32>* HandleTrackingTable, TSparseArray<int32>* HandleAllocator, FDynamicallyIndexableContainer* ObjectStorage, ObjectAccessorFuncType ObjectAccessor) : FCompactingObjectHandleBase(ObjectAddress, HandleTrackingTable, HandleAllocator), ObjectStorage(ObjectStorage), ObjectAccessor(ObjectAccessor)`
- L127 _public function_ `ObjectType& Get() const`
- L128 _public function_ `ObjectType& operator*() const`
- L129 _public function_ `ObjectType* operator->() const`
- L130 _public function_ `operator ObjectType& () const`

#### class `TCompactingObjectPool`  
`template<typename ObjectType> class TCompactingObjectPool : public FDynamicallyIndexableContainer`  
_L134-274_
- inherits: `FDynamicallyIndexableContainer`
- L137 _protected member_ `TArray<TSet<int32>> HandleTrackingTablePerObject;`
- L138 _protected member_ `TSparseArray<int32> HandleAllocator;`
- L139 _protected member_ `TArray<ObjectType> Objects;`
- L143 _public function_ `template <typename... ArgsType> TObjectHandle<ObjectType> Emplace(ArgsType&&... Args)`
- L159 _public function_ `template<typename InterfaceType = ObjectType> static InterfaceType& ObjectAccessor(FDynamicallyIndexableContainer* ObjectStorage, int32 ObjectAddress)` — Core function for implementing dynamic polymorphic indexing behavior An array of Base and an array of Derived are inherently different types: their indexing behavior is totally different The first one indexes each element at i * sizeof(Base) while the second one does so at i * sizeof(Derived) To properly access the Base of each element out of an array of Derived, the indexing must be done as Derived but then the indexed element is accessed as Base This means the concrete type of the element stored in this container (in other words, the type of the container) must be known at indexing time, prior to the element being accessed - that means dynamic dispatches happen here before the vtable of the element is accessed. A side effect of that is we don't even need the object's vtable to achieve dynamic polymorphism
- L167 _public function_ `template<typename InterfaceType = ObjectType> TObjectHandle<InterfaceType> GetHandleForObject(ObjectType& Object)`
- L175 _public function_ `void RemoveAt(int32 ObjectAddress, bool bCheckNoActiveHandle = false)` — Move the last object in the pool to the address being removed to achieve compaction
- L222 _public function_ `void Remove(TObjectHandle<ObjectType>& Handle)`
- L229 _public function_ `ObjectType& operator[](int32 Index)`
- L234 _public function_ `const ObjectType& operator[](int32 Index) const`
- L239 _public function_ `int32 Num()`
- L272 _public function_ `TIterator begin()`
- L273 _public function_ `TIterator end()`

#### struct `TCompactingObjectPool::TIterator`  
`struct TIterator`  
_L244-270_
- L246 _public member_ `TArray<ObjectType>& ObjectStorage;`
- L247 _public member_ `int32 Index;`
- L249 _public function_ `TIterator& operator++()`
- L255 _public function_ `bool operator!=(const TIterator& Other)`
- L261 _public function_ `ObjectType& operator*() const`
- L266 _public function_ `ObjectType& operator->() const`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/EntityArray.h` (Private)


#### class `FGenericEntityRef`  
`class FGenericEntityRef`  
_L125-216_
- L128 _public function_ `FGenericEntityRef() : Addr(-1), RefsArrayPtr(nullptr), RefAllocatorPtr(nullptr)`
- L132 _public function_ `FGenericEntityRef(int32 ElementId, TArray<TSet<RefAddr>>& Refs, TSparseArray<int32>& RefAllocator) : RefsArrayPtr(&Refs) , RefAllocatorPtr(&RefAllocator)`
- L144 _public function_ `void Unregister()`
- L156 _public function_ `FGenericEntityRef& operator=(const FGenericEntityRef& Other)`
- L173 _public function_ `FGenericEntityRef(const FGenericEntityRef& Other)`
- L186 _public function_ `~FGenericEntityRef()`
- L191 _public function_ `int32 GetElementId() const`
- L196 _public function_ `bool IsValid() const`
- L201 _public function_ `int32 GetElementIdChecked() const`
- L207 _public function_ `bool operator==(const FGenericEntityRef& Other) const`
- L213 _protected member_ `RefAddr Addr;`
- L214 _protected member_ `TArray<TSet<RefAddr>>* RefsArrayPtr;`
- L215 _protected member_ `TSparseArray<int32>* RefAllocatorPtr;`

#### class `TEntityArray`  
`template<typename T> class TEntityArray`  
_L219-311_
- L248 _public function_ `void RemoveAt(int32 Index, bool bCheckNoActiveRef = false)`
- L287 _public function_ `void Remove(EntityRefType& Ref)`
- L295 _public function_ `template <typename... ArgsType> EntityRefType Emplace(ArgsType&&... Args)`
- L302 _public function_ `EntityRefType CreateNullRef()`
- L307 _public member_ `TArray<T> Elements;`
- L309 _protected member_ `TArray<TSet<RefAddr>> Refs;`
- L310 _protected member_ `TSparseArray<int32> RefAllocator;`

#### class `TEntityArray::EntityRefType`  
`class EntityRefType : public FGenericEntityRef`  
_L222-246_
- inherits: `FGenericEntityRef`
- L225 _public prototype_ `EntityRefType();`
- L226 _public prototype_ `EntityRefType(const EntityRefType& Other);`
- L227 _public prototype_ `EntityRefType(const T& Element, TEntityArray<T>& Container);`
- L228 _public prototype_ `EntityRefType(TEntityArray<T>& Container);`
- L229 _public function_ `~EntityRefType()`
- L231 _public function_ `T* GetUnderlyingAddress_Unsafe() const`
- L232 _public function_ `T* operator->() const`
- L233 _public function_ `T& GetReference_Unsafe() const`
- L234 _public function_ `operator T& () const`
- L235 _public function_ `bool IsValid() const`
- L239 _public function_ `bool operator==(const EntityRefType& Other) const`
- L244 _private member_ `TArray<T>* ElementsPtr;`
- L314 _function_ `template<typename T> TEntityArray<T>::EntityRefType::EntityRefType() : FGenericEntityRef() , ElementsPtr(nullptr)`
- L321 _function_ `template<typename T> TEntityArray<T>::EntityRefType::EntityRefType(const EntityRefType& Other) : FGenericEntityRef(Other) , ElementsPtr(Other.ElementsPtr)`
- L328 _function_ `template<typename T> TEntityArray<T>::EntityRefType::EntityRefType(const T& Element, TEntityArray<T>& Container) : FGenericEntityRef(&Element - Container.Elements.GetData(), Container.Refs, Container.RefAllocator) , ElementsPtr(&Container.Elements)`
- L336 _function_ `template<typename T> TEntityArray<T>::EntityRefType::EntityRefType(TEntityArray<T>& Container) : FGenericEntityRef(INDEX_NONE, Container.Refs, Container.RefAllocator) , ElementsPtr(&Container.Elements)`

#### Free symbols / members of external scopes

- L123 _typedef_ `using RefAddr = int32;`
- L343 _function_ `template<typename T> uint32 GetTypeHash(const typename TEntityArray<T>::EntityRefType& Ref)`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/GPULightmass.h` (Private)


#### class `FGPULightmass`  
`class FGPULightmass : public IStaticLightingSystem`  
_L12-59_
- inherits: `IStaticLightingSystem`
- L15 _public prototype_ `FGPULightmass(UWorld* InWorld, FGPULightmassModule* GPULightmassModule, UGPULightmassSettings* InSettings = nullptr);`
- L16 _public prototype_ `virtual ~FGPULightmass();`
- L17 _public prototype_ `void GameThreadDestroy();`
- L19 _public prototype_ `virtual const FMeshMapBuildData* GetPrimitiveMeshMapBuildData(const UPrimitiveComponent* Component, int32 LODIndex) override;`
- L20 _public prototype_ `virtual const FLightComponentMapBuildData* GetLightComponentMapBuildData(const ULightComponent* Component) override;`
- L21 _public prototype_ `virtual const FPrecomputedVolumetricLightmap* GetPrecomputedVolumetricLightmap() override;`
- L23 _public member_ `UWorld* World;`
- L24 _public member_ `FGPULightmassModule* GPULightmassModule;`
- L25 _public member_ `UGPULightmassSettings* Settings;`
- L26 _public member_ `TUniquePtr<FGCObjectScopeGuard> SettingsGuard;`
- L28 _public member_ `GPULightmass::FScene Scene;`
- L30 _public prototype_ `void InstallGameThreadEventHooks();`
- L31 _public prototype_ `void RemoveGameThreadEventHooks();`
- L33 _public prototype_ `void ShowLightBuildNotification();`
- L34 _public prototype_ `void RemoveLightBuildNotification();`
- L36 _public prototype_ `void StartRecordingVisibleTiles();`
- L37 _public prototype_ `void EndRecordingVisibleTiles();`
- L40 _public member_ `TSharedPtr<SNotificationItem> LightBuildNotification;` — Game thread objects. Must be destroyed in GameThreadDestroy()
- L41 _public member_ `int32 LightBuildPercentage;`
- L43 _public member_ `double StartTime = 0;`
- L45 _public prototype_ `void EditorTick();`
- L49 _private prototype_ `void OnPreWorldFinishDestroy(UWorld* World);` — Game thread event hooks
- L51 _private prototype_ `void OnPrimitiveComponentRegistered(UPrimitiveComponent* InComponent);`
- L52 _private prototype_ `void OnPrimitiveComponentUnregistered(UPrimitiveComponent* InComponent);`
- L53 _private prototype_ `void OnLightComponentRegistered(ULightComponentBase* InComponent);`
- L54 _private prototype_ `void OnLightComponentUnregistered(ULightComponentBase* InComponent);`
- L55 _private prototype_ `void OnStationaryLightChannelReassigned(ULightComponentBase* InComponent, int32 NewShadowMapChannel);`
- L56 _private prototype_ `void OnLightmassImportanceVolumeModified();`
- L57 _private prototype_ `void OnMaterialInvalidated(FMaterialRenderProxy* Material);`
- L58 _private prototype_ `void OnSkyAtmosphereModified();`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/GPULightmassCommon.h` (Private)


#### struct `FTileVirtualCoordinates`  
`struct FTileVirtualCoordinates`  
_L12-28_
- L14 _public member_ `FIntPoint Position{ EForceInit::ForceInitToZero };`
- L15 _public member_ `int32 MipLevel = -1;`
- L17 _public prototype_ `FTileVirtualCoordinates() = default;`
- L19 _public function_ `FTileVirtualCoordinates(uint32 vAddress, uint8 vLevel) : Position((int32)FMath::ReverseMortonCode2(vAddress), (int32)FMath::ReverseMortonCode2(vAddress >> 1)), MipLevel(vLevel)`
- L20 _public function_ `FTileVirtualCoordinates(FIntPoint InPosition, uint8 vLevel) : Position(InPosition), MipLevel(vLevel)`
- L22 _public function_ `uint32 GetVirtualAddress() const`
- L24 _public function_ `bool operator==(const FTileVirtualCoordinates& Rhs) const`

#### Free symbols / members of external scopes

- L7 _variable_ `static const int32 GPreviewLightmapVirtualTileSize = 64;`
- L8 _variable_ `static const int32 GPreviewLightmapTileBorderSize = 2;`
- L9 _variable_ `static const int32 GPreviewLightmapPhysicalTileSize = GPreviewLightmapVirtualTileSize + 2 * GPreviewLightmapTileBorderSize;`
- L10 _variable_ `static const int32 GPreviewLightmapMipmapMaxLevel = 14;`
- L30 _function_ `FORCEINLINE uint32 GetTypeHash(const FTileVirtualCoordinates& Tile)`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/IrradianceCaching.h` (Private)


#### struct `FIrradianceCache`  
`struct FIrradianceCache`  
_L27-47_
- L29 _public member_ `const int32 IrradianceCacheMaxSize = 4194304;`
- L31 _public member_ `FBufferRHIRef IrradianceCacheRecords;`
- L32 _public member_ `FUnorderedAccessViewRHIRef IrradianceCacheRecordsUAV;`
- L33 _public member_ `FBufferRHIRef IrradianceCacheRecordBackfaceHits;`
- L34 _public member_ `FUnorderedAccessViewRHIRef IrradianceCacheRecordBackfaceHitsUAV;`
- L36 _public member_ `TUniformBufferRef<FIrradianceCachingParameters> IrradianceCachingParametersUniformBuffer;`
- L38 _public prototype_ `FIrradianceCache(FRHICommandList& RHICmdList, int32 Quality, float Spacing, float CornerRejection);`
- L40 _public member_ `FRWBuffer HashTable;`
- L41 _public member_ `FRWBuffer HashToIndex;`
- L42 _public member_ `FRWBuffer IndexToHash;`
- L43 _public member_ `FRWBuffer RecordAllocator;`
- L44 _public member_ `FRWBuffer HashTableSemaphore;`
- L46 _public member_ `int32 CurrentRevision = 0;`

#### class `FVisualizeIrradianceCachePS`  
`class FVisualizeIrradianceCachePS : public FGlobalShader`  
_L49-66_
- inherits: `FGlobalShader`
- L52 _public prototype_ `DECLARE_GLOBAL_SHADER(FVisualizeIrradianceCachePS);`
- L53 _public function_ `SHADER_USE_PARAMETER_STRUCT(FVisualizeIrradianceCachePS, FGlobalShader) BEGIN_SHADER_PARAMETER_STRUCT(FParameters, ) SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View) SHADER_PARAMETER_RDG_UNIFORM_BUFFER(FSceneTextureUniformParameters, SceneTextures) SHADER_PARAMETER_STRUCT_REF(FIrradianceCachingParameters, IrradianceCachingParameters) RENDER_TARGET_BINDING_SLOTS() END_SHADER_PARAMETER_STRUCT() static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapDenoising.h` (Private)


#### struct `FDenoiserFilterSet`  
`struct FDenoiserFilterSet`  
_L18-35_
- L20 _public member_ `struct FDenoiserContext& Context;`
- L23 _public member_ `oidn::FilterRef filter;`
- L26 _public member_ `FIntPoint Size;`
- L27 _public member_ `TArray<FVector3f> InputBuffer;`
- L28 _public member_ `TArray<FVector3f> OutputBuffer;`
- L30 _public prototype_ `FDenoiserFilterSet(FDenoiserContext& Context, FIntPoint NewSize, bool bSHDenoiser = false);`
- L32 _public prototype_ `void Execute();`
- L34 _public prototype_ `void Clear();`

#### struct `FDenoiserContext`  
`struct FDenoiserContext`  
_L37-89_
- L39 _public member_ `int32 NumFilterInit = 0;`
- L40 _public member_ `int32 NumFilterExecution = 0;`
- L41 _public member_ `double FilterInitTime = 0.0;`
- L42 _public member_ `double FilterExecutionTime = 0.0;`
- L45 _public member_ `oidn::DeviceRef OIDNDevice;`
- L48 _public member_ `TMap<FIntPoint, FDenoiserFilterSet> Filters;`
- L49 _public member_ `TMap<FIntPoint, FDenoiserFilterSet> SHFilters;`
- L51 _public function_ `FDenoiserContext()`
- L59 _public function_ `~FDenoiserContext()`
- L64 _public function_ `FDenoiserFilterSet& GetFilterForSize(FIntPoint Size, bool bSHDenoiser = false)`

#### struct `FLightSampleDataProvider`  
`struct FLightSampleDataProvider`  
_L104-111_
- L106 _public function_ `virtual ~FLightSampleDataProvider()`
- L107 _public prototype_ `virtual FIntPoint GetSize() const = 0;`
- L108 _public prototype_ `virtual bool IsMapped(FIntPoint Location) const = 0;`
- L109 _public prototype_ `virtual float GetL(FIntPoint Location) const = 0;`
- L110 _public prototype_ `virtual void OverwriteTexel(FIntPoint Dst, FIntPoint Src) = 0;`

#### struct `TLightSampleDataProvider`  
`template<typename LightSampleType> struct TLightSampleDataProvider`  
_L114-114_
- L119 _public member_ `FIntPoint Size;`
- L120 _public member_ `TArray<FLinearColor>& IncidentLighting;`
- L121 _public member_ `TArray<FLinearColor>& LuminanceSH;`
- L123 _public function_ `TLightSampleDataProvider<FLinearColor>( FIntPoint Size, TArray<FLinearColor>& IncidentLighting, TArray<FLinearColor>& LuminanceSH) : Size(Size) , IncidentLighting(IncidentLighting) , LuminanceSH(LuminanceSH)`
- L133 _public function_ `virtual FIntPoint GetSize() const override`
- L138 _public function_ `virtual bool IsMapped(FIntPoint Location) const override`
- L143 _public function_ `virtual float GetL(FIntPoint Location) const override`
- L148 _public function_ `virtual void OverwriteTexel(FIntPoint Dst, FIntPoint Src) override`
- L159 _public member_ `TArray<FLinearColor>& IncidentLightingAsValidityMask;`
- L160 _public member_ `TArray<FVector3f>& SkyBentNormal;`
- L162 _public function_ `TLightSampleDataProvider<FVector3f>( FIntPoint Size, TArray<FLinearColor>& IncidentLightingAsValidityMask, TArray<FVector3f>& SkyBentNormal) : Size(Size) , IncidentLightingAsValidityMask(IncidentLightingAsValidityMask) , SkyBentNormal(SkyBentNormal)`

#### struct `TLightSampleDataProvider`  
`template<> struct TLightSampleDataProvider<FLinearColor> : public FLightSampleDataProvider`  
_L117-153_
- inherits: `FLightSampleDataProvider`
- L119 _public member_ `FIntPoint Size;`
- L120 _public member_ `TArray<FLinearColor>& IncidentLighting;`
- L121 _public member_ `TArray<FLinearColor>& LuminanceSH;`
- L123 _public function_ `TLightSampleDataProvider<FLinearColor>( FIntPoint Size, TArray<FLinearColor>& IncidentLighting, TArray<FLinearColor>& LuminanceSH) : Size(Size) , IncidentLighting(IncidentLighting) , LuminanceSH(LuminanceSH)`
- L133 _public function_ `virtual FIntPoint GetSize() const override`
- L138 _public function_ `virtual bool IsMapped(FIntPoint Location) const override`
- L143 _public function_ `virtual float GetL(FIntPoint Location) const override`
- L148 _public function_ `virtual void OverwriteTexel(FIntPoint Dst, FIntPoint Src) override`
- L159 _public member_ `TArray<FLinearColor>& IncidentLightingAsValidityMask;`
- L160 _public member_ `TArray<FVector3f>& SkyBentNormal;`
- L162 _public function_ `TLightSampleDataProvider<FVector3f>( FIntPoint Size, TArray<FLinearColor>& IncidentLightingAsValidityMask, TArray<FVector3f>& SkyBentNormal) : Size(Size) , IncidentLightingAsValidityMask(IncidentLightingAsValidityMask) , SkyBentNormal(SkyBentNormal)`

#### struct `TLightSampleDataProvider`  
`template<> struct TLightSampleDataProvider<FVector3f> : public FLightSampleDataProvider`  
_L156-191_
- inherits: `FLightSampleDataProvider`
- L119 _public member_ `FIntPoint Size;`
- L120 _public member_ `TArray<FLinearColor>& IncidentLighting;`
- L121 _public member_ `TArray<FLinearColor>& LuminanceSH;`
- L123 _public function_ `TLightSampleDataProvider<FLinearColor>( FIntPoint Size, TArray<FLinearColor>& IncidentLighting, TArray<FLinearColor>& LuminanceSH) : Size(Size) , IncidentLighting(IncidentLighting) , LuminanceSH(LuminanceSH)`
- L133 _public function_ `virtual FIntPoint GetSize() const override`
- L138 _public function_ `virtual bool IsMapped(FIntPoint Location) const override`
- L143 _public function_ `virtual float GetL(FIntPoint Location) const override`
- L148 _public function_ `virtual void OverwriteTexel(FIntPoint Dst, FIntPoint Src) override`
- L159 _public member_ `TArray<FLinearColor>& IncidentLightingAsValidityMask;`
- L160 _public member_ `TArray<FVector3f>& SkyBentNormal;`
- L162 _public function_ `TLightSampleDataProvider<FVector3f>( FIntPoint Size, TArray<FLinearColor>& IncidentLightingAsValidityMask, TArray<FVector3f>& SkyBentNormal) : Size(Size) , IncidentLightingAsValidityMask(IncidentLightingAsValidityMask) , SkyBentNormal(SkyBentNormal)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define WITH_INTELOIDN 0`
- L91 _prototype_ `void DenoiseSkyBentNormal( FIntPoint Size, TArray<FLinearColor>& ValidityMask, TArray<FVector3f>& BentNormal, FDenoiserContext& DenoiserContext);`
- L97 _prototype_ `void DenoiseRawData( FIntPoint Size, TArray<FLinearColor>& IncidentLighting, TArray<FLinearColor>& LuminanceSH, FDenoiserContext& DenoiserContext, bool bPrepadTexels = true);`
- L193 _prototype_ `void SimpleFireflyFilter(FLightSampleDataProvider& SampleData);`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapEncoding.h` (Private)


#### struct `FLightSampleData`  
`struct FLightSampleData`  
_L12-51_
- desc: Incident lighting for a single sample, as produced by a lighting build. FGatheredLightSample is used for gathering lighting instead of this format as FLightSampleData is not additive.
- L14 _public function_ `FLightSampleData()`
- L29 _public member_ `float Coefficients[NUM_STORED_LIGHTMAP_COEF][3];` — Coefficients[0] stores the normalized average color, Coefficients[1] stores the maximum color component in each lightmap basis direction, and Coefficients[2] stores the simple lightmap which is colored incident lighting along the vertex normal.
- L31 _public member_ `float SkyOcclusion[3];`
- L33 _public member_ `float AOMaterialMask;`
- L36 _public member_ `bool bIsMapped;` — True if this sample maps to a valid point on a triangle.  This is only meaningful for texture lightmaps.
- L43 _public function_ `FColor GetColor(int32 Component) const` — Export helper @param Component Which directional lightmap component to retrieve @return An FColor for this component, clamped to White

#### Free symbols / members of external scopes

- L53 _prototype_ `FLightSampleData ConvertToLightSample(FLinearColor IncidentLighting, FLinearColor LuminanceSH);`
- L55 _prototype_ `void QuantizeLightSamples( TArray<FLightSampleData> InLightSamples, TArray<FLightMapCoefficients>& OutLightSamples, float OutMultiply[NUM_STORED_LIGHTMAP_COEF][4], float OutAdd[NUM_STORED_LIGHTMAP_COEF][4]);`
- L61 _prototype_ `FQuantizedSignedDistanceFieldShadowSample ConvertToShadowSample(FLinearColor ShadowMask, int32 ChannelIndex);`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapGBuffer.h` (Private)


#### struct `FLightmapElementData`  
`struct FLightmapElementData : public FMeshMaterialShaderElementData`  
_L22-32_
- inherits: `FMeshMaterialShaderElementData`
- L24 _public member_ `const FLightCacheInterface* LCI;`
- L26 _public member_ `FVector4f VirtualTexturePhysicalTileCoordinateScaleAndBias;`
- L27 _public member_ `int32 RenderPassIndex;`
- L28 _public member_ `FIntPoint ScratchTilePoolOffset;`
- L29 _public member_ `int32 bMaterialTwoSided = 0;`
- L31 _public function_ `FLightmapElementData(const FLightCacheInterface* LCI) : LCI(LCI)`

#### class `FLightmapGBufferVS`  
`class FLightmapGBufferVS : public FMeshMaterialShader`  
_L34-108_
- inherits: `FMeshMaterialShader`
- L36 _private prototype_ `DECLARE_SHADER_TYPE(FLightmapGBufferVS, MeshMaterial);`
- L44 _protected function_ `FLightmapGBufferVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FMeshMaterialShader(Initializer)`
- L52 _protected prototype_ `FLightmapGBufferVS() = default;`
- L54 _protected function_ `static void ModifyCompilationEnvironment(const FMaterialShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L63 _protected function_ `static bool ShouldCompilePermutation(const FMeshMaterialShaderPermutationParameters& Parameters)`
- L82 _public function_ `void GetShaderBindings( const FScene* Scene, ERHIFeatureLevel::Type FeatureLevel, const FPrimitiveSceneProxy* PrimitiveSceneProxy, const FMaterialRenderProxy& MaterialRenderProxy, const FMaterial& Material, const FLightmapElementData& ShaderElementData, FMeshDrawSingleShaderBindings& ShaderBindings) const`

#### class `FLightmapGBufferPS`  
`class FLightmapGBufferPS : public FMeshMaterialShader`  
_L110-166_
- inherits: `FMeshMaterialShader`
- L112 _private prototype_ `DECLARE_SHADER_TYPE(FLightmapGBufferPS, MeshMaterial);`
- L117 _public function_ `static bool ShouldCompilePermutation(const FMeshMaterialShaderPermutationParameters& Parameters)`
- L135 _public function_ `static void ModifyCompilationEnvironment(const FMaterialShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L144 _public prototype_ `FLightmapGBufferPS() = default;`
- L146 _public function_ `FLightmapGBufferPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FMeshMaterialShader(Initializer)`
- L153 _public function_ `void GetShaderBindings( const FScene* Scene, ERHIFeatureLevel::Type FeatureLevel, const FPrimitiveSceneProxy* PrimitiveSceneProxy, const FMaterialRenderProxy& MaterialRenderProxy, const FMaterial& Material, const FLightmapElementData& ShaderElementData, FMeshDrawSingleShaderBindings& ShaderBindings) const`

#### class `FLightmapGBufferMeshProcessor`  
`class FLightmapGBufferMeshProcessor : public FMeshPassProcessor`  
_L168-267_
- inherits: `FMeshPassProcessor`
- L171 _public function_ `FLightmapGBufferMeshProcessor( const FScene* InScene, const FSceneView* InView, FMeshPassDrawListContext* InDrawListContext, FVector4f VirtualTexturePhysicalTileCoordinateScaleAndBias, int32 RenderPassIndex, FIntPoint ScratchTilePoolOffset ) : FMeshPassProcessor(TEXT("LightmapGBuffer"), InScene, InView->GetFeatureLevel(), InView, InDrawListContext) , VirtualTexturePhysicalTileCoordinateScaleAndBias(VirtualTexturePhysicalTileCoordinateScaleAndBias) , RenderPassIndex(RenderPassIndex) , ScratchTilePoolOffset(ScratchTilePoolOffset)`
- L188 _public function_ `virtual void AddMeshBatch(const FMeshBatch& RESTRICT MeshBatch, uint64 BatchElementMask, const FPrimitiveSceneProxy* RESTRICT PrimitiveSceneProxy, int32 StaticMeshId = -1) override final`
- L206 _private function_ `bool Process( const FMeshBatch& MeshBatch, uint64 BatchElementMask, int32 StaticMeshId, bool bMaterialTwoSided, const FPrimitiveSceneProxy* RESTRICT PrimitiveSceneProxy, const FMaterialRenderProxy& RESTRICT MaterialRenderProxy, const FMaterial& RESTRICT MaterialResource)`
- L262 _private member_ `FMeshPassProcessorRenderState DrawRenderState;`
- L264 _private member_ `FVector4f VirtualTexturePhysicalTileCoordinateScaleAndBias;`
- L265 _private member_ `int32 RenderPassIndex;`
- L266 _private member_ `FIntPoint ScratchTilePoolOffset;`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapPreviewVirtualTexture.h` (Private)


#### class `GPULightmass::FLightmapPreviewVirtualTexture`  
`class FLightmapPreviewVirtualTexture : public IVirtualTexture`  
_L16-53_
- inherits: `IVirtualTexture`
- L19 _public prototype_ `FLightmapPreviewVirtualTexture(FLightmapRenderStateRef LightmapRenderState, FLightmapRenderer* Renderer);`
- L21 _public function_ `virtual bool IsPageStreamed(uint8 vLevel, uint32 vAddress) const override`
- L26 _public prototype_ `virtual FVTRequestPageResult RequestPageData( FRHICommandListBase& RHICmdList, const FVirtualTextureProducerHandle& ProducerHandle, uint8 LayerMask, uint8 vLevel, uint64 vAddress, EVTRequestPagePriority Priority ) override;`
- L35 _public prototype_ `virtual IVirtualTextureFinalizer* ProducePageData( FRHICommandListBase& RHICmdList, ERHIFeatureLevel::Type FeatureLevel, EVTProducePageFlags Flags, const FVirtualTextureProducerHandle& InProducerHandle, uint8 LayerMask, uint8 vLevel, uint64 vAddress, uint64 RequestHandle, const FVTProduceTargetLayer* TargetLayers ) override;`
- L47 _public member_ `IAllocatedVirtualTexture* AllocatedVT;`
- L48 _public member_ `FVirtualTextureProducerHandle ProducerHandle;`
- L51 _private member_ `FLightmapRenderStateRef LightmapRenderState;`
- L52 _private member_ `FLightmapRenderer* LightmapRenderer;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace GPULightmass`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRayTracing.h` (Private)


#### class `FLightmapRayTracingMeshProcessor`  
`class FLightmapRayTracingMeshProcessor : public FRayTracingMeshProcessor`  
_L30-34_
- inherits: `FRayTracingMeshProcessor`
- L33 _public prototype_ `FLightmapRayTracingMeshProcessor(FRayTracingMeshCommandContext* InCommandContext);`

#### class `FLightmapPathTracingRGS`  
`class FLightmapPathTracingRGS : public FGlobalShader`  
_L36-104_
- inherits: `FGlobalShader`
- L45 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FUseIrradianceCaching, FUseFirstBounceRayGuiding, FUseICBackfaceDetection>;`
- L47 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L59 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L68 _private function_ `static ERayTracingPayloadType GetRayTracingPayloadType(const int32 PermutationId)`

#### class `FVolumetricLightmapPathTracingRGS`  
`class FVolumetricLightmapPathTracingRGS : public FGlobalShader`  
_L106-169_
- inherits: `FGlobalShader`
- L113 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FUseIrradianceCaching>;`
- L115 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L120 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L129 _private function_ `static ERayTracingPayloadType GetRayTracingPayloadType(const int32 PermutationId)`

#### class `FStationaryLightShadowTracingRGS`  
`class FStationaryLightShadowTracingRGS : public FGlobalShader`  
_L171-213_
- inherits: `FGlobalShader`
- L174 _private function_ `SHADER_USE_ROOT_PARAMETER_STRUCT(FStationaryLightShadowTracingRGS, FGlobalShader) static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L181 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L188 _private function_ `static ERayTracingPayloadType GetRayTracingPayloadType(const int32 PermutationId)`

#### class `FFirstBounceRayGuidingCDFBuildCS`  
`class FFirstBounceRayGuidingCDFBuildCS : public FGlobalShader`  
_L215-239_
- inherits: `FGlobalShader`
- L217 _private prototype_ `DECLARE_GLOBAL_SHADER(FFirstBounceRayGuidingCDFBuildCS);`
- L218 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FFirstBounceRayGuidingCDFBuildCS, FGlobalShader);`
- L220 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L225 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FStaticShadowDepthMapTracingRGS`  
`class FStaticShadowDepthMapTracingRGS : public FGlobalShader`  
_L241-278_
- inherits: `FGlobalShader`
- L248 _private typedef_ `using FPermutationDomain = TShaderPermutationDomain<FLightType>;`
- L250 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L255 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`
- L261 _private function_ `static ERayTracingPayloadType GetRayTracingPayloadType(const int32 PermutationId)`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRenderer.h` (Private)


#### struct `GPULightmass::FLightmapTileRequest`  
`struct FLightmapTileRequest`  
_L21-57_
- L23 _public member_ `FLightmapRenderStateRef RenderState;`
- L24 _public member_ `FTileVirtualCoordinates VirtualCoordinates;`
- L26 _public function_ `FLightmapTileRequest( FLightmapRenderStateRef RenderState, FTileVirtualCoordinates VirtualCoordinates) : RenderState(RenderState) , VirtualCoordinates(VirtualCoordinates)`
- L33 _public function_ `~FLightmapTileRequest()` — this deletes the move constructor while keeps copy constructors
- L35 _public member_ `FIntPoint OutputPhysicalCoordinates[8];`
- L36 _public member_ `IPooledRenderTarget* OutputRenderTargets[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };`
- L37 _public member_ `uint32 TileAddressInWorkingSet = ~0u;`
- L38 _public member_ `uint32 TileAddressInScratch = ~0u;`
- L40 _public function_ `bool operator==(const FLightmapTileRequest& Rhs) const`
- L45 _public function_ `bool IsScreenOutputTile() const`

#### struct `GPULightmass::FLightmapReadbackGroup`  
`struct FLightmapReadbackGroup`  
_L59-82_
- L61 _public member_ `bool bIsFree = true;`
- L62 _public member_ `int32 Revision;`
- L63 _public member_ `int32 GPUIndex = 0;`
- L64 _public member_ `TUniquePtr<FLightmapTilePoolGPU> ReadbackTilePoolGPU;`
- L65 _public member_ `TArray<FLightmapTileRequest> ConvergedTileRequests;`
- L66 _public member_ `TUniquePtr<FRHIGPUTextureReadback> StagingHQLayer0Readback;`
- L67 _public member_ `TUniquePtr<FRHIGPUTextureReadback> StagingHQLayer1Readback;`
- L68 _public member_ `TUniquePtr<FRHIGPUTextureReadback> StagingShadowMaskReadback;`
- L69 _public member_ `TUniquePtr<FRHIGPUTextureReadback> StagingSkyOcclusionReadback;`
- L81 _public member_ `TUniquePtr<FTextureData> TextureData;`

#### struct `GPULightmass::FLightmapReadbackGroup::FTextureData`  
`struct FTextureData`  
_L71-79_
- L74 _public member_ `FIntPoint SizeInTiles;` — Duplicate some metadata so the async thread doesn't need to access FLightmapReadbackGroup
- L75 _public member_ `int32 RowPitchInPixels[4];`
- L76 _public member_ `TArray<FLinearColor> Texture[4];`
- L78 _public member_ `volatile int32 bDenoisingFinished = 0;`

#### struct `GPULightmass::FLightmapTileDenoiseGroup`  
`struct FLightmapTileDenoiseGroup`  
_L84-101_
- L86 _public function_ `FLightmapTileDenoiseGroup(FLightmapTileRequest& TileRequest) : TileRequest(TileRequest)`
- L88 _public member_ `int32 Revision;`
- L89 _public member_ `FLightmapTileRequest TileRequest;`
- L90 _public member_ `bool bShouldBeCancelled = false;`
- L99 _public member_ `TSharedPtr<FTextureData, ESPMode::ThreadSafe> TextureData;`
- L100 _public member_ `class FLightmapTileDenoiseAsyncTask* AsyncDenoisingWork = nullptr;`

#### struct `GPULightmass::FLightmapTileDenoiseGroup::FTextureData`  
`struct FTextureData`  
_L92-97_
- L94 _public member_ `TArray<FLinearColor> Texture[4];`
- L96 _public member_ `volatile int32 bDenoisingFinished = 0;`

#### class `GPULightmass::FLightmapTileDenoiseAsyncTask`  
`class FLightmapTileDenoiseAsyncTask : public IQueuedWork`  
_L103-112_
- inherits: `IQueuedWork`
- L106 _public member_ `FIntPoint Size;`
- L107 _public member_ `TSharedPtr<FLightmapTileDenoiseGroup::FTextureData, ESPMode::ThreadSafe> TextureData;`
- L108 _public member_ `EGPULightmassDenoiser Denoiser;`
- L110 _public prototype_ `virtual void DoThreadedWork();`
- L111 _public function_ `virtual void Abandon()`

#### class `GPULightmass::FLightmapRenderer`  
`class FLightmapRenderer : public IVirtualTextureFinalizer`  
_L114-179_
- inherits: `IVirtualTextureFinalizer`
- L117 _public prototype_ `FLightmapRenderer(FRHICommandList& RHICmdList, FSceneRenderState* InScene);`
- L119 _public prototype_ `void AddRequest(FLightmapTileRequest TileRequest);`
- L121 _public prototype_ `void RenderMeshBatchesIntoGBuffer( FRHICommandList& RHICmdList, const FSceneView* View, int32 GPUScenePrimitiveId, TArray<FMeshBatch> MeshBatches, FVector4f VirtualTexturePhysicalTileCoordinateScaleAndBias, int32 RenderPassIndex, FIntPoint ScratchTilePoolOffset);`
- L130 _public prototype_ `virtual void Finalize(FRDGBuilder& GraphBuilder) override;`
- L132 _public prototype_ `virtual ~FLightmapRenderer();`
- L134 _public prototype_ `void BackgroundTick(FRHICommandListImmediate& RHICmdList);`
- L136 _public prototype_ `void BumpRevision();`
- L137 _public function_ `int32 GetCurrentRevision()`
- L139 _public member_ `int32 FrameNumber = 0;`
- L141 _public member_ `int32 NumTotalPassesToRender = 0;`
- L143 _public member_ `bool bDenoiseDuringInteractiveBake = false;`
- L144 _public member_ `bool bOnlyBakeWhatYouSee = false;`
- L146 _public member_ `TArray<TArray<FLightmapTileRequest>> TilesVisibleLastFewFrames;`
- L148 _public member_ `bool bIsRecordingTileRequests = false;`
- L149 _public member_ `TArray<FLightmapTileRequest> RecordedTileRequests;`
- L150 _public prototype_ `void DeduplicateRecordedTileRequests();`
- L153 _private member_ `int32 CurrentRevision = 0;`
- L154 _private member_ `int32 LastInvalidationFrame = 0;`
- L155 _private member_ `int32 Mip0WorkDoneLastFrame = 0;`
- L156 _private member_ `bool bIsExiting = false;`
- L157 _private member_ `bool bInsideBackgroundTick = false;`
- L158 _private member_ `bool bWasRunningAtFullSpeed = true;`
- L160 _private member_ `FSceneRenderState* Scene;`
- L162 _private member_ `TArray<FLightmapTileRequest> PendingTileRequests;`
- L164 _private member_ `FLightmapTilePoolGPU LightmapTilePoolGPU;`
- L166 _private member_ `TUniquePtr<FLightmapTilePoolGPU> ScratchTilePoolGPU;`
- L168 _private member_ `TArray<FLightmapReadbackGroup*> OngoingReadbacks;`
- L169 _private member_ `TArray<TUniquePtr<FLightmapReadbackGroup>> RecycledReadbacks;`
- L171 _private member_ `TArray<FLightmapTileDenoiseGroup> OngoingDenoiseGroups;`
- L173 _private member_ `TUniquePtr<FLightmapTilePoolGPU> UploadTilePoolGPU;`
- L175 _private member_ `FQueuedThreadPool* DenoisingThreadPool;`
- L177 _private prototype_ `void RenderIrradianceCacheVisualization(FPostOpaqueRenderParameters& Parameters);`
- L178 _private member_ `FDelegateHandle IrradianceCacheVisualizationDelegateHandle;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace GPULightmass`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapStorage.h` (Private)


#### struct `GPULightmass::FTileDataLayer`  
`struct FTileDataLayer`  
_L15-45_
- L17 _public member_ `TArray<FLinearColor> Data;`
- L18 _public member_ `TArray<uint8> CompressedData;`
- L20 _public member_ `TDoubleLinkedList<FTileDataLayer*>::TDoubleLinkedListNode Node;`
- L21 _public member_ `bool bNodeAddedToList = false;`
- L23 _public member_ `static TDoubleLinkedList<FTileDataLayer*> AllUncompressedTiles;`
- L25 _public function_ `FTileDataLayer() : Node(this)`
- L33 _public function_ `~FTileDataLayer()`
- L41 _public prototype_ `int64 Compress(bool bParallelCompression = false);`
- L42 _public prototype_ `void Decompress();`
- L43 _public prototype_ `void AllocateForWrite();`
- L44 _public prototype_ `static void Evict();`

#### struct `GPULightmass::FTileStorage`  
`struct FTileStorage`  
_L47-64_
- L49 _public member_ `TUniquePtr<FTileDataLayer> CPUTextureData[(int32)ELightMapVirtualTextureType::Count];`
- L50 _public member_ `TUniquePtr<FTileDataLayer> CPUTextureRawData[(int32)ELightMapVirtualTextureType::Count];`
- L52 _public function_ `FTileStorage()`

#### class `GPULightmass::FLightmap`  
`class FLightmap`  
_L66-91_
- L69 _public prototype_ `FLightmap(FString InName, FIntPoint InSize);`
- L71 _public prototype_ `void CreateGameThreadResources();`
- L73 _public function_ `FIntPoint GetPaddedSizeInTiles() const`
- L79 _public function_ `FIntPoint GetPaddedSize() const`
- L81 _public member_ `FString Name;`
- L82 _public member_ `FIntPoint Size;`
- L84 _public member_ `TUniquePtr<FLightmapResourceCluster> ResourceCluster;`
- L85 _public member_ `TUniquePtr<FGCObjectScopeGuard> TextureUObjectGuard = nullptr;`
- L86 _public member_ `ULightMapVirtualTexture2D* TextureUObject = nullptr;`
- L87 _public member_ `TUniquePtr<FMeshMapBuildData> MeshMapBuildData;`
- L88 _public member_ `TRefCountPtr<FLightMap2D> LightmapObject;`
- L90 _public member_ `int32 NumStationaryLightsPerShadowChannel[4] = { 0, 0, 0, 0 };`

#### class `GPULightmass::FLightmapRenderState`  
`class FLightmapRenderState : public FLightCacheInterface`  
_L95-301_
- inherits: `FLightCacheInterface`
- L112 _public prototype_ `FLightmapRenderState(Initializer InInitializer, FGeometryInstanceRenderStateRef GeometryInstanceRef);`
- L114 _public function_ `FIntPoint GetSize() const`
- L115 _public function_ `int32 GetMaxLevel() const`
- L116 _public function_ `uint32 GetNumTilesAcrossAllMipmapLevels() const`
- L117 _public function_ `FIntPoint GetPaddedSizeInTiles() const`
- L123 _public function_ `FIntPoint GetPaddedSize() const`
- L124 _public function_ `FIntPoint GetPaddedPhysicalSize() const`
- L125 _public function_ `FIntPoint GetPaddedSizeAtMipLevel(int32 MipLevel) const`
- L126 _public function_ `FIntPoint GetPaddedSizeInTilesAtMipLevel(int32 MipLevel) const`
- L156 _public function_ `bool IsTileCoordinatesValid(FTileVirtualCoordinates Coords)`
- L173 _public function_ `FTileState& RetrieveTileState(FTileVirtualCoordinates Coords)`
- L187 _public function_ `uint32 RetrieveTileStateIndex(FTileVirtualCoordinates Coords)`
- L210 _public function_ `FTileRelevantLightSampleCountState& RetrieveTileRelevantLightSampleState(FTileVirtualCoordinates Coords)`
- L224 _public prototype_ `bool IsTileGIConverged(FTileVirtualCoordinates Coords, int32 NumGISamples);`
- L225 _public prototype_ `bool IsTileShadowConverged(FTileVirtualCoordinates Coords, int32 NumShadowSamples);`
- L226 _public prototype_ `bool DoesTileHaveValidCPUData(FTileVirtualCoordinates Coords, int32 CurrentRevision);`
- L228 _public member_ `FString Name;`
- L229 _public member_ `TUniquePtr<FLightmapResourceCluster> ResourceCluster;`
- L230 _public member_ `FVector4f LightmapCoordinateScaleBias;`
- L231 _public member_ `uint32 DistributionPrefixSum = 0;`
- L235 _public member_ `class FLightmapPreviewVirtualTexture* LightmapPreviewVirtualTexture = nullptr;` — The virtual texture & producer that handles actual rendering Can't use a unique ptr, because ReleaseVirtualTextureProducer deletes the pointer
- L238 _public member_ `FUintVector4 LightmapVTPackedPageTableUniform[2];` — Cached VT uniforms to avoid surprisingly high cost
- L239 _public member_ `FUintVector4 LightmapVTPackedUniform[5];` — VT (5 layers, 1x uint4 per layer)
- L241 _public member_ `TMap<FTileVirtualCoordinates, FTileStorage> TileStorage;`
- L243 _public member_ `FGeometryInstanceRenderStateRef GeometryInstanceRef;`
- L245 _public member_ `TArray<FPointLightRenderStateRef> RelevantPointLights;`
- L246 _public member_ `TArray<FSpotLightRenderStateRef> RelevantSpotLights;`
- L247 _public member_ `TArray<FRectLightRenderStateRef> RelevantRectLights;`
- L249 _public function_ `void AddRelevantLight(FDirectionalLightRenderStateRef Light)`
- L254 _public function_ `void RemoveRelevantLight(FDirectionalLightRenderStateRef Light)`
- L259 _public function_ `void AddRelevantLight(FPointLightRenderStateRef Light)`
- L264 _public function_ `void RemoveRelevantLight(FPointLightRenderStateRef Light)`
- L269 _public function_ `void AddRelevantLight(FSpotLightRenderStateRef Light)`
- L274 _public function_ `void RemoveRelevantLight(FSpotLightRenderStateRef Light)`
- L279 _public function_ `void AddRelevantLight(FRectLightRenderStateRef Light)`
- L284 _public function_ `void RemoveRelevantLight(FRectLightRenderStateRef Light)`
- L289 _public function_ `virtual FLightInteraction GetInteraction(const class FLightSceneProxy* LightSceneProxy) const override`
- L294 _public prototype_ `void ReleasePreviewVirtualTexture();`
- L297 _private member_ `FIntPoint Size;`
- L298 _private member_ `int32 MaxLevel;`
- L299 _private member_ `TArray<FTileState> TileStates;`
- L300 _private member_ `TArray<FTileRelevantLightSampleCountState> TileRelevantLightSampleCountStates;`

#### struct `GPULightmass::FLightmapRenderState::Initializer`  
`struct Initializer`  
_L98-110_
- L100 _public member_ `FString Name;`
- L101 _public member_ `FIntPoint Size { EForceInit::ForceInitToZero };`
- L102 _public member_ `int32 MaxLevel = -1;`
- L103 _public member_ `FLightmapResourceCluster* ResourceCluster = nullptr;`
- L104 _public member_ `FVector4f LightmapCoordinateScaleBias { EForceInit::ForceInitToZero };`
- L106 _public function_ `bool IsValid()`

#### struct `GPULightmass::FLightmapRenderState::FTileState`  
`struct FTileState`  
_L131-154_
- L133 _public member_ `int32 Revision = -1;`
- L134 _public member_ `int32 RenderPassIndex = 0;`
- L135 _public member_ `int32 CPURevision = -1;`
- L136 _public member_ `int32 OngoingReadbackRevision = -1;`
- L137 _public member_ `bool bCanBeDenoised = false;`
- L138 _public member_ `bool bWasDenoisedWithoutProximity = false;`
- L140 _public function_ `void Invalidate()`
- L147 _public function_ `void InvalidateCPUData()`

#### struct `GPULightmass::FLightmapRenderState::FTileRelevantLightSampleCountState`  
`struct FTileRelevantLightSampleCountState`  
_L201-208_
- L203 _public member_ `uint32 RoundRobinIndex = 0;`
- L204 _public member_ `TMap<FDirectionalLightRenderStateRef, int32> RelevantDirectionalLightSampleCount;`
- L205 _public member_ `TMap<FPointLightRenderStateRef, int32> RelevantPointLightSampleCount;`
- L206 _public member_ `TMap<FSpotLightRenderStateRef, int32> RelevantSpotLightSampleCount;`
- L207 _public member_ `TMap<FRectLightRenderStateRef, int32> RelevantRectLightSampleCount;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace GPULightmass`
- L93 _typedef_ `using FLightmapRef = TEntityArray<FLightmap>::EntityRefType;` (scope `GPULightmass`)
- L303 _typedef_ `using FLightmapRenderStateRef = TEntityArray<FLightmapRenderState>::EntityRefType;` (scope `GPULightmass`)
- L305 _prototype_ `void CreateLightmapPreviewVirtualTexture(FLightmapRenderStateRef LightmapRenderState, ERHIFeatureLevel::Type FeatureLevel, class FLightmapRenderer* LightmapRenderer);` (scope `GPULightmass`)
- L309 _function_ `static uint32 GetTypeHash(const GPULightmass::FLightmapRenderStateRef& Ref)`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapTilePool.h` (Private)


#### struct `FVirtualTile`  
`struct FVirtualTile`  
_L10-16_
- L13 _public member_ `GPULightmass::FLightmapRenderStateRef RenderState;` — Comparison of FLightmapRenderStateRef is solely based on ElementId, which means it won't survive array changes (which means element swaps)
- L14 _public member_ `int32 MipLevel = 0;`
- L15 _public member_ `int32 VirtualAddress = 0;`

#### class `FLightmapTilePool`  
`class FLightmapTilePool`  
_L28-47_
- L31 _public prototype_ `FLightmapTilePool(int32 InNumTotalTiles);`
- L33 _public member_ `int32 NumTotalTiles;`
- L35 _public prototype_ `void AllocAndLock(int32 NumTilesToAllocate, TArray<int32>& OutSuccessfullyAllocatedTiles);`
- L36 _public prototype_ `void Lock(const TArrayView<int32> InTiles);`
- L37 _public prototype_ `void MakeAvailable(const TArrayView<int32> InSuccessfullyAllocatedTiles, const uint32 NewTileKey);`
- L38 _public prototype_ `void QueryResidency(const TArrayView<FVirtualTile> InTilesToQuery, TArray<uint32>& OutTileIndexIfResident);`
- L39 _public prototype_ `void Map(const TArrayView<FVirtualTile> InVirtualTiles, const TArrayView<int32> InTiles, TArray<FVirtualTile>& OutVirtualTilesEvicted);`
- L40 _public prototype_ `void Unmap(const TArrayView<FVirtualTile> InVirtualTiles);`
- L41 _public prototype_ `void UnmapAll();`
- L44 _private member_ `FBinaryHeap<uint32, uint32> FreeHeap;`
- L45 _private member_ `TMap<uint32, FVirtualTile> TileIndexToVirtualTileMap;`
- L46 _private member_ `TMap<FVirtualTile, uint32> VirtualTileToTileIndexMap;`

#### class `FLightmapTilePoolGPU`  
`class FLightmapTilePoolGPU : public FLightmapTilePool`  
_L49-72_
- inherits: `FLightmapTilePool`
- L58 _public function_ `FLightmapTilePoolGPU(FIntPoint InSizeInTiles) : FLightmapTilePool(InSizeInTiles.X * InSizeInTiles.Y), SizeInTiles(InSizeInTiles)`
- L59 _public prototype_ `FLightmapTilePoolGPU(FRHICommandListBase& RHICmdList, int32 NumLayers, FIntPoint InSizeInTiles, FIntPoint TileSize);`
- L61 _public prototype_ `void Initialize(FRHICommandListBase& RHICmdList, TArray<FLayerFormatAndTileSize> Layers);`
- L63 _public member_ `FIntPoint SizeInTiles;`
- L65 _public member_ `TArray<FLayerFormatAndTileSize> LayerFormatAndTileSize;`
- L66 _public member_ `TArray<TRefCountPtr<IPooledRenderTarget>> PooledRenderTargets;`
- L67 _public member_ `TArray<FString> PooledRenderTargetDebugNames;`
- L69 _public prototype_ `FIntPoint GetPositionFromLinearAddress(uint32 Address);`
- L71 _public prototype_ `void ReleaseRenderTargets();`

#### struct `FLightmapTilePoolGPU::FLayerFormatAndTileSize`  
`struct FLayerFormatAndTileSize`  
_L52-56_
- L54 _public member_ `EPixelFormat Format;`
- L55 _public member_ `FIntPoint TileSize;`

#### Free symbols / members of external scopes

- L18 _function_ `inline uint32 GetTypeHash(const FVirtualTile& TypeVar)`
- L23 _function_ `inline bool operator==(const FVirtualTile& LHS, const FVirtualTile& RHS)`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/PathTracingLightParameters.inl` (Private)


#### Free symbols / members of external scopes

- L12 _prototype_ `void PrepareLightGrid(FRDGBuilder& GraphBuilder, ERHIFeatureLevel::Type FeatureLevel, FPathTracingLightGrid* LightGridParameters, const FPathTracingLight* Lights, uint32 NumLights, uint32 NumInfiniteLights, FRDGBufferSRV* LightsSRV);`
- L14 _function_ `static uint32 EncodeToF16x2(const FVector2f& In)`
- L20 _function_ `template<typename PassParameterType> void SetupPathTracingLightParameters( const GPULightmass::FLightSceneRenderState& LightScene, FRDGBuilder& GraphBuilder, const FViewInfo& View, PassParameterType* PassParameters)`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/Scene/GeometryInterface.h` (Private)


#### struct `GPULightmass::FGeometryRenderState`  
`struct FGeometryRenderState`  
_L16-27_
- L18 _public member_ `FMatrix LocalToWorld;`
- L20 _public member_ `FBoxSphereBounds WorldBounds;`
- L21 _public member_ `FVector ActorPosition;`
- L22 _public member_ `FBoxSphereBounds LocalBounds;`
- L24 _public member_ `bool bCastShadow;`
- L26 _public member_ `TArray<FLightmapRenderStateRef> LODLightmapRenderStates;`

#### struct `GPULightmass::FGeometry`  
`struct FGeometry`  
_L29-43_
- L31 _public function_ `virtual ~FGeometry()`
- L32 _public prototype_ `FGeometry() = default;`
- L33 _public prototype_ `FGeometry(FGeometry&& In) = default;` — Default move constructor is killed by the custom destructor
- L35 _public member_ `FBoxSphereBounds WorldBounds;`
- L37 _public member_ `bool bCastShadow;`
- L38 _public member_ `bool bLODsShareStaticLighting;`
- L40 _public member_ `TArray<FLightmapRef> LODLightmaps;`
- L42 _public prototype_ `virtual UPrimitiveComponent* GetComponentUObject() const = 0;`

#### class `GPULightmass::FGeometryInstanceRenderStateRef`  
`class FGeometryInstanceRenderStateRef : public FGenericEntityRef`  
_L47-70_
- inherits: `FGenericEntityRef`
- L50 _public function_ `FGeometryInstanceRenderStateRef( FGeometryInstanceRenderStateCollectionBase& Collection, TArray<TSet<RefAddr>>& Refs, TSparseArray<int32>& RefAllocator, int32 ElementId, int32 LODIndex) : FGenericEntityRef(ElementId, Refs, RefAllocator) , LODIndex(LODIndex) , Collection(Collection)`
- L61 _public prototype_ `TArray<FMeshBatch> GetMeshBatchesForGBufferRendering(FTileVirtualCoordinates CoordsForCulling = FTileVirtualCoordinates{});`
- L62 _public prototype_ `FVector GetOrigin() const;`
- L64 _public member_ `int32 LODIndex;`
- L66 _private member_ `FGeometryInstanceRenderStateCollectionBase& Collection;`

#### class `GPULightmass::FGeometryInstanceRenderStateCollectionBase`  
`class FGeometryInstanceRenderStateCollectionBase`  
_L72-78_
- L75 _public function_ `virtual ~FGeometryInstanceRenderStateCollectionBase()`
- L76 _public prototype_ `virtual TArray<FMeshBatch> GetMeshBatchesForGBufferRendering(const FGeometryInstanceRenderStateRef& GeometryInstanceRef, FTileVirtualCoordinates CoordsForCulling) = 0;`
- L77 _public prototype_ `virtual FGeometryRenderState& Get(int32 ElementId) = 0;`

#### class `GPULightmass::TGeometryInstanceRenderStateCollection`  
`template<typename GeometryType> class TGeometryInstanceRenderStateCollection : public FGeometryInstanceRenderStateCollectionBase, public TEntityArray<GeometryType>`  
_L81-105_
- inherits: `FGeometryInstanceRenderStateCollectionBase,TEntityArray<GeometryType>`
- L84 _public prototype_ `virtual TArray<FMeshBatch> GetMeshBatchesForGBufferRendering(const FGeometryInstanceRenderStateRef& GeometryInstanceRef, FTileVirtualCoordinates CoordsForCulling) override;`
- L86 _public function_ `FGeometryInstanceRenderStateRef CreateGeometryInstanceRef(const GeometryType& Element, int32 LODIndex)`
- L91 _public function_ `GeometryType& ResolveGeometryInstanceRef(const FGeometryInstanceRenderStateRef& GeometryInstanceRef)`
- L96 _public function_ `bool Contains(const FGeometryInstanceRenderStateRef& GeometryInstanceRef) const`
- L101 _public function_ `virtual FGeometryRenderState& Get(int32 ElementId) override`

#### class `GPULightmass::FGeometryArrayBase`  
`class FGeometryArrayBase`  
_L106-117_
- L109 _public function_ `virtual ~FGeometryArrayBase()`
- L110 _public prototype_ `virtual int32 Num() const = 0;`
- L111 _public prototype_ `virtual FGeometry& Get(int32 Index) = 0;`
- L112 _public function_ `void LinkRenderStateArray(FGeometryInstanceRenderStateCollectionBase& InRenderStateArray)`
- L113 _public function_ `FGeometryInstanceRenderStateCollectionBase* GetRenderStateArray()`
- L116 _private member_ `FGeometryInstanceRenderStateCollectionBase* RenderStateArray = nullptr;`

#### class `GPULightmass::TGeometryArray`  
`template<typename GeometryType> class TGeometryArray : public FGeometryArrayBase, public TEntityArray<GeometryType>`  
_L120-125_
- inherits: `FGeometryArrayBase,TEntityArray<GeometryType>`
- L123 _public function_ `virtual int32 Num() const override`
- L124 _public function_ `virtual FGeometry& Get(int32 Index) override`

#### struct `GPULightmass::FGeometryAndItsArray`  
`struct FGeometryAndItsArray`  
_L127-133_
- L129 _public member_ `int32 Index;`
- L130 _public member_ `FGeometryArrayBase& Array;`
- L132 _public function_ `FGeometry& GetGeometry()`

#### struct `GPULightmass::FGeometryIterator`  
`struct FGeometryIterator`  
_L135-170_
- L137 _public member_ `int32 IndexInCurrentArray;`
- L138 _public member_ `TArray<FGeometryArrayBase*> ArraysToIterate;`
- L139 _public member_ `int32 ArrayIndex;`
- L141 _public function_ `FGeometryIterator& operator++()`
- L160 _public function_ `bool operator!=(const FGeometryIterator& Other)`
- L166 _public function_ `FGeometryAndItsArray operator*() const`

#### struct `GPULightmass::FGeometryRenderStateToken`  
`struct FGeometryRenderStateToken`  
_L172-176_
- L174 _public member_ `int32 ElementId;`
- L175 _public member_ `FGeometryInstanceRenderStateCollectionBase* RenderStateArray;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace GPULightmass`
- L13 _typedef_ `using FLightmapRef = TEntityArray<class FLightmap>::EntityRefType;` (scope `GPULightmass`)
- L14 _typedef_ `using FLightmapRenderStateRef = TEntityArray<class FLightmapRenderState>::EntityRefType;` (scope `GPULightmass`)

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/Scene/InstancedStaticMesh.h` (Private)


#### class `GPULightmass::FInstanceGroupRenderState`  
`class FInstanceGroupRenderState : public FGeometryRenderState`  
_L12-25_
- inherits: `FGeometryRenderState`
- L15 _public member_ `UInstancedStaticMeshComponent* ComponentUObject;`
- L16 _public member_ `FStaticMeshRenderData* RenderData;`
- L17 _public member_ `TUniquePtr<FInstancedStaticMeshRenderData> InstancedRenderData;`
- L19 _public member_ `TArray<FIntPoint> LODPerInstanceLightmapSize;`
- L20 _public member_ `int32 NumInstances = 0;`
- L21 _public member_ `TSharedPtr<FInstanceDataSceneProxy, ESPMode::ThreadSafe> InstanceDataSceneProxy;`
- L22 _public member_ `const FInstanceSceneDataBuffers *InstanceSceneDataBuffers = nullptr;`
- L24 _public prototype_ `TArray<FMeshBatch> GetMeshBatchesForGBufferRendering(int32 LODIndex, FTileVirtualCoordinates CoordsForCulling);`

#### class `GPULightmass::FInstanceGroup`  
`class FInstanceGroup : public FGeometry`  
_L29-42_
- inherits: `FGeometry`
- L32 _public prototype_ `FInstanceGroup(UInstancedStaticMeshComponent* ComponentUObject);`
- L34 _public prototype_ `const class FMeshMapBuildData* GetMeshMapBuildDataForLODIndex(int32 LODIndex);`
- L36 _public member_ `TArray<FIntPoint> LODPerInstanceLightmapSize;`
- L38 _public prototype_ `void AllocateLightmaps(TEntityArray<FLightmap>& LightmapContainer);`
- L40 _public member_ `UInstancedStaticMeshComponent* ComponentUObject;`
- L41 _public function_ `virtual UPrimitiveComponent* GetComponentUObject() const override`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace GPULightmass`
- L27 _typedef_ `using FInstanceGroupRenderStateRef = TEntityArray<FInstanceGroupRenderState>::EntityRefType;` (scope `GPULightmass`)
- L44 _typedef_ `using FInstanceGroupRef = TEntityArray<FInstanceGroup>::EntityRefType;` (scope `GPULightmass`)

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/Scene/Landscape.h` (Private)


#### class `GPULightmass::FLandscapeRenderState`  
`class FLandscapeRenderState : public FGeometryRenderState`  
_L16-65_
- inherits: `FGeometryRenderState`
- L50 _public member_ `TStaticArray<TUniquePtr<FLandscapeSectionRayTracingState>, 4> SectionRayTracingStates;`
- L52 _public member_ `ULandscapeComponent* ComponentUObject;`
- L54 _public member_ `int32 SubsectionSizeVerts;`
- L55 _public member_ `int32 NumSubsections;`
- L56 _public member_ `uint32 SharedBuffersKey;`
- L57 _public member_ `FLandscapeSharedBuffers* SharedBuffers;`
- L58 _public member_ `UMaterialInterface* MaterialInterface;`
- L59 _public member_ `FMatrix LocalToWorldNoScaling;`
- L60 _public member_ `FLandscapeBatchElementParams BatchElementParams;`
- L61 _public member_ `TUniquePtr<TUniformBuffer<FLandscapeUniformShaderParameters>> LandscapeUniformShaderParameters;`
- L62 _public member_ `TArray<TUniformBuffer<FLandscapeFixedGridUniformShaderParameters>> LandscapeFixedGridUniformShaderParameters;`
- L64 _public prototype_ `TArray<FMeshBatch> GetMeshBatchesForGBufferRendering(int32 LODIndex);`

#### struct `GPULightmass::FLandscapeRenderState::Initializer`  
`struct Initializer`  
_L19-37_
- L21 _public member_ `int32 SubsectionSizeQuads;`
- L22 _public member_ `int32 NumSubsections;`
- L23 _public member_ `int32 ComponentSizeQuads;`
- L24 _public member_ `int32 ComponentSizeVerts;`
- L25 _public member_ `int32 SubsectionSizeVerts;`
- L26 _public member_ `float StaticLightingResolution;`
- L27 _public member_ `int32 StaticLightingLOD;`
- L28 _public member_ `float InvLODBlendRange;`
- L29 _public member_ `FIntPoint ComponentBase;`
- L30 _public member_ `FIntPoint SectionBase;`
- L31 _public member_ `UTexture2D* HeightmapTexture;`
- L32 _public member_ `float HeightmapSubsectionOffsetU;`
- L33 _public member_ `float HeightmapSubsectionOffsetV;`
- L34 _public member_ `FVector4f HeightmapScaleBias;`
- L35 _public member_ `FVector4f WeightmapScaleBias;`
- L36 _public member_ `float WeightmapSubsectionOffset;`

#### struct `GPULightmass::FLandscapeRenderState::FLandscapeSectionRayTracingState`  
`struct FLandscapeSectionRayTracingState`  
_L39-48_
- L41 _public member_ `int8 CurrentLOD;`
- L43 _public member_ `FRayTracingGeometry Geometry;`
- L44 _public member_ `FRWBuffer RayTracingDynamicVertexBuffer;`
- L45 _public member_ `FLandscapeVertexFactoryMVFUniformBufferRef UniformBuffer;`
- L47 _public function_ `FLandscapeSectionRayTracingState() : CurrentLOD(-1)`

#### class `GPULightmass::FLandscape`  
`class FLandscape : public FGeometry`  
_L69-80_
- inherits: `FGeometry`
- L72 _public prototype_ `FLandscape(ULandscapeComponent* ComponentUObject);`
- L74 _public prototype_ `const class FMeshMapBuildData* GetMeshMapBuildDataForLODIndex(int32 LODIndex);`
- L76 _public prototype_ `void AllocateLightmaps(TEntityArray<FLightmap>& LightmapContainer);`
- L78 _public member_ `ULandscapeComponent* ComponentUObject;`
- L79 _public function_ `virtual UPrimitiveComponent* GetComponentUObject() const override`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace GPULightmass`
- L67 _typedef_ `using FLandscapeRenderStateRef = TEntityArray<FLandscapeRenderState>::EntityRefType;` (scope `GPULightmass`)
- L82 _typedef_ `using FLandscapeRef = TEntityArray<FLandscape>::EntityRefType;` (scope `GPULightmass`)

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/Scene/Lights.h` (Private)


#### struct `FLightShaderConstants`  
`struct FLightShaderConstants`  
_L16-56_
- L18 _public member_ `FVector3f PositionHigh;`
- L19 _public member_ `float InvRadius;`
- L20 _public member_ `FVector3f Color;`
- L21 _public member_ `float FalloffExponent;`
- L22 _public member_ `FVector3f Direction;`
- L23 _public member_ `float SpecularScale;`
- L24 _public member_ `FVector3f Tangent;`
- L25 _public member_ `float SourceRadius;`
- L26 _public member_ `FVector3f PositionLow;`
- L27 _public member_ `float SourceLength;`
- L28 _public member_ `FVector2f SpotAngles;`
- L29 _public member_ `float SoftSourceRadius;`
- L30 _public member_ `float RectLightBarnCosAngle;`
- L31 _public member_ `float RectLightBarnLength;`
- L32 _public member_ `float DiffuseScale;`
- L34 _public prototype_ `FLightShaderConstants() = default;`
- L36 _public function_ `FLightShaderConstants(const FLightRenderParameters& LightShaderParameters)`

#### struct `GPULightmass::FLocalLightBuildInfo`  
`struct FLocalLightBuildInfo`  
_L68-86_
- L70 _public prototype_ `FLocalLightBuildInfo(ULightComponent* LightComponent);`
- L71 _public function_ `virtual ~FLocalLightBuildInfo()`
- L72 _public prototype_ `FLocalLightBuildInfo(FLocalLightBuildInfo&& In) = default;` — Default move constructor is killed by the custom destructor
- L74 _public member_ `bool bStationary = false;`
- L75 _public member_ `bool bCastShadow = true;`
- L76 _public member_ `int ShadowMapChannel = INDEX_NONE;`
- L79 _public member_ `TSharedPtr<FLightComponentMapBuildData, ESPMode::ThreadSafe> LightComponentMapBuildData;` — This will also be held by FLocalLightRenderState to extend its lifetime until RenderThread has finished with it
- L81 _public prototype_ `virtual bool AffectsBounds(const FBoxSphereBounds& InBounds) const = 0;`
- L82 _public prototype_ `virtual ULightComponent* GetComponentUObject() const = 0;`
- L83 _public function_ `bool CastsStationaryShadow()`
- L85 _public prototype_ `void AllocateMapBuildData(ULevel* StorageLevel);`

#### struct `GPULightmass::FLocalLightRenderState`  
`struct FLocalLightRenderState`  
_L88-107_
- L90 _public prototype_ `FLocalLightRenderState(ULightComponent* LightComponent);`
- L91 _public prototype_ `virtual void RenderThreadInit();`
- L92 _public prototype_ `virtual void RenderThreadFinalize();`
- L93 _public function_ `virtual ~FLocalLightRenderState()`
- L95 _public member_ `bool bStationary = false;`
- L96 _public member_ `bool bCastShadow = true;`
- L97 _public member_ `int ShadowMapChannel = INDEX_NONE;`
- L98 _public member_ `uint32 IESAtlasId = INDEX_NONE;`
- L99 _public member_ `UTextureLightProfile* IESTexture = nullptr;`
- L101 _public prototype_ `float GetIESAtlasIndex() const;`
- L103 _public member_ `TSharedPtr<FLightComponentMapBuildData, ESPMode::ThreadSafe> LightComponentMapBuildData;`
- L105 _public prototype_ `virtual FLightRenderParameters GetLightShaderParameters() const = 0;`
- L106 _public function_ `virtual void RenderStaticShadowDepthMap(FRHICommandListImmediate& RHICmdList, class FSceneRenderState& RenderState)`

#### class `GPULightmass::FLightBuildInfoRef`  
`class FLightBuildInfoRef : public FGenericEntityRef`  
_L111-131_
- inherits: `FGenericEntityRef`
- L114 _public function_ `FLightBuildInfoRef( FLightArrayBase& LightArray, TArray<TSet<RefAddr>>& Refs, TSparseArray<int32>& RefAllocator, int32 ElementId) : FGenericEntityRef(ElementId, Refs, RefAllocator) , LightArray(LightArray)`
- L123 _public prototype_ `void RemoveFromAray();`
- L124 _public prototype_ `FLocalLightBuildInfo& Resolve();`
- L127 _private member_ `FLightArrayBase& LightArray;`

#### class `GPULightmass::FLightRenderStateRef`  
`class FLightRenderStateRef : public FGenericEntityRef`  
_L135-159_
- inherits: `FGenericEntityRef`
- L138 _public function_ `FLightRenderStateRef( FLightRenderStateArrayBase& LightArray, TArray<TSet<RefAddr>>& Refs, TSparseArray<int32>& RefAllocator, int32 ElementId) : FGenericEntityRef(ElementId, Refs, RefAllocator) , LightRenderStateArray(LightArray)`
- L147 _public function_ `FLightRenderStateRef(FLightRenderStateArrayBase& LightArray, const FGenericEntityRef& InRef) : FGenericEntityRef(InRef) , LightRenderStateArray(LightArray)`
- L152 _public prototype_ `FLocalLightRenderState& Resolve();`
- L155 _private member_ `FLightRenderStateArrayBase& LightRenderStateArray;`

#### struct `GPULightmass::FDirectionalLightBuildInfo`  
`struct FDirectionalLightBuildInfo : public FLocalLightBuildInfo`  
_L161-169_
- inherits: `FLocalLightBuildInfo`
- L163 _public prototype_ `FDirectionalLightBuildInfo(UDirectionalLightComponent* DirectionalLightComponent);`
- L165 _public member_ `UDirectionalLightComponent* ComponentUObject = nullptr;`
- L167 _public function_ `virtual ULightComponent* GetComponentUObject() const override`
- L168 _public function_ `virtual bool AffectsBounds(const FBoxSphereBounds& InBounds) const override`

#### struct `GPULightmass::FPointLightBuildInfo`  
`struct FPointLightBuildInfo : public FLocalLightBuildInfo`  
_L173-184_
- inherits: `FLocalLightBuildInfo`
- L175 _public prototype_ `FPointLightBuildInfo(UPointLightComponent* ComponentUObject);`
- L177 _public member_ `UPointLightComponent* ComponentUObject = nullptr;`
- L179 _public member_ `FVector Position;`
- L180 _public member_ `float AttenuationRadius;`
- L182 _public function_ `virtual ULightComponent* GetComponentUObject() const override`
- L183 _public prototype_ `virtual bool AffectsBounds(const FBoxSphereBounds& InBounds) const override;`

#### struct `GPULightmass::FSpotLightBuildInfo`  
`struct FSpotLightBuildInfo : public FLocalLightBuildInfo`  
_L188-202_
- inherits: `FLocalLightBuildInfo`
- L190 _public prototype_ `FSpotLightBuildInfo(USpotLightComponent* ComponentUObject);`
- L192 _public member_ `USpotLightComponent* ComponentUObject = nullptr;`
- L194 _public member_ `FVector Position;`
- L195 _public member_ `FVector Direction;`
- L196 _public member_ `float InnerConeAngle;`
- L197 _public member_ `float OuterConeAngle;`
- L198 _public member_ `float AttenuationRadius;`
- L200 _public function_ `virtual ULightComponent* GetComponentUObject() const override`
- L201 _public prototype_ `virtual bool AffectsBounds(const FBoxSphereBounds& InBounds) const override;`

#### struct `GPULightmass::FRectLightBuildInfo`  
`struct FRectLightBuildInfo : public FLocalLightBuildInfo`  
_L206-217_
- inherits: `FLocalLightBuildInfo`
- L208 _public prototype_ `FRectLightBuildInfo(URectLightComponent* ComponentUObject);`
- L210 _public member_ `URectLightComponent* ComponentUObject = nullptr;`
- L212 _public member_ `FVector Position;`
- L213 _public member_ `float AttenuationRadius;`
- L215 _public function_ `virtual ULightComponent* GetComponentUObject() const override`
- L216 _public prototype_ `virtual bool AffectsBounds(const FBoxSphereBounds& InBounds) const override;`

#### struct `GPULightmass::FDirectionalLightRenderState`  
`struct FDirectionalLightRenderState : public FLocalLightRenderState`  
_L221-232_
- inherits: `FLocalLightRenderState`
- L223 _public prototype_ `FDirectionalLightRenderState(UDirectionalLightComponent* DirectionalLightComponent);`
- L225 _public member_ `FVector Direction;`
- L226 _public member_ `FLinearColor Color;`
- L227 _public member_ `float LightSourceAngle;`
- L228 _public member_ `float LightSourceSoftAngle;`
- L230 _public prototype_ `virtual FLightRenderParameters GetLightShaderParameters() const override;`
- L231 _public prototype_ `virtual void RenderStaticShadowDepthMap(FRHICommandListImmediate& RHICmdList, FSceneRenderState& RenderState) override;`

#### struct `GPULightmass::FPointLightRenderState`  
`struct FPointLightRenderState : public FLocalLightRenderState`  
_L236-253_
- inherits: `FLocalLightRenderState`
- L238 _public prototype_ `FPointLightRenderState(UPointLightComponent* PointLightComponent);`
- L240 _public member_ `FVector Position;`
- L241 _public member_ `FVector Direction;`
- L242 _public member_ `FVector Tangent;`
- L243 _public member_ `FLinearColor Color;`
- L244 _public member_ `float AttenuationRadius;`
- L245 _public member_ `float SourceRadius;`
- L246 _public member_ `float SourceSoftRadius;`
- L247 _public member_ `float SourceLength;`
- L248 _public member_ `float FalloffExponent;`
- L249 _public member_ `bool IsInverseSquared;`
- L251 _public prototype_ `virtual FLightRenderParameters GetLightShaderParameters() const override;`
- L252 _public prototype_ `virtual void RenderStaticShadowDepthMap(FRHICommandListImmediate& RHICmdList, FSceneRenderState& RenderState) override;`

#### struct `GPULightmass::FSpotLightRenderState`  
`struct FSpotLightRenderState : public FLocalLightRenderState`  
_L257-275_
- inherits: `FLocalLightRenderState`
- L259 _public prototype_ `FSpotLightRenderState(USpotLightComponent* ComponentUObject);`
- L261 _public member_ `FVector Position;`
- L262 _public member_ `FVector Direction;`
- L263 _public member_ `FVector Tangent;`
- L264 _public member_ `FVector2D SpotAngles;`
- L265 _public member_ `FLinearColor Color;`
- L266 _public member_ `float AttenuationRadius;`
- L267 _public member_ `float SourceRadius;`
- L268 _public member_ `float SourceSoftRadius;`
- L269 _public member_ `float SourceLength;`
- L270 _public member_ `float FalloffExponent;`
- L271 _public member_ `bool IsInverseSquared;`
- L273 _public prototype_ `virtual FLightRenderParameters GetLightShaderParameters() const override;`
- L274 _public prototype_ `virtual void RenderStaticShadowDepthMap(FRHICommandListImmediate& RHICmdList, FSceneRenderState& RenderState) override;`

#### struct `GPULightmass::FRectLightRenderState`  
`struct FRectLightRenderState : public FLocalLightRenderState`  
_L279-302_
- inherits: `FLocalLightRenderState`
- L281 _public prototype_ `FRectLightRenderState(URectLightComponent* ComponentUObject);`
- L282 _public prototype_ `virtual void RenderThreadInit() override;`
- L283 _public prototype_ `virtual void RenderThreadFinalize() override;`
- L285 _public member_ `FLinearColor Color;`
- L286 _public member_ `float AttenuationRadius;`
- L287 _public member_ `FVector Position;`
- L288 _public member_ `FVector Direction;`
- L289 _public member_ `FVector Tangent;`
- L290 _public member_ `float SourceWidth;`
- L291 _public member_ `float SourceHeight;`
- L292 _public member_ `float BarnDoorAngle;`
- L293 _public member_ `float BarnDoorLength;`
- L294 _public member_ `UTexture* SourceTexture;`
- L295 _public member_ `uint32 RectAtlasId;`
- L296 _public member_ `FVector2f RectLightAtlasUVOffset;`
- L297 _public member_ `FVector2f RectLightAtlasUVScale;`
- L298 _public member_ `float RectLightAtlasMaxLevel;`
- L300 _public prototype_ `virtual FLightRenderParameters GetLightShaderParameters() const override;`
- L301 _public prototype_ `virtual void RenderStaticShadowDepthMap(FRHICommandListImmediate& RHICmdList, FSceneRenderState& RenderState) override;`

#### struct `GPULightmass::FSkyLightRenderState`  
`struct FSkyLightRenderState`  
_L306-325_
- L308 _public member_ `bool bStationary = false;`
- L309 _public member_ `bool bCastShadow = true;`
- L310 _public function_ `bool CastsStationaryShadow()`
- L312 _public member_ `FLinearColor Color;`
- L313 _public member_ `FTextureRHIRef ProcessedTexture;`
- L314 _public member_ `FSamplerStateRHIRef ProcessedTextureSampler;`
- L315 _public member_ `FIntPoint TextureDimensions;`
- L316 _public member_ `FSHVectorRGB3 IrradianceEnvironmentMap;`
- L317 _public member_ `FRWBufferStructured SkyIrradianceEnvironmentMap;`
- L320 _public prototype_ `void PrepareSkyTexture(FRHICommandListImmediate& RHICmdList, ERHIFeatureLevel::Type FeatureLevel);` — New sky dome
- L321 _public member_ `float SkylightInvResolution;`
- L322 _public member_ `int32 SkylightMipCount;`
- L323 _public member_ `TRefCountPtr<IPooledRenderTarget> PathTracingSkylightTexture;`
- L324 _public member_ `TRefCountPtr<IPooledRenderTarget> PathTracingSkylightPdf;`

#### struct `GPULightmass::FSkyLightBuildInfo`  
`struct FSkyLightBuildInfo`  
_L327-334_
- L329 _public member_ `USkyLightComponent* ComponentUObject = nullptr;`
- L331 _public member_ `bool bStationary = false;`
- L332 _public member_ `bool bCastShadow = true;`
- L333 _public function_ `bool CastsStationaryShadow()`

#### class `GPULightmass::FLightArrayBase`  
`class FLightArrayBase`  
_L336-342_
- L339 _public function_ `virtual ~FLightArrayBase()`
- L340 _public prototype_ `virtual void Remove(const FLightBuildInfoRef& Light) = 0;`
- L341 _public prototype_ `virtual FLocalLightBuildInfo& ResolveAsLocalLightBuildInfo(const FLightBuildInfoRef& Light) = 0;`

#### class `GPULightmass::TLightArray`  
`template<typename T> class TLightArray : public FLightArrayBase, public TEntityArray<T>`  
_L345-361_
- inherits: `FLightArrayBase,TEntityArray<T>`
- L348 _public function_ `virtual void Remove(const FLightBuildInfoRef& Light) override`
- L355 _public function_ `virtual FLocalLightBuildInfo& ResolveAsLocalLightBuildInfo(const FLightBuildInfoRef& Light) override`

#### class `GPULightmass::FLightRenderStateArrayBase`  
`class FLightRenderStateArrayBase`  
_L363-368_
- L366 _public function_ `virtual ~FLightRenderStateArrayBase()`
- L367 _public prototype_ `virtual FLocalLightRenderState& ResolveAsLocalLightRenderState(const FLightRenderStateRef& Light) = 0;`

#### class `GPULightmass::TLightRenderStateArray`  
`template<typename T> class TLightRenderStateArray : public FLightRenderStateArrayBase, public TEntityArray<T>`  
_L371-380_
- inherits: `FLightRenderStateArrayBase,TEntityArray<T>`
- L374 _public function_ `virtual FLocalLightRenderState& ResolveAsLocalLightRenderState(const FLightRenderStateRef& Light) override`

#### struct `GPULightmass::FLightScene`  
`struct FLightScene`  
_L382-394_
- L384 _public member_ `TOptional<FSkyLightBuildInfo> SkyLight;`
- L385 _public member_ `TLightArray<FDirectionalLightBuildInfo> DirectionalLights;`
- L386 _public member_ `TLightArray<FPointLightBuildInfo> PointLights;`
- L387 _public member_ `TLightArray<FSpotLightBuildInfo> SpotLights;`
- L388 _public member_ `TLightArray<FRectLightBuildInfo> RectLights;`
- L390 _public member_ `TMap<UDirectionalLightComponent*, FDirectionalLightRef> RegisteredDirectionalLightComponentUObjects;`
- L391 _public member_ `TMap<UPointLightComponent*, FPointLightRef> RegisteredPointLightComponentUObjects;`
- L392 _public member_ `TMap<USpotLightComponent*, FSpotLightRef> RegisteredSpotLightComponentUObjects;`
- L393 _public member_ `TMap<URectLightComponent*, FRectLightRef> RegisteredRectLightComponentUObjects;`

#### struct `GPULightmass::FLightSceneRenderState`  
`struct FLightSceneRenderState`  
_L396-403_
- L398 _public member_ `TOptional<FSkyLightRenderState> SkyLight;`
- L399 _public member_ `TLightRenderStateArray<FDirectionalLightRenderState> DirectionalLights;`
- L400 _public member_ `TLightRenderStateArray<FPointLightRenderState> PointLights;`
- L401 _public member_ `TLightRenderStateArray<FSpotLightRenderState> SpotLights;`
- L402 _public member_ `TLightRenderStateArray<FRectLightRenderState> RectLights;`

#### Free symbols / members of external scopes

- L58 _namespace_ `namespace GPULightmass`
- L171 _typedef_ `using FDirectionalLightRef = TEntityArray<FDirectionalLightBuildInfo>::EntityRefType;` (scope `GPULightmass`)
- L186 _typedef_ `using FPointLightRef = TEntityArray<FPointLightBuildInfo>::EntityRefType;` (scope `GPULightmass`)
- L204 _typedef_ `using FSpotLightRef = TEntityArray<FSpotLightBuildInfo>::EntityRefType;` (scope `GPULightmass`)
- L219 _typedef_ `using FRectLightRef = TEntityArray<FRectLightBuildInfo>::EntityRefType;` (scope `GPULightmass`)
- L234 _typedef_ `using FDirectionalLightRenderStateRef = TEntityArray<FDirectionalLightRenderState>::EntityRefType;` (scope `GPULightmass`)
- L255 _typedef_ `using FPointLightRenderStateRef = TEntityArray<FPointLightRenderState>::EntityRefType;` (scope `GPULightmass`)
- L277 _typedef_ `using FSpotLightRenderStateRef = TEntityArray<FSpotLightRenderState>::EntityRefType;` (scope `GPULightmass`)
- L304 _typedef_ `using FRectLightRenderStateRef = TEntityArray<FRectLightRenderState>::EntityRefType;` (scope `GPULightmass`)
- L407 _function_ `static uint32 GetTypeHash(const GPULightmass::FDirectionalLightRenderState& O)`
- L412 _function_ `static uint32 GetTypeHash(const GPULightmass::FDirectionalLightRenderStateRef& Ref)`
- L417 _function_ `static uint32 GetTypeHash(const GPULightmass::FPointLightRenderState& O)`
- L422 _function_ `static uint32 GetTypeHash(const GPULightmass::FPointLightRenderStateRef& Ref)`
- L427 _function_ `static uint32 GetTypeHash(const GPULightmass::FSpotLightRenderState& O)`
- L432 _function_ `static uint32 GetTypeHash(const GPULightmass::FSpotLightRenderStateRef& Ref)`
- L437 _function_ `static uint32 GetTypeHash(const GPULightmass::FRectLightRenderState& O)`
- L452 _function_ `static uint32 GetTypeHash(const GPULightmass::FRectLightRenderStateRef& Ref)`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/Scene/Scene.h` (Private)


#### class `GPULightmass::FFullyCachedRayTracingMeshCommandContext`  
`class FFullyCachedRayTracingMeshCommandContext : public FRayTracingMeshCommandContext`  
_L25-69_
- inherits: `FRayTracingMeshCommandContext`
- L28 _public function_ `FFullyCachedRayTracingMeshCommandContext( TChunkedArray<FRayTracingMeshCommand>& CommandStorage, TArray<FRayTracingShaderBindingData>& InDirtyShaderBindingsStorage, const FRHIRayTracingGeometry* InRayTracingGeometry, uint32 InGeometrySegmentIndex, bool bInDynamicRayTracingGeometry, FRayTracingSBTAllocation* InSBTAllocation ) : CommandStorage(CommandStorage) , DirtyShaderBindingsStorage(InDirtyShaderBindingsStorage) , RayTracingGeometry(InRayTracingGeometry) , GeometrySegmentIndex(InGeometrySegmentIndex) , bDynamicRayTracingGeometry(bInDynamicRayTracingGeometry) , SBTAllocation(InSBTAllocation)`
- L43 _public function_ `virtual FRayTracingMeshCommand& AddCommand(const FRayTracingMeshCommand& Initializer) override final`
- L51 _public function_ `virtual void FinalizeCommand(FRayTracingMeshCommand& RayTracingMeshCommand) override final`
- L62 _private member_ `TChunkedArray<FRayTracingMeshCommand>& CommandStorage;`
- L63 _private member_ `TArray<FRayTracingShaderBindingData>& DirtyShaderBindingsStorage;`
- L65 _private member_ `const FRHIRayTracingGeometry* RayTracingGeometry;`
- L66 _private member_ `uint32 GeometrySegmentIndex;`
- L67 _private member_ `bool bDynamicRayTracingGeometry;`
- L68 _private member_ `FRayTracingSBTAllocation* SBTAllocation;`

#### struct `GPULightmass::FCachedRayTracingSceneData`  
`struct FCachedRayTracingSceneData`  
_L71-101_
- L73 _public prototype_ `~FCachedRayTracingSceneData();`
- L75 _public member_ `FRayTracingShaderBindingTable RaytracingSBT;`
- L76 _public member_ `TArray<FRayTracingSBTAllocation*> StaticSBTAllocations;`
- L78 _public member_ `TArray<TArray<FRayTracingShaderBindingData>> ShaderBindingsPerLOD;`
- L79 _public member_ `TChunkedArray<FRayTracingMeshCommand> MeshCommandStorage;`
- L81 _public member_ `FBufferRHIRef InstanceIdsIdentityBufferRHI;`
- L82 _public member_ `FShaderResourceViewRHIRef InstanceIdsIdentityBufferSRV;`
- L83 _public member_ `TArray<uint32> InstanceDataOriginalOffsets;`
- L85 _public member_ `TArray<TArray<FRayTracingGeometryInstance>> RayTracingGeometryInstancesPerLOD;`
- L86 _public member_ `TArray<TUniquePtr<FMatrix>> OwnedRayTracingInstanceTransforms;`
- L88 _public member_ `TArray<uint32> RayTracingNumSegmentsPerLOD;`
- L90 _public member_ `TRefCountPtr<FRDGPooledBuffer> GPUScenePrimitiveDataBuffer;`
- L91 _public member_ `TRefCountPtr<FRDGPooledBuffer> GPUSceneLightmapDataBuffer;`
- L92 _public member_ `TRefCountPtr<FRDGPooledBuffer> GPUSceneInstanceDataBuffer;`
- L93 _public member_ `int GPUSceneInstanceDataSOAStride;`
- L94 _public member_ `int32 GPUSceneNumInstances;`
- L95 _public member_ `TRefCountPtr<FRDGPooledBuffer> GPUSceneInstancePayloadDataBuffer;`
- L96 _public member_ `TRefCountPtr<FRDGPooledBuffer> GPUSceneLightDataBuffer;`
- L98 _public prototype_ `void SetupViewAndSceneUniformBufferFromSceneRenderState(FRDGBuilder& GraphBuilder, class FSceneRenderState& Scene, FSceneUniformBuffer& SceneUniforms);`
- L99 _public prototype_ `void SetupFromSceneRenderState(class FSceneRenderState& Scene);`
- L100 _public prototype_ `void RestoreCachedBuffers(FRDGBuilder& GraphBuilder, FSceneUniformBuffer& SceneUniforms);`

#### class `GPULightmass::FSceneRenderState`  
`class FSceneRenderState`  
_L103-151_
- L106 _public member_ `UGPULightmassSettings* Settings;`
- L108 _public prototype_ `void RenderThreadInit(FRHICommandList& RHICmdList);`
- L109 _public prototype_ `void BackgroundTick(FRHICommandListImmediate& RHICmdList);`
- L111 _public member_ `FRayTracingSceneRHIRef RayTracingScene;`
- L112 _public member_ `FShaderResourceViewRHIRef RayTracingSceneSRV;`
- L113 _public member_ `FBufferRHIRef RayTracingSceneBuffer;`
- L114 _public member_ `FBufferRHIRef RayTracingScratchBuffer;`
- L116 _public member_ `FShaderBindingTableRHIRef SBT;`
- L118 _public member_ `FRayTracingPipelineState* RayTracingPipelineState;`
- L119 _public member_ `TSharedPtr<FViewInfo> ReferenceView;`
- L121 _public member_ `TUniquePtr<FCachedRayTracingSceneData> CachedRayTracingScene;`
- L123 _public member_ `TGeometryInstanceRenderStateCollection<FStaticMeshInstanceRenderState> StaticMeshInstanceRenderStates;`
- L124 _public member_ `TGeometryInstanceRenderStateCollection<FInstanceGroupRenderState> InstanceGroupRenderStates;`
- L125 _public member_ `TGeometryInstanceRenderStateCollection<FLandscapeRenderState> LandscapeRenderStates;`
- L127 _public member_ `TEntityArray<FLightmapRenderState> LightmapRenderStates;`
- L129 _public member_ `FLightSceneRenderState LightSceneRenderState;`
- L131 _public member_ `TUniquePtr<FLightmapRenderer> LightmapRenderer;`
- L132 _public member_ `TUniquePtr<FVolumetricLightmapRenderer> VolumetricLightmapRenderer;`
- L133 _public member_ `TUniquePtr<FIrradianceCache> IrradianceCache;`
- L135 _public member_ `FBox CombinedImportanceVolume;`
- L136 _public member_ `TArray<FBox> ImportanceVolumes;`
- L138 _public member_ `ERHIFeatureLevel::Type FeatureLevel;`
- L140 _public prototype_ `int32 GetPrimitiveIdForGPUScene(const FGeometryInstanceRenderStateRef& GeometryInstanceRef) const;`
- L142 _public prototype_ `bool SetupRayTracingScene(FRDGBuilder& GraphBuilder, FSceneUniformBuffer& SceneUniforms, int32 LODIndex = INDEX_NONE);`
- L143 _public prototype_ `void DestroyRayTracingScene();`
- L145 _public prototype_ `void CalculateDistributionPrefixSumForAllLightmaps();`
- L147 _public member_ `TArray<FLightmapRenderStateRef> MortonSortedLightmapRefList;`
- L148 _public prototype_ `void BuildMortonSortedLightmapRefList();`
- L150 _public member_ `volatile int32 Percentage = 0;`

#### class `GPULightmass::FGeometryRange`  
`class FGeometryRange`  
_L155-165_
- L158 _public function_ `FGeometryRange(FScene& Scene) : Scene(Scene)`
- L160 _public prototype_ `FGeometryIterator begin();`
- L161 _public prototype_ `FGeometryIterator end();`
- L164 _private member_ `FScene& Scene;`

#### class `GPULightmass::FScene`  
`class FScene`  
_L167-228_
- L170 _public prototype_ `FScene(FGPULightmass* InGPULightmass);`
- L172 _public member_ `FGPULightmass* GPULightmass;`
- L173 _public member_ `UGPULightmassSettings* Settings;`
- L175 _public prototype_ `const FMeshMapBuildData* GetComponentLightmapData(const UPrimitiveComponent* InComponent, int32 LODIndex);`
- L176 _public prototype_ `const FLightComponentMapBuildData* GetComponentLightmapData(const ULightComponent* InComponent);`
- L178 _public prototype_ `void AddGeometryInstanceFromComponent(UStaticMeshComponent* InComponent);`
- L179 _public prototype_ `void RemoveGeometryInstanceFromComponent(UStaticMeshComponent* InComponent);`
- L181 _public prototype_ `void AddGeometryInstanceFromComponent(UInstancedStaticMeshComponent* InComponent);`
- L182 _public prototype_ `void RemoveGeometryInstanceFromComponent(UInstancedStaticMeshComponent* InComponent);`
- L184 _public prototype_ `void AddGeometryInstanceFromComponent(ULandscapeComponent* InComponent);`
- L185 _public prototype_ `void RemoveGeometryInstanceFromComponent(ULandscapeComponent* InComponent);`
- L187 _public prototype_ `void AddLight(USkyLightComponent* SkyLight);`
- L188 _public prototype_ `void RemoveLight(USkyLightComponent* SkyLight);`
- L191 _public prototype_ `template<typename LightComponentType> void AddLight(LightComponentType* Light);`
- L194 _public prototype_ `template<typename LightComponentType> void RemoveLight(LightComponentType* Light);`
- L197 _public prototype_ `template<typename LightComponentType> bool HasLight(LightComponentType* Light);`
- L199 _public prototype_ `void GatherImportanceVolumes();`
- L200 _public prototype_ `void OnSkyAtmosphereModified();`
- L201 _public prototype_ `void ConditionalTriggerSkyLightRecapture();`
- L203 _public prototype_ `void BackgroundTick();`
- L204 _public prototype_ `void AddRelevantStaticLightGUIDs(FQuantizedLightmapData* QuantizedLightmapData, const FBoxSphereBounds& WorldBounds);`
- L205 _public prototype_ `void ApplyFinishedLightmapsToWorld();`
- L206 _public prototype_ `void RemoveAllComponents();`
- L208 _public member_ `TGeometryArray<FStaticMeshInstance> StaticMeshInstances;`
- L209 _public member_ `TGeometryArray<FInstanceGroup> InstanceGroups;`
- L210 _public member_ `TGeometryArray<FLandscape> Landscapes;`
- L212 _public member_ `FGeometryRange Geometries;`
- L214 _public member_ `TEntityArray<FLightmap> Lightmaps;`
- L216 _public member_ `FLightScene LightScene;`
- L218 _public member_ `FSceneRenderState RenderState;`
- L220 _public member_ `ERHIFeatureLevel::Type FeatureLevel;`
- L222 _public member_ `bool bNeedsVoxelization = true;`
- L225 _private member_ `TMap<UStaticMeshComponent*, FStaticMeshInstanceRef> RegisteredStaticMeshComponentUObjects;`
- L226 _private member_ `TMap<UInstancedStaticMeshComponent*, FInstanceGroupRef> RegisteredInstancedStaticMeshComponentUObjects;`
- L227 _private member_ `TMap<ULandscapeComponent*, FLandscapeRef> RegisteredLandscapeComponentUObjects;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace GPULightmass`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/Scene/StaticMesh.h` (Private)


#### class `GPULightmass::FStaticMeshInstanceRenderState`  
`class FStaticMeshInstanceRenderState : public FGeometryRenderState`  
_L13-25_
- inherits: `FGeometryRenderState`
- L16 _public member_ `UStaticMeshComponent* ComponentUObject;`
- L17 _public member_ `FStaticMeshRenderData* RenderData;`
- L19 _public member_ `TArray<FColorVertexBuffer*> LODOverrideColorVertexBuffers;`
- L20 _public member_ `TArray<TUniformBufferRef<FLocalVertexFactoryUniformShaderParameters>> LODOverrideColorVFUniformBuffers;`
- L22 _public prototype_ `TArray<FMeshBatch> GetMeshBatchesForGBufferRendering(int32 LODIndex);`
- L24 _public member_ `int32 ClampedMinLOD;`

#### class `GPULightmass::FStaticMeshInstance`  
`class FStaticMeshInstance : public FGeometry`  
_L29-43_
- inherits: `FGeometry`
- L32 _public prototype_ `FStaticMeshInstance(UStaticMeshComponent* ComponentUObject);`
- L34 _public prototype_ `const class FMeshMapBuildData* GetMeshMapBuildDataForLODIndex(int32 LODIndex);`
- L36 _public prototype_ `void AllocateLightmaps(TEntityArray<FLightmap>& LightmapContainer);`
- L38 _public member_ `UStaticMeshComponent* ComponentUObject;`
- L40 _public function_ `virtual UPrimitiveComponent* GetComponentUObject() const override`
- L42 _public member_ `int32 ClampedMinLOD;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace GPULightmass`
- L27 _typedef_ `using FStaticMeshInstanceRenderStateRef = TEntityArray<FStaticMeshInstanceRenderState>::EntityRefType;` (scope `GPULightmass`)
- L45 _typedef_ `using FStaticMeshInstanceRef = TEntityArray<FStaticMeshInstance>::EntityRefType;` (scope `GPULightmass`)

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.h` (Private)


#### class `GPULightmass::FVolumetricLightmapRenderer`  
`class FVolumetricLightmapRenderer`  
_L14-50_
- L17 _public member_ `const int32 BrickBatchSize = 2048;`
- L19 _public prototype_ `FVolumetricLightmapRenderer(FSceneRenderState* Scene);`
- L21 _public prototype_ `void VoxelizeScene(FRHICommandListImmediate& RHICmdList);`
- L22 _public prototype_ `void BackgroundTick(FRHICommandListImmediate& RHICmdList);`
- L24 _public prototype_ `FPrecomputedVolumetricLightmap* GetPrecomputedVolumetricLightmapForPreview();`
- L26 _public member_ `float TargetDetailCellSize = 50.0f;`
- L27 _public member_ `int32 NumTotalBricks = 0;`
- L29 _public member_ `int32 FrameNumber = 0;`
- L30 _public member_ `int32 NumTotalPassesToRender = 0;`
- L31 _public member_ `uint64 SamplesTaken = 0;`
- L34 _private member_ `FSceneRenderState* Scene;`
- L36 _private member_ `FPrecomputedVolumetricLightmap VolumetricLightmap;`
- L37 _private member_ `FPrecomputedVolumetricLightmapData VolumetricLightmapData;`
- L38 _private member_ `FVolumetricLightmapBrickData AccumulationBrickData;`
- L39 _private member_ `TRefCountPtr<IPooledRenderTarget> IndirectionTexture;`
- L41 _private member_ `FVector VolumeMin;`
- L42 _private member_ `FVector VolumeSize;`
- L43 _private member_ `FIntVector IndirectionTextureDimensions;`
- L45 _private member_ `TArray<TRefCountPtr<IPooledRenderTarget>> VoxelizationVolumeMips;`
- L47 _private member_ `FRWBuffer BrickAllocatorParameters;`
- L48 _private member_ `FRWBuffer BrickRequests;`
- L49 _private member_ `TRefCountPtr<IPooledRenderTarget> ValidityBrickData;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace GPULightmass`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmapVoxelization.h` (Private)


#### class `FVLMVoxelizationVS`  
`class FVLMVoxelizationVS : public FMeshMaterialShader`  
_L32-54_
- inherits: `FMeshMaterialShader`
- L34 _private prototype_ `DECLARE_SHADER_TYPE(FVLMVoxelizationVS, MeshMaterial);`
- L38 _protected function_ `FVLMVoxelizationVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FMeshMaterialShader(Initializer)`
- L43 _protected function_ `FVLMVoxelizationVS()`
- L47 _protected function_ `static bool ShouldCompilePermutation(const FMeshMaterialShaderPermutationParameters& Parameters)`

#### class `FVLMVoxelizationGS`  
`class FVLMVoxelizationGS : public FMeshMaterialShader`  
_L56-78_
- inherits: `FMeshMaterialShader`
- L58 _private prototype_ `DECLARE_SHADER_TYPE(FVLMVoxelizationGS, MeshMaterial);`
- L62 _protected function_ `FVLMVoxelizationGS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FMeshMaterialShader(Initializer)`
- L67 _protected function_ `FVLMVoxelizationGS()`
- L71 _protected function_ `static bool ShouldCompilePermutation(const FMeshMaterialShaderPermutationParameters& Parameters)`

#### class `FVLMVoxelizationPS`  
`class FVLMVoxelizationPS : public FMeshMaterialShader`  
_L80-102_
- inherits: `FMeshMaterialShader`
- L82 _private prototype_ `DECLARE_SHADER_TYPE(FVLMVoxelizationPS, MeshMaterial);`
- L86 _protected function_ `FVLMVoxelizationPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer) : FMeshMaterialShader(Initializer)`
- L91 _protected function_ `FVLMVoxelizationPS()`
- L95 _protected function_ `static bool ShouldCompilePermutation(const FMeshMaterialShaderPermutationParameters& Parameters)`

#### class `FVLMVoxelizationMeshProcessor`  
`class FVLMVoxelizationMeshProcessor : public FMeshPassProcessor`  
_L104-187_
- inherits: `FMeshPassProcessor`
- L107 _public function_ `FVLMVoxelizationMeshProcessor(const FScene* InScene, const FSceneView* InView, FMeshPassDrawListContext* InDrawListContext) : FMeshPassProcessor(TEXT("VLMVoxelization"), InScene, InView->GetFeatureLevel(), InView, InDrawListContext)`
- L114 _public function_ `virtual void AddMeshBatch(const FMeshBatch& RESTRICT MeshBatch, uint64 BatchElementMask, const FPrimitiveSceneProxy* RESTRICT PrimitiveSceneProxy, int32 StaticMeshId = -1) override final`
- L131 _private function_ `bool Process( const FMeshBatch& MeshBatch, uint64 BatchElementMask, int32 StaticMeshId, const FPrimitiveSceneProxy* RESTRICT PrimitiveSceneProxy, const FMaterialRenderProxy& RESTRICT MaterialRenderProxy, const FMaterial& RESTRICT MaterialResource)`
- L186 _private member_ `FMeshPassProcessorRenderState DrawRenderState;`

#### class `FClearVolumeCS`  
`class FClearVolumeCS : public FGlobalShader`  
_L189-208_
- inherits: `FGlobalShader`
- L191 _private prototype_ `DECLARE_GLOBAL_SHADER(FClearVolumeCS);`
- L192 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FClearVolumeCS, FGlobalShader);`
- L194 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L199 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FVoxelizeImportanceVolumeCS`  
`class FVoxelizeImportanceVolumeCS : public FGlobalShader`  
_L210-232_
- inherits: `FGlobalShader`
- L212 _private prototype_ `DECLARE_GLOBAL_SHADER(FVoxelizeImportanceVolumeCS);`
- L213 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FVoxelizeImportanceVolumeCS, FGlobalShader);`
- L215 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L220 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FDownsampleVolumeCS`  
`class FDownsampleVolumeCS : public FGlobalShader`  
_L234-254_
- inherits: `FGlobalShader`
- L236 _private prototype_ `DECLARE_GLOBAL_SHADER(FDownsampleVolumeCS);`
- L237 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FDownsampleVolumeCS, FGlobalShader);`
- L239 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L244 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FCountNumBricksCS`  
`class FCountNumBricksCS : public FGlobalShader`  
_L256-276_
- inherits: `FGlobalShader`
- L258 _private prototype_ `DECLARE_GLOBAL_SHADER(FCountNumBricksCS);`
- L259 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FCountNumBricksCS, FGlobalShader);`
- L261 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L266 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FGatherBrickRequestsCS`  
`class FGatherBrickRequestsCS : public FGlobalShader`  
_L278-303_
- inherits: `FGlobalShader`
- L280 _private prototype_ `DECLARE_GLOBAL_SHADER(FGatherBrickRequestsCS);`
- L281 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FGatherBrickRequestsCS, FGlobalShader);`
- L283 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L288 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FWriteSortedBrickRequestsCS`  
`class FWriteSortedBrickRequestsCS : public FGlobalShader`  
_L305-327_
- inherits: `FGlobalShader`
- L307 _private prototype_ `DECLARE_GLOBAL_SHADER(FWriteSortedBrickRequestsCS);`
- L308 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FWriteSortedBrickRequestsCS, FGlobalShader);`
- L310 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L315 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FPermuteVoxelizeVolumeCS`  
`class FPermuteVoxelizeVolumeCS : public FGlobalShader`  
_L329-349_
- inherits: `FGlobalShader`
- L331 _private prototype_ `DECLARE_GLOBAL_SHADER(FPermuteVoxelizeVolumeCS);`
- L332 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FPermuteVoxelizeVolumeCS, FGlobalShader);`
- L334 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L339 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FSplatVolumeCS`  
`class FSplatVolumeCS : public FGlobalShader`  
_L351-374_
- inherits: `FGlobalShader`
- L353 _private prototype_ `DECLARE_GLOBAL_SHADER(FSplatVolumeCS);`
- L354 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FSplatVolumeCS, FGlobalShader);`
- L356 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L361 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FStitchBorderCS`  
`class FStitchBorderCS : public FGlobalShader`  
_L376-410_
- inherits: `FGlobalShader`
- L378 _private prototype_ `DECLARE_GLOBAL_SHADER(FStitchBorderCS);`
- L379 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FStitchBorderCS, FGlobalShader);`
- L381 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L386 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FCopyPaddingStripsCS`  
`class FCopyPaddingStripsCS : public FGlobalShader`  
_L412-448_
- inherits: `FGlobalShader`
- L414 _private prototype_ `DECLARE_GLOBAL_SHADER(FCopyPaddingStripsCS);`
- L415 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FCopyPaddingStripsCS, FGlobalShader);`
- L417 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L422 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FFillInvalidCellCS`  
`class FFillInvalidCellCS : public FGlobalShader`  
_L450-484_
- inherits: `FGlobalShader`
- L452 _private prototype_ `DECLARE_GLOBAL_SHADER(FFillInvalidCellCS);`
- L453 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FFillInvalidCellCS, FGlobalShader);`
- L455 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L460 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### class `FFinalizeBrickResultsCS`  
`class FFinalizeBrickResultsCS : public FGlobalShader`  
_L486-526_
- inherits: `FGlobalShader`
- L488 _private prototype_ `DECLARE_GLOBAL_SHADER(FFinalizeBrickResultsCS);`
- L489 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FFinalizeBrickResultsCS, FGlobalShader);`
- L491 _private function_ `static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)`
- L496 _private function_ `static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)`

#### Free symbols / members of external scopes

- L28 _typedef_ `typedef TUniformBufferRef<FVLMVoxelizationParams> FVLMVoxelizationUniformBufferRef;`
- L30 _prototype_ `bool IsSupportedVertexFactoryType(const FVertexFactoryType* VertexFactoryType);`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Public/GPULightmassModule.h` (Public)


#### class `FGPULightmassModule`  
`class FGPULightmassModule : public IModuleInterface, public IStaticLightingSystemImpl`  
_L10-33_
- inherits: `IModuleInterface,IStaticLightingSystemImpl`
- L13 _public prototype_ `void RunSelfTests();`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `virtual IStaticLightingSystem* GetStaticLightingSystemForWorld(UWorld* InWorld) override;`
- L20 _public prototype_ `virtual bool IsStaticLightingSystemRunning() override;`
- L21 _public prototype_ `virtual void EditorTick() override;`
- L23 _public prototype_ `class FGPULightmass* CreateGPULightmassForWorld(UWorld* InWorld, class UGPULightmassSettings* Settings);`
- L24 _public prototype_ `void RemoveGPULightmassFromWorld(UWorld* InWorld);`
- L26 _public prototype_ `static bool IsRealtimeOn();`
- L30 _public member_ `TMap<UWorld*, class FGPULightmass*> StaticLightingSystems;` — Due to limitations in our TMap implementation I cannot use TUniquePtr here But the GPULightmassModule is the only owner of all static lighting systems, and all worlds weak refer to the systems
- L32 _public member_ `FSimpleMulticastDelegate OnStaticLightingSystemsChanged;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGPULightmass, Log, All);`
- L35 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGPULightmass, Log, All);`

### `Plugins/Experimental/GPULightmass/Source/GPULightmass/Public/GPULightmassSettings.h` (Public)


#### enum `EGPULightmassMode`  
`enum class EGPULightmassMode : uint8`  
_L10-15_
- reflection: `UENUM()`
- L12 _public enumerator_ `FullBake`
- L13 _public enumerator_ `BakeWhatYouSee`

#### enum `EGPULightmassDenoisingOptions`  
`enum class EGPULightmassDenoisingOptions : uint8`  
_L18-23_
- reflection: `UENUM()`
- L20 _public enumerator_ `None`
- L21 _public enumerator_ `OnCompletion`
- L22 _public enumerator_ `DuringInteractivePreview`

#### enum `EGPULightmassDenoiser`  
`enum class EGPULightmassDenoiser : uint8`  
_L26-30_
- reflection: `UENUM()`
- L28 _public enumerator_ `IntelOIDN UMETA(DisplayName = "Intel Open Image Denoise")`
- L29 _public enumerator_ `SimpleFireflyRemover`

#### class `UGPULightmassSettings`  
`class UGPULightmassSettings : public UObject`  
_L33-140_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L42 _public member_ `bool bShowProgressBars = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General)` — If true, draw a green progress bar within each tile as it renders. A red bar indicates that First Bounce Ray Guiding is in progress. Bars may appear black in very bright scenes that have been exposed down.
- L49 _public member_ `EGPULightmassMode Mode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General)` — Full Bake mode renders the full lightmap resolution for every object in the scene. Bake What You See mode renders only the virtual texture tiles for objects in view, at the mip level determined by the virtual texture system. The camera can be moved to render more tiles. Bake What You See mode only saves its results if you press the Save button.
- L54 _public member_ `EGPULightmassDenoisingOptions DenoisingOptions = EGPULightmassDenoisingOptions::OnCompletion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Denoising, DisplayName = "Denoise when")` — If enabled, denoise the results on the CPU after rendering. On Completion denoises the entire lightmap when it is finished. During Interactive Preview denoises each tile as it finishes, which is useful for previewing but less efficient.
- L57 _public member_ `EGPULightmassDenoiser Denoiser = EGPULightmassDenoiser::IntelOIDN;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Denoising, meta = (EditCondition = "DenoisingOptions != EGPULightmassDenoisingOptions::None"))`
- L62 _public member_ `bool bCompressLightmaps = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General)` — Whether to compress lightmap textures.  Disabling lightmap texture compression will reduce artifacts but increase memory and disk size by 4x. Use caution when disabling this.
- L67 _public member_ `int32 GISamples = 512;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GlobalIllumination, DisplayName = "GI Samples", meta = (ClampMin = "32", ClampMax = "65536", UIMax = "8192"))` — Total number of ray paths executed per texel across all bounces. Set this to the lowest value that gives artifact-free results with the denoiser.
- L71 _public member_ `int32 StationaryLightShadowSamples = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GlobalIllumination, meta = (ClampMin = "32", ClampMax = "65536", UIMax = "8192"))` — Number of samples for stationary shadows, which are calculated and stored separately from GI.
- L76 _public member_ `bool bUseIrradianceCaching = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GlobalIllumination)` — Irradiance Caching should be enabled with interior scenes to achieve more physically correct GI intensities, albeit with some biasing. Without IC the results may be darker than expected. It should be disabled for exterior scenes.
- L83 _public member_ `bool bUseFirstBounceRayGuiding = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GlobalIllumination, meta = (EditCondition = "bUseIrradianceCaching"))` — If Irradiance Caching is enabled, First Bounce Ray Guiding will search the hemisphere over each first bounce sample to find the brightest directions to weigh the rest of the samples towards. This improves results for interior scenes with specific sources of light like a window. The quality of this pass is controlled with the Trial Samples setting.
- L86 _public member_ `int32 VolumetricLightmapQualityMultiplier = 4;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VolumetricLightmap, DisplayName = "Quality Multiplier", meta = (ClampMin = "1", ClampMax = "256", UIMax = "32"))`
- L92 _public member_ `int32 VolumetricLightmapDetailCellSize = 200;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VolumetricLightmap, DisplayName = "Detail Cell Size", meta = (ClampMin = "1", ClampMax = "20000", UIMax = "2000"))` — Size of an Volumetric Lightmap voxel at the highest density (used around geometry), in world space units. This setting has a large impact on build times and memory, use with caution. Halving the DetailCellSize can increase memory by up to a factor of 8x.
- L96 _public member_ `int32 IrradianceCacheQuality = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IrradianceCaching, DisplayName = "Quality", meta = (EditCondition = "bUseIrradianceCaching", ClampMin = "4", ClampMax = "65536", UIMax = "8192"))` — Number of samples per Irradiance Cache cell.
- L100 _public member_ `bool bUseIrradianceCacheBackfaceDetection = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = IrradianceCaching, DisplayName = "Aggressive Leak Prevention", meta = (EditCondition = "bUseIrradianceCaching"))` — Further prevent leaks caused by irradiance cache cells being placed inside geometry, at the cost of more fireflies and slower sampling speed. Recommended to be used with higher irradiance cache quality (>=256)
- L104 _public member_ `int32 IrradianceCacheSpacing = 32;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = IrradianceCaching, DisplayName = "Size", meta = (EditCondition = "bUseIrradianceCaching", ClampMin = "4", ClampMax = "1024"))` — Size of each Irradiance Cache cell. Smaller sizes will be slower but more accurate.
- L108 _public member_ `float IrradianceCacheCornerRejection = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = IrradianceCaching, DisplayName = "Corner Rejection", meta = (EditCondition = "bUseIrradianceCaching", ClampMin = "0.0", ClampMax = "8.0"))` — Reject IC entries around corners to help reduce leaking and artifacts.
- L113 _public member_ `bool bVisualizeIrradianceCache = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = IrradianceCaching, DisplayName = "Debug: Visualize", meta = (EditCondition = "bUseIrradianceCaching"))` — If true, visualize the Irradiance Cache cells. This can be useful for setting the IC size and quality. The visualization may appear black in very bright scenes that have been exposed down.
- L117 _public member_ `int32 FirstBounceRayGuidingTrialSamples = 128;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FirstBounceRayGuiding, DisplayName = "Trial Samples", meta = (EditCondition = "bUseFirstBounceRayGuiding"))` — Number of samples used for First Bounce Ray Guiding, which are thrown away before sampling for lighting.
- L122 _public member_ `int32 TilePassesInSlowMode = 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = System, DisplayName = "Realtime Workload Factor", meta = (ClampMin = "1", ClampMax = "1024"))` — Baking speed multiplier when Realtime is enabled in the viewer. Setting this too high can cause the editor to become unresponsive with heavy scenes.
- L126 _public member_ `int32 TilePassesInFullSpeedMode = 8;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = System, DisplayName = "Non-Realtime Workload Factor", meta = (ClampMin = "1", ClampMax = "1024"))` — Baking speed multiplier when Realtime is disabled in the viewer.
- L131 _public member_ `int32 LightmapTilePoolSize = 55;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = System, meta = (ClampMin = "16", ClampMax = "128"))` — GPU Lightmass manages a pool for calculations of visible tiles. The pool size should be set based on the size of the viewport and how many tiles will be visible on screen at once. Increasing this number increases GPU memory usage.
- L134 _public prototype_ `void ApplyImmediateSettingsToRunningInstances();`
- L137 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L138 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`

#### class `AGPULightmassSettingsActor`  
`class AGPULightmassSettingsActor : public AInfo`  
_L143-154_
- reflection: `UCLASS(NotPlaceable)`
- inherits: `AInfo`
- L148 _private function_ `virtual bool ActorTypeIsMainWorldOnly() const override`
- L153 _public member_ `TObjectPtr<UGPULightmassSettings> Settings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)`

#### class `UGPULightmassSubsystem`  
`class UGPULightmassSubsystem : public UWorldSubsystem`  
_L157-202_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- L161 _public prototype_ `virtual void PostInitialize() override;`
- L164 _public prototype_ `UGPULightmassSettings* GetSettings();` — `UFUNCTION(BlueprintCallable, Category = GPULightmass)`
- L167 _public prototype_ `void Launch();` — `UFUNCTION(BlueprintCallable, Category = GPULightmass)`
- L170 _public prototype_ `void Stop();` — `UFUNCTION(BlueprintCallable, Category = GPULightmass)`
- L173 _public prototype_ `bool IsRunning();` — `UFUNCTION(BlueprintCallable, Category = GPULightmass)`
- L176 _public prototype_ `void StartRecordingVisibleTiles();` — `UFUNCTION(BlueprintCallable, Category = GPULightmass)`
- L179 _public prototype_ `void EndRecordingVisibleTiles();` — `UFUNCTION(BlueprintCallable, Category = GPULightmass)`
- L182 _public prototype_ `int32 GetPercentage();` — `UFUNCTION(BlueprintCallable, Category = GPULightmass)`
- L185 _public prototype_ `void SetRealtime(bool bInRealtime);` — `UFUNCTION(BlueprintCallable, Category = GPULightmass)`
- L188 _public prototype_ `void Save();` — `UFUNCTION(BlueprintCallable, Category = GPULightmass)`
- L191 _public function_ `FSimpleMulticastDelegate& OnLightBuildEnded()` — Accessor for the delegate called when the light build finishes successfully or is cancelled
- L197 _private prototype_ `AGPULightmassSettingsActor* GetSettingsActor();`
- L201 _private member_ `FSimpleMulticastDelegate LightBuildEnded;` — Called when the light build finishes successfully or is cancelled
