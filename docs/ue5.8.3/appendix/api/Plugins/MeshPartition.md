# Plugins / MeshPartition

- module root: `Plugins/Experimental/MeshPartition/Source/MeshPartition`
- headers: 24; symbols: 611
- symbol kinds: class=17, delegate=2, enum=11, enumerator=37, externvar=5, function=129, macro=10, member=149, namespace=49, prototype=172, struct=29, typedef=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, DataLayerEditor, DeveloperSettings, DynamicMesh, Engine, GeometryCore, MeshConversion, MeshDescription, PhysicsCore, RHI, RenderCore, Renderer
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartition.h` (Public)


#### class `UE::MeshPartition::AMeshPartition`  
`class AMeshPartition : public AActor`  
_L25-81_
- reflection: `UCLASS(MinimalAPI, NotPlaceable)`
- inherits: `AActor`
- desc: Actor class defining globally a MegaMesh. This actor contain handles to manipulate a MegaMesh in the editor (translate/rotate/scale). It is also the target of external modifiers to express which MegaMesh they are targeting.
- L30 _public prototype_ `AMeshPartition();`
- L34 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L35 _public prototype_ `virtual void PostLoad() override;`
- L36 _public prototype_ `virtual void PostActorCreated() override;`
- L39 _public prototype_ `void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const;` — Adds dependencies on actor-level data (transform, etc.) that affect compiled section results.
- L44 _public prototype_ `virtual void PostRegisterAllComponents() override;` — AActor Implementation
- L45 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L48 _public function_ `UMeshPartitionComponent* GetMeshPartitionComponent() const`
- L49 _public prototype_ `void SetMeshPartitionComponent(UMeshPartitionComponent* InMeshPartitionComponent);`
- L52 _public function_ `UMeshPartitionDefinition* GetMeshPartitionDefinition() const` — `UFUNCTION(BlueprintCallable, Category = "Mesh Partition")`
- L53 _public prototype_ `void SetMeshPartitionDefinition(UMeshPartitionDefinition* InMeshPartitionDefinition);`
- L58 _public prototype_ `FBox WorldToLocal(const FBox& InWorldBounds) const;` — World<->local AABB conversion against this actor's live transform. Convention used by the build pipeline: cell coords / build mesh vertices are in MeshPartition-local space; descriptor bounds and streaming bounds are in world space.
- L59 _public prototype_ `FBox LocalToWorld(const FBox& InLocalBounds) const;`
- L64 _public function_ `USceneComponent* GetTransientSectionAttachAnchor() const` — Attach target for transient editor-only section actors (APreviewSection, AInteractiveSection). Attaching temporary section actors keeps these actors' attachments off of undo-tracked state.
- L68 _private prototype_ `void InitializeDefinition();`
- L72 _private member_ `TObjectPtr<UMeshPartitionComponent> MegaMeshComponent;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition", meta=(DisplayName="Mesh Partition Component"))`
- L75 _private member_ `TObjectPtr<UMeshPartitionDefinition> MegaMeshDefinition;` — `UPROPERTY(EditAnywhere, Category = "MeshPartition", meta=(DisplayName="Mesh Partition Definition"))`
- L79 _private member_ `TObjectPtr<USceneComponent> TransientSectionAttachAnchor;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPARTITION_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionActorDescUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MeshPartition` (scope `UE`)
- L8 _namespace_ `namespace Utils` (scope `UE::MeshPartition`)
- L8 _namespace_ `namespace ActorDesc` (scope `UE::MeshPartition::Utils`)
- L12 _prototype_ `int32 GetPropertyInt32(FPropertyPairsMap& PropertyPairsMap, const FName PropertyName, int32 DefaultValue);` (scope `UE::MeshPartition::Utils::ActorDesc`) — functions to work with typed properties
- L13 _prototype_ `int32 GetPropertyInt32(const FWorldPartitionActorDescInstance& InActorDescInstance, const FName PropertyName, int32 DefaultValue);` (scope `UE::MeshPartition::Utils::ActorDesc`)
- L14 _prototype_ `void SetPropertyInt32(FPropertyPairsMap& PropertyPairsMap, const FName PropertyName, int32 NewValue);` (scope `UE::MeshPartition::Utils::ActorDesc`)
- L16 _prototype_ `int32 IncrementPropertyInt32(FPropertyPairsMap& PropertyPairsMap, const FName PropertyName);` (scope `UE::MeshPartition::Utils::ActorDesc`)
- L18 _prototype_ `void SetPropertyGUID(FPropertyPairsMap& PropertyPairsMap, const FName PropertyName, const FGuid& NewValue);` (scope `UE::MeshPartition::Utils::ActorDesc`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionChannel.h` (Public)


#### struct `UE::MeshPartition::FChannelDesc`  
`struct FChannelDesc`  
_L28-37_
- reflection: `USTRUCT(MinimalAPI)`
- L34 _public member_ `FName Name = NAME_Default;` — `UPROPERTY(EditAnywhere, Category = "MeshPartition")`
- L36 _public function_ `bool operator ==(const FName& InOtherName) const`

#### struct `UE::MeshPartition::FChannelMap`  
`struct FChannelMap`  
_L41-54_
- reflection: `USTRUCT(MinimalAPI)`
- L46 _public function_ `int32 GetNumChannels() const`
- L47 _public function_ `TArrayView<const MeshPartition::FChannelDesc> GetChannelDescs() const`
- L48 _public prototype_ `TArray<FName> GetChannels() const;`
- L49 _public prototype_ `int32 FindChannel(FName InChannelName) const;`
- L53 _private member_ `TArray<MeshPartition::FChannelDesc> ChannelDescs;` — `UPROPERTY(EditAnywhere, Category = "Material", meta = (TitleProperty = "Name"))`

#### struct `UE::MeshPartition::FChannelPacking`  
`struct FChannelPacking`  
_L62-126_
- desc: Interface to constants describing the packing of the channel slots in the channel table embedded in the section primitives and accessed by the material shader
- L65 _public member_ `static const uint8 SlotNumBits = 5;` — Slot is represented by N bits.
- L69 _public member_ `static const uint8 SlotInvalid = ((uint32)(1 << SlotNumBits) - 1);` — Invalid slot value is all N bits set to 1. SlotInvalid is also the maximum number of representable slot values with N bits
- L72 _public member_ `static const uint8 WordNumSlots = 32 / SlotNumBits;` — Number of channel slots of N bits in a 32bits word of the table
- L83 _public member_ `static const uint8 TableNumWords = 4;` — Table is a vec of P words (a word is 32bits).
- L86 _public member_ `static const uint8 TableMaxNumSlots = TableNumWords * WordNumSlots;` — Number of channel slots available in the table
- L89 _public member_ `static const uint8 MaxNumberPackedChannels = (TableMaxNumSlots >= SlotInvalid ? SlotInvalid : TableMaxNumSlots);` — Maximum number of channels supported with the packing configuration
- L125 _public prototype_ `static void SetCustomPrimitiveData(UPrimitiveComponent* InPrimitiveComponent, TConstArrayView<uint8> InChannelTable, const FVector2f& InChannelTexcoordDesc);`

#### struct `UE::MeshPartition::FNameWrapper`  
`struct FNameWrapper`  
_L134-162_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Helper struct that can be used to wrap an FName so that it can be used as the target of a detail customization without customizing all FNames. Has implicit conversions to/from FName so that it can be used as a drop-in replacement.
- L139 _public prototype_ `FNameWrapper() = default;`
- L140 _public function_ `FNameWrapper(const FName& NameIn) : Name(NameIn)`
- L142 _public function_ `void SetName(const FName& NameIn)`
- L143 _public function_ `const FName& GetName() const`
- L146 _public function_ `operator const FName& () const`
- L147 _public function_ `operator FName& ()`
- L148 _public function_ `FNameWrapper& operator=(const FName& NameIn)`
- L153 _public function_ `bool IsNone() const`
- L154 _public function_ `bool operator==(const FNameWrapper& Other)`
- L158 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L161 _private member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Name")`

#### struct `UE::MeshPartition::FChannelName`  
`struct FChannelName : public FNameWrapper`  
_L169-176_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FNameWrapper`
- desc: Version of FNameWrapper to use for channel names. Gets used with a detail customization that uses GetOptions metadata function to constrain options when a toggle is engaged.
- L173 _public prototype_ `FChannelName() = default;`
- L174 _public function_ `FChannelName(const FName& NameIn) : FNameWrapper(NameIn)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<UE::MeshPartition::FChannelName> : public TStructOpsTypeTraitsBase2<UE::MeshPartition::FChannelName>`  
_L181-187_
- inherits: `TStructOpsTypeTraitsBase2<UE::MeshPartition::FChannelName>`
- desc: Needed to get SerializeFromMismatchedTag to be called to convert from serialized FName properties

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L184-186_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHPARTITION_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshPartition` (scope `UE`)
- L56 _prototype_ `void operator += (MeshPartition::IDependencyInterface& Dependencies, const MeshPartition::FChannelMap& ChannelMap);` (scope `UE::MeshPartition`)
- L185 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anonf7a560540103`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionCollisionComponent.h` (Public)


#### struct `UE::MeshPartition::FMeshPartitionCollisionData`  
`struct FMeshPartitionCollisionData`  
_L22-32_
- reflection: `USTRUCT()`
- desc: Container for collision data that can be set on a UMeshPartitionCollisionComponent
- L26 _public member_ `TOptional<FTriMeshCollisionData> Mesh;`
- L29 _public member_ `TArray<TObjectPtr<UPhysicalMaterial>> PhysicalMaterials;` — `UPROPERTY()`
- L31 _public prototype_ `FMeshPartitionCollisionData();`

#### class `UE::MeshPartition::UMeshPartitionCollisionComponent`  
`class UMeshPartitionCollisionComponent : public UPrimitiveComponent, public IInterface_CollisionDataProvider`  
_L35-119_
- reflection: `UCLASS(MinimalAPI, meta = (BlueprintSpawnableComponent), ClassGroup = Collision, hidecategories = (Object, LOD, Lighting, TextureStreaming))`
- inherits: `UPrimitiveComponent,IInterface_CollisionDataProvider`
- L40 _public prototype_ `virtual UBodySetup* GetBodySetup() override;`
- L41 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L43 _public prototype_ `virtual void OnRegister() override;`
- L44 _public prototype_ `virtual void OnUnregister() override;`
- L47 _public prototype_ `void SetCollisionData(TSharedPtr<FMeshPartitionCollisionData> InCollisionData, FName CollisionProfileName, bool bRebuild = true);`
- L48 _public prototype_ `void RebuildIfNeeded(bool bAllowAsyncBuild);`
- L49 _public function_ `TSharedPtr<const FMeshPartitionCollisionData> GetMeshCollisionData() const`
- L53 _public prototype_ `virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* CollisionData, bool InUseAllTriData) override;`
- L54 _public prototype_ `virtual bool ContainsPhysicsTriMeshData(bool InUseAllTriData) const override;`
- L55 _public prototype_ `virtual bool GetTriMeshSizeEstimates(struct FTriMeshCollisionDataEstimates& OutTriMeshEstimates, bool bInUseAllTriData) const override;`
- L56 _public prototype_ `virtual void GetMeshId(FString& OutMeshId) override;`
- L60 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L61 _private prototype_ `void Serialize(FArchive& Ar);`
- L64 _private prototype_ `UBodySetup* CreateBodySetupHelper();`
- L65 _private prototype_ `void RebuildPhysicsData(bool bAllowAsyncBuild = true);`
- L66 _private prototype_ `void RebuildPhysicalMaterialData();`
- L67 _private prototype_ `void UpdateLocalBounds();`
- L68 _private prototype_ `void AbortPendingPhysicsCook();`
- L69 _private prototype_ `void FinishPhysicsAsyncCook(bool bSuccess, UBodySetup* FinishedBodySetup);`
- L72 _private function_ `FTriMeshCollisionData* GetCollisionMesh()` — return the complex collision, or nullptr if not available
- L76 _private function_ `const FTriMeshCollisionData* GetCollisionMesh() const`
- L84 _private prototype_ `virtual int32 GetNumMaterials() const override;` — UPrimitiveComponent materials methods -- only used to drive physical materials TODO: These overrides could be removed if BodyInstance had a way to get complex collision materials without going through render materials
- L85 _private prototype_ `virtual UMaterialInterface* GetMaterial(int32 ElementIndex) const override;`
- L88 _private prototype_ `virtual void SetMaterial(int32 ElementIndex, UMaterialInterface* Material) override;` — Note: Below material set/create methods are BP-exposed on UPrimitiveComponent, but don't make sense for our physics-only materials use case; do not call them
- L89 _private prototype_ `virtual void SetMaterialByName(FName MaterialSlotName, class UMaterialInterface* Material) override;`
- L90 _private prototype_ `virtual UMaterialInstanceDynamic* CreateAndSetMaterialInstanceDynamic(int32 ElementIndex) override;`
- L91 _private prototype_ `virtual UMaterialInstanceDynamic* CreateAndSetMaterialInstanceDynamicFromMaterial(int32 ElementIndex, class UMaterialInterface* Parent) override;`
- L92 _private prototype_ `virtual UMaterialInstanceDynamic* CreateDynamicMaterialInstance(int32 ElementIndex, class UMaterialInterface* SourceMaterial, FName OptionalName) override;`
- L98 _private member_ `TArray<TObjectPtr<UMaterialInterface>> PhysicsOnlyMaterials;` — `UPROPERTY()` — Rendering materials interfaces; used solely as storage for physical materials
- L101 _private member_ `TObjectPtr<UBodySetup> MeshBodySetup;` — `UPROPERTY(Instanced)`
- L104 _private member_ `FBox LocalBounds;` — `UPROPERTY()`
- L108 _private member_ `TObjectPtr<UBodySetup> AsyncBodySetup;` — `UPROPERTY(Transient, Instanced)` — Body setup being cooked asynchronously
- L110 _private member_ `TSharedPtr<FMeshPartitionCollisionData> CollisionData;`
- L111 _private member_ `bool bNeedsRebuild = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionCompiledSection.h` (Public)


#### struct `UE::MeshPartition::FCompiledSectionBuildInfo`  
`struct FCompiledSectionBuildInfo`  
_L43-144_
- reflection: `USTRUCT()`
- desc: Describes the build and settings that produced a compiled section Used to track invalidation of old sections, and also filtering of different build variants for platforms
- L54 _public member_ `FGuid BuildKey;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition", meta = (NoResetToDefault))` — Uniquely identifies the build job that produced this section.
- L58 _public member_ `FName BuildVariantName;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition", meta = (NoResetToDefault))` — Name of the Build Variant that produced this section.
- L62 _public member_ `FTopLevelAssetPath MegaMeshDefinitionPath;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — Definition used to build this section (asset reference)
- L66 _public member_ `TArray<FSoftObjectPath> BaseModifierPaths;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — list of ModifierPaths for each base modifier in this compiled section
- L70 _public member_ `FGuid ModifiersHash;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — hash of ALL of the Modifiers affecting this compiled section (base modifiers and non-base modifiers) -- used to detect changes to modifier settings
- L74 _public member_ `TArray<FName> PackageDependencies;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — package names for all asset dependencies, gathered from modifiers affecting this section
- L78 _public member_ `FGuid PackageHash;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — hash of ALL of the Packages affecting this compiled section (detects if any package has changed)
- L83 _public member_ `TArray<uint32> PackageChecksums;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — partial hash of each individual package dependency, useful to debug invalidation behaviors
- L88 _public member_ `FGuid ModifierSetHash;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — hash of ALL Modifier Paths affecting this compiled section -- used by PackageHash to detect when a modifier is added or removed
- L92 _public member_ `TArray<FName> ClassDependencies;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — class names for all modifier classes used to construct this compiled section
- L96 _public member_ `FGuid ClassHash;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — hash of the MegaMeshClassVersion for each class in the list above -- used to detect when modifier class implementations are changed
- L101 _public member_ `TArray<uint32> ClassChecksums;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — partial hash of each individual class dependency, useful to debug invalidation behaviors
- L106 _public member_ `FGuid BuildVariantHash;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — hash of the general MegaMeshDefinition and specific BuildVariant settings that produced this compiled section
- L110 _public member_ `FGuid MegaMeshGUID;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — actor desc GUID of the AMegaMesh actor
- L114 _public member_ `FSoftObjectPath MegaMeshPath;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — path to the AMegaMesh actor this was built for
- L117 _public member_ `static inline const FIntVector InvalidGridCellCoord = FIntVector(MIN_int32, MIN_int32, MIN_int32);` — Sentinel for sections not produced by a grid-aligned split.
- L121 _public member_ `FIntVector GridCellCoord = InvalidGridCellCoord;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition", meta = (NoResetToDefault))` — Absolute world-space grid coordinate of this section's cell.
- L131 _public member_ `FGridSettings GridSettings;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — Grid configuration that produced this section (CellSize=0 means non-grid section). Stamped at section creation by the builder or WorldUpdater so consumers (e.g. SeparateWorldBuilder) don't need to re-resolve from the pipeline. Not Transient: CPF_Transient causes StaticDuplicateObject to skip the property, which breaks PIE world duplication (editor -> PIE actor copy). Regular UPROPERTY survives both duplication and serialization; the default {0, false} is harmless for sections loaded from disk. Not part of identity or equality comparisons.
- L135 _private member_ `mutable const UMeshPartitionDefinition* MegaMeshDefinition;` — transient cache of the mega mesh definition pointer (converted from the MegaMeshDefinitionPath)
- L138 _public prototype_ `void Serialize(FArchive& Ar);` — NOTE: this is only used by the compiled section actor descriptor serialization
- L139 _public prototype_ `bool operator== (const FCompiledSectionBuildInfo& Other) const;`
- L140 _public prototype_ `bool TargetsSameCompiledSectionAs(const FCompiledSectionBuildInfo& Other) const;`
- L141 _public prototype_ `bool SetMegaMeshDefinition(const UMeshPartitionDefinition* Definition);`
- L142 _public prototype_ `const UMeshPartitionDefinition* GetMegaMeshDefinition() const;`
- L143 _public function_ `bool HasValidGridCellCoord() const`

#### struct `UE::MeshPartition::FCompiledSectionDescriptor`  
`struct FCompiledSectionDescriptor`  
_L146-158_
- L148 _public member_ `MeshPartition::FCompiledSectionBuildInfo Info;`
- L151 _public member_ `FGuid ActorDescGuid;` — the world partition actor desc GUID for the compiled section actor
- L154 _public member_ `FSoftObjectPath ActorPath;` — the path to this compiled section
- L157 _public prototype_ `static bool BuildFromActorDescInstance(const FWorldPartitionActorDescInstance& InActorDescInstance, FCompiledSectionDescriptor& OutCompiledSectionDescriptor);` — construct from the world partition actor desc properties

#### class `UE::MeshPartition::ACompiledSection`  
`class ACompiledSection : public AActor`  
_L165-285_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- desc: This is the equivalent of AMegaMeshPreviewSection but used in the final game client. Sections are built during the cook process, producing assets (StaticMesh, Collisions, MetaData), and are part of the global MegaMesh.
- L170 _public prototype_ `ACompiledSection();`
- L173 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Implementation
- L174 _public prototype_ `virtual bool NeedsLoadForTargetPlatform(const class ITargetPlatform* TargetPlatform) const override;`
- L178 _public prototype_ `virtual void PreRegisterAllComponents() override;` — AActor Implementation
- L179 _public prototype_ `virtual void PostRegisterAllComponents() override;`
- L180 _public prototype_ `virtual void PostUnregisterAllComponents() override;`
- L181 _public function_ `virtual bool IsRuntimeOnly() const override`
- L183 _public prototype_ `virtual TUniquePtr<FWorldPartitionActorDesc> CreateClassActorDesc() const override;`
- L184 _public prototype_ `virtual void GetActorDescProperties(FPropertyPairsMap& PropertyPairsMap) const override;`
- L185 _public prototype_ `virtual void GetStreamingBounds(FBox& OutRuntimeBounds, FBox& OutEditorBounds) const override;`
- L186 _public prototype_ `virtual TArray<UActorComponent*> GetHLODRelevantComponents() const override;`
- L190 _public function_ `TArray<TObjectPtr<UMeshPartitionStaticMeshComponent>>& GetMeshComponents()`
- L191 _public function_ `const TArray<TObjectPtr<UMeshPartitionStaticMeshComponent>>& GetMeshComponents() const`
- L193 _public function_ `TArray<TObjectPtr<UMeshPartitionCollisionComponent>>& GetCollisionComponents()`
- L194 _public function_ `const TArray<TObjectPtr<UMeshPartitionCollisionComponent>>& GetCollisionComponents() const`
- L196 _public prototype_ `TArray<TObjectPtr<UStaticMesh>> GetStaticMeshes() const;`
- L197 _public prototype_ `void AddStaticMesh(UStaticMesh* InStaticMesh, const FStaticMeshDescriptor& InDescriptor);`
- L199 _public prototype_ `void AddCollisionComponent(UMeshPartitionCollisionComponent* InCollisionComponent);`
- L201 _public prototype_ `UStaticMesh* GetFarFieldMesh() const;`
- L202 _public prototype_ `void SetFarFieldMesh(UStaticMesh* InStaticMesh);`
- L204 _public prototype_ `void SetParent(const AMeshPartition* InMegaMesh);`
- L205 _public prototype_ `AMeshPartition* GetParentMegaMesh() const;`
- L207 _public function_ `void SetMaterialInstance(UMaterialInstanceConstant* InMaterialInstance)`
- L208 _public function_ `UMaterialInstanceConstant* GetMaterialInstance() const`
- L209 _public prototype_ `void SetChannelData(TConstArrayView<uint8> InChannelTable, const FVector2f& InTexcoordDesc);`
- L210 _public prototype_ `void SetChannelTexture(UTexture* InChannelTexture);`
- L211 _public function_ `UTexture* GetChannelTexture()`
- L212 _public function_ `const TArray<uint8>& GetChannelTable() const`
- L213 _public prototype_ `void UpdateVirtualTextureSettings();`
- L214 _public prototype_ `void SetupChannelDataOnChildPrimitiveComponents();`
- L216 _public prototype_ `void SetMaterialCacheTileCount(const FIntPoint& TileCount);`
- L217 _public prototype_ `void RecreateMaterialCacheTextures();`
- L222 _public function_ `const MeshPartition::FCompiledSectionBuildInfo& GetBuildInfo() const` — Get/Set the Build info, describing the build and settings that produced this compiled section
- L223 _public function_ `void SetBuildInfo(const MeshPartition::FCompiledSectionBuildInfo& InBuildInfo)`
- L226 _public function_ `void SetIsPlaceholder(bool bInIsPlaceholder)`
- L227 _public function_ `void SetPlaceholderStreamingBounds(const FBox& Bounds)`
- L228 _public function_ `bool IsPlaceholder() const`
- L230 _public prototype_ `bool ShouldBeLoadedForPlatform(const class ITargetPlatform* TargetPlatform) const;`
- L233 _public prototype_ `void SetRuntimeVirtualTextures(const TArray<TObjectPtr<URuntimeVirtualTexture>>& InRVTs);`
- L236 _private prototype_ `void ForAllPrimitiveComponents(TFunctionRef<bool(UPrimitiveComponent*)> InFunc) const;`
- L240 _private member_ `TArray<TObjectPtr<UMeshPartitionStaticMeshComponent>> MeshComponents;` — `UPROPERTY(VisibleAnywhere, Category="MeshPartition")`
- L243 _private member_ `TArray<TObjectPtr<UMeshPartitionCollisionComponent>> CollisionComponents;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")`
- L247 _private member_ `TArray<TObjectPtr<UStaticMeshComponent>> VirtualTextureFallbackMeshComponents;` — `UPROPERTY()` — Fallback component for virtual texture rendering, this is a stop-gap solution, will be removed later
- L250 _private member_ `TObjectPtr<UStaticMeshComponent> FarFieldMeshComponent;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")`
- L253 _private member_ `TSoftObjectPtr<AMeshPartition> Parent;` — `UPROPERTY()`
- L256 _private member_ `TObjectPtr<UMaterialInstanceConstant> MaterialInstance;` — `UPROPERTY()`
- L259 _private member_ `TObjectPtr<UTexture> ChannelTexture;` — `UPROPERTY(EditAnywhere, Category = "Rendering")`
- L262 _private member_ `MeshPartition::FCompiledSectionBuildInfo BuildInfo;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition", meta = (NoResetToDefault))`
- L265 _private member_ `FVector2f ChannelTexcoordDesc;` — `UPROPERTY()`
- L268 _private member_ `TArray<uint8> ChannelTable;` — `UPROPERTY()`
- L271 _private member_ `FIntPoint MaterialCacheTileCount = FIntPoint(1, 1);` — `UPROPERTY()`
- L275 _private member_ `TArray<TObjectPtr<UMaterialCacheVirtualTexture>> MaterialCacheTextures;` — `UPROPERTY(Experimental)` — All allocated material cache textures
- L280 _private member_ `bool bIsPlaceholder = false;` — `UPROPERTY()` — Indicate that this compiled section was created during PIE to be a placeholder for a missing compiled section, that needs to be built on the fly.
- L283 _private member_ `FBox PlaceholderStreamingBounds;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPARTITION_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MeshPartition` (scope `UE`)
- L31 _namespace_ `namespace MegaMeshCompiledSectionProperties` (scope `UE::MeshPartition`)
- L33 _externvar_ `extern const FName MegaMeshCompiledSectionVersion;` (scope `UE::MeshPartition::MegaMeshCompiledSectionProperties`) — Version number
- L34 _externvar_ `extern const int32 CurrentVersion;` (scope `UE::MeshPartition::MegaMeshCompiledSectionProperties`) — Current Version
- L35 _externvar_ `extern const FName CurrentVersionFName;` (scope `UE::MeshPartition::MegaMeshCompiledSectionProperties`) — Current Version
- L288 _prototype_ `DEFINE_ACTORDESC_TYPE(UE::MeshPartition::ACompiledSection, UE::MeshPartition::FCompiledSectionActorDesc);`

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionCompiledSectionActorDesc.h` (Public)


#### class `UE::MeshPartition::FCompiledSectionActorDesc`  
`class FCompiledSectionActorDesc : public FWorldPartitionActorDesc`  
_L16-36_
- inherits: `FWorldPartitionActorDesc`
- desc: ActorDesc for MegaMeshCompiledSection
- L19 _public function_ `const MeshPartition::FCompiledSectionBuildInfo& GetBuildInfo() const`
- L22 _public prototype_ `static const FCompiledSectionActorDesc* GetFromActorDescInstance(const FWorldPartitionActorDescInstance& InActorDescInstance);` — may return null if the actor desc is an older one before the custom ActorDesc for compiled sections was introduced
- L26 _protected prototype_ `virtual void Init(const AActor* InActor) override;`
- L27 _protected prototype_ `virtual bool Equals(const FWorldPartitionActorDesc* Other) const override;`
- L28 _protected function_ `virtual uint32 GetSizeOf() const override`
- L29 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L30 _protected prototype_ `virtual const FGuid& GetSceneOutlinerParent() const override;`
- L35 _private member_ `MeshPartition::FCompiledSectionBuildInfo BuildInfo;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionCompilerInterface.h` (Public)


#### class `UE::MeshPartition::IMeshPartitionCompilerInterface`  
`class IMeshPartitionCompilerInterface`  
_L13-41_
- L16 _public prototype_ `static IMeshPartitionCompilerInterface* Get();`
- L22 _public prototype_ `virtual void BuildPlaceholderCompiledSection(MeshPartition::ACompiledSection* CompiledSection) = 0;` — Called to request a placeholder compiled section to be built. (may be built asynchronously, not immediately before return)
- L28 _public prototype_ `static void RegisterMegaMeshCompiler(IMeshPartitionCompilerInterface* Compiler);` — Globally register the megamesh compiler used to build compiled sections. (the compiler is in the editor package, but the placeholder needs to invoke it in runtime code)
- L33 _public prototype_ `static void UnregisterMegaMeshCompiler(IMeshPartitionCompilerInterface* Compiler);` — Globally unregister the megamesh compiler used to build compiled sections.
- L37 _protected prototype_ `~IMeshPartitionCompilerInterface();` — destructor protected and non-virtual so that you can't delete an derived class via a pointer to this interface
- L40 _private member_ `static IMeshPartitionCompilerInterface* RegisteredCompiler;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MESHPARTITION_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionComponent.h` (Public)


#### class `UE::MeshPartition::UMeshPartitionComponent`  
`class UMeshPartitionComponent : public UPrimitiveComponent`  
_L24-38_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(MeshPartition))`
- inherits: `UPrimitiveComponent`
- desc: Base class for a component of AMeshPartition actor. This is a component to be able to be stripped during the cook process. This should contain common interfaces between runtime and editor, but also allows to implement the differences only useful for specific modes.
- L29 _public prototype_ `UMeshPartitionComponent();`
- L31 _public function_ `virtual void PostRegisterMegaMeshComponents()`
- L32 _public function_ `virtual void PostUnregisterMegaMeshComponents()`
- L37 _public function_ `virtual void OnDefinitionChanged(UMeshPartitionDefinition* InNewDefinition)` — Callback called when the owner's currently used UMeshPartitionDefinition changed.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHPARTITION_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionDataLayerContainer.h` (Public)


#### struct `UE::MeshPartition::FPerBuildVariantDataLayers`  
`struct FPerBuildVariantDataLayers`  
_L18-25_
- reflection: `USTRUCT()`
- L24 _public member_ `TMap<FName, TObjectPtr<UDataLayerAsset>> Layers;` — `UPROPERTY(EditAnywhere, Category = "DataLayer")` — Build variant name to data layer.

#### class `UE::MeshPartition::AMeshPartitionDataLayerContainer`  
`class AMeshPartitionDataLayerContainer : public AActor`  
_L28-72_
- reflection: `UCLASS(MinimalAPI, NotPlaceable)`
- inherits: `AActor`
- L32 _public prototype_ `AMeshPartitionDataLayerContainer();`
- L34 _public prototype_ `static AMeshPartitionDataLayerContainer* Get(const UWorld* InWorld);`
- L36 _public prototype_ `static AMeshPartitionDataLayerContainer* GetOrCreate(UWorld* InWorld);`
- L42 _public prototype_ `bool UpdateDataLayersFromDefinition(const UMeshPartitionDefinition* InDefinition);` — Update the internal list of data layers based on build variants in the definition. @return true if the internal data layer list changed.
- L45 _public prototype_ `bool IsDataLayerOwnedByContainer(const UDataLayerAsset* InDataLayer) const;`
- L46 _public prototype_ `bool IsDataLayerRelevantForPlatform(const UDataLayerAsset* InDataLayer, ITargetPlatform* InTargetPlatform) const;`
- L48 _public prototype_ `TObjectPtr<UDataLayerAsset> FindVariantDataLayer(const UMeshPartitionDefinition* InDefinition, const FName& InBuildVariant) const;`
- L54 _public prototype_ `bool InitializeDataLayerInstancesWithWorld(const UMeshPartitionDefinition* InDefinition) const;` — Creates data layer instances for all internal data layer assets. @return true if new data layer instances were created.
- L55 _public prototype_ `void RemoveDataLayerInstancesFromWorld() const;`
- L57 _public prototype_ `void ClearAllDataLayers();`
- L64 _public prototype_ `int32 PruneUnusedDefinitions(const TSet<const UMeshPartitionDefinition*>& InUsedDefinitions);` — Remove entries for definitions that are no longer in use, plus any entries with null/stale definition keys. Data layer instances for removed entries are deleted from the world. @return number of entries removed (0 means the container was not modified).
- L67 _private prototype_ `UDataLayerAsset* NewVariantDataLayer(const FName& InVariantName);`
- L71 _private member_ `TMap<TObjectPtr<const UMeshPartitionDefinition>, MeshPartition::FPerBuildVariantDataLayers> PerDefinitionBuildVariantDataLayers;` — `UPROPERTY(EditAnywhere, Category = "DataLayer")`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionDefinition.h` (Public)


#### struct `UE::MeshPartition::FCommonBuildVariant`  
`struct FCommonBuildVariant`  
_L37-55_
- reflection: `USTRUCT()`
- L43 _public member_ `double MaxSectionComplexity = 256.0 * 256.0 * 4.0;` — `UPROPERTY(EditAnywhere, Category = "Build Variant")`
- L47 _public member_ `TObjectPtr<MeshPartition::UTransformerPipeline> TransformerPipeline;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L53 _protected prototype_ `void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const;`

#### struct `UE::MeshPartition::FCompiledSectionBuildVariant`  
`struct FCompiledSectionBuildVariant : public FCommonBuildVariant`  
_L58-74_
- reflection: `USTRUCT()`
- inherits: `FCommonBuildVariant`
- L64 _public member_ `FName Name = NAME_Default;` — `UPROPERTY(EditAnywhere, Category="Build Variant")`
- L67 _public member_ `bool bSplitSectionsToMatchWorldPartitionRuntimeGrid = false;` — `UPROPERTY(EditAnywhere, Category = "WorldPartition")`
- L72 _protected prototype_ `void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const;`

#### struct `UE::MeshPartition::FRuntimeSettings`  
`struct FRuntimeSettings`  
_L77-90_
- reflection: `USTRUCT()`
- L82 _public prototype_ `void PostSerialize(const FArchive& InAr);`
- L86 _public member_ `TArray<FName> BuildVariantNames;` — `UPROPERTY(EditAnywhere, Category = "Runtime Settings", meta=(GetOptions="GetCompiledSectionBuildVariantOptions"))`
- L89 _public member_ `FName BuildVariantName_DEPRECATED;` — `UPROPERTY(meta=(GetOptions="GetCompiledSectionBuildVariantOptions", DeprecatedProperty, DeprecationMessage="Use BuildVariantNames instead"))`

#### struct `UE::MeshPartition::FPerPlatformRuntimeSettings`  
`struct FPerPlatformRuntimeSettings #if CPP : public TPerPlatformProperty<FPerPlatformRuntimeSettings, MeshPartition::FRuntimeSettings, NAME_StructProperty> #endif`  
_L93-108_
- reflection: `USTRUCT()`
- inherits: `TPerPlatformProperty<FPerPlatformRuntimeSettings,MeshPartition::FRuntimeSettings,NAME_StructProperty>`
- L102 _public member_ `MeshPartition::FRuntimeSettings Default;` — `UPROPERTY(EditAnywhere, Category = PerPlatform)`
- L106 _public member_ `TMap<FName, MeshPartition::FRuntimeSettings> PerPlatform;` — `UPROPERTY(EditAnywhere, Category = PerPlatform)`

#### struct `UE::MeshPartition::FPhysicalMaterialChannel`  
`struct FPhysicalMaterialChannel`  
_L111-125_
- reflection: `USTRUCT()`
- L118 _public member_ `MeshPartition::FChannelName ChannelName;` — `UPROPERTY(EditAnywhere, Category = Physics, meta = (GetOptions = "GetChannelNames"))` — The channel to associate with a physical material.
- L121 _public member_ `TObjectPtr<UPhysicalMaterial> Material;` — `UPROPERTY(EditAnywhere, Category = Physics)`
- L124 _public member_ `float MinimumCollisionRelevanceWeight = 0.0f;` — `UPROPERTY(EditAnywhere, Category = Physics, Meta = (ClampMin = "0", ClampMax = "1", Tooltip = "The minimum weight for a channel to be picked up as the dominant physical layer."))`

#### class `UE::MeshPartition::UMeshPartitionDefinition`  
`class UMeshPartitionDefinition : public UDataAsset, public IMaterialEnumerationProvider`  
_L137-304_
- reflection: `UCLASS(MinimalAPI, meta=(MegaMeshClassVersion = "1"))`
- inherits: `UDataAsset,IMaterialEnumerationProvider`
- desc: Asset holding shared properties and settings for all components in a MegaMesh. MegaMeshClassVersion is used to track changes in the behavior of this class with respect to building sections. It is used, along with GatherDependencies, when determining whether existing sections are up to date, or need to be rebuilt. It should be bumped whenever code behavior changes in a way that affects how existing sections would be built. NOTE: Changing the MegaMeshClassVersion here invalidates ALL compiled sections (they all use this class).
- L141 _private prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDefinitionModified, const FName&, const FName&);`
- L144 _public prototype_ `UMeshPartitionDefinition();`
- L145 _public prototype_ `virtual ~UMeshPartitionDefinition();`
- L148 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject Implementation
- L149 _public prototype_ `virtual void PostLoad() override;`
- L151 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L155 _public function_ `UMaterialInterface* GetMaterial() const`
- L157 _public function_ `FOnDefinitionModified& GetOnDefinitionModified()`
- L160 _public function_ `const TArray<FName>& GetModifierTypePriorities() const` — `UFUNCTION(BlueprintCallable, Category = "Modifiers")`
- L162 _public function_ `static bool IsMaterialPropertyName(const FName& InName)`
- L164 _public prototype_ `static const class UMeshPartitionDefinition* GetDefaultMegaMeshDefinition();`
- L166 _public prototype_ `static bool DoesPropertyNameRequireRebuild(const FName& InMemberName, const FName& InName);`
- L168 _public prototype_ `TConstArrayView<MeshPartition::FCompiledSectionBuildVariant> GetCompiledSectionBuildVariants() const;`
- L170 _public function_ `MeshPartition::FChannelMap& GetChannelMap()`
- L171 _public function_ `const MeshPartition::FChannelMap& GetChannelMap() const`
- L174 _public function_ `TArray<FName> GetChannelNames() const` — `UFUNCTION(CallInEditor)`
- L176 _public function_ `float GetChannelTexelSize() const`
- L177 _public function_ `float GetMaterialCacheTexelSize() const`
- L178 _public function_ `EChannelCollectionUVLayoutMethod GetChannelUVLayoutMethod() const`
- L180 _public function_ `float GetChannelVEUVSamplesPerSquareMeter() const`
- L182 _public function_ `FIntVector GetChannelVEUVVoxelCount() const`
- L183 _public function_ `EPlaneProjectionNormalSource GetChannelPlaneProjectionNormalSource() const`
- L184 _public function_ `FVector GetChannelPlaneProjectionFixedNormal() const`
- L186 _public function_ `const TArray<FPhysicalMaterialChannel>& GetPhysicalMaterialChannels() const`
- L187 _public function_ `UPhysicalMaterial* GetDefaultPhysicalMaterial() const`
- L190 _public prototype_ `virtual bool ResolveValue(FName EntryName, int32& OutValue, int32 DefaultValue = 0) const override;` — Enumerarion Provider Interface
- L191 _public prototype_ `virtual void ForEachEntry(TFunctionRef<void(FName Name, int32 Value)> Iterator) const override;`
- L196 _public prototype_ `TArray<FName> GetCompiledSectionBuildVariantNamesForCurrentEditorPreview(const FName& InPreviewPlatformName, ITargetPlatform* PreviewPlatform) const;` — Get the set of build variants to use in PIE for the specified preview platform. If no preview platform is specified, returns the build variant for the current platform.
- L199 _public prototype_ `TArray<FName> GetCompiledSectionBuildVariantNamesForPlatforms(TArray<ITargetPlatform*> TargetPlatforms) const;` — Get the set of build variants needed for the specified target platforms
- L202 _public prototype_ `TArray<FName> GetCompiledSectionBuildVariantNamesForPlatform(const FName& InPlatformName, const FName& InIniPlatformName) const;` — Note that the platform name includes build type like "WindowsClient", while the IniPlatformName is just the platform "Windows".  It looks for PlatformName match first, then if not found it looks for IniPlatformName
- L203 _public prototype_ `TArray<FName> GetCompiledSectionBuildVariantNamesForPlatform(const ITargetPlatform* TargetPlatform) const;`
- L204 _public prototype_ `TArray<FName> GetAllCompiledSectionBuildVariantNames() const;`
- L206 _public prototype_ `const MeshPartition::FCompiledSectionBuildVariant& GetCompiledSectionBuildVariantByName(const FName& BuildVariantName) const;`
- L207 _public function_ `const MeshPartition::FCommonBuildVariant& GetPreviewSectionBuildVariant() const`
- L208 _public prototype_ `void SetPreviewSectionBuildVariant(const MeshPartition::FCommonBuildVariant& InNewPreviewBuildVairant);`
- L211 _public prototype_ `void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies, FName InBuildVariantName) const;` — return a hash of all the settings that affect the compiled section results - FILTERED to only those used by the BuildVariant
- L215 _private function_ `TArray<FString> GetCompiledSectionBuildVariantOptions() const` — `UFUNCTION()`
- L227 _private prototype_ `void OnObjectModified(UObject* InObject);`
- L233 _private member_ `FOnDefinitionModified OnDefinitionModified;`
- L237 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category = "Material")`
- L240 _private member_ `TArray<FName> ModifierTypePriorities;` — `UPROPERTY(EditAnywhere, Category = "Modifiers", meta=(DisplayName="Modifier Layer Priorities"))`
- L243 _private member_ `TArray<MeshPartition::FCompiledSectionBuildVariant> CompiledSectionBuildVariants;` — `UPROPERTY(EditAnywhere, Category = "Build", meta=(TitleProperty="Name"))`
- L246 _private member_ `MeshPartition::FPerPlatformRuntimeSettings PerPlatformRuntimeSettings;` — `UPROPERTY(EditAnywhere, Category = "Build|Platforms")`
- L249 _private member_ `MeshPartition::FChannelMap ChannelMap;` — `UPROPERTY(EditAnywhere, Category = "Material", meta=(ShowOnlyInnerProperties))`
- L257 _private member_ `float ChannelTexelSize = 100.0;` — `UPROPERTY(EditAnywhere, Category = "Material", meta=(ClampMin="0.05"))` — Channel Texel Size controls the resolution of rasterization of the textures capturing the channel signal. It is the width of an ideal texel in world units. Default is 100 units (1 texel per meter). A higher number produces coarser channel textures. A smaller number produces more expensive channel textures.
- L260 _private member_ `float MaterialCacheTexelSize = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Material", meta=(ClampMin="0.05"))`
- L264 _private member_ `EChannelCollectionUVLayoutMethod ChannelUVLayoutMethod = EChannelCollectionUVLayoutMethod::ReferenceBoxProject;` — `UPROPERTY(EditAnywhere, Category = "Material", meta=(DisplayName="Channel UV Layout Method"))` — Algorithm used to unwrap section UVs when rasterizing channel textures.
- L270 _private member_ `float ChannelVEUVSamplesPerSquareMeter = 0.025f;` — `UPROPERTY(EditAnywhere, Category = "Material|Experimental VEUV Controls", meta=(EditCondition="ChannelUVLayoutMethod == EChannelCollectionUVLayoutMethod::VolumeEncoded", EditConditionHides, ClampMin="0.001", DisplayName="VEUV Samples Per Square Meter"))` — Target sample count per square meter of section surface area
- L276 _private member_ `FIntVector ChannelVEUVVoxelCount = FIntVector(4, 4, 1);` — `UPROPERTY(EditAnywhere, Category = "Material|Experimental VEUV Controls", meta=(EditCondition="ChannelUVLayoutMethod == EChannelCollectionUVLayoutMethod::VolumeEncoded", EditConditionHides, ClampMin="1", ClampMax="16", DisplayName="VEUV Voxel Count"))` — Voxel grid dimensions
- L282 _private member_ `EPlaneProjectionNormalSource ChannelPlaneProjectionNormalSource = EPlaneProjectionNormalSource::FixedPlane;` — `UPROPERTY(EditAnywhere, Category = "Material|Plane Projection", meta=(EditCondition="ChannelUVLayoutMethod == EChannelCollectionUVLayoutMethod::PlaneProject", EditConditionHides, DisplayName="Plane Projection Normal Source"))` — Source of the projection-plane normal: the section's area-weighted average triangle normal, or a fixed direction below.
- L288 _private member_ `FVector ChannelPlaneProjectionFixedNormal = FVector(0.0, 0.0, 1.0);` — `UPROPERTY(EditAnywhere, Category = "Material|Plane Projection", meta=(EditCondition="ChannelUVLayoutMethod == EChannelCollectionUVLayoutMethod::PlaneProject && ChannelPlaneProjectionNormalSource == EPlaneProjectionNormalSource::FixedPlane", EditConditionHides, DisplayName="Plane Projection Fixed Normal"))` — Fixed plane normal used when ChannelPlaneProjectionNormalSource is FixedPlane. Need not be unit length; normalized at use.
- L291 _private member_ `TArray<FPhysicalMaterialChannel> PhysicalMaterialChannels;` — `UPROPERTY(EditAnywhere, Category = "Material|Physics")`
- L294 _private member_ `TObjectPtr<UPhysicalMaterial> DefaultPhysicalMaterial;` — `UPROPERTY(EditAnywhere, Category = "Material|Physics")`
- L297 _private member_ `MeshPartition::FCommonBuildVariant PreviewSectionBuildVariant;` — `UPROPERTY(EditAnywhere, Category = "Preview")`
- L301 _private member_ `TArray<MeshPartition::FCompiledSectionBuildVariant> BuildVariants_DEPRECATED;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<UE::MeshPartition::FRuntimeSettings> : public TStructOpsTypeTraitsBase2<UE::MeshPartition::FRuntimeSettings>`  
_L308-314_
- inherits: `TStructOpsTypeTraitsBase2<UE::MeshPartition::FRuntimeSettings>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L311-313_

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MESHPARTITION_API`
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace MeshPartition` (scope `UE`)
- L33 _externvar_ `const extern FName ChannelTextureParameterName;` (scope `UE::MeshPartition`)
- L34 _externvar_ `const extern int32 PrimitiveDataIndex;` (scope `UE::MeshPartition`)
- L141 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDefinitionModified, const FName&, const FName&);`
- L312 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonffbedcc40103`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionDependencyInterface.h` (Public)


