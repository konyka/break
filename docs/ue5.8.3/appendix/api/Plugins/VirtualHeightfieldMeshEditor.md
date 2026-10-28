# Plugins / VirtualHeightfieldMeshEditor

- module root: `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMeshEditor`
- headers: 7; symbols: 32
- symbol kinds: class=6, function=4, member=2, namespace=1, prototype=19
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, RHI, RenderCore, Renderer, Slate, SlateCore, SourceControl, UnrealEd, VirtualHeightfieldMesh

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMeshEditor/Private/HeightfieldMinMaxTextureAssetTypeActions.h` (Private)


#### class `FAssetTypeActions_HeightfieldMinMaxTexture`  
`class FAssetTypeActions_HeightfieldMinMaxTexture : public FAssetTypeActions_Base`  
_L10-22_
- inherits: `FAssetTypeActions_Base`
- desc: Asset actions setup for UHeightfieldMinMaxTexture
- L13 _public function_ `FAssetTypeActions_HeightfieldMinMaxTexture()`
- L17 _protected prototype_ `virtual UClass* GetSupportedClass() const override;`
- L18 _protected prototype_ `virtual FText GetName() const override;`
- L19 _protected prototype_ `virtual FColor GetTypeColor() const override;`
- L20 _protected prototype_ `virtual uint32 GetCategories() override;`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMeshEditor/Private/HeightfieldMinMaxTextureBuild.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace VirtualHeightfieldMesh`
- L11 _prototype_ `bool HasMinMaxHeightTexture(UVirtualHeightfieldMeshComponent* InComponent);` (scope `VirtualHeightfieldMesh`) — Returns true if the component has a MinMax height texture.
- L14 _prototype_ `bool BuildMinMaxHeightTexture(UVirtualHeightfieldMeshComponent* InComponent);` (scope `VirtualHeightfieldMesh`) — Build the MinMax height texture.

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMeshEditor/Private/HeightfieldMinMaxTextureFactory.h` (Private)


#### class `UHeightfieldMinMaxTextureFactory`  
`class UHeightfieldMinMaxTextureFactory : public UFactory`  
_L10-18_
- reflection: `UCLASS(hidecategories = (Object))`
- inherits: `UFactory`
- desc: Factory for UHeightfieldMinMaxTexture
- L15 _private function_ `virtual bool ShouldShowInNewMenu() const`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMeshEditor/Private/HeightfieldMinMaxTextureThumbnailRenderer.h` (Private)


#### class `UHeightfieldMinMaxTextureThumbnailRenderer`  
`class UHeightfieldMinMaxTextureThumbnailRenderer : public UTextureThumbnailRenderer`  
_L9-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTextureThumbnailRenderer`
- L14 _private prototype_ `virtual bool CanVisualizeAsset(UObject* Object) override;`
- L15 _private prototype_ `virtual void Draw(UObject* Object, int32 X, int32 Y, uint32 Width, uint32 Height, FRenderTarget*, FCanvas* Canvas, bool bAdditionalViewFamily) override;`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMeshEditor/Private/VirtualHeightfieldMeshDetailsCustomization.h` (Private)


#### class `FVirtualHeightfieldMeshComponentDetailsCustomization`  
`class FVirtualHeightfieldMeshComponentDetailsCustomization : public IDetailCustomization`  
_L10-36_
- inherits: `IDetailCustomization`
- desc: UI customization for UVirtualHeightfieldMeshComponent
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _protected prototype_ `FVirtualHeightfieldMeshComponentDetailsCustomization();`
- L19 _protected prototype_ `void RefreshThumbnail();` — Callback for updating virtual texture thumbnail.
- L22 _protected prototype_ `FReply SetBounds();` — Callback for Set Bounds button
- L25 _protected prototype_ `bool IsMinMaxTextureEnabled() const;` — Returns true if MinMax texture build button is enabled
- L27 _protected prototype_ `FReply BuildMinMaxTexture();` — Callback for Build MinMax Texture button
- L30 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L34 _private member_ `class UVirtualHeightfieldMeshComponent* VirtualHeightfieldMeshComponent;`
- L35 _private member_ `TSharedRef<class FAssetThumbnail> AssetThumbnail;`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMeshEditor/Private/WorldPartitionVirtualHeightfieldMeshBuilder.h` (Private)


#### class `UWorldPartitionVirtualHeightfieldMeshBuilder`  
`class UWorldPartitionVirtualHeightfieldMeshBuilder : public UWorldPartitionBuilder`  
_L9-20_
- reflection: `UCLASS()`
- inherits: `UWorldPartitionBuilder`
- L15 _public function_ `virtual bool RequiresCommandletRendering() const override` — UWorldPartitionBuilder interface begin
- L16 _public function_ `virtual ELoadingMode GetLoadingMode() const override`
- L18 _protected prototype_ `virtual bool RunInternal(UWorld* World, const FCellInfo& InCellInfo, FPackageSourceControlHelper& PackageHelper) override;`

### `Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMeshEditor/Public/VirtualHeightfieldMeshEditorModule.h` (Public)


#### class `IVirtualHeightfieldMeshEditorModule`  
`class IVirtualHeightfieldMeshEditorModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- desc: Module interface for VirtualHeightfieldMesh editor  extensions.
- L12 _public prototype_ `virtual bool HasMinMaxHeightTexture(class UVirtualHeightfieldMeshComponent* InComponent) const = 0;` — Returns true if the component describes a runtime virtual texture that has streaming low mips.
- L14 _public prototype_ `virtual bool BuildMinMaxHeightTexture(class UVirtualHeightfieldMeshComponent* InComponent) const = 0;` — Build the contents of the streaming low mips.
