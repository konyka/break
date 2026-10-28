# Plugins / NiagaraNanite

- module root: `Plugins/FX/NiagaraNanite/Source/NiagaraNanite`
- headers: 5; symbols: 138
- symbol kinds: class=4, enum=1, enumerator=7, function=12, macro=1, member=50, prototype=55, struct=6, typedef=2
- PrivateDependencyModuleNames: UnrealEd

### `Plugins/FX/NiagaraNanite/Source/NiagaraNanite/Internal/NiagaraParameterComponentBinding.h` (Internal)


#### struct `FNiagaraParameterComponentBinding`  
`struct FNiagaraParameterComponentBinding`  
_L10-38_
- reflection: `USTRUCT()`
- L15 _public member_ `FNiagaraVariableBase ResolvedParameter;` — `UPROPERTY()`
- L19 _public member_ `FNiagaraVariableBase AliasedParameter;` — `UPROPERTY()`
- L22 _public member_ `FNiagaraVariableBase DisplayParameter;` — `UPROPERTY()`
- L26 _public member_ `int Component = 0;` — `UPROPERTY()`
- L29 _public member_ `float DefaultValue = 0.0f;` — `UPROPERTY()`
- L32 _public prototype_ `virtual ~FNiagaraParameterComponentBinding() = default;`
- L33 _public function_ `virtual FNiagaraTypeDefinition GetTypeDef() const`
- L34 _public prototype_ `void OnRenameEmitter(FStringView EmitterName);`
- L35 _public prototype_ `void OnRenameVariable(const FNiagaraVariableBase& OldVariable, const FNiagaraVariableBase& NewVariable, FStringView EmitterName);`
- L36 _public prototype_ `void OnRemoveVariable(const FNiagaraVariableBase& OldVariable, FStringView EmitterName);`

#### struct `FNiagaraFloatParameterComponentBinding`  
`struct FNiagaraFloatParameterComponentBinding : public FNiagaraParameterComponentBinding`  
_L41-49_
- reflection: `USTRUCT()`
- inherits: `FNiagaraParameterComponentBinding`
- L46 _public prototype_ `virtual ~FNiagaraFloatParameterComponentBinding() = default;`
- L47 _public function_ `virtual FNiagaraTypeDefinition GetTypeDef() const override`

### `Plugins/FX/NiagaraNanite/Source/NiagaraNanite/Internal/Renderer/NiagaraNaniteRendererProperties.h` (Internal)


#### enum `ENiagaraNaniteVFLayout`  
`enum class ENiagaraNaniteVFLayout`  
_L21-32_
- L23 _public enumerator_ `Position`
- L24 _public enumerator_ `Rotation`
- L25 _public enumerator_ `Scale`
- L27 _public enumerator_ `PrevPosition`
- L28 _public enumerator_ `PrevRotation`
- L29 _public enumerator_ `PrevScale`
- L31 _public enumerator_ `Max`

#### struct `FNiagaraNaniteMeshRendererMeshProperties`  
`struct FNiagaraNaniteMeshRendererMeshProperties`  
_L35-62_
- reflection: `USTRUCT()`
- L39 _public prototype_ `FNiagaraNaniteMeshRendererMeshProperties();`
- L43 _public member_ `TObjectPtr<UStaticMesh> Mesh;` — `UPROPERTY(EditAnywhere, Category = "Mesh")` — The mesh to use when rendering this slot
- L47 _public member_ `FVector3f Scale = FVector3f::OneVector;` — `UPROPERTY(EditAnywhere, Category = "Mesh")` — Scale of the mesh
- L51 _public member_ `FRotator3f Rotation = FRotator3f::ZeroRotator;` — `UPROPERTY(EditAnywhere, Category = "Mesh")` — Rotation of the mesh
- L59 _public member_ `FNiagaraParameterBinding MeshParameterBinding;` — `UPROPERTY(EditAnywhere, Category = "Mesh")` — Binding to supported mesh types.
- L61 _public prototype_ `UStaticMesh* GetResolvedMesh(const FNiagaraEmitterInstance* InEmitter) const;`

