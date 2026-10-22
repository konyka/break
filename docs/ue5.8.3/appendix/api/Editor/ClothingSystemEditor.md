# Editor / ClothingSystemEditor

- module root: `Source/Editor/ClothingSystemEditor`
- headers: 3; symbols: 20
- symbol kinds: class=2, delegate=1, function=1, macro=1, namespace=3, prototype=12
- PrivateDependencyModuleNames: Engine, RenderCore
- PublicDependencyModuleNames: ClothingSystemEditorInterface, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, ClothingSystemRuntimeNv, ContentBrowser, Core, CoreUObject, EditorFramework, Slate, SlateCore, UnrealEd
- PublicIncludePathModuleNames: ClothingSystemEditorInterface, ClothingSystemRuntimeInterface, ClothingSystemRuntimeNv, Persona, UnrealEd

### `Source/Editor/ClothingSystemEditor/Public/ClothingAssetFactory.h` (Public)


#### class `UClothingAssetFactory`  
`class UClothingAssetFactory : public UClothingAssetFactoryBase`  
_L46-87_
- reflection: `UCLASS(MinimalAPI, hidecategories=Object)`
- inherits: `UClothingAssetFactoryBase`
- L52 _public prototype_ `UClothingAssetFactory(const FObjectInitializer& ObjectInitializer);`
- L54 _public prototype_ `virtual const UClass* GetSupportedSourceAssetType() const override;`
- L56 _public prototype_ `virtual TArray<UClothingAssetBase*> CreateFromSourceAsset(USkeletalMesh* TargetMesh, const UObject* SourceAsset) const override;`
- L58 _public prototype_ `virtual UClothingAssetBase* CreateFromSkeletalMesh(USkeletalMesh* TargetMesh, FSkeletalMeshClothBuildParams& Params) override;`
- L60 _public prototype_ `virtual UClothingAssetBase* ImportLodToClothing(USkeletalMesh* TargetMesh, FSkeletalMeshClothBuildParams& Params) override;`
- L64 _public function_ `virtual UClothingAssetBase* CreateFromExistingCloth(USkeletalMesh* TargetMesh, USkeletalMesh* SourceMesh, UClothingAssetBase* SourceAsset) override` — `UE_DEPRECATED(5.7, "Use CreateFromSupportedAsset instead.")` — Deprecated methods, cannot be removed because of them being virtual
- L80 _private prototype_ `UClothingAssetBase* CreateFromExistingCloth(USkeletalMesh* TargetMesh, const USkeletalMesh* SourceMesh, const UClothingAssetBase* SourceAsset) const;` — Given a target mesh and a source clothing asset bound to source mesh, clone the clothing asset for use on the target mesh @param TargetMesh - The mesh to target @param SourceMesh - The mesh to copy the clothing asset from @param SourceAsset - The clothing asset to copy
- L83 _private prototype_ `bool ImportToLodInternal(USkeletalMesh* SourceMesh, int32 SourceLodIndex, int32 SourceSectionIndex, UClothingAssetCommon* DestAsset, FClothLODDataCommon& DestLod, int32 DestLodIndex, const FClothLODDataCommon* InParameterRemapSource = nullptr);` — Handles internal import of LODs

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API CLOTHINGSYSTEMEDITOR_API`
- L27 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogClothingAssetFactory, Log, All);`
- L27 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogClothingAssetFactory, Log, All);`
- L32 _namespace_ `namespace nvidia`
- L34 _namespace_ `namespace apex` (scope `nvidia`)
- L40 _namespace_ `namespace NvParameterized`

### `Source/Editor/ClothingSystemEditor/Public/ClothingSystemEditorModule.h` (Public)


#### class `FClothingSystemEditorModule`  
`class FClothingSystemEditorModule : public IModuleInterface, public IClothingAssetFactoryProvider`  
_L11-25_
- inherits: `IModuleInterface,IClothingAssetFactoryProvider`
- L16 _public prototype_ `FClothingSystemEditorModule();`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `virtual UClothingAssetFactoryBase* GetFactory() override;`

### `Source/Editor/ClothingSystemEditor/Public/SimulationEditorExtenderNv.h` (Public)
_(no declarations extracted)_
