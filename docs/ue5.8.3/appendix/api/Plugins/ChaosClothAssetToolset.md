# Plugins / ChaosClothAssetToolset

- module root: `Plugins/Experimental/Toolsets/ChaosClothAssetToolset/Source/ChaosClothAssetToolset`
- headers: 2; symbols: 13
- symbol kinds: class=2, function=1, member=3, prototype=6, struct=1
- PrivateDependencyModuleNames: ChaosClothAssetEditor, ChaosClothAssetEngine, ClothingSystemEditorInterface, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, CoreUObject, Engine, SkeletalMeshEditor, ToolsetRegistry, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/ChaosClothAssetToolset/Source/ChaosClothAssetToolset/Private/ChaosClothAsset/ChaosClothAssetConversionSkill.h` (Private)


#### class `UChaosClothAssetConversionSkill`  
`class UChaosClothAssetConversionSkill : public UAgentSkill`  
_L15-43_
- reflection: `UCLASS()`
- inherits: `UAgentSkill`
- desc: Agent skill that documents the end-to-end workflow for converting a legacy UClothingAssetCommon on a SkeletalMesh into a new UChaosClothAsset using the ChaosClothAsset toolset.
- L20 _public function_ `UChaosClothAssetConversionSkill()`

### `Plugins/Experimental/Toolsets/ChaosClothAssetToolset/Source/ChaosClothAssetToolset/Private/ChaosClothAsset/ClothAssetToolset.h` (Private)


#### struct `FClothingAssetInfo`  
`struct FClothingAssetInfo`  
_L14-36_
- reflection: `USTRUCT(BlueprintType)`
- desc: Information about a clothing asset on a skeletal mesh, returned by ListClothingAssets.
- L20 _public member_ `FString AssetName;` — `UPROPERTY()` — Name of the clothing asset. Pass to AssignClothingToSection.
- L28 _public member_ `bool bRequiresMatchingLodIndex = true;` — `UPROPERTY()` — If true, ClothingLodIndex passed to AssignClothingToSection must match the skeletal mesh LodIndex. This is the case for ChaosClothAsset-derived types. If false (UClothingAssetCommon), any value in [0, NumClothingLods-1] is valid.
- L35 _public member_ `int32 NumClothingLods = 0;` — `UPROPERTY()` — Number of LODs available in this clothing asset. Only relevant when bRequiresMatchingLodIndex is false.

#### class `UChaosClothAssetToolset`  
`class UChaosClothAssetToolset : public UToolsetDefinition`  
_L43-138_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UToolsetDefinition`
- desc: Provides tools for creating and assigning ChaosClothAsset clothing data to skeletal meshes. Replicates the workflow available via the SkeletalMesh Editor viewport context menu.
- L56 _public prototype_ `static TArray<FString> CreateClothingAsset( const FString& SkeletalMeshPath, const FString& ChaosClothAssetPath);` — `UFUNCTION(meta=(AICallable), Category = "ChaosClothAsset")` — Creates a UChaosClothAssetSKMClothingAsset from a Chaos Cloth/Outfit Asset and adds it to the skeletal mesh's clothing asset array, making it available to assign to sections. @param SkeletalMeshPath Object path to the target USkeletalMesh asset. @param ChaosClothAssetPath Object path to the source UChaosClothAssetBase (cloth or outfit asset). @return List of created clothing assets, or empty if failed.
- L76 _public prototype_ `static bool AssignClothingToSection( const FString& SkeletalMeshPath, const FString& ClothingAssetName, int32 LodIndex, int32 SectionIndex, int32 ClothingLodIndex);` — `UFUNCTION(meta=(AICallable), Category = "ChaosClothAsset")` — Binds a clothing asset to a specific LOD and section on the skeletal mesh. Mirrors the SkeletalMesh Editor's "Apply Clothing Data" action. Any clothing already bound to the section is unbound first. @param SkeletalMeshPath Object path to the target USkeletalMesh asset. @param ClothingAssetName Name of the Clothing Asset on the mesh (e.g., from CreateClothingAsset or ListClothingAssets). @param LodIndex Skeletal mesh LOD index to bind to. @param SectionIndex Section index within the LOD to bind to. @param ClothingLodIndex LOD index within the clothing asset to bind. For ChaosClothAsset-derived types (bRequiresMatchingLodIndex == true in ListClothingAssets), pass the same value as LodIndex. For UClothingAssetCommon, pass the desired clothing LOD (0 to NumClothingLods-1 as reported by ListClothingAssets). @return True if the binding succeeded.
- L92 _public prototype_ `static bool RemoveClothingFromSection( const FString& SkeletalMeshPath, int32 LodIndex, int32 SectionIndex);` — `UFUNCTION(meta=(AICallable), Category = "ChaosClothAsset")` — Removes the clothing binding from a specific LOD section on the skeletal mesh. Mirrors the SkeletalMesh Editor's "Remove Clothing Data" action. @param SkeletalMeshPath Object path to the target USkeletalMesh asset. @param LodIndex Skeletal mesh LOD index. @param SectionIndex Section index within the LOD. @return True if a binding was found and removed.
- L107 _public prototype_ `static TArray<FClothingAssetInfo> ListClothingAssets(const FString& SkeletalMeshPath);` — `UFUNCTION(meta=(AICallable), Category = "ChaosClothAsset")` — Returns information about all Clothing Assets on a skeletal mesh. Use AssetName with AssignClothingToSection. Check bRequiresMatchingLodIndex to determine how to supply ClothingLodIndex: - true  (ChaosClothAsset): pass the same value as LodIndex - false (UClothingAssetCommon): pass any value in [0, NumClothingLods-1] @param SkeletalMeshPath Object path to the target USkeletalMesh asset. @return Array of clothing asset info structs.
- L117 _public prototype_ `static FString GetSectionClothing( const FString& SkeletalMeshPath, int32 LodIndex, int32 SectionIndex);` — `UFUNCTION(meta=(AICallable), Category = "ChaosClothAsset")` — Returns the name of clothing bound for a specific LOD section (if any). @param SkeletalMeshPath Object path to the target USkeletalMesh asset. @param LodIndex Skeletal mesh LOD index. @param SectionIndex Section index within the LOD. @return The name of the clothing asset, or empty if none bound.
- L133 _public prototype_ `static FString ConvertClothingAssetCommonToChaosClothAsset( const FString& SkeletalMeshPath, const FString& ClothingAssetName, const FString& OutputPackagePath, const FString& AssetName);` — `UFUNCTION(meta=(AICallable), Category = "ChaosClothAsset")` — Converts a legacy UClothingAssetCommon (the cloth asset created via UChaosClothingSimulationFactory) into a new UChaosClothAsset whose embedded Dataflow graph mirrors the legacy UChaosClothConfig and UChaosClothSharedSimConfig values, with one WeightMap node per legacy weight map. @param SkeletalMeshPath  Object path to the USkeletalMesh that owns the legacy clothing asset. @param ClothingAssetName Name of the UClothingAssetCommon on the mesh (from ListClothingAssets). @param OutputPackagePath Folder where the new asset should be created (e.g. "/Game/Cloth/"). @param AssetName         Name of the new asset; empty for default ("CA_Converted_<source>"). @return Object path of the new UChaosClothAsset; empty on failure.
