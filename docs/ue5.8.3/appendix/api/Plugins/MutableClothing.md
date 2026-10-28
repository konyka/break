# Plugins / MutableClothing

- module root: `Plugins/Experimental/MutableClothing/Source/MutableClothing`
- headers: 1; symbols: 7
- symbol kinds: class=1, macro=1, prototype=5
- PrivateDependencyModuleNames: ClothingSystemRuntimeCommon, Core, CoreUObject, Engine
- PublicDependencyModuleNames: CustomizableObject

### `Plugins/Experimental/MutableClothing/Source/MutableClothing/Private/MutableClothingModule.h` (Private)


#### class `FMutableClothingModule`  
`class FMutableClothingModule : public IMutableClothingModule`  
_L13-29_
- inherits: `IMutableClothingModule`
- L17 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L21 _public prototype_ `virtual bool UpdateClothSimulationLOD( int32 InSimulationLODIndex, UClothingAssetCommon& InOutClothingAsset, TConstArrayView<TArrayView<FMeshToMeshVertData>> InOutAttachedLODsRenderData) override;` — IMutableClothingModule interface
- L26 _public prototype_ `virtual void FixLODTransitionMappings( int32 InSimulationLODIndex, UClothingAssetCommon& InOutClothingAsset) override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MUTABLECLOTHING_API`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMutableClothing, Log, All);`
