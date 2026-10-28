# Plugins / UAFStateTreeUncookedOnly

- module root: `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeUncookedOnly`
- headers: 5; symbols: 30
- symbol kinds: class=4, member=7, namespace=3, prototype=14, struct=2
- PrivateDependencyModuleNames: PropertyBindingUtils, RigVM, RigVMDeveloper, StateTreeEditorModule
- PublicDependencyModuleNames: Core, CoreUObject, Engine, SlateCore, StateTreeModule, UAF, UAFAnimGraph, UAFAnimGraphUncookedOnly, UAFAnimNode, UAFStateTree, UAFUncookedOnly, WorkspaceEditor

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeUncookedOnly/Internal/AnimNextStateTreeWorkspaceAssetUserData.h` (Internal)


#### class `UAnimNextStateTreeWorkspaceAssetUserData`  
`class UAnimNextStateTreeWorkspaceAssetUserData : public UAnimNextAnimGraphWorkspaceAssetUserData`  
_L11-21_
- reflection: `UCLASS()`
- inherits: `UAnimNextAnimGraphWorkspaceAssetUserData`
- L18 _protected prototype_ `virtual void GetRootAssetExport(FAssetRegistryTagsContext Context) const override;`
- L19 _protected prototype_ `virtual void GetWorkspaceAssetExports(FAssetRegistryTagsContext Context) const override;`

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeUncookedOnly/Internal/AnimNextStateTree_EditorData.h` (Internal)


#### class `UAnimNextStateTree_EditorData`  
`class UAnimNextStateTree_EditorData : public UUAFAnimGraph_EditorData`  
_L10-33_
- reflection: `UCLASS()`
- inherits: `UUAFAnimGraph_EditorData`
- L15 _protected prototype_ `virtual TSubclassOf<UAssetUserData> GetAssetUserDataClass() const override;`
- L21 _protected prototype_ `virtual void RecompileVM() override;` — IRigVMClientHost interface
- L24 _protected prototype_ `virtual TConstArrayView<TSubclassOf<UUAFRigVMAssetEntry>> GetEntryClasses() const override;` — UUAFRigVMAssetEditorData interface
- L25 _protected prototype_ `virtual void BuildFunctionHeadersContext(const FRigVMCompileSettings& InSettings, FAnimNextGetFunctionHeaderCompileContext& OutCompileContext) const override;`
- L26 _protected prototype_ `virtual void OnPreCompileGetProgrammaticGraphs(const FRigVMCompileSettings& InSettings, FAnimNextGetGraphCompileContext& OutCompileContext) override;`
- L27 _protected prototype_ `virtual void OnPostCompileVariables(const FRigVMCompileSettings& InSettings, const FAnimNextGetVariableCompileContext& InCompileContext) override;`
- L32 _private member_ `FInstancedPropertyBag CombinedVariablesPropertyBag;` — `UPROPERTY()` — Property bag that forms the root parameters. Consists of all combined variables from shared variable assets/structs.

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeUncookedOnly/Private/AnimNextStateTreeUncookedModule.h` (Private)


#### class `UE::UAF::StateTree::FAnimNextStateTreeUncookedModule`  
`class FAnimNextStateTreeUncookedModule : public IModuleInterface`  
_L11-13_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UAF` (scope `UE`)
- L8 _namespace_ `namespace StateTree` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeUncookedOnly/Public/AnimNextStateTreeEditorData.h` (Public)


#### class `UAnimNextStateTreeTreeEditorData`  
`class UAnimNextStateTreeTreeEditorData : public UStateTreeEditorData`  
_L14-29_
- reflection: `UCLASS()`
- inherits: `UStateTreeEditorData`
- L20 _public prototype_ `virtual void PostLoad() override;`
- L21 _public prototype_ `virtual const FInstancedPropertyBag& GetRootParametersPropertyBag() const override;`
- L22 _public prototype_ `virtual void CreateRootProperties(TArrayView<UE::PropertyBinding::FPropertyCreationDescriptor> InOutCreationDescs) override;`
- L26 _protected prototype_ `void HandleStateTreeAssetChanges(UUAFRigVMAssetEditorData* InEditorData, EAnimNextEditorDataNotifType InType, UObject* InSubject) const;`

### `Plugins/Experimental/UAF/UAFStateTree/Source/UAFStateTreeUncookedOnly/Public/AnimNextStateTreeWorkspaceExports.h` (Public)


#### struct `FAnimNextStateTreeOutlinerData`  
`struct FAnimNextStateTreeOutlinerData : public FAnimNextRigVMAssetOutlinerData`  
_L14-19_
- reflection: `USTRUCT()`
- inherits: `FAnimNextRigVMAssetOutlinerData`
- L18 _public prototype_ `FAnimNextStateTreeOutlinerData() = default;`

#### struct `FAnimNextStateTreeStateOutlinerData`  
`struct FAnimNextStateTreeStateOutlinerData : public FWorkspaceOutlinerItemData`  
_L22-45_
- reflection: `USTRUCT()`
- inherits: `FWorkspaceOutlinerItemData`
- L26 _public prototype_ `FAnimNextStateTreeStateOutlinerData() = default;`
- L29 _public member_ `FName StateName = NAME_None;` — `UPROPERTY()`
- L32 _public member_ `FGuid StateId;` — `UPROPERTY()`
- L35 _public member_ `bool bIsLeafState = true;` — `UPROPERTY()`
- L38 _public member_ `EStateTreeStateSelectionBehavior SelectionBehavior = EStateTreeStateSelectionBehavior::None;` — `UPROPERTY()`
- L41 _public member_ `EStateTreeStateType Type = EStateTreeStateType::State;` — `UPROPERTY()`
- L44 _public member_ `FSlateColor Color;` — `UPROPERTY()`
