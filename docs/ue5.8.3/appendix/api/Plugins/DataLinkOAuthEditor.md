# Plugins / DataLinkOAuthEditor

- module root: `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuthEditor`
- headers: 2; symbols: 12
- symbol kinds: class=2, member=1, prototype=9
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, ClassViewer, Core, CoreUObject, DataLinkOAuth, Engine, UnrealEd

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuthEditor/Private/AssetDefinition_DataLinkOAuthSettings.h` (Private)


#### class `UAssetDefinition_DataLinkOAuthSettings`  
`class UAssetDefinition_DataLinkOAuthSettings : public UAssetDefinitionDefault`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L16 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L17 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`

### `Plugins/VirtualProduction/DataLinkOAuth/Source/DataLinkOAuthEditor/Private/DataLinkOAuthSettingsFactory.h` (Private)


#### class `UDataLinkOAuthSettingsFactory`  
`class UDataLinkOAuthSettingsFactory : public UFactory`  
_L11-30_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L16 _public prototype_ `UDataLinkOAuthSettingsFactory();`
- L19 _public prototype_ `virtual FText GetDisplayName() const override;`
- L20 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L21 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L22 _public prototype_ `virtual bool ConfigureProperties() override;`
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`
- L29 _private member_ `TSubclassOf<UDataLinkOAuthSettings> OAuthSettingsClass;` — `UPROPERTY(EditAnywhere, Category="OAuth")` — The OAuth Settings Type to create