#### struct `FNiagaraNaniteMICOverride`  
`struct FNiagaraNaniteMICOverride`  
_L65-74_
- reflection: `USTRUCT()`
- L70 _public member_ `TObjectPtr<UMaterialInterface> OriginalMaterial;` — `UPROPERTY()`
- L73 _public member_ `TObjectPtr<UMaterialInstanceConstant> ReplacementMaterial;` — `UPROPERTY()`

#### struct `FNiagaraNaniteMaterialOverride`  
`struct FNiagaraNaniteMaterialOverride`  
_L77-95_
- reflection: `USTRUCT()`
- L81 _public prototype_ `FNiagaraNaniteMaterialOverride();`
- L85 _public member_ `TObjectPtr<UMaterialInterface> ExplicitMat;` — `UPROPERTY(EditAnywhere, Category = "Material")` — Use this UMaterialInterface if set to a valid value. This will be subordinate to UserParamBinding if it is set to a valid user variable.
- L89 _public member_ `FNiagaraUserParameterBinding UserParamBinding;` — `UPROPERTY(EditAnywhere, Category = "Material")` — Use the UMaterialInterface bound to this user variable if it is set to a valid value. If this is bound to a valid value and ExplicitMat is also set, UserParamBinding wins.
- L91 _public function_ `bool operator==(const FNiagaraNaniteMaterialOverride& Other)const`

