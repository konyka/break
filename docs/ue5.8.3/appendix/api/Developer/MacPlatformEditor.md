# Developer / MacPlatformEditor

- module root: `Source/Developer/Mac/MacPlatformEditor`
- headers: 2; symbols: 26
- symbol kinds: class=2, member=10, prototype=14
- DynamicallyLoadedModuleNames: GameProjectGeneration
- PrivateDependencyModuleNames: AudioSettingsEditor, Core, CoreUObject, DesktopPlatform, Engine, InputCore, MacTargetPlatformControls, MacTargetPlatformSettings, MainFrame, MaterialShaderQualitySettings, PropertyEditor, RHI, RenderCore, SettingsEditor, ShaderPlatformConfigEditor, SharedSettingsWidgets, Slate, SlateCore, SourceControl, TargetPlatform, UnrealEd
- PrivateIncludePathModuleNames: GameProjectGeneration, Settings

### `Source/Developer/Mac/MacPlatformEditor/Private/MacTargetSettingsCustomization.h` (Private)


#### class `FMacTargetSettingsCustomization`  
`class FMacTargetSettingsCustomization : public IDetailCustomization`  
_L18-61_
- inherits: `IDetailCustomization`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L29 _private prototype_ `bool HandlePreExternalIconCopy(const FString& InChosenImage);` — Delegate handler for before an icon is copied
- L32 _private prototype_ `FString GetPickerPath();` — Delegate handler to get the path to start picking from
- L35 _private prototype_ `bool HandlePostExternalIconCopy(const FString& InChosenImage);` — Delegate handler to set the path to start picking from
- L38 _private prototype_ `TSharedRef<SWidget> OnGetShaderVersionContent();` — Delegate handler to get the list of shader standards
- L41 _private prototype_ `FText GetShaderVersionDesc() const;` — Delegate handler to get the description of the shader standard
- L44 _private prototype_ `void SetShaderStandard(int32 Value);` — Delegate handler to set the new max. shader standard
- L47 _private prototype_ `void UpdateShaderStandardWarning();` — Delegate to update the shader standard warning
- L51 _private member_ `TSharedPtr<FShaderFormatsPropertyDetails> TargetShaderFormatsDetails;` — Reference to the target shader formats property view
- L54 _private member_ `TSharedPtr<IPropertyHandle> ShaderVersionPropertyHandle;` — Reference to the shader version property
- L57 _private member_ `TSharedPtr< SErrorText > ShaderVersionWarningTextBox;` — Reference to the shader version property warning text box.
- L60 _private member_ `FAudioPluginWidgetManager AudioPluginWidgetManager;` — Widget for platform specific audio plugins.

### `Source/Developer/Mac/MacPlatformEditor/Public/XcodeProjectSettingsDetailsCustomization.h` (Public)


#### class `FXcodeProjectSettingsDetailsCustomization`  
`class FXcodeProjectSettingsDetailsCustomization : public IDetailCustomization`  
_L16-38_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L26 _public prototype_ `FReply OnRestorePlistClicked();`
- L27 _public prototype_ `FReply OnRestoreEntitlementClicked();`
- L29 _public member_ `TSharedPtr<IPropertyHandle> TemplateMacPlist;`
- L30 _public member_ `TSharedPtr<IPropertyHandle> TemplateIOSPlist;`
- L31 _public member_ `TSharedPtr<IPropertyHandle> PremadeMacEntitlements;`
- L32 _public member_ `TSharedPtr<IPropertyHandle> ShippingMacEntitlements;`
- L33 _public member_ `TSharedPtr<IPropertyHandle> PremadeIOSEntitlements;`
- L34 _public member_ `TSharedPtr<IPropertyHandle> ShippingIOSEntitlements;`
- L37 _private prototype_ `static void RestoreDefault(const FStringView& SubFolder, const TCHAR* Filename, TSharedPtr<IPropertyHandle> Property);`
