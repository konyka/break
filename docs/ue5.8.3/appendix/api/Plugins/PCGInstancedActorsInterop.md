# Plugins / PCGInstancedActorsInterop

- module root: `Plugins/Experimental/PCGInterops/PCGInstancedActorsInterop/Source/PCGInstancedActorsInterop`
- headers: 3; symbols: 32
- symbol kinds: class=4, delegate=1, function=9, macro=1, member=5, prototype=12
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InstancedActors, PCG

### `Plugins/Experimental/PCGInterops/PCGInstancedActorsInterop/Source/PCGInstancedActorsInterop/Public/Elements/PCGSpawnInstancedActors.h` (Public)


#### class `UPCGSpawnInstancedActorsSettings`  
`class UPCGSpawnInstancedActorsSettings : public UPCGSettings`  
_L18-53_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Node that allows to spawn instanced actors. Important notes: - In some cases, the actor class must be properly registered in the project settings prior to spawning. See the Instanced Actor plugin documentation for more details. - It is not currently possible to create or remove instanced actors at runtime and will log errors/warnings accordingly. - The Instanced Actor plugin does not support the preview/load as preview workflow, and using this node in such a way will log errors/warnings.
- L25 _public function_ `virtual FName GetDefaultNodeName() const override`
- L26 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L27 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L28 _public function_ `virtual EPCGSettingsType GetType() const override`
- L32 _protected function_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override`
- L33 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L34 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L40 _public member_ `bool bSpawnByAttribute = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Controls whether the actor class to use will be driven by an attribute on the input data.
- L44 _public member_ `FPCGAttributePropertyInputSelector SpawnAttributeSelector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (EditCondition = "bSpawnByAttribute", EditConditionHides, PCG_Overridable))` — Attribute specifier for the attribute class to spawn.
- L48 _public member_ `TSubclassOf<AActor> ActorClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (EditCondition = "!bSpawnByAttribute", EditConditionHides, OnlyPlaceable, DisallowCreateNew, PCG_Overridable))` — Actor class to spawn when not using the 'Spawn by Attribute' mode.
- L52 _public member_ `bool bMuteOnEmptyClass = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Settings, meta = (PCG_Overridable))` — Mutes warnings on empty class, which can be useful when some points might not have a valid class.

#### class `FPCGSpawnInstancedActorsElement`  
`class FPCGSpawnInstancedActorsElement : public IPCGElement`  
_L55-64_
- inherits: `IPCGElement`
- L58 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* InContext) const override`
- L59 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L62 _protected function_ `virtual bool SupportsBasePointDataInputs(FPCGContext* InContext) const override`
- L63 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/PCGInterops/PCGInstancedActorsInterop/Source/PCGInstancedActorsInterop/Public/PCGInstancedActorsInteropModule.h` (Public)


#### class `FPCGInstancedActorsInteropModule`  
`class FPCGInstancedActorsInteropModule final : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- L14 _public function_ `virtual bool SupportsDynamicReloading() override`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGInstancedActorsInterop, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGInstancedActorsInterop, Log, All);`

### `Plugins/Experimental/PCGInterops/PCGInstancedActorsInterop/Source/PCGInstancedActorsInterop/Public/PCGInstancedActorsResource.h` (Public)


#### class `UPCGInstancedActorsManagedResource`  
`class UPCGInstancedActorsManagedResource : public UPCGManagedResource`  
_L14-41_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UPCGManagedResource`
- L20 _public prototype_ `virtual void PostEditImport() override;`
- L24 _public prototype_ `virtual bool Release(bool bHardRelease, TSet<TSoftObjectPtr<AActor>>& OutActorsToDelete) override;`
- L25 _public prototype_ `virtual bool ReleaseIfUnused(TSet<TSoftObjectPtr<AActor>>& OutActorsToDelete) override;`
- L26 _public prototype_ `virtual bool MoveResource(const FPCGMoveResourceParams& Params) override;`
- L27 _public prototype_ `virtual void MarkAsUsed() override;`
- L30 _public prototype_ `virtual void ChangeTransientState(EPCGEditorDirtyMode NewEditingMode) override;`
- L31 _public prototype_ `virtual void MarkTransientOnLoad() override;`
- L35 _public function_ `virtual bool MoveResourceToNewActor(AActor* NewActor) override` — `UE_DEPRECATED(5.8, "This has been replaced with MoveResource.")`
- L40 _public member_ `TArray<FInstancedActorsInstanceHandle> Handles;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = GeneratedData)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PCGINSTANCEDACTORSINTEROP_API`
