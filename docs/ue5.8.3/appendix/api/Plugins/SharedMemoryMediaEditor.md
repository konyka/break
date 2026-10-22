# Plugins / SharedMemoryMediaEditor

- module root: `Plugins/Runtime/nDisplay/Source/SharedMemoryMediaEditor`
- headers: 3; symbols: 16
- symbol kinds: class=3, function=3, member=1, prototype=9
- PrivateDependencyModuleNames: AssetDefinition, Core, CoreUObject, DisplayClusterModularFeaturesEditor, Engine, MediaPlayerEditor, SharedMemoryMedia, UnrealEd

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMediaEditor/Private/AssetDefinition/AssetDefinition_SharedMemoryMediaSource.h` (Private)


#### class `UAssetDefinition_SharedMemoryMediaSource`  
`class UAssetDefinition_SharedMemoryMediaSource : public UAssetDefinition_MediaSource`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaSource`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMediaEditor/Private/ModularFeatures/SharedMemoryMediaInitializerFeature.h` (Private)


#### class `FSharedMemoryMediaInitializerFeature`  
`class FSharedMemoryMediaInitializerFeature : public IDisplayClusterModularFeatureMediaInitializer`  
_L12-24_
- inherits: `IDisplayClusterModularFeatureMediaInitializer`
- desc: ShareMemory media source/output initializer for nDisplay
- L18 _public prototype_ `virtual bool IsMediaObjectSupported(const UObject* MediaObject) override;`
- L19 _public prototype_ `virtual bool AreMediaObjectsCompatible(const UObject* MediaSource, const UObject* MediaOutput) override;`
- L20 _public prototype_ `virtual bool GetSupportedMediaPropagationTypes(const UObject* MediaSource, const UObject* MediaOutput, EMediaStreamPropagationType& OutPropagationTypes) override;`
- L21 _public prototype_ `virtual void InitializeMediaObjectForTile(UObject* MediaObject, const FMediaObjectOwnerInfo& OnwerInfo, const FIntPoint& TilePos) override;`
- L22 _public prototype_ `virtual void InitializeMediaObjectForFullFrame(UObject* MediaObject, const FMediaObjectOwnerInfo& OnwerInfo) override;`

### `Plugins/Runtime/nDisplay/Source/SharedMemoryMediaEditor/Private/SharedMemoryMediaEditorModule.h` (Private)


#### class `FSharedMemoryMediaEditorModule`  
`class FSharedMemoryMediaEditorModule : public IModuleInterface`  
_L11-33_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _private prototype_ `void RegisterModularFeatures();` — Registers modular features for external modules
- L27 _private prototype_ `void UnregisterModularFeatures();` — Unregisters modular features
- L32 _private member_ `TUniquePtr<FSharedMemoryMediaInitializerFeature> MediaInitializer;` — MediaInitializer modular feature instance
