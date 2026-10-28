# Runtime / AnalyticsVisualEditing

- module root: `Source/Runtime/Analytics/AnalyticsVisualEditing`
- headers: 2; symbols: 23
- symbol kinds: class=3, function=11, member=6, prototype=3
- PrivateDependencyModuleNames: Analytics, Core, CoreUObject, DeveloperSettings, Engine

### `Source/Runtime/Analytics/AnalyticsVisualEditing/Classes/AnalyticsSettings.h` (Public)


#### class `UAnalyticsSettingsBase`  
`class UAnalyticsSettingsBase : public UDeveloperSettings`  
_L15-83_
- reflection: `UCLASS(Abstract)`
- inherits: `UDeveloperSettings`
- L21 _private member_ `FText SettingsDisplayName;` — `UPROPERTY()`
- L24 _private member_ `FText SettingsTooltip;` — `UPROPERTY()`
- L27 _private function_ `inline FString GetReleaseIniSection() const` — Helpers so that subclasses don't need to hardcode the strings in case they change
- L28 _private function_ `inline FString GetDebugIniSection() const`
- L29 _private function_ `inline FString GetTestIniSection() const`
- L30 _private function_ `inline FString GetDevelopmentIniSection() const`
- L31 _private function_ `inline FString GetIniName() const`
- L39 _private function_ `virtual void PostInitProperties() override`
- L46 _private function_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override`
- L58 _private prototype_ `virtual FName GetCategoryName() const override;` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L65 _protected function_ `virtual void ReadConfigSettings()` — Provides a mechanism to read the section based information into this UObject's properties
- L69 _protected function_ `virtual void WriteConfigSettings()` — Provides a mechanism to save this object's properties to the section based ini values
- L73 _protected function_ `virtual FText GetSectionText() const` — Gets the section text for this
- L78 _protected function_ `virtual FText GetSectionDescription() const` — Gets the description for the section, uses the classes ToolTip by default.

#### class `UAnalyticsSettings`  
`class UAnalyticsSettings : public UAnalyticsSettingsBase`  
_L86-117_
- reflection: `UCLASS()`
- inherits: `UAnalyticsSettingsBase`
- L93 _private member_ `FString DevelopmentProviderName;` — `UPROPERTY(EditAnywhere, DisplayName="Development", Category=Providers, meta=(ConfigRestartRequired=true))` — The name of the plugin containing your desired analytics provider
- L97 _private member_ `FString DebugProviderName;` — `UPROPERTY(EditAnywhere, DisplayName="Debug", Category=Providers, meta=(ConfigRestartRequired=true))` — The name of the plugin containing your desired analytics provider
- L101 _private member_ `FString TestProviderName;` — `UPROPERTY(EditAnywhere, DisplayName="Test", Category=Providers, meta=(ConfigRestartRequired=true))` — The name of the plugin containing your desired analytics provider
- L105 _private member_ `FString ReleaseProviderName;` — `UPROPERTY(EditAnywhere, DisplayName="Release", Category=Providers, meta=(ConfigRestartRequired=true))` — The name of the plugin containing your desired analytics provider
- L112 _protected prototype_ `virtual void ReadConfigSettings();` — Provides a mechanism to read the section based information into this UObject's properties
- L116 _protected prototype_ `virtual void WriteConfigSettings();` — Provides a mechanism to save this object's properties to the section based ini values

### `Source/Runtime/Analytics/AnalyticsVisualEditing/Public/AnalyticsVisualEditing.h` (Public)


#### class `FAnalyticsVisualEditingModule`  
`class FAnalyticsVisualEditingModule : public IModuleInterface`  
_L13-16_
- inherits: `IModuleInterface`
- desc: This module holds the base UObject class that allows visual editing of configuration settings in the Unreal Editor. This is needed because the settings need to be usable outside of the UObject framework so these objects wrap those settings for editor display purposes and write the non-UObject config property information out
