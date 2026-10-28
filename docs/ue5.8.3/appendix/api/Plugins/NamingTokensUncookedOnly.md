# Plugins / NamingTokensUncookedOnly

- module root: `Plugins/Developer/NamingTokens/Source/NamingTokensUncookedOnly`
- headers: 3; symbols: 14
- symbol kinds: class=2, member=1, namespace=5, prototype=6
- PrivateDependencyModuleNames: BlueprintGraph, Blutility, Core, CoreUObject, Engine, NamingTokens, UnrealEd

### `Plugins/Developer/NamingTokens/Source/NamingTokensUncookedOnly/Private/NamingTokensFactory.h` (Private)


#### class `UNamingTokensFactory`  
`class UNamingTokensFactory : public UFactory`  
_L11-19_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory`
- L16 _public prototype_ `UNamingTokensFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Developer/NamingTokens/Source/NamingTokensUncookedOnly/Private/NamingTokensUncookedOnlyModule.h` (Private)


#### class `FNamingTokensUncookedOnlyModule`  
`class FNamingTokensUncookedOnlyModule : public IModuleInterface`  
_L10-21_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void OnAssetAdded(const FAssetData& InAssetData);`
- L20 _private member_ `FDelegateHandle AssetAddedHandle;`

### `Plugins/Developer/NamingTokens/Source/NamingTokensUncookedOnly/Private/Utils/NamingTokensUncookedOnlyUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NamingTokens` (scope `UE`)
- L7 _namespace_ `namespace Utils` (scope `UE::NamingTokens`)
- L7 _namespace_ `namespace UncookedOnly` (scope `UE::NamingTokens::Utils`)
- L7 _namespace_ `namespace Private` (scope `UE::NamingTokens::Utils::UncookedOnly`)
- L10 _prototype_ `void SetupInitialBlueprint(UBlueprint* InBlueprint);` (scope `UE::NamingTokens::Utils::UncookedOnly::Private`) — Configure a new blueprint for Naming Token use.
