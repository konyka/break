# Developer / AudioSettingsEditor

- module root: `Source/Developer/AudioSettingsEditor`
- headers: 1; symbols: 21
- symbol kinds: class=1, macro=1, member=12, prototype=7
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicIncludePathModuleNames: Engine

### `Source/Developer/AudioSettingsEditor/Public/TargetPlatformAudioCustomization.h` (Public)


#### class `FAudioPluginWidgetManager`  
`class FAudioPluginWidgetManager`  
_L13-49_
- L16 _public prototype_ `FAudioPluginWidgetManager();`
- L17 _public prototype_ `~FAudioPluginWidgetManager();`
- L20 _public prototype_ `void BuildAudioCategory(IDetailLayoutBuilder& DetailLayout, const FString& PlatformName, const UStruct* ClassOuterMost = nullptr);` — Builds out the audio category for a specific audio section for a platform settings page.
- L23 _public prototype_ `TSharedRef<SWidget> MakeAudioPluginSelectorWidget(const TSharedPtr<IPropertyHandle>& PropertyHandle, EAudioPlugin AudioPluginType, const FString& PlatformName);` — Creates widget from a scan of loaded audio plugins for an individual plugin type.
- L27 _private prototype_ `static void OnPluginSelected(FString PluginName, TSharedPtr<IPropertyHandle> PropertyHandle);` — Handles when a new plugin is selected.
- L29 _private prototype_ `void OnPluginTextCommitted(const FText& InText, ETextCommit::Type CommitType, EAudioPlugin AudioPluginType, TSharedPtr<IPropertyHandle> PropertyHandle);`
- L31 _private prototype_ `FText OnGetPluginText(EAudioPlugin AudioPluginType);`
- L35 _private member_ `TSharedPtr<FText> SelectedReverb;` — Cached references to text for Spatialization, Reverb and Occlusion settings
- L36 _private member_ `TSharedPtr<FText> SelectedSpatialization;`
- L37 _private member_ `TSharedPtr<FText> SelectedOcclusion;`
- L38 _private member_ `TSharedPtr<FText> SelectedSourceDataOverride;`
- L40 _private member_ `TSharedPtr<FText> ManualSpatializationEntry;`
- L41 _private member_ `TSharedPtr<FText> ManualReverbEntry;`
- L42 _private member_ `TSharedPtr<FText> ManualOcclusionEntry;`
- L43 _private member_ `TSharedPtr<FText> ManualSourceDataOverrideEntry;`
- L45 _private member_ `TArray<TSharedPtr<FText>> SpatializationPlugins;`
- L46 _private member_ `TArray<TSharedPtr<FText>> SourceDataOverridePlugins;`
- L47 _private member_ `TArray<TSharedPtr<FText>> ReverbPlugins;`
- L48 _private member_ `TArray<TSharedPtr<FText>> OcclusionPlugins;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOSETTINGSEDITOR_API`
