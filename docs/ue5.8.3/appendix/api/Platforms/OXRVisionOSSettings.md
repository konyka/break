# Platforms / OXRVisionOSSettings

- module root: `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOSSettings`
- headers: 3; symbols: 10
- symbol kinds: class=2, macro=1, member=4, prototype=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PrivateIncludePathModuleNames: Settings
- PublicDependencyModuleNames: DeveloperSettings

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOSSettings/Private/OXRVisionOSSettingsModule.h` (Private)


#### class `IOXRVisionOSSettingsModule`  
`class IOXRVisionOSSettingsModule : public IModuleInterface`  
_L13-16_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L8 _macro_ `#define OXRVISIONOS_SETTINGS_MODULE_NAME "OXRVisionOSSettings"`

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOSSettings/Public/OXRVisionOSRuntimeSettings.h` (Public)


#### class `UOXRVisionOSRuntimeSettings`  
`class UOXRVisionOSRuntimeSettings : public UDeveloperSettings`  
_L12-40_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UDeveloperSettings`
- L18 _public prototype_ `virtual FName GetCategoryName() const;`
- L20 _public prototype_ `virtual FText GetSectionText() const override;`
- L21 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L27 _public member_ `FRotator OXRVisionOSAimPoseAdjustment = FRotator(0.0f, 0.0f, 0.0f);` — `UPROPERTY(config, EditAnywhere, Category="OpenXR visionOS", Meta = (DisplayName = "Aim Pose Adjustment"))` — Defines a rotation adjustment to the aim pose from the OpenXR visionOS native controller orientation.  This pose may be fine without adjustment.
- L31 _public member_ `FRotator OXRVisionOSGripPoseAdjustment = FRotator(45.0f,0.0f,0.0f);` — `UPROPERTY(config, EditAnywhere, Category = "OpenXR visionOS", Meta = (DisplayName = "Grip Pose Adjustment"))` — Defines a rotation adjustment to the grip pose from the OpenXR visionOS native controller orientation.  We provide a default adjustment to grip.
- L35 _public member_ `FRotator OXRVisionOSGripSurfacePoseAdjustment = FRotator(0.0f, 0.0f, 0.0f);` — `UPROPERTY(config, EditAnywhere, Category = "OpenXR visionOS", Meta = (DisplayName = "Grip Surface Pose Adjustment"))` — Defines a rotation adjustment to the grip surface pose from the OpenXR visionOS native controller orientation.  We provide a default adjustment to grip surface.
- L39 _public member_ `int32 OXRVisionOSNumUILayers = 0;` — `UPROPERTY(config, EditAnywhere, Category = "OpenXR visionOS", Meta = (DeprecatedProperty, ClampMin = "0", ClampMax = "4", DisplayName = "Max Number UI Layers"))` — Number of UI2D/quad layers supported by OpenXR visionOS, required at app startup time

### `Platforms/VisionOS/Plugins/Runtime/OpenXRVisionOS/Source/OXRVisionOSSettings/Public/OXRVisionOSSettingsTypes.h` (Public)
_(no declarations extracted)_
