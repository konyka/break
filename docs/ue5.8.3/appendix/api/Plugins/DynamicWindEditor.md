# Plugins / DynamicWindEditor

- module root: `Plugins/Experimental/DynamicWind/Source/DynamicWindEditor`
- headers: 4; symbols: 20
- symbol kinds: class=3, function=1, member=6, namespace=1, prototype=7, struct=2
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, Core, CoreUObject, EditorFramework, EditorStyle, Engine, ImageCore, Json, JsonUtilities, MeshDescription, PropertyEditor, RHI, SkeletalMeshDescription, Slate, SlateCore, SourceControl, StaticMeshDescription, TargetPlatform, UnrealEd
- PrivateIncludePathModuleNames: DerivedDataCache
- PublicDependencyModuleNames: DynamicWind, EditorSubsystem

### `Plugins/Experimental/DynamicWind/Source/DynamicWindEditor/Private/DynamicWindBlueprintLibrary.h` (Private)


#### class `UDynamicWindBlueprintLibrary`  
`class UDynamicWindBlueprintLibrary : public UObject`  
_L14-29_
- reflection: `UCLASS()`
- inherits: `UObject`
- L19 _private prototype_ `static bool ConvertPivotPainterTreeToSkeletalMesh( const UStaticMesh* TreeStaticMesh, UTexture2D* TreePivotPosTexture, int32 TreePivotUVIndex, USkeletalMesh* TargetSkeletalMesh, USkeleton* TargetSkeleton );` — `UFUNCTION(BlueprintCallable, Category="DynamicWind")`
- L28 _private prototype_ `static bool ImportDynamicWindSkeletalDataFromFile(USkeletalMesh* TargetSkeletalMesh);` — `UFUNCTION(BlueprintCallable, Category="DynamicWind")`

### `Plugins/Experimental/DynamicWind/Source/DynamicWindEditor/Private/DynamicWindEditorModule.h` (Private)


#### class `FDynamicWindEditorModule`  
`class FDynamicWindEditorModule : public IModuleInterface`  
_L11-22_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `static FDynamicWindEditorModule& GetModule();`

### `Plugins/Experimental/DynamicWind/Source/DynamicWindEditor/Public/DynamicWindFactory.h` (Public)


#### class `UDynamicWindDataFactory`  
`class UDynamicWindDataFactory : public UTransformProviderDataFactory`  
_L12-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTransformProviderDataFactory`
- L16 _private prototype_ `virtual bool ConfigureProperties() override;`
- L17 _private function_ `virtual bool ShouldShowInNewMenu() const override`

### `Plugins/Experimental/DynamicWind/Source/DynamicWindEditor/Public/DynamicWindImportData.h` (Public)


#### struct `FDynamicWindJointImportData`  
`struct FDynamicWindJointImportData`  
_L12-21_
- reflection: `USTRUCT()`
- L17 _public member_ `FName JointName;` — `UPROPERTY(EditAnywhere, Category = "Default")`
- L20 _public member_ `int32 SimulationGroupIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Default")`

#### struct `FDynamicWindSkeletalImportData`  
`struct FDynamicWindSkeletalImportData`  
_L24-39_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `TArray<FDynamicWindJointImportData> Joints;` — `UPROPERTY(EditAnywhere, Category = "SkeletalData")`
- L32 _public member_ `TArray<FDynamicWindSimulationGroupData> SimulationGroups;` — `UPROPERTY(EditAnywhere, Category = "SkeletalData")`
- L35 _public member_ `bool bIsGroundCover = false;` — `UPROPERTY(EditAnywhere, Category = "SkeletalData")`
- L38 _public member_ `float GustAttenuation = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "SkeletalData")`

#### Free symbols / members of external scopes

- L41 _namespace_ `namespace DynamicWind`
- L45 _prototype_ `UDynamicWindSkeletalData* ImportSkeletalData( USkeletalMesh& TargetSkeletalMesh, const FDynamicWindSkeletalImportData& ImportData );` (scope `DynamicWind`) — Attempts to create dynamic wind asset user data for a skeletal mesh with the given import data