#### enum `UE::MeshPartition::EDependencyFlags`  
`enum class EDependencyFlags`  
_L21-25_
- L23 _public enumerator_ `None = 0` — don't add any sub-dependencies of the specified object or package
- L24 _public enumerator_ `RecurseOnPackageDependencies = 1` — automatically add any package dependencies of the specified object or package (and recurse on those)

#### struct `UE::MeshPartition::IDependencyInterface`  
`struct IDependencyInterface`  
_L27-101_
- L29 _public function_ `virtual ~IDependencyInterface()`
- L30 _public prototype_ `virtual void AddPackageDependency(const UObject* InObject, MeshPartition::EDependencyFlags InDependencyFlags = MeshPartition::EDependencyFlags::None) = 0;`
- L31 _public prototype_ `virtual void AddPackageDependency(TArrayView<UObject*> InObjectArray) = 0;`
- L32 _public prototype_ `virtual void AddClassDependency(const UClass* InClass) = 0;`
- L35 _public prototype_ `virtual FArchive& GetDependentDataArchive() = 0;` — use this archive to do custom serialization for dependent data, if necessary
- L39 _public prototype_ `virtual void operator += (const UDynamicMesh& InMesh) = 0;` — prebuilt custom dependent data serialization functions for commonly used data these take advantage of existing hashes if possible
- L40 _public prototype_ `virtual void operator += (const UStaticMesh& InMesh) = 0;`
- L41 _public prototype_ `virtual void operator += (const UTexture& InTexture) = 0;`
- L42 _public prototype_ `virtual void operator += (const UTexture2D& InTexture) = 0;`
- L43 _public prototype_ `virtual void operator += (const UCurveFloat& InTexture) = 0;`
- L44 _public prototype_ `virtual void operator += (const USplineComponent& InSpline) = 0;`
- L45 _public prototype_ `virtual void operator += (const UObject& InObject) = 0;`
- L49 _public function_ `template<typename T> void operator += (const TObjectPtr<T> InObjectPtr)` — pointer dependencies are assumed to be pointing to data dependencies
- L58 _public function_ `template<typename T> void operator += (const T* InDataPtr)`
- L67 _public function_ `template<typename T> void operator += (T* InDataPtr)`
- L77 _public function_ `template<typename T> void operator += (const T& Data)` — for any other types, we just serialize it to our dependent data hasher
- L84 _public function_ `template<typename T> void operator += (T& Data)`
- L92 _public function_ `template <typename T> void AddUStructDependencyViaReflection(const T& DataStruct)` — adds a dependency on the USTRUCT reflected properties of DataStruct. NOTE: this cannot handle reference types, any pointer/ref properties in the struct will result in a compile error.

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionGridSettings.h` (Public)


#### struct `UE::MeshPartition::FGridSettings`  
`struct FGridSettings`  
_L21-44_
- reflection: `USTRUCT(BlueprintType)`
- desc: Grid configuration: cell size, 2D-vs-3D mode, and grid origin offset. Used everywhere a mesh is split on a regular grid -- WP-aligned compiled sections, complexity-driven subsection splits, and PIE placeholders. Hashed in field-declaration order via GatherDependencies; new attributes (padding, ...) extend this struct rather than threading parallel parameters.
- L27 _public member_ `uint32 CellSize = 0;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — Cell size in unreal units. 0 means "no grid splitting" (single-section path).
- L31 _public member_ `bool bIs2D = false;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — True when the grid collapses Z into a single column per X/Y cell (matches WP runtime LHGrid Is2D).
- L37 _public member_ `FVector WorldOriginOffset = FVector::ZeroVector;` — `UPROPERTY(VisibleAnywhere, Category = "MeshPartition")` — World-space anchor of the grid (typically FFixedGridInfo::Origin). Consumers must shift by the MeshPartition actor's LocalToWorld translation before snapping mesh-local bounds -- see GridHelpers::ComputeLocalAnchor.
- L41 _public function_ `bool IsGridSplit() const` — True when the grid is configured for grid-aligned splitting (CellSize > 0). CellSize == 0 means "no grid" (single-section path, or WP grid resolution failed).
- L43 _public prototype_ `void GatherDependencies(IDependencyInterface& InOutDependencies) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MeshPartition` (scope `UE`)
- L46 _prototype_ `FArchive& operator<<(FArchive& Ar, FGridSettings& InOutSettings);` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionMaterialCacheCommon.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MeshPartition` (scope `UE`)
- L9 _prototype_ `bool IsMaterialCacheEnabled(UWorld* World);` (scope `UE::MeshPartition`)
- L11 _prototype_ `void UpdateMaterialCacheTextures( class USceneComponent* Owner, class UMaterialInterface* Material, const FIntPoint& TileCount, TArray<TObjectPtr<UMaterialCacheVirtualTexture>>& Textures );` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionMeshData.h` (Public)


#### class `UE::MeshPartition::FMeshData`  
`class FMeshData`  
_L17-599_
- L20 _public member_ `static constexpr int16 INVALID_REF_COUNT = -1;`
- L21 _public member_ `static constexpr int32 MAX_SOURCE_UV_CHANNELS = 7;`
- L22 _public member_ `static constexpr int32 CHANNEL_UV_INDEX = 0;`
- L23 _public member_ `static constexpr int32 NUM_CHANNEL_UVS = 1;`
- L24 _public member_ `static constexpr int32 SOURCE_UV_OFFSET = 1;`
- L26 _public function_ `void Copy(const FMeshData& InOther)`
- L31 _public function_ `void Clear()`
- L46 _public function_ `void Reset()`
- L134 _public function_ `FIndexRange VertexIndicesItr() const`
- L139 _public function_ `inline int32 MaxVertexID() const`
- L144 _public function_ `inline FIndexRange TriangleIndicesItr() const`
- L149 _public function_ `inline void GetTriVertices(int InTriangleID, FVector& InA, FVector& InB, FVector& InC) const`
- L158 _public function_ `inline FVector3d GetVertex(int InVertexID) const`
- L164 _public function_ `inline FVector3d& GetVertex(int InVertexID)`
- L170 _public function_ `inline void SetVertex(int InVertexID, const FVector3d& InNewVertexPos)`
- L176 _public prototype_ `int AppendVertex(const FVector3d& InPosition);`
- L178 _public function_ `inline void RemoveVertex(int InVertexID)`
- L187 _public function_ `inline int VertexCount() const`
- L193 _public function_ `void ReserveAdditionalVertices(SIZE_T InAdditionalNum)` — Reserves space in the internal data structures for InAdditionalNum additional vertices.
- L213 _public function_ `inline bool IsVertex(int InVertexID) const`
- L218 _public function_ `inline bool HasTriangle(int InVertexID) const`
- L224 _public function_ `inline Geometry::FIndex3i GetTriangle(int InTriangleID) const`
- L230 _public function_ `inline Geometry::FIndex3i& GetTriangle(int InTriangleID)`
- L236 _public function_ `inline bool IsTriangle(int TriangleID) const`
- L241 _public function_ `inline int TriangleCount() const`
- L247 _public function_ `inline int MaxTriangleID() const`
- L252 _public prototype_ `int AppendTriangle(const Geometry::FIndex3i& InTriangle);`
- L254 _public function_ `void RemoveTriangle(int TriangleID, bool bRemoveUnusedVertices)`
- L271 _public function_ `void ReserveAdditionalTriangles(SIZE_T InAdditionalNum)` — Reserves space in the internal data structures for InAdditionalNum additional triangles.
- L278 _public function_ `inline void SetVertexUV(int InVertexID, const FVector2f& InUV, int32 InUVChannelIndex)`
- L285 _public function_ `inline void SetVertexNormal(int InVertexID, const FVector3f& InNormal)`
- L291 _public function_ `TArray<FName> GetWeightLayerNames() const`
- L302 _public function_ `bool HasWeightLayer(const FName& InWeightLayerName) const`
- L307 _public function_ `void InitializeWeightLayer(const FName& InWeightLayerName)`
- L313 _public function_ `inline TArray<float> GetWeightLayerValues(const FName& InWeightLayerName, TConstArrayView<int> InVertexIDs) const`
- L328 _public function_ `void SetWeightLayerValues(const FName& InWeightLayerName, TConstArrayView<int> InVertexIDs, TConstArrayView<float> InWeightLayerValues)`
- L344 _public function_ `void SetWeightLayerValue(const FName& InWeightLayerName, int InVertexID, float Value)`
- L350 _public function_ `const TArray<float>& GetWeightLayerValues(const FName& InWeightLayerName) const`
- L355 _public function_ `float GetWeightLayerValue(const FName& InWeightLayerName, int InVertexID) const`
- L361 _public function_ `int GetBaseID(int InTriangleID) const`
- L367 _public function_ `void SetBaseID(int InTriangleID, int InBaseID)`
- L373 _public prototype_ `void RecomputeNormals(const bool bRequireDeterministicNormals = true);`
- L374 _public function_ `void RecomputeTangents()`
- L379 _public prototype_ `void SummarizeUVRegion();`
- L381 _public function_ `FBox2f GetUVRegion() const`
- L386 _public function_ `FVector3f GetVertexNormal(int InVertexID) const`
- L392 _public prototype_ `FVector3d GetTriNormal(int InTriangleID) const;`
- L394 _public function_ `inline FVector2f GetVertexUV(int InVertexID, int32 InUVChannelIndex) const`
- L401 _public function_ `inline FVector2f GetChannelUV(int InVertexID) const`
- L407 _public function_ `inline void SetChannelUV(int InVertexID, const FVector2f& InUV)`
- L413 _public function_ `inline int32 GetNumSourceUVChannels() const`
- L418 _public function_ `inline int32 GetNumUVChannels() const`
- L423 _public function_ `void SetNumSourceUVChannels(int32 InNumChannels)`
- L434 _public function_ `void GrowSourceUVChannelsTo(int32 InNumChannels)`
- L444 _public function_ `inline int32 GetChangeStamp() const`
- L450 _public function_ `bool CheckValidity() const`
- L473 _public prototype_ `Geometry::FAxisAlignedBox3d GetBounds(bool bParallel = true) const;`
- L481 _public prototype_ `void Serialize(FArchive& Ar);`
- L495 _public prototype_ `void MergeVertexPairs(TConstArrayView<TPair<int, int>> InMergePairs, TOptional<TConstArrayView<int>> InTriangleFilter);` — Merge pairs of vertices, mapping all indices in triangles from the discarded vertex to the kept vertex. Any attributes on the discarded vertex are simply discarded and only the attributes on the kept vertex remain. This function is optimized for performance and does not support or validate that the list of merge pairs does not contain duplicates, or that the same vertex does not map to two separate kept vertices. These constraints are left up to the caller to ensure. @param InMergePairs List of pairs of merges in the format {KeepVID, DiscardVID}. @param InTriangleFilter Optional parameter which reduces the subset of triangles which could possibly be modified when fixing triangle indices. This improves the performance as the VID -> TriangleID map is restricted.
- L506 _public prototype_ `void AppendDynamicMesh(const Geometry::FDynamicMesh3& InOtherMesh, const FTransform& InRelativeTransform, int InNewBaseID = INDEX_NONE, TSet<int>* OutMergeBoundaryVertices = nullptr);` — Merges a dynamic mesh into this Mega Mesh, transfering all uvs, normals, and weight channels. @param InNewBaseID optional parameter. If valid, new triangles appended will have this base id assigned to them. @param OutMergeBoundaryVertices Optional output parameter. If non-null, all boundary vertices from the input mesh are added to the set. This is useful since the primary purpose of this function is to merge base meshes, and callers may want to use these vertices to apply a weld step after appending. Since this structure doesn't store explicit edge information, using the input dynamic mesh to derive a set of edge boundary vertices allows the weld step to be fast as it doesn't need to recompute any of this information.
- L513 _public prototype_ `void WeldCoincidentVertices(TConstArrayView<TPair<int, int>> InVertexSourcePairs);` — Weld coincident vertices from within a subset of mesh vertices. Only considers vertices which are within the passed set and only welds vertices from different sources. @param InVertexSourcePairs pairs of {VertexID, SourceID}.
- L515 _public prototype_ `void ConvertToDynamicMesh(Geometry::FDynamicMesh3& OutDynamicMesh) const;`
- L516 _public prototype_ `void ConvertToMeshDescription(FMeshDescription& OutMeshDescription) const;`
- L518 _public prototype_ `bool ConvertToTriMeshCollisionData(FTriMeshCollisionData* CollisionData) const;`
- L521 _public prototype_ `static FGuid GetVersionKey();` — Returns a static version key for this mesh format. Increment this if the serialized mesh data format changes.
- L523 _public function_ `SIZE_T GetByteCount() const`
- L556 _protected function_ `template <typename T> static void ReserveGeometric(TArray<T>& InArray, typename TArray<T>::SizeType InNewSize)` — Reserves additional elements in an array while respecting geometric growth factors. This ensures that calling Reserve incrementally while appending data does not invoke a new memory allocation every single time. This has a measurable performance impact when a lot of topology modifiers are inserting new geometry into the mesh.
- L571 _private member_ `TArray<FVector3d> Vertices;`
- L576 _private member_ `TArray<int16> VertexRefCount;` — Ref count keeping track of number of triangles which reference each vertex this is used to determine if a vertex should be removed if the last owning triangle is removed.
- L578 _private member_ `TArray<Geometry::FIndex3i> Triangles;`
- L580 _private member_ `TArray<FVector3f> Normals;`
- L583 _private member_ `TArray<TArray<FVector2f>> SourceUVChannels;` — Source UVs from imported mesh (passed through modifier pipeline)
- L586 _private member_ `TArray<FVector2f> ChannelUVs;` — Auto-generated channel rendering UVs (separate, not passed to modifiers)
- L588 _private member_ `TMap<FName, TArray<float>> WeightLayers;`
- L590 _private member_ `FBox2f UVRegion = FBox2f(FVector2f::Zero(), FVector2f::One());`
- L593 _private member_ `TArray<int> BaseIDLayer;` — per triangle
- L595 _private member_ `TArray<int16> TriangleRefCount;` — Refcount which acts as a boolean if this triangle is valid or not. INVALID_REF_COUNT if unused, 1 otherwise.
- L597 _private member_ `TArray<int> FreeVertices;`
- L598 _private member_ `TArray<int> FreeTriangles;`

#### struct `UE::MeshPartition::FMeshData::IndexIterator`  
`struct IndexIterator`  
_L61-112_
- L63 _public function_ `inline bool operator==(const IndexIterator& InOther) const`
- L67 _public function_ `inline bool operator!=(const IndexIterator& InOther) const`
- L72 _public function_ `inline int operator*() const`
- L77 _public function_ `inline IndexIterator& operator++()` — prefix
- L82 _public function_ `inline IndexIterator operator++(int)` — postfix
- L89 _public function_ `IndexIterator(TConstArrayView<int16> InRefCounts, int InIndex, int InLength) : RefCounts(InRefCounts) , Index(InIndex) , Length(InLength)`
- L100 _private function_ `void Next()`
- L109 _private member_ `const TConstArrayView<int16> RefCounts;`
- L110 _private member_ `int Index = 0;`
- L111 _private member_ `int Length = 0;`

#### struct `UE::MeshPartition::FMeshData::FIndexRange`  
`struct FIndexRange`  
_L114-132_
- L116 _public function_ `FIndexRange(TConstArrayView<int16> InRefCounts, int InLength) : RefCounts(InRefCounts) , Length(InLength)`
- L121 _public function_ `IndexIterator begin()`
- L125 _public function_ `IndexIterator end()`
- L130 _public member_ `TConstArrayView<int16> RefCounts;`
- L131 _public member_ `int Length = 0;`

#### struct `UE::MeshPartition::FSectionChannelGenerationMeshData`  
`struct FSectionChannelGenerationMeshData`  
_L605-613_
- desc: Simple mesh data representation used during the generation of the channel textures Used by the Preview Section in order to inspect the channel texture.
- L607 _public member_ `TArray<int32> Indices;`
- L608 _public member_ `TArray<FVector2f> Texcoords;`
- L609 _public member_ `TArray<float> Channels;`
- L610 _public member_ `TArray<FInt32Vector3> Outlines;`
- L611 _public member_ `TArray<int32> UVElementToVertexID;`
- L612 _public member_ `int32 VertexCount;`

#### struct `UE::MeshPartition::FSectionChannelDomainData`  
`struct FSectionChannelDomainData`  
_L615-620_
- L617 _public member_ `double Area3D;`
- L618 _public member_ `double AreaUV;`
- L619 _public member_ `double GutterUV;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshPartition` (scope `UE`)
- L475 _function_ `friend FArchive& operator<<(FArchive& Ar, FMeshData& Mesh)` (scope `UE::MeshPartition`)
- L601 _typedef_ `using FMeshABBTree3 = Geometry::TMeshAABBTree3<FMeshData>;` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionModifierBlueprintInterfaces.h` (Public)


