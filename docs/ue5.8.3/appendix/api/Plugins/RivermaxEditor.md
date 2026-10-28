# Plugins / RivermaxEditor

- module root: `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxEditor`
- headers: 4; symbols: 26
- symbol kinds: class=3, delegate=1, function=1, member=7, namespace=3, prototype=11
- PrivateDependencyModuleNames: CoreUObject, EditorStyle, InputCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, PropertyEditor, RivermaxCore

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxEditor/Private/Customizations/RivermaxSettingsDetailsCustomization.h` (Private)


#### class `FRivermaxSettingsDetailsCustomization`  
`class FRivermaxSettingsDetailsCustomization : public IDetailCustomization`  
_L10-19_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxEditor/Private/RivermaxEditorModule.h` (Private)


#### class `FRivermaxEditorModule`  
`class FRivermaxEditorModule : public IModuleInterface`  
_L10-20_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private member_ `TArray<FName> CustomizedClasses;`

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxEditor/Private/Widgets/SRivermaxInterfaceComboBox.h` (Private)


#### class `SRivermaxInterfaceComboBox`  
`class SRivermaxInterfaceComboBox : public SCompoundWidget`  
_L17-62_
- inherits: `SCompoundWidget`
- desc: Widget used to pick IP address of Rivermax / Mellanox device
- L21 _public function_ `DECLARE_DELEGATE_OneParam(FOnChooseIP, FString) SLATE_BEGIN_ARGS(SRivermaxInterfaceComboBox)`
- L25 _public prototype_ `SLATE_ARGUMENT(FString, InitialValue) SLATE_EVENT(FOnChooseIP, OnIPAddressSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `void OnIpAddressSelected(TSharedPtr<FString> InAddress, ESelectInfo::Type InType);` — Handles changes in the local adapter address combo box
- L37 _private prototype_ `void OnIPAddressTextCommmited(const FText&, ETextCommit::Type);` — Called when the IP Address was commited in the editable text block
- L40 _private prototype_ `TSharedRef<SWidget> GenerateRivermaxAdaptersComboBoxEntry(TSharedPtr<FString> InAddress);` — Generates an entry in the local adapter address combo box
- L43 _private prototype_ `void UpdateIPWarning();` — Updates image showing warning if IP is invalid
- L47 _private member_ `TArray<TSharedPtr<FString>> RivermaxAdapterAddressSource;`
- L49 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> RivermaxAdapterAddressComboBox;`
- L52 _private member_ `TSharedPtr<SEditableText> IPAddressEditableTextBlock;` — Text box shown on top of the local adapter address address combo box
- L55 _private member_ `TSharedPtr<SImage> IPAddressWarningImage;` — Warning images displayed when IP is not valid or no device matches resolved IP
- L58 _private member_ `TSharedPtr<SHorizontalBox> HorizontalBoxContainer;` — Horizontal box containing combo button, text and image
- L61 _private member_ `FOnChooseIP OnIPAddressSelectedDelegate;` — Delegate executed when a local IP address was selected

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnChooseIP, FString) SLATE_BEGIN_ARGS(SRivermaxInterfaceComboBox) {} SLATE_ARGUMENT(FString, InitialValue) SLATE_EVENT(FOnChooseIP, OnIPAddressSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/Rivermax/RivermaxCore/Source/RivermaxEditor/Public/Customizations/RivermaxDeviceSelectionCustomization.h` (Public)


#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace RivermaxCore` (scope `UE`)
- L12 _namespace_ `namespace Utils` (scope `UE::RivermaxCore`)
- L14 _prototype_ `void SetupDeviceSelectionCustomization(int32 InObjectIndex, const FString& InitialValue, TSharedPtr<IPropertyHandle> PropertyHandle, IDetailLayoutBuilder& DetailBuilder);` (scope `UE::RivermaxCore::Utils`)
- L15 _prototype_ `void AddInterfaceAddressRow(IDetailChildrenBuilder& ChildBuilder, TSharedRef<IPropertyHandle> InterfaceHandle, const FString& InitialValue, IPropertyTypeCustomizationUtils& CustomizationUtils);` (scope `UE::RivermaxCore::Utils`)