#### class `UNiagaraNaniteRendererProperties`  
`class UNiagaraNaniteRendererProperties : public UNiagaraRendererProperties`  
_L98-226_
- reflection: `UCLASS(editinlinenew, MinimalAPI, meta = (DisplayName = "Nanite Renderer"))`
- inherits: `UNiagaraRendererProperties`
- L103 _public prototype_ `UNiagaraNaniteRendererProperties();`
- L106 _public prototype_ `virtual void PostLoad() override;` — UObject Interface
- L107 _public prototype_ `virtual void PostInitProperties() override;`
- L108 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L110 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L114 _public prototype_ `static void InitCDOPropertiesAfterModuleStartup();`
- L117 _public prototype_ `virtual FNiagaraRenderer* CreateEmitterRenderer(ERHIFeatureLevel::Type FeatureLevel, const FNiagaraEmitterInstance* Emitter, const FNiagaraSystemInstanceController& InController) override;`
- L118 _public prototype_ `virtual class FNiagaraBoundsCalculator* CreateBoundsCalculator() override;`
- L119 _public prototype_ `virtual void GetUsedMaterials(const FNiagaraEmitterInstance* InEmitter, TArray<UMaterialInterface*>& OutMaterials) const override;`
- L120 _public prototype_ `virtual void GetUsedMeshes(const FNiagaraEmitterInstance* InEmitter, TArray<UObject*>& OutMeshes) const override;`
- L121 _public function_ `virtual bool IsSimTargetSupported(ENiagaraSimTarget InSimTarget) const override`
- L123 _public prototype_ `virtual const TArray<FNiagaraVariable>& GetOptionalAttributes() override;`
- L124 _public prototype_ `virtual void GetAdditionalVariables(TArray<FNiagaraVariableBase>& OutArray) const override;`
- L125 _public prototype_ `virtual void GetRendererWidgets(const FNiagaraEmitterInstance* InEmitter, TArray<TSharedPtr<SWidget>>& OutWidgets, TSharedPtr<FAssetThumbnailPool> InThumbnailPool) const override;`
- L126 _public prototype_ `virtual void GetRendererTooltipWidgets(const FNiagaraEmitterInstance* InEmitter, TArray<TSharedPtr<SWidget>>& OutWidgets, TSharedPtr<FAssetThumbnailPool> InThumbnailPool) const override;`
- L127 _public prototype_ `virtual void GetRendererFeedback(const FVersionedNiagaraEmitter& InEmitter, TArray<FNiagaraRendererFeedback>& OutErrors, TArray<FNiagaraRendererFeedback>& OutWarnings, TArray<FNiagaraRendererFeedback>& OutInfo) const override;`
- L128 _public prototype_ `virtual TArray<FNiagaraVariable> GetBoundAttributes() const override;`
- L129 _public prototype_ `virtual void RenameVariable(const FNiagaraVariableBase& OldVariable, const FNiagaraVariableBase& NewVariable, const FVersionedNiagaraEmitterBase& InEmitter) override;`
- L130 _public prototype_ `virtual void RemoveVariable(const FNiagaraVariableBase& OldVariable, const FVersionedNiagaraEmitterBase& InEmitter) override;`
- L131 _public prototype_ `virtual void RenameEmitter(const FName& InOldName, const UNiagaraEmitter* InRenamedEmitter) override;`
- L133 _public prototype_ `virtual void CacheFromCompiledData(const FNiagaraDataSetCompiledData* CompiledData) override;`
- L134 _public prototype_ `virtual void UpdateSourceModeDerivates(ENiagaraRendererSourceDataMode InSourceMode, bool bFromPropertyEdit = false) override;`
- L135 _public function_ `virtual ENiagaraRendererSourceDataMode GetCurrentSourceMode() const override`
- L136 _public prototype_ `virtual bool PopulateRequiredBindings(FNiagaraParameterStore& InParameterStore) override;`
- L137 _public function_ `virtual bool NeedsMIDsForMaterials() const override`
- L138 _public function_ `virtual bool NeedsSystemPostTick() const override`
- L139 _public function_ `virtual bool NeedsSystemCompletion() const override`
- L142 _public prototype_ `void GetMeshUsedMaterials(const FNiagaraNaniteMeshRendererMeshProperties& MeshProperties, const FNiagaraEmitterInstance* InEmitter, TArray<UMaterialInterface*>& OutMaterials) const;`
- L144 _public prototype_ `void UpdatePreviousBindings(const FVersionedNiagaraEmitterBase& Emitter);`
- L146 _public prototype_ `void UpdateMICs();`
- L148 _public prototype_ `void ApplyMaterialOverrides(const FNiagaraEmitterInstance* EmitterInstance, TArray<UMaterialInterface*>& InOutMaterials) const;`
- L151 _public member_ `TArray<FNiagaraNaniteMeshRendererMeshProperties> Meshes;` — `UPROPERTY(EditAnywhere, Category = "Mesh Rendering")`
- L155 _public member_ `ENiagaraRendererSourceDataMode SourceMode = ENiagaraRendererSourceDataMode::Particles;` — `UPROPERTY(EditAnywhere, Category = "Mesh Rendering")` — Whether or not to draw a single element for the Emitter or to draw the particles.
- L159 _public member_ `uint32 bOverrideMaterials : 1;` — `UPROPERTY(EditAnywhere, Category = "Mesh Rendering", DisplayName = "Enable Material Overrides")` — Whether or not to use the OverrideMaterials array instead of the mesh's existing materials.
- L167 _public member_ `TArray<FNiagaraNaniteMaterialOverride> OverrideMaterials;` — `UPROPERTY(EditAnywhere, Category = "Mesh Rendering", meta = (EditCondition = "bOverrideMaterials", EditConditionHides))` — The materials to be used instead of the StaticMesh's materials. Note that each material must have the Niagara Mesh Particles flag checked. If the ParticleMesh	requires more materials than exist in this array or any entry in this array is set to None, we will use the ParticleMesh's existing Material instead.
- L170 _public member_ `TArray<FNiagaraNaniteMICOverride> MICOverrideMaterials;` — `UPROPERTY()`
- L174 _public member_ `int32 RendererVisibility = 0;` — `UPROPERTY(EditAnywhere, Category = "Nanite Rendering")` — If a render visibility tag is present, particles whose tag matches this value will be visible in this renderer.
- L178 _public member_ `FNiagaraVariableAttributeBinding PositionBinding;` — `UPROPERTY(EditAnywhere, Category = "Bindings")` — Which attribute should we use for position when generating instanced meshes?
- L182 _public member_ `FNiagaraVariableAttributeBinding RotationBinding;` — `UPROPERTY(EditAnywhere, Category = "Bindings")` — Which attribute should we use for orienting meshes when generating instanced meshes?
- L186 _public member_ `FNiagaraVariableAttributeBinding ScaleBinding;` — `UPROPERTY(EditAnywhere, Category = "Bindings")` — Which attribute should we use for scale when generating instanced meshes?
- L190 _public member_ `FNiagaraVariableAttributeBinding RendererVisibilityTagBinding;` — `UPROPERTY(EditAnywhere, Category = "Bindings")` — Which attribute should we use for the renderer visibility tag?
- L194 _public member_ `FNiagaraVariableAttributeBinding MeshIndexBinding;` — `UPROPERTY(EditAnywhere, Category = "Bindings")` — Which attribute should we use to pick the element in the mesh array on the mesh renderer?
- L198 _public member_ `FNiagaraRendererMaterialParameters MaterialParameters;` — `UPROPERTY(EditAnywhere, Category = "Bindings")` — If this array has entries, we will create a MaterialInstanceDynamic per Emitter instance from Material and set the Material parameters using the Niagara simulation variables listed.
- L202 _public member_ `TArray<FNiagaraFloatParameterComponentBinding> PerInstanceDataBindings;` — `UPROPERTY(EditAnywhere, Category = "Bindings")` — Defines data we should pass through as per instance data inside the material.
- L205 _public member_ `TArray<int32> PerInstanceDataFloatComponents;` — Indicies into particle dataset, can be INDEX_NONE if we are reading from none particle data.
- L209 _public member_ `FNiagaraVariableAttributeBinding PreviousPositionBinding;` — `UPROPERTY(Transient)` — The following bindings are not provided by the user, but are filled based on what other bindings are set to, and the value of bGenerateAccurateMotionVectors
- L211 _public member_ `FNiagaraVariableAttributeBinding PreviousRotationBinding;` — `UPROPERTY(Transient)`
- L213 _public member_ `FNiagaraVariableAttributeBinding PreviousScaleBinding;` — `UPROPERTY(Transient)`
- L215 _public member_ `FNiagaraRendererLayout RendererLayout;`
- L217 _public member_ `FNiagaraDataSetAccessor<FNiagaraPosition> PositionDataSetAccessor;`
- L218 _public member_ `FNiagaraDataSetAccessor<FQuat4f> RotationDataSetAccessor;`
- L219 _public member_ `FNiagaraDataSetAccessor<FVector3f> ScaleDataSetAccessor;`
- L220 _public member_ `FNiagaraDataSetAccessor<int32> RendererVisTagDataSetAccessor;`
- L221 _public member_ `FNiagaraDataSetAccessor<int32> MeshIndexDataSetAccessor;`
- L223 _public member_ `FNiagaraDataSetAccessor<FNiagaraPosition> PreviousPositionDataSetAccessor;`
- L224 _public member_ `FNiagaraDataSetAccessor<FQuat4f> PreviousRotationDataSetAccessor;`
- L225 _public member_ `FNiagaraDataSetAccessor<FVector3f> PreviousScaleDataSetAccessor;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API NIAGARANANITE_API`

