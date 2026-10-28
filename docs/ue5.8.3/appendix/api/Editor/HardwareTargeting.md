# Editor / HardwareTargeting

- module root: `Source/Editor/HardwareTargeting`
- headers: 2; symbols: 32
- symbol kinds: class=2, delegate=3, enum=2, enumerator=6, function=1, macro=1, member=8, prototype=8, struct=1
- PrivateDependencyModuleNames: CoreUObject, EditorFramework, EditorWidgets, Engine, EngineSettings, InputCore, Settings, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Source/Editor/HardwareTargeting/Public/HardwareTargetingModule.h` (Public)


#### struct `FModifiedDefaultConfig`  
`struct FModifiedDefaultConfig`  
_L24-34_
- desc: Struct specifying pending changes to a settings object
- L27 _public member_ `TWeakObjectPtr<UObject> SettingsObject;` — The settings object to which the description relates
- L30 _public member_ `FText CategoryHeading;` — Heading describing the name of the category
- L33 _public member_ `FText Description;` — Text describing the pending changes to the settings

#### class `IHardwareTargetingModule`  
`class IHardwareTargetingModule : public IModuleInterface`  
_L36-54_
- inherits: `IModuleInterface`
- L41 _public prototype_ `static IHardwareTargetingModule& Get();` — Singleton access to this module
- L44 _public prototype_ `virtual void ApplyHardwareTargetingSettings() = 0;` — Apply the current hardware targeting settings if they have changed
- L47 _public prototype_ `virtual TArray<FModifiedDefaultConfig> GetPendingSettingsChanges() = 0;` — Gets a list of objects that are required to be writable in order to apply the settings
- L50 _public prototype_ `virtual TSharedRef<SWidget> MakeHardwareClassTargetCombo(FOnHardwareClassChanged OnChanged, TAttribute<EHardwareClass> SelectedEnum) = 0;` — Make a new combo box for choosing a hardware class target
- L53 _public prototype_ `virtual TSharedRef<SWidget> MakeGraphicsPresetTargetCombo(FOnGraphicsPresetChanged OnChanged, TAttribute<EGraphicsPreset> SelectedEnum) = 0;` — Make a new combo box for choosing a graphics preference

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnHardwareClassChanged, EHardwareClass) DECLARE_DELEGATE_OneParam(FOnGraphicsPresetChanged, EGraphicsPreset) struct FModifiedDefaultConfig { TWeakObjectPtr<UObject> SettingsObject; FText CategoryHeading; FText Description; };`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGraphicsPresetChanged, EGraphicsPreset) struct FModifiedDefaultConfig { TWeakObjectPtr<UObject> SettingsObject; FText CategoryHeading; FText Description; };`

### `Source/Editor/HardwareTargeting/Public/HardwareTargetingSettings.h` (Public)


#### enum `EHardwareClass`  
`enum class EHardwareClass : uint8`  
_L18-28_
- reflection: `UENUM()`
- desc: Enum specifying a class of hardware
- L21 _public enumerator_ `Unspecified UMETA(Hidden)` — Unspecified, meaning no choice has been made yet
- L24 _public enumerator_ `Desktop` — Desktop or console
- L27 _public enumerator_ `Mobile` — Mobile or tablet

#### enum `EGraphicsPreset`  
`enum class EGraphicsPreset : uint8`  
_L32-42_
- reflection: `UENUM()`
- desc: Enum specifying a graphics preset preference
- L35 _public enumerator_ `Unspecified UMETA(Hidden)` — Unspecified, meaning no choice has been made yet
- L38 _public enumerator_ `Maximum` — Maximum quality - High-end features default to enabled
- L41 _public enumerator_ `Scalable` — Scalable quality - Some features are disabled by default but can be enabled based on the actual hardware

#### class `UHardwareTargetingSettings`  
`class UHardwareTargetingSettings : public UObject`  
_L46-83_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Hardware targeting settings, stored in default config, per-project
- L52 _private member_ `EHardwareClass TargetedHardwareClass;` — `UPROPERTY(config, EditAnywhere, category=None)` — Enum specifying which class of hardware this game is targeting
- L56 _private member_ `EHardwareClass AppliedTargetedHardwareClass;` — `UPROPERTY(config)` — Enum that is set to TargetedHardwareClass when the settings have been successfully applied
- L60 _private member_ `EGraphicsPreset DefaultGraphicsPerformance;` — `UPROPERTY(config, EditAnywhere, category=None)` — Enum specifying a graphics preset to use for this game
- L64 _private member_ `EGraphicsPreset AppliedDefaultGraphicsPerformance;` — `UPROPERTY(config)` — Enum that is set to DefaultGraphicsPerformance when the settings have been successfully applied
- L67 _private prototype_ `bool HasPendingChanges() const;` — Check if these settings have any pending changes that require action
- L72 _public prototype_ `DECLARE_EVENT(UHardwareTargetingSettings, FSettingChangedEvent);` — Returns an event delegate that is executed when a setting has changed.
- L73 _public function_ `FSettingChangedEvent& OnSettingChanged( )`
- L77 _protected prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent ) override;` — Called when a property on this object is changed
- L81 _private member_ `FSettingChangedEvent SettingChangedEvent;` — Holds an event delegate that is executed when a setting has changed.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API HARDWARETARGETING_API`
- L72 _delegate_ `DECLARE_EVENT(UHardwareTargetingSettings, FSettingChangedEvent);` — Returns an event delegate that is executed when a setting has changed.