#### class `UE::MeshPartition::UModifierBlueprintInterface`  
`class UModifierBlueprintInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(NotBlueprintable)`
- inherits: `UInterface`

#### class `UE::MeshPartition::IModifierBlueprintInterface`  
`class IModifierBlueprintInterface`  
_L22-30_
- desc: This interface exists in a non-editor module to allow some functions to be called in blueprints that do not derive from an editor-only class.
- L29 _public prototype_ `virtual void BP_SetAffectedMegaMesh(AMeshPartition* InMegaMesh) = 0;` — `UFUNCTION(BlueprintCallable, Category = "MeshPartitionModifier", meta = (DisplayName = "Set Affected Mesh Partition"))`

#### class `UE::MeshPartition::USplineModifierBlueprintInterface`  
`class USplineModifierBlueprintInterface : public UInterface`  
_L34-37_
- reflection: `UINTERFACE(NotBlueprintable)`
- inherits: `UInterface`

#### class `UE::MeshPartition::ISplineModifierBlueprintInterface`  
`class ISplineModifierBlueprintInterface`  
_L39-47_
- L46 _public prototype_ `virtual void BP_SetSplineComponent(USplineComponent* InSplineComponent) = 0;` — `UFUNCTION(BlueprintCallable, Category = "Spline", meta = (DisplayName = "Set Spline Component"))`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionModule.h` (Public)


#### class `UE::MeshPartition::FMeshPartitionModule`  
`class FMeshPartitionModule : public IModuleInterface`  
_L12-18_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`