### `Plugins/FX/NiagaraNanite/Source/NiagaraNanite/Private/NiagaraNaniteModule.h` (Private)


#### class `FNiagaraNaniteModule`  
`class FNiagaraNaniteModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/FX/NiagaraNanite/Source/NiagaraNanite/Private/Renderer/NiagaraRendererNanite.h` (Private)


#### class `FNiagaraRendererNanite`  
`class FNiagaraRendererNanite : public FNiagaraRenderer`  
_L10-41_
- inherits: `FNiagaraRenderer`
- L22 _public prototype_ `explicit FNiagaraRendererNanite(ERHIFeatureLevel::Type FeatureLevel, const UNiagaraRendererProperties* InProps, const FNiagaraEmitterInstance* Emitter);`
- L23 _public prototype_ `~FNiagaraRendererNanite();`
- L25 _public prototype_ `void Initialize(const UNiagaraRendererProperties* InProperties, const FNiagaraEmitterInstance* InEmitter, const FNiagaraSystemInstanceController& InController) override;`
- L27 _public prototype_ `void ReleaseComponents();`
- L30 _public prototype_ `virtual void PostSystemTick_GameThread(const UNiagaraRendererProperties* InProperties, const FNiagaraEmitterInstance* Emitter) override;` — FNiagaraRenderer interface BEGIN
- L31 _public prototype_ `virtual void OnSystemComplete_GameThread(const UNiagaraRendererProperties* InProperties, const FNiagaraEmitterInstance* Emitter) override;`
- L34 _public prototype_ `static int32 GetMaxCustomFloats();`
- L37 _private member_ `int32 MeshIndexComponentOffset = INDEX_NONE;`
- L38 _private member_ `int32 RendererVisComponentOffset = INDEX_NONE;`
- L40 _private member_ `TArray<FMeshData, TInlineAllocator<4>> MeshDatas;`

