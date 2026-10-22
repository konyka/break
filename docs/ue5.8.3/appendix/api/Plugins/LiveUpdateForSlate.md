# Plugins / LiveUpdateForSlate

- module root: `Plugins/Editor/LiveUpdateForSlate/Source/LiveUpdateForSlate`
- headers: 2; symbols: 7
- symbol kinds: class=2, member=2, prototype=3
- PrivateDependencyModuleNames: CoreUObject, Engine, LiveCoding, MainFrame, Settings, SettingsEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Editor/LiveUpdateForSlate/Source/LiveUpdateForSlate/Public/LiveUpdateForSlate.h` (Public)


#### class `FLiveUpdateForSlateModule`  
`class FLiveUpdateForSlateModule : public IModuleInterface`  
_L8-20_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void OnPatchComplete();`
- L19 _private member_ `FDelegateHandle OnPatchCompleteHandle;`

### `Plugins/Editor/LiveUpdateForSlate/Source/LiveUpdateForSlate/Public/LiveUpdateSlateSettings.h` (Public)


#### class `ULiveUpdateSlateSettings`  
`class ULiveUpdateSlateSettings : public UObject`  
_L9-16_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L15 _public member_ `bool bEnableLiveUpdateForSlate = true;` — `UPROPERTY(Config, EditAnywhere, Category=Slate, meta=(ToolTip="Refreshes the editor's Slate layout when Live Coding patches are complete."))`