#### struct `UE::MeshPartition::FCustomVersion`  
`struct FCustomVersion`  
_L20-51_
- L50 _public member_ `const static FGuid GUID;`

#### enum `UE::MeshPartition::FCustomVersion::Type`  
`enum Type`  
_L22-48_
- L24 _public enumerator_ `BeforeCustomVersionWasAdded = 0`
- L25 _public enumerator_ `AddedMeshPartitionPathToBuildInfo = 1`
- L27 _public enumerator_ `DefaultPriorityLayerSetToNone = 2` — Default priority layer for mesh terrain modifiers was set to None
- L29 _public enumerator_ `SculptPriorityLayerSetToNone = 3` — Default priority layer for sculpt modifier (which was missed above) set to None
- L31 _public enumerator_ `BuildVariantCleanup = 4` — Split FCompiledSectionBuildVariant from FCommonBuildVariant so it can be used for defining preview builds
- L33 _public enumerator_ `AddedChecksumsToBuildInfo = 5` — Added debug checksums to the package and class hashes in the compiled section build infos
- L35 _public enumerator_ `AddedGridCellCoordToBuildInfo = 6` — Added GridCellCoord (FIntVector) and ResolvedGridCellSize to FCompiledSectionBuildInfo for WP-grid-aligned sections
- L37 _public enumerator_ `VirtualIsBaseModifier = 7` — Added a virtual method to identify modifiers as bases instead of relying on a named "Base" priority layer.
- L39 _public enumerator_ `ComponentToActorTransform = 8` — Store the component to actor relative transform in component descriptors rather than the component to world transform.
- L41 _public enumerator_ `Added2DFlagToBuildInfo = 9` — Added bIs2D flag to FCompiledSectionBuildInfo::GridSettings so 2D-grid-aware splits round-trip through serialization.
- L43 _public enumerator_ `AddedGridOriginToBuildInfo = 10` — Added FVector Origin to FCompiledSectionBuildInfo::GridSettings so WP-grid Origin offsets are honored during snap.
- L46 _public enumerator_ `LatestVersionPlusOne`
- L47 _public enumerator_ `LatestVersion = LatestVersionPlusOne - 1`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMegaMesh, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMegaMesh, Log, All);`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionSettings.h` (Public)


