# Plugins / RigLogicUAFUncookedOnly

- module root: `Plugins/Experimental/RigLogicUAF/Source/RigLogicUAFUncookedOnly`
- headers: 2; symbols: 11
- symbol kinds: class=2, delegate=1, function=1, macro=1, namespace=2, prototype=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core, Engine, Projects, RigLogicModule, RigLogicUAF, UAF, UAFAnimGraph, UAFAnimGraphUncookedOnly

### `Plugins/Experimental/RigLogicUAF/Source/RigLogicUAFUncookedOnly/Public/RigLogicUAFUncookedOnly.h` (Public)


#### class `UE::UAF::FRigLogicModuleUncookedOnly`  
`class FRigLogicModuleUncookedOnly : public IModuleInterface`  
_L12-20_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `static const FSlateBrush& GetIcon();`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicUAFUncookedOnly, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicUAFUncookedOnly, Log, All);`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UAF` (scope `UE`)

### `Plugins/Experimental/RigLogicUAF/Source/RigLogicUAFUncookedOnly/Public/UAFGraphNodeTemplate_RigLogic.h` (Public)


#### class `UUAFGraphNodeTemplate_RigLogic`  
`class UUAFGraphNodeTemplate_RigLogic : public UUAFGraphNodeTemplate`  
_L16-51_
- reflection: `UCLASS()`
- inherits: `UUAFGraphNodeTemplate`
- L20 _private function_ `UUAFGraphNodeTemplate_RigLogic()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "UAFGraphNodeTemplate_RigLogic"`
