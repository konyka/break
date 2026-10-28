# Plugins / ChaosClothAssetUsdDataflowNodes

- module root: `Plugins/ChaosClothAssetUsdDataflowNodes/Source/ChaosClothAssetUsdDataflowNodes`
- headers: 3; symbols: 55
- symbol kinds: class=2, function=11, member=21, namespace=6, prototype=14, struct=1
- PrivateDependencyModuleNames: AssetTools, Chaos, ChaosClothAsset, ChaosClothAssetDataflowNodes, ChaosClothAssetEngine, ChaosClothAssetTools, Core, CoreUObject, DataflowCore, DataflowEditor, DataflowEngine, DesktopWidgets, Engine, MeshDescription, SlateCore, StaticMeshDescription, USDClasses, USDSchemas, USDStage, USDStageImporter, USDUtilities, UnrealEd, UnrealUSDWrapper
- PublicDependencyModuleNames: 

### `Plugins/ChaosClothAssetUsdDataflowNodes/Source/ChaosClothAssetUsdDataflowNodes/Private/ChaosClothAsset/ImportFilePathCustomization.h` (Private)


#### class `UE::Chaos::ClothAsset::FImportFilePathCustomization`  
`class FImportFilePathCustomization : public IPropertyTypeCustomization`  
_L17-36_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for import file path, modelled after FFilePathStructCustomization with the addition of a reimport button whenever a bForceReimport property is present in the customized struct.
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L23 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> , IDetailChildrenBuilder& , IPropertyTypeCustomizationUtils& ) override`
- L26 _private prototype_ `FReply OnClicked();`
- L28 _private prototype_ `FString HandleFilePathPickerFilePath() const;`
- L29 _private prototype_ `void HandleFilePathPickerPathPicked(const FString& PickedPath);`
- L31 _private member_ `TWeakPtr<const SDataflowGraphEditor> DataflowGraphEditor;`
- L32 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L33 _private member_ `TSharedPtr<IPropertyHandle> PathStringProperty;`
- L34 _private member_ `bool bLongPackageName;`
- L35 _private member_ `bool bRelativeToGameDir;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Chaos` (scope `UE`)
- L11 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)

### `Plugins/ChaosClothAssetUsdDataflowNodes/Source/ChaosClothAssetUsdDataflowNodes/Private/ChaosClothAsset/USDImportNode_v3.h` (Private)


#### struct `FChaosClothAssetUSDImportNode_v3`  
`struct FChaosClothAssetUSDImportNode_v3 : public FDataflowNode`  
_L15-107_
- reflection: `USTRUCT(Meta = (DataflowCloth))`
- inherits: `FDataflowNode`
- desc: Import a USD file from a third party garment construction software.
- L27 _public member_ `bool bImportSimMesh = true;` — `UPROPERTY(EditAnywhere, Category = "USD Import")` — Only import the simulation mesh data from the USD file.
- L31 _public member_ `bool bImportRenderMesh = true;` — `UPROPERTY(EditAnywhere, Category = "USD Import")` — Only import the render mesh data from the USD file.
- L35 _public member_ `bool bImportWithOpacity = false;` — `UPROPERTY(EditAnywhere, Category = "USD Import", Meta = (EditCondition = "bImportRenderMesh", EditConditionHides))` — Importing the render mesh with opacity requires transluscency to be enable in the project settings.
- L39 _public member_ `FChaosClothAssetImportFilePath UsdFile;` — `UPROPERTY(EditAnywhere, Category = "USD Import", Meta = (DisplayName = "USD File"))` — Path of the USD file to import.
- L43 _public member_ `FDataflowFunctionProperty ReimportUsdFile;` — `UPROPERTY(EditAnywhere, Category = "USD Import", Meta = (ButtonImage = "Persona.ReimportAsset", DisplayName = "Reimport USD File"))` — Click on this button to reimport the specified USD file and regenerate the intermediary assets.
- L47 _public member_ `FDataflowFunctionProperty ReloadSimStaticMesh;` — `UPROPERTY(EditAnywhere, Category = "USD Import", Meta = (ButtonImage = "Icons.Refresh", EditCondition = "ImportedSimStaticMesh != nullptr && bImportSimMesh", EditConditionHides))` — The USD import process generates an intermediary simulation static mesh. Click on this button to reimport it without reimporting the USD file.
- L51 _public member_ `FDataflowFunctionProperty ReloadRenderStaticMesh;` — `UPROPERTY(EditAnywhere, Category = "USD Import", Meta = (ButtonImage = "Icons.Refresh", EditCondition = "ImportedRenderStaticMesh != nullptr && bImportRenderMesh", EditConditionHides))` — The USD import process generates an intermediary render static mesh. Click on this button to reimport it without reimporting the USD file.
- L53 _public prototype_ `FChaosClothAssetUSDImportNode_v3(const UE::Dataflow::FNodeParameters & InParam, FGuid InGuid = FGuid::NewGuid());`
- L57 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext & Context, const FDataflowOutput * Out) const override;`
- L58 _private prototype_ `virtual void Serialize(FArchive & Archive) override;`
- L62 _private prototype_ `void ResetImport();` — Clear the imported data properties
- L64 _private prototype_ `bool ImportUsdFile_Schemaless(const FString & UsdPath, const FString & AssetPath, class FText& OutErrorText);` — Import USD data if provided in the original legacy schemaless USD format
- L66 _private prototype_ `bool ImportUsdFile(const FString & UsdPath, const FString & AssetPath, class FText& OutErrorText);` — Import USD data if provided with a valid cloth schema
- L69 _private prototype_ `bool ImportSimStaticMesh(const TSharedRef<FManagedArrayCollection> ClothCollection, class FText& OutErrorText);` — Import the given static mesh as a simulation mesh into the cloth collection
- L71 _private prototype_ `bool ImportRenderStaticMesh(const TSharedRef<FManagedArrayCollection> ClothCollection, class FText& OutErrorText);` — Import the given static mesh as a render mesh into the cloth collection
- L74 _private prototype_ `void UpdateImportedAssets(const FString & SimMeshName, const FString & RenderMeshName);` — Find the two imported static meshes
- L78 _private member_ `FString PackagePath;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — Content folder where all the USD assets are imported.
- L86 _private member_ `TObjectPtr<UStaticMesh> ImportedSimStaticMesh;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — The static mesh created from the USD import process used as simulation mesh. Note that this property can still be empty after successfully importing a simulation mesh depending on whether the simulation mesh is imported from an older version of USD cloth schema.
- L90 _private member_ `FVector2f ImportedUVScale = { 1.f, 1.f };` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — The UV scale used to import the patterns from the imported static mesh UV coordinates.
- L94 _private member_ `TObjectPtr<UStaticMesh> ImportedRenderStaticMesh;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — The static mesh created from the USD import process used as render mesh.
- L98 _private member_ `TArray<TObjectPtr<UObject>> ImportedSimAssets;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — List of all the simulation static mesh's dependent assets. This does not include any Engine, or Engine plugin content.
- L102 _private member_ `TArray<TObjectPtr<UObject>> ImportedRenderAssets;` — `UPROPERTY(VisibleAnywhere, Category = "USD Import")` — List of all the render static mesh's dependent assets. This does not include any Engine, or Engine plugin content.
- L106 _private member_ `FChaosClothAssetUsdClothData UsdClothData;` — `UPROPERTY()` — Support struct for storage of the extra data that doesn't fit inside a static mesh.

