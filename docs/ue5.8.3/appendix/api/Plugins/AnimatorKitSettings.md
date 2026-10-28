# Plugins / AnimatorKitSettings

- module root: `Plugins/Animation/AnimatorKit/Source/AnimatorKitSettings`
- headers: 2; symbols: 12
- symbol kinds: class=2, delegate=1, macro=1, member=2, prototype=6
- PrivateDependencyModuleNames: ControlRigEditor, Core, CoreUObject, DeveloperSettings, Engine

### `Plugins/Animation/AnimatorKit/Source/AnimatorKitSettings/Public/AnimatorKitSettings.h` (Public)


#### class `UAnimatorKitSettings`  
`class UAnimatorKitSettings : public UDeveloperSettings`  
_L13-27_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, meta = (Experimental, DisplayName = "Animator Kit Settings"))`
- inherits: `UDeveloperSettings`
- L20 _public member_ `bool bEnableFocusMode = true;` — `UPROPERTY(config, EditAnywhere, Category = "Animation Settings|Focus", meta=(ConsoleVariable="AnimMode.PendingFocusMode"))`
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateSettings, const UAnimatorKitSettings*);`
- L23 _public member_ `static FOnUpdateSettings OnSettingsChange;`
- L25 _public prototype_ `virtual void PostInitProperties() override;`
- L26 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATORKITSETTINGS_API`
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateSettings, const UAnimatorKitSettings*);`

### `Plugins/Animation/AnimatorKit/Source/AnimatorKitSettings/Public/AnimatorKitSettingsModule.h` (Public)


#### class `FAnimatorKitSettingsModule`  
`class FAnimatorKitSettingsModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L12 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _private prototype_ `virtual void ShutdownModule() override;`
- L15 _private prototype_ `void UpdateSettings(const UAnimatorKitSettings* InSettings);`