#### class `UE::MeshPartition::USettings`  
`class USettings : public UDeveloperSettings`  
_L17-27_
- reflection: `UCLASS(config = MeshPartition, defaultconfig, meta = (DisplayName = "Mesh Partition"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L22 _public function_ `TSoftObjectPtr<MeshPartition::UMeshPartitionDefinition> GetDefaultDefinition() const`
- L26 _protected member_ `TSoftObjectPtr<MeshPartition::UMeshPartitionDefinition> DefaultDefinition;` — `UPROPERTY(EditAnywhere, config, Category = "Definition", meta = (ToolTip = "Default Definition that will be used when creating new mesh partition actors."))`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MESHPARTITION_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionStaticMeshComponent.h` (Public)


#### class `UE::MeshPartition::UMeshPartitionStaticMeshComponent`  
`class UMeshPartitionStaticMeshComponent : public UStaticMeshComponent`  
_L15-25_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UStaticMeshComponent`
- L20 _public prototype_ `UMeshPartitionStaticMeshComponent(const FObjectInitializer& ObjectInitializer);`
- L23 _protected prototype_ `virtual void OnRegister() override;`
- L24 _protected prototype_ `virtual void OnUnregister() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MESHPARTITION_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionStaticMeshDescriptor.h` (Public)


#### struct `UE::MeshPartition::FStaticMeshDescriptor`  
`struct FStaticMeshDescriptor`  
_L8-15_
- L10 _public member_ `FName CollisionProfileName = NAME_None;`
- L12 _public member_ `bool bCanEverAffectNavigation = true;`
- L14 _public member_ `FBox2f UVRegion = FBox2f(FVector2f::Zero(), FVector2f::One());`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionTransformer.h` (Public)


