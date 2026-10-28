# Plugins / UAFControlRigEditor

- module root: `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRigEditor`
- headers: 2; symbols: 33
- symbol kinds: class=2, member=7, namespace=9, prototype=15
- PrivateDependencyModuleNames: RigVMDeveloper, RigVMEditor, Slate, SlateCore, UAFAnimGraphUncookedOnly, UAFControlRig, UAFEditor, UAFUncookedOnly, UnrealEd, WorkspaceEditor
- PublicDependencyModuleNames: ControlRig, ControlRigDeveloper, Core, CoreUObject, Engine, RigVM, UAF, UAFAnimGraph

### `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRigEditor/Internal/ControlRigTraitCustomization.h` (Internal)


#### class `UE::UAF::Editor::FControlRigTraitSharedDataCustomization`  
`class FControlRigTraitSharedDataCustomization : public IPropertyTypeCustomization`  
_L25-60_
- inherits: `IPropertyTypeCustomization`
- L28 _public prototype_ `FControlRigTraitSharedDataCustomization() = default;`
- L29 _public prototype_ `virtual ~FControlRigTraitSharedDataCustomization();`
- L33 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L34 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L37 _private prototype_ `void OnVariableMappingChanged(const FName& PathName, const FName& Curve, bool bInput);` — --- IO Mapping ---
- L38 _private prototype_ `void OnPropertyExposeCheckboxChanged(ECheckBoxState NewState, FName PropertyName);`
- L40 _private prototype_ `static TSharedPtr<FStructOnScope> GetControlRigSharedData(const TSharedPtr<IPropertyHandle>& StructPropertyHandle);`
- L41 _private prototype_ `FControlRigAssetStrongReference GetTargetAssetReference() const;`
- L42 _private prototype_ `USkeleton* GetTargetSkeleton() const;`
- L44 _private prototype_ `static const FControlRigIOMapping::FControlsInfo* GetControlInfo(const TArray<FControlRigIOMapping::FControlsInfo>& Controls, const FName& ControlName);`
- L46 _private prototype_ `template<typename TSharedData> static bool IsVariableProperty(TSharedData* ControlRigTraitSharedData, const FName& PropertyName);`
- L48 _private prototype_ `void OnObjectsReinstanced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);`
- L50 _private prototype_ `FString FindControlRigTraitPinName(URigVMNode* ModelNode);`
- L52 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L53 _private member_ `TSharedPtr<FStructOnScope> ScopedControlRigTraitSharedData;`
- L55 _private member_ `TWeakObjectPtr<UEdGraphNode> SelectedNodeWeak = nullptr;`
- L56 _private member_ `TArray<FOptionalPinFromProperty> CustomPinProperties;`
- L57 _private member_ `TSharedPtr <FControlRigIOMapping> ControlRigIOMapping;`
- L59 _private member_ `FDelegateHandle OnObjectsReinstancedHandle;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Workspace` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UAF` (scope `UE`)
- L22 _namespace_ `namespace Editor` (scope `UE::UAF`)

### `Plugins/Experimental/UAF/UAFControlRig/Source/UAFControlRigEditor/Private/AnimNextControlRigEditorModule.h` (Private)


#### class `UE::UAF::ControlRig::Editor::FAnimNextControlRigEditorModule`  
`class FAnimNextControlRigEditorModule : public IModuleInterface`  
_L10-19_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `FDelegateHandle OnNodeDblClickDelegateHandle;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UAF` (scope `UE`)
- L7 _namespace_ `namespace ControlRig` (scope `UE::UAF`)
- L7 _namespace_ `namespace Editor` (scope `UE::UAF::ControlRig`)