#### struct `FNiagaraRendererNanite::FMeshData`  
`struct FMeshData`  
_L12-19_
- L14 _public member_ `TWeakObjectPtr<UNiagaraStaticMeshComponent> MeshComponent;`
- L15 _public member_ `FVector3f Scale = FVector3f::OneVector;`
- L16 _public member_ `FQuat4f Rotation = FQuat4f::Identity;`
- L18 _public member_ `TArray<uint32, TInlineAllocator<4>> MaterialRemapTable;` — FVector3f									PivotOffset = FVector3f::ZeroVector;

### `Plugins/FX/NiagaraNanite/Source/NiagaraNanite/Private/Renderer/NiagaraStaticMeshComponent.h` (Private)


#### class `UNiagaraStaticMeshComponent`  
`class UNiagaraStaticMeshComponent : public UStaticMeshComponent`  
_L16-66_
- reflection: `UCLASS()`
- inherits: `UStaticMeshComponent`
- L20 _private typedef_ `using FCpuInstanceUpdateFunction = TFunction<void(FInstanceSceneDataBuffers::FWriteView&)>;`
- L21 _private typedef_ `using FGpuInstanceUpdateFunction = TFunction<void(FRDGBuilder&, const FGPUSceneWriteDelegateParams&)>;`
- L25 _public prototype_ `virtual void OnComponentDestroyed(bool) override;`
- L29 _public function_ `bool ShouldCreatePhysicsState() const override`
- L30 _public function_ `bool IsHLODRelevant() const override`
- L34 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L35 _public prototype_ `virtual FMatrix GetRenderMatrix() const override;`
- L36 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& BoundTransform) const override;`
- L37 _public function_ `bool SupportsStaticLighting() const override`
- L39 _public prototype_ `virtual FBox GetStreamingBounds() const override;`
- L41 _public prototype_ `virtual bool BuildTextureStreamingDataImpl(ETextureStreamingBuildType BuildType, EMaterialQualityLevel::Type QualityLevel, ERHIFeatureLevel::Type FeatureLevel, TSet<FGuid>& DependentResources, bool& bOutSupportsBuildTextureStreamingData) override;`
- L42 _public prototype_ `virtual void GetStreamingRenderAssetInfo(FStreamingTextureLevelContext& LevelContext, TArray<FStreamingRenderAssetPrimitiveInfo>& OutStreamingRenderAssets) const override;`
- L46 _public function_ `bool IsNavigationRelevant() const override`
- L50 _public prototype_ `virtual bool GetMaterialStreamingData(int32 MaterialIndex, FPrimitiveMaterialInfo& MaterialData) const override;`
- L51 _public prototype_ `virtual FPrimitiveSceneProxy* CreateStaticMeshSceneProxy(Nanite::FMaterialAudit& NaniteMaterials, bool bCreateNanite) override;`
- L54 _public prototype_ `void GetSceneProxyDesc(FInstancedStaticMeshSceneProxyDesc& OutSceneProxyDesc) const;`
- L57 _public prototype_ `void UpdateInstanceCPU(int32 NumRequiredInstances, FCpuInstanceUpdateFunction UpdateFunction);`
- L58 _public prototype_ `void UpdateInstanceGPU(int32 NumRequiredInstances, FGpuInstanceUpdateFunction UpdateFunction);`
- L60 _public member_ `bool bUseCpuOnlyUpdates = false;`
- L61 _public member_ `int32 NumInstances = 0;`
- L62 _public member_ `int32 NumCustomDataFloats = 0;`
- L64 _public member_ `FCpuInstanceUpdateFunction PendingCpuUpdateFunction;`
