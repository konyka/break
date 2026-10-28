# Plugins / RivermaxSyncEditor

- module root: `Plugins/VirtualProduction/Rivermax/RivermaxSync/Source/RivermaxSyncEditor`
- headers: 1; symbols: 4
- symbol kinds: class=1, prototype=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, RivermaxSync, UnrealEd

### `Plugins/VirtualProduction/Rivermax/RivermaxSync/Source/RivermaxSyncEditor/Private/MediaOutputSynchronizationPolicyRivermaxFactory.h` (Private)


#### class `UMediaOutputSynchronizationPolicyRivermaxFactory`  
`class UMediaOutputSynchronizationPolicyRivermaxFactory : public UFactory`  
_L16-26_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- desc: Factory for UMediaOutputSynchronizationPolicyRivermax objects.
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L24 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L25 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
