# Plugins / ModelViewViewModelAssetSearch

- module root: `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelAssetSearch`
- headers: 1; symbols: 12
- symbol kinds: class=1, enum=1, enumerator=3, function=4, namespace=3
- PrivateDependencyModuleNames: InputCore, UMGEditor
- PublicDependencyModuleNames: AssetSearch, Core, CoreUObject, ModelViewViewModel, ModelViewViewModelBlueprint

### `Plugins/Runtime/ModelViewViewModel/Source/ModelViewViewModelAssetSearch/Private/MVVMAssetSearchIndexer.h` (Private)


#### class `UE::MVVM::Private::FAssetSearchIndexer`  
`class FAssetSearchIndexer : public IAssetIndexer`  
_L16-53_
- inherits: `IAssetIndexer`
- L29 _public function_ `virtual FString GetName() const override`
- L34 _public function_ `virtual int32 GetVersion() const override`
- L39 _public function_ `virtual void IndexAsset(const UObject* InAssetObject, FSearchSerializer& Serializer) const override`

#### enum `UE::MVVM::Private::FAssetSearchIndexer::EIndexerVersion`  
`enum class EIndexerVersion`  
_L19-26_
- L21 _public enumerator_ `Initial = 0`
- L24 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L25 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MVVM` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::MVVM`)
- L46 _function_ `FIndexerUtilities::IterateIndexableProperties(View, [&Serializer](const FProperty* Property, const FString& Value) { Serializer.IndexProperty(Property, Value); UE_LOGF(LogTemp, Warning, "--%ls [Serialized]", *Property->GetName()); });` (scope `UE::MVVM::Private::FAssetSearchIndexer::IndexAsset`)
