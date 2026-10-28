# Plugins / DisplayClusterMediaEditor

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterMediaEditor`
- headers: 4; symbols: 22
- symbol kinds: class=5, function=3, prototype=14
- PrivateDependencyModuleNames: AssetDefinition, Core, CoreUObject, DisplayClusterMedia, Engine, MediaIOCore, MediaIOEditor, SharedMemoryMedia, UnrealEd

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMediaEditor/Private/AssetDefinition/AssetDefinition_SharedMemoryMediaOutput.h` (Private)


#### class `UAssetDefinition_SharedMemoryMediaOutput`  
`class UAssetDefinition_SharedMemoryMediaOutput : public UAssetDefinition_MediaOutput`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_MediaOutput`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMediaEditor/Private/DisplayClusterMediaOutputSynchronizationPolicyFactories.h` (Private)


#### class `UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierFactory`  
`class UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierFactory : public UFactory`  
_L16-26_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Factory for UDisplayClusterMediaSynchronizationPolicyEthernetBarrier objects.
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L25 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

#### class `UDisplayClusterMediaOutputSynchronizationPolicyVblankFactory`  
`class UDisplayClusterMediaOutputSynchronizationPolicyVblankFactory : public UFactory`  
_L33-43_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- desc: Factory for UDisplayClusterMediaSynchronizationPolicyVblank objects.
- L40 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L41 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L42 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMediaEditor/Private/SharedMemoryMediaOutputFactory.h` (Private)


#### class `USharedMemoryMediaOutputFactory`  
`class USharedMemoryMediaOutputFactory : public UFactory`  
_L15-27_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for USharedMemoryMediaOutput objects.
- L21 _public prototype_ `USharedMemoryMediaOutputFactory();`
- L24 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L25 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L26 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMediaEditor/Private/SharedMemoryMediaSourceFactory.h` (Private)


#### class `USharedMemoryMediaSourceFactory`  
`class USharedMemoryMediaSourceFactory : public UFactory`  
_L13-27_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for USharedMemoryMediaSource objects.
- L20 _public prototype_ `USharedMemoryMediaSourceFactory();`
- L24 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L25 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L26 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
