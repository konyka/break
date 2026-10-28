# Plugins / MSGamingSupportEditor

- module root: `Plugins/Runtime/Windows/MSGamingSupport/Source`
- headers: 2; symbols: 20
- symbol kinds: class=2, function=3, member=10, prototype=5
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, GDKPlatformEditor, Projects, Settings, Slate, SlateCore

### `Plugins/Runtime/Windows/MSGamingSupport/Source/MSGamingSupportEditor/Private/MSGamingSettings.h` (Private)


#### class `UMSGamingSettings`  
`class UMSGamingSettings : public UGDKTargetSettings`  
_L13-70_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, ConfigDoNotCheckDefaults)`
- inherits: `UGDKTargetSettings`
- desc: Implements the settings for the MS Gaming plugins
- L20 _public function_ `virtual const TCHAR* GetPlatformName() const override`
- L25 _public function_ `void virtual OverrideConfigSection(FString& InOutSectionName) override`
- L33 _public member_ `bool bAutoGeneratePackage = true;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging)` — Automatically generate an MSIXVC package during Win64 packaging
- L37 _public member_ `bool bAlwaysIncludeDX11Dependency = false;` — `UPROPERTY(EditAnywhere, Config, Category = Packaging, Meta=(DisplayName="Always Include DX11 Dependency"))` — Whether to always include DX11 dependency, regardless of the 'default rhi' setting. Use this if you plan to expose bUseD3D12InGame to users, or provide an alternative method of choosing an RHI
- L41 _public member_ `bool bAlwaysIncludeGameInputDependency = false;` — `UPROPERTY(EditAnywhere, Config, Category = Packaging, Meta=(DisplayName="Always Include GameInput Dependency"))` — Whether to automatically include GameInputRedist in the custom install actions
- L45 _public member_ `TArray<FGDKCustomInstallAction> CustomInstallActions;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging, Meta=(TitleProperty=Name))` — Custom installation actions. See the GDK documentation for details
- L49 _public member_ `FString CustomInstallStagingRoot;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging)` — Relative path in the package where the custom install actions are staged. Defaults to a folder under the root of the package
- L53 _public member_ `FString RequiredMinimumWindowsVersion;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging, AdvancedDisplay)` — Blocks the game from installing or launching on a Windows version older than this. Set to a four-part version number (e.g., 10.0.18362.0) or leave blank to use the GDK's default value.
- L57 _public member_ `FString SuggestedMinimumWindowsVersion;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging, AdvancedDisplay)` — The Windows version displayed as the Minimum Requirements on Microsoft store fronts. Set to a four-part version number (e.g., 10.0.18362.0) or leave blank to use the GDK's default value.
- L61 _public member_ `FString RecommendedWindowsVersion;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging, AdvancedDisplay)` — The Windows version displayed as the Recommended Requirements on Microsoft store fronts. Set to a four-part version number (e.g., 10.0.18362.0) or leave blank to use the GDK's default value.
- L65 _public member_ `bool bRestartRuntimeForPIE = true;` — `UPROPERTY(EditAnywhere, Config, Category=Features)` — Whether to restart the GDK runtime between Play-In-Editor runs
- L69 _public member_ `bool bLazyInitialize = true;` — `UPROPERTY(EditAnywhere, Config, Category=Features, Meta=(DisplayName="Lazy Runtime initialize"))` — Whether the GDK runtime will be initialized on startup or the first time is is needed. Note: Enabling the GDK OSS plugin will override this and force initialization on startup

### `Plugins/Runtime/Windows/MSGamingSupport/Source/MSGamingSupportEditor/Private/MSGamingSettingsDetails.h` (Private)


#### class `FMSGamingSettingsDetails`  
`class FMSGamingSettingsDetails : public FGDKTargetSettingsDetails`  
_L9-27_
- inherits: `FGDKTargetSettingsDetails`
- desc: Detail customization for MSGamingSettings panel
- L12 _public prototype_ `FMSGamingSettingsDetails();`
- L13 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L22 _private prototype_ `void HideMSGameStoreProperties(IDetailLayoutBuilder& DetailBuilder, TSharedRef<IPropertyHandle> PropertyHandle);`
- L24 _private prototype_ `void OnClickImportFromWinGDK( class UGDKTargetSettings* GDKTargetSettings, UGDKTargetSettings* WinGDKTargetSettings, const TSharedRef<class IPropertyUtilities> PropertyUtilities );`
- L25 _private prototype_ `virtual void AddAdditionalGettingStartedItems( TSharedPtr<class SHorizontalBox> GettingStartedBox, TWeakObjectPtr<class UGDKTargetSettings> GDKTargetSettings, const TSharedRef<class IPropertyUtilities> PropertyUtilities ) override;`
