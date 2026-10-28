# Plugins / UAFMirroringUncookedOnly

- module root: `Plugins/Experimental/UAF/UAFMirroring/Source/UAFMirroringUncookedOnly`
- headers: 1; symbols: 6
- symbol kinds: class=1, function=4, macro=1
- PrivateDependencyModuleNames: AnimationCore, Core, CoreUObject, Engine, RigVM, RigVMDeveloper, Slate, SlateCore, UAF, UAFAnimGraph, UAFAnimGraphUncookedOnly, UAFMirroring, UAFUncookedOnly

### `Plugins/Experimental/UAF/UAFMirroring/Source/UAFMirroringUncookedOnly/Private/UAFGraphNodeTemplate_Mirror.h` (Private)


#### class `UUAFGraphNodeTemplate_Mirror`  
`class UUAFGraphNodeTemplate_Mirror : public UUAFGraphNodeTemplate`  
_L18-111_
- reflection: `UCLASS()`
- inherits: `UUAFGraphNodeTemplate`
- L22 _private function_ `UUAFGraphNodeTemplate_Mirror()`
- L46 _private function_ `virtual void HandleAssetDropped_Implementation(UAnimNextController* Controller, URigVMUnitNode* Node, UObject* Asset) const`
- L69 _private function_ `virtual void HandlePinDefaultValueChanged_Implementation(UAnimNextController* Controller, URigVMPin* Pin) const`
- L91 _private function_ `virtual void HandleAssetRenamed_Implementation(UAnimNextController* Controller, URigVMNode* Node, const FAssetData& AssetData, const FString& OldName) const`

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "UAFGraphNodeTemplate_Mirror"`