### `Plugins/ChaosClothAssetUsdDataflowNodes/Source/ChaosClothAssetUsdDataflowNodes/Private/ChaosClothAsset/UsdPrimAttributeAccessor.h` (Private)


#### class `UE::Chaos::ClothAsset::FUsdPrimAttributeAccessor`  
`class FUsdPrimAttributeAccessor`  
_L13-81_
- L16 _public function_ `explicit FUsdPrimAttributeAccessor(const FUsdPrim& InUsdPrim, const EUsdUpAxis UsdUpAxis = EUsdUpAxis::ZAxis) : UsdPrim(InUsdPrim) , AxesOrder( 0, (UsdUpAxis == EUsdUpAxis::ZAxis) ? 1 : 2, (UsdUpAxis == EUsdUpAxis::ZAxis) ? 2 : 1)`
- L26 _public function_ `template<typename ValueType> ValueType GetValue(const TCHAR* AttributeName, const ValueType DefaultValue = ValueType(0)) const`
- L42 _public function_ `template<typename ValueType> TArray<ValueType> GetArray(const TCHAR* AttributeName) const`
- L58 _public function_ `template<typename ValueType> ValueType GetArrayValue(const TCHAR* AttributeName, const ValueType DefaultValue = ValueType(0), const int32 ValueIndex = 0) const`
- L66 _private function_ `template<typename ValueType> ValueType GetValueAs(const FVtValue& VtValue, const ValueType DefaultValue = ValueType(0)) const`
- L73 _private function_ `template<typename ValueType> TArray<ValueType> GetArrayAs(const FVtValue& VtValue) const`
- L79 _private member_ `const FUsdPrim UsdPrim;`
- L80 _private member_ `const FIntVector AxesOrder;`
- L84 _function_ `template<> inline uint32 FUsdPrimAttributeAccessor::GetValueAs<uint32>(const FVtValue& VtValue, const uint32 DefaultValue) const`
- L90 _function_ `template<> inline float FUsdPrimAttributeAccessor::GetValueAs<float>(const FVtValue& VtValue, const float DefaultValue) const`
- L96 _function_ `template<> inline FVector3f FUsdPrimAttributeAccessor::GetValueAs<FVector3f>(const FVtValue& VtValue, const FVector3f DefaultValue) const`
- L113 _function_ `template<> inline TArray<float> FUsdPrimAttributeAccessor::GetArrayAs<float>(const FVtValue& VtValue) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Chaos` (scope `UE`)
- L11 _namespace_ `namespace ClothAsset` (scope `UE::Chaos`)