#### struct `UE::MeshPartition::FTransformerUnit`  
`struct FTransformerUnit`  
_L25-31_
- L27 _public member_ `TWeakObjectPtr<AActor> Section;`
- L28 _public member_ `TSharedPtr<const MeshPartition::FMeshData> MeshData;`
- L29 _public member_ `bool bShouldRecomputeNormals = false;`
- L30 _public member_ `bool bShouldRecomputeTangents = false;`

#### struct `UE::MeshPartition::FTransformerContext`  
`struct FTransformerContext`  
_L39-47_
- L41 _public prototype_ `~FTransformerContext();`
- L43 _public member_ `TArray<TInstancedStruct<MeshPartition::FTransformer>> Transformers;`
- L44 _public member_ `TArray<MeshPartition::FTransformerUnit> TransformerUnits;`
- L45 _public member_ `UE::Tasks::FTask JoinTask;`
- L46 _public member_ `bool bWasCancelled = false;`

#### struct `UE::MeshPartition::FTransformer`  
`struct FTransformer`  
_L56-88_
- reflection: `USTRUCT()`
- desc: Parent struct for mesh partition transformers. Transformers are pipeline processors being executed sequentially to produce derived data associated with sections.
- L60 _public prototype_ `virtual ~FTransformer() = default;`
- L68 _public function_ `virtual void Initialize(const MeshPartition::UMeshPartitionDefinition* InDefinition, const MeshPartition::FCommonBuildVariant& InVariant)` — After intantiating the transformer. Initializes it with the definition in use. Useful if the transformer needs to capture members from the definition. @param InDefinition The definition in use. @param InVariant The build variant in use.
- L78 _public function_ `virtual bool Execute(MeshPartition::UPreviewMeshComponent& InPreviewMeshComponent, const MeshPartition::UMeshPartitionDefinition* InDefinition, const MeshPartition::FCommonBuildVariant& InBuildVariant) const` — Only used when building a preview section. Executes a transformer on a preview mesh component. This is a synchronous operation and should only be used to be able to render properly the preview mesh. Any expensive operation should be delayed until building proper derived data. @param InPreviewMeshComponent The preview component the transformer will be executed on. @param InDefinition The definition in use. @param InBuildVariant The build variant in use.
- L85 _public function_ `virtual bool Execute(MeshPartition::FTransformerContext& InTransformerContext) const` — Executes a transformers's payload. The execute method will be launched as a task by the editor component. @param InTransformerContext The context associated with this transformer. @return True if the execution succeeds.
- L87 _public function_ `virtual void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MESHPARTITION_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)
- L34 _prototype_ `FTransformerUnit MakeTransformerUnit(AActor* InSection, TSharedPtr<const FMeshData> InMesh, bool bInRecomputeNormals = true, bool bInRecomputeTangents = true);` (scope `UE::MeshPartition`) — Construct a transformer unit from a section actor and its mesh data.
- L37 _prototype_ `AActor* GetSectionChecked(const FTransformerUnit& InTransformerUnit);` (scope `UE::MeshPartition`) — Resolve the section actor from a transformer unit.
- L49 _prototype_ `void WaitOnGameThread(const FTransformerContext& InTransformerContext);` (scope `UE::MeshPartition`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionTransformerPipeline.h` (Public)


