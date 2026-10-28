# Plugins / AnalyticsMulticastEditor

- module root: `Plugins/Runtime/Analytics/AnalyticsMulticast/Source/AnaltyicsMulticastEditor`
- headers: 2; symbols: 12
- symbol kinds: class=2, member=4, prototype=6
- DynamicallyLoadedModuleNames: AssetTools
- PrivateDependencyModuleNames: Analytics, AnalyticsVisualEditing, Core, CoreUObject, DeveloperSettings, EditorFramework, EditorWidgets, Engine, Projects, PropertyEditor, Slate, SlateCore, UnrealEd, WorkspaceMenuStructure

### `Plugins/Runtime/Analytics/AnalyticsMulticast/Source/AnaltyicsMulticastEditor/Classes/AnalyticsMulticastSettings.h` (Public)


#### class `UAnalyticsMulticastSettings`  
`class UAnalyticsMulticastSettings : public UAnalyticsSettingsBase`  
_L11-48_
- reflection: `UCLASS()`
- inherits: `UAnalyticsSettingsBase`
- L18 _private member_ `TArray<FString> ReleaseMulticastProviders;` — `UPROPERTY(EditAnywhere, DisplayName="Release Providers", Category=Multicast, meta=(ConfigRestartRequired=true))` — The list of analytics providers to forward analytics events to
- L22 _private member_ `TArray<FString> DebugMulticastProviders;` — `UPROPERTY(EditAnywhere, DisplayName="Debug Providers", Category=Multicast, meta=(ConfigRestartRequired=true))` — The list of analytics providers to forward analytics events to
- L26 _private member_ `TArray<FString> TestMulticastProviders;` — `UPROPERTY(EditAnywhere, DisplayName="Test Providers", Category=Multicast, meta=(ConfigRestartRequired=true))` — The list of analytics providers to forward analytics events to
- L30 _private member_ `TArray<FString> DevelopmentMulticastProviders;` — `UPROPERTY(EditAnywhere, DisplayName="Development Providers", Category=Multicast, meta=(ConfigRestartRequired=true))` — The list of analytics providers to forward analytics events to
- L37 _protected prototype_ `virtual void ReadConfigSettings();` — Provides a mechanism to read the section based information into this UObject's properties
- L41 _protected prototype_ `virtual void WriteConfigSettings();` — Provides a mechanism to save this object's properties to the section based ini values
- L45 _private prototype_ `void BuildArrayFromString(const FString& List, TArray<FString>& Array);` — Helper to populate an array with the results of the config read
- L47 _private prototype_ `FString BuildStringFromArray(TArray<FString>& Array);` — Helper to build the comma delimited string from the array

### `Plugins/Runtime/Analytics/AnalyticsMulticast/Source/AnaltyicsMulticastEditor/Public/AnalyticsMulticastEditor.h` (Public)


#### class `FAnalyticsMulticastEditorModule`  
`class FAnalyticsMulticastEditorModule : public IModuleInterface`  
_L8-14_
- inherits: `IModuleInterface`
- L12 _private prototype_ `virtual void StartupModule() override;`
- L13 _private prototype_ `virtual void ShutdownModule() override;`
