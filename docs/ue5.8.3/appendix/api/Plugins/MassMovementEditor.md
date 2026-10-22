# Plugins / MassMovementEditor

- module root: `Plugins/Runtime/MassGameplay/Source/MassMovementEditor`
- headers: 4; symbols: 22
- symbol kinds: class=3, function=2, macro=1, member=5, namespace=3, prototype=8
- PrivateDependencyModuleNames: AppFramework, KismetWidgets, Projects, RenderCore, ToolMenus
- PublicDependencyModuleNames: AssetTools, Core, CoreUObject, DetailCustomizations, EditorFramework, Engine, InputCore, MassCommon, MassCore, MassEntity, MassMovement, PropertyEditor, RHI, Slate, SlateCore, UnrealEd

### `Plugins/Runtime/MassGameplay/Source/MassMovementEditor/Public/IMassMovementEditor.h` (Public)


#### class `IMassMovementEditor`  
`class IMassMovementEditor : public FAssetEditorToolkit`  
_L9-13_
- inherits: `FAssetEditorToolkit`
- desc: MassMovement Editor public interface

### `Plugins/Runtime/MassGameplay/Source/MassMovementEditor/Public/MassMovementEditorModule.h` (Public)


#### class `FMassMovementEditorModule`  
`class FMassMovementEditorModule : public IModuleInterface`  
_L19-25_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public prototype_ `virtual void StartupModule() override;`
- L24 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/MassGameplay/Source/MassMovementEditor/Public/MassMovementPropertyUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "MassMovementEditor"`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MassMovement` (scope `UE`)
- L13 _namespace_ `namespace PropertyUtils` (scope `UE::MassMovement`)
- L18 _function_ `template<typename T> TOptional<T> GetValue(const TSharedPtr<IPropertyHandle>& ValueProperty)` (scope `UE::MassMovement::PropertyUtils`) — Expects T is struct.
- L63 _function_ `template<typename T> void SetValue(TSharedPtr<IPropertyHandle>& ValueProperty, T NewValue, EPropertyValueSetFlags::Type Flags = 0)` (scope `UE::MassMovement::PropertyUtils`) — Expects T is struct.

### `Plugins/Runtime/MassGameplay/Source/MassMovementEditor/Public/MassMovementStyleRefDetails.h` (Public)


#### class `FMassMovementStyleRefDetails`  
`class FMassMovementStyleRefDetails : public IPropertyTypeCustomization`  
_L17-39_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FMassMovementStyleRef.
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L25 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L29 _private prototype_ `void OnProfileComboChange(int32 Idx);`
- L30 _private prototype_ `TSharedRef<SWidget> OnGetProfileContent() const;`
- L31 _private prototype_ `FText GetCurrentProfileDesc() const;`
- L33 _private member_ `TSharedPtr<IPropertyHandle> NameProperty;`
- L34 _private member_ `TSharedPtr<IPropertyHandle> IDProperty;`
- L35 _private member_ `TSharedPtr<IPropertyHandle> LanesProperty;`
- L37 _private member_ `class IPropertyUtilities* PropUtils = nullptr;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
