# Plugins / MutableAssetUserData

- module root: `Plugins/Experimental/MutableAssetUserData/Source/MutableAssetUserData`
- headers: 3; symbols: 12
- symbol kinds: class=1, member=3, prototype=6, struct=2
- PrivateDependencyModuleNames: CustomizableObject
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MutableRuntime

### `Plugins/Experimental/MutableAssetUserData/Source/MutableAssetUserData/Public/MeshAddAssetUserData.h` (Public)


#### struct `FMeshAddAssetUserData`  
`struct FMeshAddAssetUserData : public UE::Mutable::FExternalOperation`  
_L11-23_
- reflection: `USTRUCT(DisplayName = "Mesh Add Asset User Data")`
- inherits: `UE::Mutable::FExternalOperation`
- L15 _public prototype_ `virtual ~FMeshAddAssetUserData() override = default;`
- L16 _public prototype_ `virtual TArray<TPair<FText, const UScriptStruct*>> GetInputs() const override;`
- L17 _public prototype_ `virtual TPair<FText, const UScriptStruct*> GetOutput() const override;`
- L18 _public prototype_ `virtual void Evaluate(UE::Mutable::FContext& Context) const override;`
- L20 _public member_ `static const FText TextInputMesh;`
- L22 _public member_ `static const FText TextInputAssetUserData;`

### `Plugins/Experimental/MutableAssetUserData/Source/MutableAssetUserData/Public/MutableAssetUserData.h` (Public)


#### struct `FMutableAssetUserData`  
`struct FMutableAssetUserData`  
_L12-18_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "Asset User Data", PinColor = "#949494"))`
- L17 _public member_ `TObjectPtr<UAssetUserData> AssetUserData;` — `UPROPERTY(BlueprintReadWrite, Transient, Category = AssetUserData)`

### `Plugins/Experimental/MutableAssetUserData/Source/MutableAssetUserData/Public/MutableAssetUserDataModule.h` (Public)


#### class `FMutableAssetUserDataModule`  
`class FMutableAssetUserDataModule : public IModuleInterface`  
_L8-12_
- inherits: `IModuleInterface`
- L10 _private prototype_ `virtual void StartupModule() override;`
- L11 _private prototype_ `virtual void ShutdownModule() override;`