#### class `UE::MeshPartition::UTransformerPipeline`  
`class UTransformerPipeline : public UDataAsset`  
_L24-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: Asset describing a transformer pipeline. Can be used in mesh partition definition variants.
- L29 _public function_ `const TArray<TInstancedStruct<MeshPartition::FTransformer>>& GetTransformers() const`
- L32 _public prototype_ `void GatherDependencies(MeshPartition::IDependencyInterface& InDependencies) const;`
- L37 _private member_ `TArray<TInstancedStruct<MeshPartition::FTransformer>> Transformers;` — `UPROPERTY(EditAnywhere, Category = "Pipeline", Meta = (ExcludeBaseStruct))`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MEGAMESH_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/MeshPartitionUVLayoutMethod.h` (Public)


#### enum `UE::MeshPartition::EChannelCollectionUVLayoutMethod`  
`enum class EChannelCollectionUVLayoutMethod : uint8`  
_L13-23_
- reflection: `UENUM()`
- L16 _public enumerator_ `FastBoxProject = 1 UMETA(Hidden)` — A fast box-projection heuristic. May produce visible artifacts.
- L18 _public enumerator_ `ReferenceBoxProject = 2` — A reference box-projection implementation.
- L20 _public enumerator_ `VolumeEncoded = 3 UMETA(DisplayName = "Volume Encoded (VEUV)")` — Volume-encoded UVs produced by the VEUV plugin.
- L22 _public enumerator_ `PlaneProject = 4 UMETA(DisplayName = "Plane Project")` — Project all triangles onto a single plane.

#### enum `UE::MeshPartition::EPlaneProjectionNormalSource`  
`enum class EPlaneProjectionNormalSource : uint8`  
_L27-33_
- reflection: `UENUM()`
- desc: Source of the projection-plane normal for the PlaneProject UV layout method.
- L30 _public enumerator_ `AverageNormal` — Use the area-weighted average of the section's triangle normals.
- L32 _public enumerator_ `FixedPlane` — Use a fixed normal supplied by the asset.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/Modifiers/MeshPartitionProjectModifierTypes.h` (Public)


