# Plugins / UAFChooserUncookedOnly

- module root: `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserUncookedOnly`
- headers: 1; symbols: 5
- symbol kinds: member=3, prototype=1, struct=1
- PrivateDependencyModuleNames: ChooserEditor, CoreUObject, Engine, UAF, UAFAnimGraph, UAFAnimGraphUncookedOnly, UAFEditor, UAFUncookedOnly, WorkspaceEditor
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/UAF/UAFChooser/Source/UAFChooserUncookedOnly/Public/UAFAnimChooserOutlinerData.h` (Public)


#### struct `FUAFChooserOutlinerItemData`  
`struct FUAFChooserOutlinerItemData : public FWorkspaceOutlinerItemData`  
_L9-23_
- reflection: `USTRUCT()`
- inherits: `FWorkspaceOutlinerItemData`
- L13 _public prototype_ `FUAFChooserOutlinerItemData() = default;`
- L16 _public member_ `FSoftObjectPath ObjectPath;` — `UPROPERTY()`
- L19 _public member_ `bool bIsNestedObject = false;` — `UPROPERTY()`
- L22 _public member_ `bool bExternalAsset = false;` — `UPROPERTY()`