#### enum `UE::MeshPartition::EProjectModifierFalloffMode`  
`enum class EProjectModifierFalloffMode : uint8`  
_L20-25_
- reflection: `UENUM(BlueprintType)`
- L22 _public enumerator_ `Linear`
- L23 _public enumerator_ `Smooth`
- L24 _public enumerator_ `CustomCurve`

#### enum `UE::MeshPartition::EProjectModifierBlendMode`  
`enum class EProjectModifierBlendMode : uint8`  
_L28-44_
- reflection: `UENUM(BlueprintType)`
- L34 _public enumerator_ `Raise` — Only allow moving vertices in the positive Z direction in projection space, i.e. in the opposite direction of the projection raycast.
- L39 _public enumerator_ `Lower` — Only allow moving vertices in the negative Z direction in projection space, i.e. in the same direction as the projeciton raycast.
- L43 _public enumerator_ `Set` — Raise or lower the vertices as needed to get to the projected position.

#### enum `UE::MeshPartition::EProjectModifierChannelSourceMode`  
`enum class EProjectModifierChannelSourceMode : uint8`  
_L47-51_
- reflection: `UENUM()`
- L49 _public enumerator_ `VertexColor`
- L50 _public enumerator_ `VertexWeight`

#### struct `UE::MeshPartition::FProjectModifierFalloffSettings`  
`struct FProjectModifierFalloffSettings`  
_L54-90_
- reflection: `USTRUCT()`
- L63 _private member_ `MeshPartition::EProjectModifierFalloffMode Mode = MeshPartition::EProjectModifierFalloffMode::Smooth;` — `UPROPERTY(EditAnywhere, Category = Falloff)` — How effects of the modifier are decreased closer to the edges of the 2d projected bounds of the mesh.
- L71 _private member_ `float Distance = 0;` — `UPROPERTY(EditAnywhere, Category = Falloff, meta = (ClampMin = "0", UIMax = "2000"))` — Distance (in projected space) across which to fall off the modifier effects, applied inwards from the 2d rectangular bounds of the mesh projection, and only relevant where there was a potential value to write (e.g. a projection mesh was hit).
- L79 _private member_ `float CornerRadius = 0;` — `UPROPERTY(EditAnywhere, Category = Falloff, meta = (ClampMin = "0", UIMax = "2000"))` — When not 0, the 2d projected bounds used for falloff are considered to have rounded corners (clamped to half of the smallest dimension). This means that the bounds will be circular if the projected bounds were square and the corner radius is higher than half the width.
- L83 _private member_ `TObjectPtr<UCurveFloat> FalloffCurve = nullptr;` — `UPROPERTY(EditAnywhere, Category = Falloff, meta = ( EditCondition = "Mode == EProjectModifierFalloffMode::CustomCurve", EditConditionHides))`
- L85 _private member_ `FDelegateHandle FalloffCurveListenerHandle;`

#### struct `UE::MeshPartition::FProjectModifierWeightEntry`  
`struct FProjectModifierWeightEntry`  
_L93-143_
- reflection: `USTRUCT()`
- L101 _private member_ `MeshPartition::FChannelName ChannelName;` — `UPROPERTY(EditAnywhere, Category = Weight, meta = (GetOptions = "GetMegaMeshDefinitionChannels"))` — The destination attribute channel to write.
- L105 _private member_ `MeshPartition::EProjectModifierChannelSourceMode SourceMode = MeshPartition::EProjectModifierChannelSourceMode::VertexColor;` — `UPROPERTY(EditAnywhere, Category = Weight)` — Determines where the values to write are acquired.
- L110 _private member_ `int32 VertexColorIndex = 0;` — `UPROPERTY(EditAnywhere, Category = Weight, meta = (ClampMin = "0", ClampMax = "3", EditCondition = "SourceMode == EProjectModifierChannelSourceMode::VertexColor", EditConditionHides))` — Which channel of a vertex color to use as source data (0 through 3 for RGBA)
- L115 _private member_ `FName SourceWeightChannelName;` — `UPROPERTY(EditAnywhere, Category = Weight, meta = ( EditCondition = "SourceMode == EProjectModifierChannelSourceMode::VertexWeight", EditConditionHides))` — Vertex color channel name to use for the source data
- L118 _private member_ `MeshPartition::EProjectModifierBlendMode BlendMode = MeshPartition::EProjectModifierBlendMode::Set;` — `UPROPERTY(EditAnywhere, Category = Weight)`
- L122 _private member_ `TOptional<MeshPartition::FProjectModifierFalloffSettings> FalloffOverrides;` — `UPROPERTY(EditAnywhere, Category = Weight, Meta = (ShowOnlyInnerProperties))` — If set, the falloff settings for attributes will be different from the falloff settings used for positions
- L129 _private member_ `bool bApplyHeightMinMaxBlend = false;` — `UPROPERTY(EditAnywhere, Category = Weight)` — Only relevant when Raise or Lower blend mode is used for positions. When true, the weights are not applied in areas where the position data was ignored due to being above/below the current values in Raise/Lower blend mode.
- L138 _private member_ `double HeightMinMaxBlendDistance = 0.0;` — `UPROPERTY(EditAnywhere, Category = Weight, meta = (ClampMin = "0", UIMax = "1000", EditCondition = "bApplyHeightMinMaxBlend", EditConditionHides))` — When using "Apply Height Min Max Blend," this parameter sets the range of heights across which the weights will blend. If this parameter is equal to softness parameter, then heights blended by the softness parameter will also have their weights linearly blended.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshPartition` (scope `UE`)

### `Plugins/Experimental/MeshPartition/Source/MeshPartition/Public/Modifiers/MeshPartitionRemeshModifierTypes.h` (Public)


#### enum `EMegaMeshRemeshModifierBoundaryMode`  
`enum class EMegaMeshRemeshModifierBoundaryMode : uint8`  
_L8-20_
- reflection: `UENUM()`
- L13 _public enumerator_ `FullyConstrained` — The boundaries of the covered region are not modified in any way. If their edges are much longer than the target remeshed edges, this could result in sliver triangles, since the interior vertices still need to connect to long edges.
- L16 _public enumerator_ `SplitOnly` — Allow the boundary edges to be split, but otherwise do not move them.
- L19 _public enumerator_ `Free` — Allow the boundary to move freely, including by the smoothing steps.

#### enum `EMegaMeshRemeshModifierTessellateMethod`  
`enum class EMegaMeshRemeshModifierTessellateMethod : uint8`  
_L23-33_
- reflection: `UENUM()`
- L26 _public enumerator_ `UniformRings UMETA(DisplayName = "Uniform Rings (GLSL-style)")` — GLSL-style tessellation, uniformly increases resolution on all triangles within Modifier bounds
- L29 _public enumerator_ `AdaptiveRings UMETA(DisplayName = "Adaptive Rings (GLSL-style)")` — GLSL-style tessellation, resolution increases gradually towards Modifier center
- L32 _public enumerator_ `AdaptiveRegular UMETA(DisplayName = "Adaptive Regular (Red Green)")` — Adaptive Red-Green tessellation, resolution increases gradually towards Modifier center
